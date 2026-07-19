### cluster global_0968  (global, 1 members, 4 fields, size>=0x119)

Global object at fixed address 0x00033bbc.

library hint: likely G1-original

members (1 shown of 1):
  - stage_pending_message_for_resend @ 0x33b88  as 0x00033bbc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0968 {
    uint8_t    _pad_0x0[0x114];   /* +0x0 pad */
    uint8_t    field_0x114;   /* +0x114  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x115;   /* +0x115  sz=1 rw=r types=byte */
    uint8_t    field_0x116;   /* +0x116  sz=1 rw=r types=char */
    uint8_t    _pad_0x117[0x1];   /* +0x117 pad */
    uint8_t    field_0x118;   /* +0x118  sz=1 rw=r types=byte */
};
```