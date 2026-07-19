### cluster param_0214  (param, 3 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 2/3 members are LIBRARY-class)

members (3 shown of 3):
  - send_conn_le_param_update @ 0x57038  as param_2  [APPLICATION]
  - bt_le_conn_params_valid @ 0x80f14  as param_1  [LIBRARY]
  - bt_conn_le_conn_update @ 0x8152a  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0214 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```