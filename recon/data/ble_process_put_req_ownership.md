# `ble_process_put_req` code/data ownership

The original function at `0x0001a75c` uses a 39-entry `TBH` dispatch table at
`0x0001a7a4`.  Its reachable opcode handlers are not confined to the first
242 bytes: they occupy 44 disjoint code ranges from `0x0001a75c` through
`0x00021309`, totalling 25,616 executable bytes in Ghidra's function body.

The non-code islands between those ranges are owned by the readable constant
definitions `rodata_1aa5c.c` through `rodata_2130c.c` in this directory (38
files).  The initial island `0x1a7a4..0x1a7f1` is the `TBH` table itself.  A
few alignment bytes immediately before a named constant account for starts
such as `0x1aa5a`/`rodata_1aa5c.c`.  None of these islands is trailing opaque
function content.

Opcode target map, relative to the table PC (`0x1a7a4`):

```
01 1a7f2   02 1a7f2   03 1a7f2   04 1a96c   05 1a7f2
06 1ab34   07 1aa88   08 1a97e   09 1e06a   0a 1fa42
0b 1a7f2   0c 212ca   0d 20b5c   0e 20db6   0f 20c8c
10 1a84e   11 212ca   12 212ca   13 212ca   14 1a7f2
15 20f3a   16 21062   17 210b8   18 210ec   19 212ca
1a 212ca   1b 212ca   1c 20eca   1d 212ca   1e 1f2d0
1f 21154   20 20fae   21 212ca   22 1dfda   23 212ca
24 1f08e   25 1f1f2   26 211be   27 2103a
```

Opcodes `0x0c`, `0x11..0x13`, `0x19..0x1b`, `0x1d`, `0x21`, and `0x23`
share the invalid/error handler at `0x212ca`.
