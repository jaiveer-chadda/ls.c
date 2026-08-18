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
    -I/Users/jv/dev/C/ls.c/source          \
    -lmagic -framework CoreFoundation      \
    -fsanitize=address,undefined           \
    --output "$_root/out/lk"               \
    "$_root/source/"**/*.c                 \
      && "$_root/out/lk" --clear
}

# ——————————————————————————————————————————————————————————————————————————— #

function -- () {

  readonly _root="${${(%):-%x}:a:h}"

  readonly CC=clang
  readonly -a CFLAGS=( O0 )

  # ————————————————————————————————————————————————————————————————————————— #

  local -a DEFINITIONS=()
  if [[ "$1" == (--|)debug ]] DEFINITIONS+=( DEBUG_MODE ) && shift

  readonly -a WARNINGS=( all extra pedantic )
  readonly -a NO_WARN=(
    deprecated-declarations
    variadic-macro-arguments-omitted
  )

  # ————————————————————————————————————————————————————————————————————————— #

  readonly TARGET="$_root/out/lk"
  readonly -a CMD=( "$TARGET" --clear )

  # ———————————————————————————————————————————————————— #

  readonly -a SOURCE_FILES=( "$_root/source/"**/*.c )

  # ———————————————————————————————————————————————————— #

  readonly -a FRAMEWORKS=( -framework CoreFoundation )
  readonly -a _sanitise=( address undefined )

  # find where the `libmagic` library is stored, and pass it to the linker
  readonly _brew_prefix="$( brew --prefix libmagic )"
  readonly -a INCLUDES=( "$_brew_prefix/include" "$_root/source" )
  readonly -a  LDFLAGS=( "L$_brew_prefix/lib" fsanitize=${(j:,:)_sanitise} )
  readonly -a   LDLIBS=( magic )

  # ————————————————————————————————————————————————————————————————————————— #

  readonly -a ALL_BUILD_ARGS=(
    "-W-no-${(@)^NO_WARN}"
    "-W${(@)^WARNINGS}"
    "-D${(@)^DEFINITIONS}"
    "-W${(@)^WARNINGS}"
    "-I${(@)^INCLUDES}"
    "-l${(@)^LDLIBS}"
    "-${(@)^LDFLAGS}"
    "-${(@)^CFLAGS}"
    "${(@)FRAMEWORKS}"
    "${(@)SOURCE_FILES}"
  )

  echo "$CC" "${(@)ALL_BUILD_ARGS}" --output "$TARGET" && "${(@)CMD}" "$@"
} "$@"

# spell:ignoreRegExp /(?<!-)-\w+/g
