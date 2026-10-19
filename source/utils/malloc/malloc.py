#!/usr/bin/env python3

from sys       import exit as sysexit, argv, stderr

from pathlib   import Path
from signal    import Signals, signal, SIGINFO, SIGINT, SIGTERM

from types     import FrameType
from functools import partial
from typing    import Callable, Final, NoReturn, Optional, TextIO

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #
# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

ARROW_LEN  : Final[int] = len(" --> ")
HEX_PTR_LEN: Final[int] = 12

TO_HEX     : Final[Callable[[str], int]] = lambda s: int(s, 16)
RJUST_PTR  : Final[Callable[[str], str]] = lambda s: s.rjust(HEX_PTR_LEN)

error      : Final[Callable[... , None]] = partial(print, file=stderr)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #
# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

# 128 is the offset at which signals start to be defined
SIGNAL: Final[int] = 128

def catch_signal(signum: int | Signals, __: Optional[FrameType]) -> NoReturn:
    match signum:
        case Signals.SIGTERM: pass
        case Signals.SIGINFO: print_report()
        case Signals.SIGINT : error("\33[2D" "interrupted by user")
        case _              : error(f"unexpected signal: {Signals(signum)._name_}")

    sysexit(SIGNAL + signum)

signal(SIGINT , catch_signal)
signal(SIGINFO, catch_signal)
signal(SIGTERM, catch_signal)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #
# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

type Ptr = int
type info = str
type PtrInfo = tuple[bool, list[Ptr], list[info], Optional[info]]
type PtrDict = dict[Ptr, PtrInfo]

# this is quicker & easier than making a whole enum
IS_FREED: Final[int] = 0
OLD_PTRS: Final[int] = 1
OLD_INFO: Final[int] = 2
FREEINFO: Final[int] = 3

NULL: Final[Ptr] = 0

ptr_dict: PtrDict = {}

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

def print_report() -> None:
    if len(ptr_dict) == 0: return

    for is_freed, old_ptrs, old_info, _ in ptr_dict.values():
        if is_freed: continue
        assert len(old_ptrs) == len(old_info)

        for o_ptr, o_info in zip(old_ptrs, old_info):
            print(RJUST_PTR(hex(o_ptr)[2:]), o_info, sep='\t')

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

def proc_realloc(old: Ptr, new: Ptr, info: info) -> None:
    if new in ptr_dict: error("realloc assigned to a ptr already in `ptr_dict`"); return

    if old == NULL:
        proc_alloc(new, info + " [initialised from NULL pointer]")
        return

    if old not in ptr_dict    : error("realloc reassigned from an untracked ptr"); return
    if ptr_dict[old][IS_FREED]: error("realloc trying to reassign a freed ptr"  ); return

    # I have to reassign the whole thing here,
    #  cos there's no other way t change the elems of a tuple otherwise
    ptr_dict[new] = ( False, ptr_dict[old][OLD_PTRS] + [new], ptr_dict[old][OLD_INFO] + [info], None )

    del ptr_dict[old]

# —————————————————————————————————————————————————————— #

def proc_alloc(ptr: Ptr, info: info) -> None:
    if ptr in ptr_dict: error("malloc returned a ptr which was already being used"); return
    ptr_dict[ptr] = ( False, [ptr], [info], None )

# —————————————————————————————————————————————————————— #

def proc_free(ptr: Ptr, info: info) -> None:
    if ptr == 0           : error("trying to free a null pointer (should have been caught)"); return
    if ptr not in ptr_dict: error("trying to free a pointer which wasn't `malloc`ed"       ); return

    ptr_dict[ptr] = ( True, ptr_dict[ptr][OLD_PTRS], ptr_dict[ptr][OLD_INFO], info )

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

FREED_SLICE: Final[slice] = slice( 0, HEX_PTR_LEN                                                             )
ARROW_SLICE: Final[slice] = slice(    HEX_PTR_LEN, HEX_PTR_LEN + ARROW_LEN                                    )
ALLOC_SLICE: Final[slice] = slice(                 HEX_PTR_LEN + ARROW_LEN, (HEX_PTR_LEN * 2) + ARROW_LEN     )
EXTRA_SLICE: Final[slice] = slice(                                          (HEX_PTR_LEN * 2) + ARROW_LEN, -1 )

# —————————————————————————————————————————————————————— #

def process_line(line: str, output: TextIO) -> None:
    freed: Final[str] = line[FREED_SLICE].strip()
    arrow: Final[str] = line[ARROW_SLICE].strip()
    alloc: Final[str] = line[ALLOC_SLICE].strip()
    extra: Final[str] = line[EXTRA_SLICE].strip()

    assert arrow in ( '', "-->" )

    print(f"{RJUST_PTR(freed)} | {RJUST_PTR(alloc)} | {extra}", file=output)

    if freed and alloc: proc_realloc(TO_HEX(freed), TO_HEX(alloc), extra)
    elif         alloc:   proc_alloc(               TO_HEX(alloc), extra)
    else              :    proc_free(TO_HEX(freed),                extra)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

OUTPUT_FILE: Final[Path] = Path("/dev/null") # "ttys001" # "stdout"

def process_pipe(input: TextIO) -> NoReturn:
    with open(OUTPUT_FILE, 'w') as output:
        while True:
            for line in input:
                process_line(line, output)

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #
# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

def main() -> int:
    if (len(argv) != 2):
        error(f"usage: {argv[0]} <path-to-fifo>")
        return 1

    with open(argv[1], 'r') as pipe:
        process_pipe(pipe)

    return 0

# —————————————————————————————————————————————————————— #

if __name__ == "__main__":
    sysexit(main())

# ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————— #

# spell:ignore ptrs
