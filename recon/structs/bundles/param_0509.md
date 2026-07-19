### cluster param_0509  (param, 1 members, 3 fields, size>=0x1a8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ipc_rpmsg_deinit @ 0x7ed2a  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0509 {
    uint8_t    _pad_0x0[0x19c];   /* +0x0 pad */
    uint32_t   field_0x19c;   /* +0x19c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x1a0;   /* +0x1a0  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x1a4;   /* +0x1a4  sz=4 rw=w types=undefined4 */
};
```