#!/usr/bin/env zsh

# build.zsh
# ‾‾‾‾‾‾‾‾‾

# don't try and source this file - it should only be executed directly
if [[ "$ZSH_EVAL_CONTEXT" != 'toplevel' ]] return 1

function -- () {

  # ————————————————————————————————————————————————————————————————————————— #
  # —— Process CLI Args ————————————————————————————————————————————————————— #

  # dev mode is supposed to be halfway between the debug and production modes
  local mode=dev
  local -i 2 print_cmd=0 do_time=0 do_dump=0 run_cmd=1 do_clear=1

  while [[ -n "$1" ]] { #
    case "$1" {
      ( --(print-|)cmd   ) print_cmd=1 ;;
      ( --debug(ging|)   ) mode=debug  ;;
      ( --prod(uction|)  ) mode=prod   ;;
      ( --dev(elopment|) ) mode=dev    ;;
      ( --no-clear       ) do_clear=0  ;;
      ( --no-run         ) run_cmd=0   ;;
      ( --time           ) do_time=1   ;;
      ( --dump           ) do_dump=1   ;;
      ( -- ) shift ;&
      ( *  ) break ;;
    }
    shift
  }

  # ————————————————————————————————————————————————————————————————————————— #
  # —— Compilation Options —————————————————————————————————————————————————— #

  # equivalent to running `dirname` on this file's path (w/o resolving links)
  local -r _proj_root="${${(%):-%x}:a:h}"
  local -r _source="$_proj_root/source"

  local -r _alloc_debugger="$_source/utils/malloc/malloc.py"

  local -r _log_file="$_proj_root/logs/allocations.log"
  local -r _log_pipe="$_proj_root/logs/allocations.fifo"

  local -r CC='clang'
  local -a CFLAGS=( )

  # —— Definitions/Undefinitions ——————————————————————— #

  local -a DEFINITIONS=(
    TTYCOLUMNS="$COLUMNS"
    LOG_FILE="\"$_log_file\""
    LOG_PIPE="\"$_log_pipe\""
  )

  local -a UNDEFINE=( )

  # —— Enable & Disable Warnings ——————————————————————— #

  # all `-W...` warnings to enable
  local -a WARNINGS=(
    all      # warn about basic/near-essential code quality & safety issues
    extra    # warn about deeper code issues, which aren't always necessary
    pedantic # warn about the most minute issues like standard compliance, etc.
    vla      # don't allow the use of variable-length arrays
  )

  # all `-W-no-...` warnings to disable
  local -ra NO_WARN=(
    # stops warnings about using `sprintf` instead of the preferred `snprintf`
    deprecated-declarations
    # stops a warning about using a macro that passes 0 inputs to __VA_ARGS__
    #  however, this is needed for the `OPTION_IS()` macro in `options.c`
    variadic-macro-arguments-omitted
  )

  # —— Libraries & Inclusions —————————————————————————— #

  local -ra LIBPATHS=( ) LDLIBS=( )
  local -ra INCLUDES=( "$_source/"{{utils,debugging}{/**,},} )

  local -ra FRAMEWORKS=( CoreFoundation )

  # —— Sanitisation ———————————————————————————————————— #

  local -a SANITISE=(
    address   # throw an error when any memory inconsistencies occur
    undefined # raise a warning during undefined behaviour (eg `bool x = 2;`)
  )

  local -a ASAN_OPTS=(
    print_legend=0
    stack_trace_format=$'"  %n\t%f   \t%S"'
  )

  # —— Source Files ———————————————————————————————————— #

  # an array of all the program's source files
  local -ra SOURCE_FILES=( "$_source/"**/*.c )

  # —— Execution Options ——————————————————————————————— #

  # location of the outputted binary
  local -r TARGET="$_proj_root/out/lk"
  # where the binary should be copied to
  local -r COPY_TO="$HOME/bin/lk"

  # the command that should be run after compilation
  local -a CMD=( "$TARGET" )

  # ————————————————————————————————————————————————————————————————————————— #
  # —— Option Processing ———————————————————————————————————————————————————— #

  local optimisation

  case "$mode" {
    ( debug ) optimisation=0; CFLAGS+=( g ) ;;
    ( dev   ) optimisation=1 ;;
    ( prod  ) optimisation=3 ;;
  }

  CFLAGS+=( O$optimisation )

  # —— $CMD ———————————————————————————————————————————— #

  if (( do_clear )) CMD+=( --clear )
  CMD+=( "$@" )

  if (( do_time )) CMD=( zsh -c "time ${(@q)CMD}" )

  # —— $WARNINGS ——————————————————————————————————————— #

  if (( $#NO_WARN )) WARNINGS+=( "no-${(@)^NO_WARN}" )

  # —— $DEFINITIONS ———————————————————————————————————— #

  if (( do_dump )) DEFINITIONS+=( DUMP );

  # note: `NDEBUG` disables the `assert` macro
  if [[ "$mode" == 'debug' ]] {
    UNDEFINE+=( NDEBUG ); DEFINITIONS+=( DEBUG_MODE );

  } elif [[ "$mode" == 'prod' ]] {
    DEFINITIONS+=( NDEBUG ); UNDEFINE+=( DEBUG_MODE )
  }

  # —— $SANITISE ——————————————————————————————————————— #

  if [[ "$mode" == 'prod'  ]] SANITISE=()

  local -r ASAN="${(j.:.)ASAN_OPTS}"

  # ————————————————————————————————————————————————————————————————————————— #
  # —— Collate Build Arguments —————————————————————————————————————————————— #

  # pack the build args into an array, adding each of their relevant prefixes,
  #  and making sure not to add any empty arrays
  local -a BUILD_ARGS

  if (( $#CFLAGS      )) BUILD_ARGS+=(  "-${(@)^CFLAGS}"      )
  if (( $#DEFINITIONS )) BUILD_ARGS+=( "-D${(@)^DEFINITIONS}" )
  if (( $#UNDEFINE    )) BUILD_ARGS+=( "-U${(@)^UNDEFINE}"    )
  if (( $#WARNINGS    )) BUILD_ARGS+=( "-W${(@)^WARNINGS}"    )
  if (( $#INCLUDES    )) BUILD_ARGS+=( "-I${(@)^INCLUDES}"    )
  if (( $#LIBPATHS    )) BUILD_ARGS+=( "-L${(@)^LIBPATHS}"    )
  if (( $#LDLIBS      )) BUILD_ARGS+=( "-l${(@)^LDLIBS}"      )
  if (( $#FRAMEWORKS  )) BUILD_ARGS+=( "-framework ${(@)^FRAMEWORKS}" )
  if (( $#SANITISE    )) BUILD_ARGS+=( "-fsanitize=${(j:,:)SANITISE}" )

  # always add the target file
  BUILD_ARGS+=( --output "$TARGET" )

  # ————————————————————————————————————————————————————————————————————————— #
  # —— Print Command ———————————————————————————————————————————————————————— #

  if (( print_cmd )) {
    bat -pp -lzsh <<< "${"${:-"$CC $BUILD_ARGS source/**/*.c \\
      && $CMD \\
      && cp $TARGET ~cs/bin/${TARGET##*/}"}"//$_proj_root\//./}"
  }

  # —— Compilation —————————————————————————————————————————————————————————— #

  # source files are added here so they don't mess up the `print_cmd` output
  BUILD_ARGS=( "${(@z)BUILD_ARGS}" -- "${(@)SOURCE_FILES}" )

  echo -n 'compiling...' >&2

  # pass that array of arguments to the compiler
  "$CC" "${(@)BUILD_ARGS}" # compile the program
  local -i 10 retcode=$?

  echo $'\r\e[K' >&2

  if   (( retcode )) return retcode # failed to compile `$CC`
  if ! (( run_cmd )) return 0       # we don't want to run the command

  # —— Run Program ————————————————————————————————————— #

  if [[ "$mode" == 'debug' ]] {
    "$_alloc_debugger" "$_log_pipe" &
    local -ri 10 debugger_pid=$!
  }

  { # then, if successful, execute the program
    #  run the newly compiled binary (with sanitisation options set)
    ASAN_OPTIONS="$ASAN" "${(@)CMD}"
    retcode=$? # get the return code of `CMD`

  } always { # no matter what happens, make sure to kill the debugger
    if [[ "$mode" == 'debug' ]] {
      if (( retcode == 0 )) { =kill -s SIGINFO $debugger_pid; } \
      else                  { =kill -s SIGTERM $debugger_pid; }
    }
  }

  # —— Cleanup & Copying ——————————————————————————————— #

  if (( retcode )) return retcode # the function failed

  # if everything compiled, and the function ran without errors,
  #  then copy the binary into `$CS/bin`
  if [[ "$mode" != 'debug' ]] cp "$TARGET" "$CS/bin/${TARGET##*/}"

  # —— Return ——————————————————————————————————————————————————————————————— #

  return retcode

} "$@"

# ——————————————————————————————————————————————————————————————————————————— #
# ——————————————————————————————————————————————————————————————————————————— #

# spell:ignoreRegExp /(?<!-)[-_]\w+|\w+(?=\|)|asan/gi
