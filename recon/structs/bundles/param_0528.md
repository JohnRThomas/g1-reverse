### cluster param_0528  (param, 1 members, 4 fields, size>=0x15c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - svc_attr_memory_release @ 0x7f3c2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0528 {
    uint8_t    _pad_0x0[0x134];   /* +0x0 pad */
    uint32_t   field_0x134;   /* +0x134  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x138[0x18];   /* +0x138 pad */
    void *     field_0x150;   /* +0x150  sz=4 rw=rw types=ptr,undefined4 */
    void *     field_0x154;   /* +0x154  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0x158;   /* +0x158  sz=4 rw=w types=undefined4 */
};
```