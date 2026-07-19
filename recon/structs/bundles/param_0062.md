### cluster param_0062  (param, 1 members, 2 fields, size>=0x68)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - register_ipc_service_context @ 0x25d40  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0062 {
    uint8_t    _pad_0x0[0x60];   /* +0x0 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=w types=undefined4 */
};
```