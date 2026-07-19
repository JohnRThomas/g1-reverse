### cluster param_0714  (param, 1 members, 2 fields, size>=0xac)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - rpmsg_deinit_vdev @ 0x85bf6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0714 {
    uint8_t    _pad_0x0[0xa4];   /* +0x0 pad */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=r types=idx4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=r types=idx4 */
};
```