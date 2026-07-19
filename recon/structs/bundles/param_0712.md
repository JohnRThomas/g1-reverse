### cluster param_0712  (param, 1 members, 2 fields, size>=0xa8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - virtqueue_return_rx_buffer @ 0x85a9c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0712 {
    uint8_t    _pad_0x0[0xa0];   /* +0x0 pad */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=int */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=undefined4 */
};
```