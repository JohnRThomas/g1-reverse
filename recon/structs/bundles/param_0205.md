### cluster param_0205  (param, 2 members, 5 fields, size>=0x15)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - conn_tx_send_to_driver @ 0x560cc  as param_2  [APPLICATION]
  - saadc_start_read @ 0x5f760  as param_2  [APPLICATION]

layout notes: overlap at 0x11 (prev field ends 0x14)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0205 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x1];   /* +0x14 pad */
};
```