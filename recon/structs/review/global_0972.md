## review group global_0972  (1 cluster(s), kinds=global)

### proposal for global_0972
struct_name: confirm_message_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state object for an on-glasses confirmation/dialog message (status flags plus a trailing marker byte) referenced by confirm_message.
fields:
  0x110  uint32_t     msg_status  read-only status/type code
  0x115  uint8_t      confirm_flag  single-byte flag, read
  0x118  uint8_t      dismiss_flag  single-byte flag, read
  0x2b8  uint8_t      trailer_flag  byte near struct end, read

<ground-truth bundle for global_0972>
### cluster global_0972  (global, 1 members, 4 fields, size>=0x2bc)

Global object at fixed address 0x000347a0.

library hint: likely G1-original

members (1 shown of 1):
  - confirm_message @ 0x34524  as 0x000347a0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0972 {
    uint8_t    _pad_0x0[0x110];   /* +0x0 pad */
    uint32_t   field_0x110;   /* +0x110  sz=4 rw=r types=int */
    uint8_t    _pad_0x114[0x1];   /* +0x114 pad */
    uint8_t    field_0x115;   /* +0x115  sz=1 rw=r types=char */
    uint8_t    _pad_0x116[0x2];   /* +0x116 pad */
    uint8_t    field_0x118;   /* +0x118  sz=1 rw=r types=char */
    uint8_t    _pad_0x119[0x19f];   /* +0x119 pad */
    uint8_t    field_0x2b8;   /* +0x2b8  sz=1 rw=r types=char */
    uint8_t    _pad_0x2b9[0x3];   /* +0x2b9 pad */
};
```
