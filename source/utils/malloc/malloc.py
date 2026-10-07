#!/usr/bin/env python3

from sys       import exit as sysexit, argv, stderr

from pathlib   import Path
from signal    import Signals, signal, SIGINT, SIGTERM

from types     import FrameType
from functools import partial
from typing    import Callable, Final, NoReturn, Optional, TextIO

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

error: Final[Callable[..., None]] = partial(print, file=stderr)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

# 128 is the offset at which signals start to be defined
SIGNAL: Final[int] = 128

def catch_signal(signum: int | Signals, _f: Optional[FrameType]) -> NoReturn:
    match signum:
        case Signals.SIGTERM: pass # error("process terminated")
        case Signals.SIGINT : error("\33[2D" "interrupted by user")
        case _              : error(f"unexpected terminating signal: {Signals(signum)._name_}")

    sysexit(SIGNAL + signum)

signal(SIGINT , catch_signal)
signal(SIGTERM, catch_signal)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

WRITE_TO   : Final[str]  = "ttys001" # "stdout"
OUTPUT_FILE: Final[Path] = Path("/dev") / WRITE_TO

def process_alloc_info(input: TextIO, output: TextIO):
    print(input.read(), file=output, end='')

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

def main() -> int:
    if (len(argv) != 2):
        error(f"usage: {argv[0]} <path-to-fifo>")
        return 1

    log_pipe: Final[Path] = Path(argv[1])

    with open(log_pipe, 'r') as pipe:
        with open(OUTPUT_FILE, 'w') as output:
            while True: process_alloc_info(pipe, output)

    return 0

# —————————————————————————————————————————————————————— #

if __name__ == "__main__":
    sysexit(main())

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #
