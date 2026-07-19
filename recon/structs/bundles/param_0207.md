### cluster param_0207  (param, 2 members, 4 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,k; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - bt_conn_prepare_tx_events @ 0x565c4  as param_1  [APPLICATION]
  - k_poll_event_init @ 0x75574  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0207 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=1,4 rw=rw types=byte,uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=int */
    uint8_t    _pad_0x14[0xc];   /* +0x14 pad */
    uint8_t    field_0x20;   /* +0x20  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x21[0x3];   /* +0x21 pad */
};
```