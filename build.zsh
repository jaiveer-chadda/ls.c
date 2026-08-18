#!/usr/bin/env zsh

# build.zsh
# ‾‾‾‾‾‾‾‾‾

if [[ "$ZSH_EVAL_CONTEXT" != 'toplevel' ]] return 1

# ——————————————————————————————————————————————————————————————————————————— #

function -- () {

  # equivalent to running `dirname` on this file's path (w/o resolving links)
  local -r _proj_root="${${(%):-%x}:a:h}"
  local -r CC='clang'

  # ————————————————————————————————————————————————————————————————————————— #

  # dev mode is supposed to be halfway between the debug and production modes
  local mode=dev
  local -i 2 print_cmd=0 do_time=0

  while [[ -n "$1" ]] { #
    case "$1" {
      ( --(print-|)cmd   ) print_cmd=1 ;;
      ( --debug(ging|)   ) mode=debug  ;;
      ( --prod(uction|)  ) mode=prod   ;;
      ( --dev(elopment|) ) mode=dev    ;;
      ( --time           ) do_time=1   ;;
      ( -- ) shift ;&
      ( *  ) break ;;
    }
    shift
  }

  # ————————————————————————————————————————————————————————————————————————— #

  local -a DEFINITIONS
  if [[ "$mode" == debug ]] DEFINITIONS+=( DEBUG_MODE )

  # ————————————————————————————————————————————————————————————————————————— #

  local -a CFLAGS
  local optimisation

  case "$mode" {
    ( debug ) optimisation=0; CFLAGS+=( g ) ;;
    ( dev   ) optimisation=1 ;;
    ( prod  ) optimisation=3 ;;
  }

  local -ra CFLAGS=( O$optimisation )

  # ———————————————————————————————————————————————————— #

  # all `-W...` warnings to enable
  local -a WARNINGS=( all extra pedantic )

  # all `-W-no-...` warnings to disable
  local -ra NO_WARN=(
    # stops warnings about using `sprintf` instead of the preferred `snprintf`
    deprecated-declarations
    # stops a warning about using a macro that passes 0 inputs to __VA_ARGS__
    #  however, this is needed for the `OPTION_IS()` macro in `options.c`
    variadic-macro-arguments-omitted
  )

  WARNINGS+=( "no-${(@)^NO_WARN}" )

  # ————————————————————————————————————————————————————————————————————————— #

  # location of the outputted binary
  local -r TARGET="$_proj_root/out/lk"
  # where the binary should be copied to
  local -r COPY_TO="$HOME/bin/lk"

  # the command that should be run after compilation
  local -a CMD=( "$TARGET" --clear "$@" )
  if (( do_time )) CMD=( zsh -c "time ${(@q)CMD}" )

  # ———————————————————————————————————————————————————— #

  # an array of all the program's source files
  local -ra SOURCE_FILES=( "$_proj_root/source/"**/*.c )

  # ———————————————————————————————————————————————————— #

  # find where the `libmagic` library is stored, to be passed to the linker
  local -r _lmagic_prefix="$( brew --prefix libmagic )"
  local -ra LIBPATHS=( "$_lmagic_prefix/lib" )
  local -ra INCLUDES=( "$_lmagic_prefix/include" "$_proj_root/source" )
  local -ra   LDLIBS=( magic )

  local -ra FRAMEWORKS=( CoreFoundation )

  local -a SANITISE=( address undefined )
  if [[ "$mode" == prod ]] SANITISE=()

  # ————————————————————————————————————————————————————————————————————————— #

  # pack the build args into an array, adding each of their relevant prefixes,
  #  and making sure not to add any empty arrays
  local -a BUILD_ARGS

  if (( $#CFLAGS      )) BUILD_ARGS+=(  "-${(@)^CFLAGS}"      )
  if (( $#WARNINGS    )) BUILD_ARGS+=( "-W${(@)^WARNINGS}"    )
  if (( $#DEFINITIONS )) BUILD_ARGS+=( "-D${(@)^DEFINITIONS}" )
  if (( $#INCLUDES    )) BUILD_ARGS+=( "-I${(@)^INCLUDES}"    )
  if (( $#LIBPATHS    )) BUILD_ARGS+=( "-L${(@)^LIBPATHS}"    )
  if (( $#LDLIBS      )) BUILD_ARGS+=( "-l${(@)^LDLIBS}"      )
  if (( $#FRAMEWORKS  )) BUILD_ARGS+=( "-framework ${(@)^FRAMEWORKS}" )
  if (( $#SANITISE    )) BUILD_ARGS+=( "-fsanitize=${(j:,:)SANITISE}" )

  # always add the target file
  BUILD_ARGS+=( --output "$TARGET" )

  # ———————————————————————————————————————————————————— #

  if (( print_cmd )) {
    bat -pp -lzsh <<< "${"${:-"$CC $BUILD_ARGS source/**/*.c \\
      && $CMD \\
      && cp $TARGET ~/bin/${TARGET##*/}"}"//$_proj_root\//./}"
  }

  # ———————————————————————————————————————————————————— #

  # source files are added here so they don't mess up the `print_cmd` output
  BUILD_ARGS=( "${(@z)BUILD_ARGS}" -- "${(@)SOURCE_FILES}" )

  # pass that array of arguments to the compiler
  # then, if successful, execute the program
  # and if that _also_ works, make a copy of the binary available in `~/bin`
  "$CC" "${(@)BUILD_ARGS}" \
    &&  "${(@)CMD}"         \
    && cp "$TARGET" "$HOME/bin/${TARGET##*/}"

} "$@"

# ——————————————————————————————————————————————————————————————————————————— #

# spell:ignoreRegExp /(?<!-)[-_]\w+|\w+(?=\|)/g
