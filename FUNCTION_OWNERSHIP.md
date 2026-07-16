# Function ownership corrections

## App `0x0006b3c8` and `0x0006b9b8`

The MCUBoot payload mapping is `file_offset = VA - 0xc200 + 0x200` (equivalently,
raw-binary objdump uses `--adjust-vma=0xc000`).  Under that mapping these are two
genuine libLC3 functions, not one inflated function.

- `0x6b3c8` (`fft`) starts `2d e9 f0 4f 2d ed 0c 8b`, a full integer/VFP
  prologue.  Its late branches rejoin the body and leave through the matching
  epilogues at `0x6b990..0x6b996` and `0x6b99a..0x6b9a2`.  The catalogued
  extent `0x5ea` ending at `0x6b9b2` is therefore correct.
- `0x6b9b8` (`lc3_mdct_forward`) starts
  `2d e9 f0 4f 14 46 2d ed 02 8b`: its own integer/VFP prologue, followed by
  its own dynamic stack frame.  `0x69318` directly calls it with `BL
  0x6b9b8`.  It calls the distinct FFT with `BL 0x6b3c8` at `0x6bc84`, then
  leaves via its own epilogue at `0x6bd48..0x6bd50`.  Its executable extent is
  `0x3ae` (`0x6b9b8..0x6bd65`); words at `0x6bd68`, `0x6bd6c`, and `0x6bd70`
  are its constants/table pointers.

Consequently `0x6b9b8` must never be placed on an interior-entry exclusion
list, and strict verification of `fft` must not absorb it.
