### cluster param_0032  (param, 1 members, 7 fields, size>=0x36a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ancs_ctx_init @ 0x18208  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0032 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0xc9];   /* +0x10 pad */
    uint8_t    field_0xd9;   /* +0xd9  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xda[0x172];   /* +0xda pad */
    uint32_t   field_0x24c;   /* +0x24c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x250;   /* +0x250  sz=4 rw=r types=idx4 */
    uint32_t   field_0x254;   /* +0x254  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x258[0x10d];   /* +0x258 pad */
    uint8_t    field_0x365;   /* +0x365  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x366;   /* +0x366  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x367[0x3];   /* +0x367 pad */
};
```