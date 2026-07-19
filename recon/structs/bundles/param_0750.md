### cluster param_0750  (param, 1 members, 5 fields, size>=0x4a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dynbuf_push_byte_grow @ 0x8790e  as param_2  [APPLICATION]

layout notes: overlap at 0x45 (prev field ends 0x48); overlap at 0x46 (prev field ends 0x48)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0750 {
    uint8_t    _pad_0x0[0x34];   /* +0x0 pad */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3c[0x8];   /* +0x3c pad */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x48[0x2];   /* +0x48 pad */
};
```