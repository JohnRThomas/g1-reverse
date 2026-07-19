### cluster param_0215  (param, 1 members, 2 fields, size>=0x54)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ble_conn_process_complete_or_disconnect @ 0x570a0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0215 {
    uint8_t    _pad_0x0[0x48];   /* +0x0 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x4c[0x4];   /* +0x4c pad */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=undefined4 */
};
```