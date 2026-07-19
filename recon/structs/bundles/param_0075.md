### cluster param_0075  (param, 1 members, 3 fields, size>=0x107c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - click_event_dispatch_loop @ 0x28a1c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0075 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=char */
    uint8_t    _pad_0x2[0x105a];   /* +0x2 pad */
    uint16_t   field_0x105c;   /* +0x105c  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x105e[0x1a];   /* +0x105e pad */
    uint32_t   field_0x1078;   /* +0x1078  sz=4 rw=r types=undefined4 */
};
```