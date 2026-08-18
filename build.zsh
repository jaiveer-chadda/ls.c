#!/usr/bin/env zsh

# build.zsh
# ‾‾‾‾‾‾‾‾‾

if { false; } {
  clang                                    \
    -O0 -Wall -Wextra -Wpedantic           \
    -Wno-deprecated-declarations           \
    -Wno-variadic-macro-arguments-omitted  \
    -L"$( brew --prefix libmagic )"lib     \
    -I"$( brew --prefix libmagic )"include \
    -I$HOME/dev/C/ls.c/source              \
    -lmagic -framework CoreFoundation      \
    -fsanitize=address,undefined           \
    "$root/source/"**/*.c                  \
    --output "$root/out/lk"                \
      &&     "$root/out/lk" --clear        \
      && cp  "$root/out/lk" "$HOME/bin/lk"
}

# ——————————————————————————————————————————————————————————————————————————— #

function -- () {

  # equivalent to running `dirname` on this file's path (w/o resolving links)
  local -r _proj_root="${${(%):-%x}:a:h}"

  # ————————————————————————————————————————————————————————————————————————— #

  local -r CC='clang'
  local -ra CFLAGS=( O0 )

  # ————————————————————————————————————————————————————————————————————————— #

  # if the `--debug` flag is passed to this script, then define the
  #  `DEBUG_MODE` macro for the compiler to build with debug enabled
  local mode
  if [[ "$1" == --debug ]] mode=debug && shift

  local -a DEFINITIONS
  if [[ "$mode" == debug ]] DEFINITIONS+=( DEBUG_MODE )

  # ————————————————————————————————————————————————————————————————————————— #

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
  local -r COPY_TO="$_proj_root/out/lk"
  # the command that should be run after compilation & linking
  local -ra CMD=( "$TARGET" --clear )

  # ———————————————————————————————————————————————————— #

  # an array of all the program's source files
  local -ra SOURCE_FILES=( "$_proj_root/source/"**/*.c )

  # ———————————————————————————————————————————————————— #

  # find where the `libmagic` library is stored, to be passed to the linker
  local -r _lmagic_prefix="$( brew --prefix libmagic )"

  local -ra FRAMEWORKS=( CoreFoundation )
  local -ra   LIBPATHS=( "$_lmagic_prefix/lib" )
  local -ra   INCLUDES=( "$_lmagic_prefix/include" "$_proj_root/source" )
  local -ra   SANITISE=( address undefined )
  local -ra     LDLIBS=( magic )

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

  # always add the target and source files
  BUILD_ARGS+=( --output "$TARGET" -- )
  BUILD_ARGS+=( "${(@)SOURCE_FILES}"  )

  # echo "$CC" "${(@z)BUILD_ARGS}" '\ \n\t' \
  #   '&&' "${(@)CMD}" "$@"         '\ \n\t' \
  #   '&&' cp "$TARGET" "$HOME/bin/${TARGET##*/}" $'\e[m'

  # pass that array of arguments to the compiler
  # then, if successful, execute the program
  # and if that _also_ works, make a copy of the binary available in `~/bin`
  "$CC" "${(@z)BUILD_ARGS}" \
    &&  "${(@)CMD}" "$@"     \
    && cp "$TARGET" "$HOME/bin/${TARGET##*/}"

} "$@"

# ——————————————————————————————————————————————————————————————————————————— #

# spell:ignoreRegExp /(?<!-)[-_]\w+/g
