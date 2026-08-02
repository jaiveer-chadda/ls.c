#!/usr/bin/env zsh

# build.zsh
# ‾‾‾‾‾‾‾‾‾

if ((0)) {
  clang                                     \
    -O0 -Wall -Wextra -Wpedantic            \
    -Wno-deprecated-declarations            \
    -I"$( brew --prefix libmagic )/include" \
    -L"$( brew --prefix libmagic )/lib"     \
    -lmagic	-framework CoreFoundation       \
    -fsanitize=address                      \
    -o "${${(%):-%x}:a:h}"/out/lk           \
    "${${(%):-%x}:a:h}"/source/**/*.c       \
      && "${${(%):-%x}:a:h}"/out/lk --clear
}

# ——————————————————————————————————————————————————————————————————————————— #

function -- () {

  local -r _root="${${(%):-%x}:a:h}"

  local -r  CC=clang
  local -ra CFLAGS=( O0 )
  local -ra WARNINGS=( all extra pedantic no-deprecated-declarations )

  # ————————————————————————————————————————————————————————————————————————— #

  local -r TARGET="$_root/out/lk"
  local -ra CMD=( "$TARGET" --clear )

  # ———————————————————————————————————————————————————— #

  # recursively find all .c files in the source directory
  local -ra SOURCE_FILES=( "$_root/"**/*.c )

  # ———————————————————————————————————————————————————— #

  local -ra FRAMEWORKS=( -framework CoreFoundation )

  # find where the `libmagic` library is stored, and pass it to the linker
  local -r BREW_PREFIX="$( brew --prefix libmagic )"
  local -ra INCLUDES=( "$BREW_PREFIX/include"                )
  local -ra  LDFLAGS=( "L$BREW_PREFIX/lib" fsanitize=address )
  local -ra   LDLIBS=( magic                                 )

  # ————————————————————————————————————————————————————————————————————————— #

  local -ra ALL_BUILD_ARGS=(
    "-W${(@)^WARNINGS}"
    "-I${(@)^INCLUDES}"
    "-l${(@)^LDLIBS}"
    "-${(@)^LDFLAGS}"
    "-${(@)^CFLAGS}"
    "${(@)FRAMEWORKS}"
    "${(@)SOURCE_FILES}"
  )

  "$CC" "${(@)ALL_BUILD_ARGS}" -o "$TARGET" && "${(@)CMD}" "$@"
} "$@"

# spell:ignoreRegExp /(?<!-)-\w+/g
