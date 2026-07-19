### cluster param_0610  (param, 1 members, 3 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_req_send_process @ 0x820ae  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0610 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=rw types=ptr,undefined4 */
    void *     field_0x8;   /* +0x8  sz=4 rw=rw types=int,ptr */
    uint8_t    _pad_0xc[0x24];   /* +0xc pad */
    void *     field_0x30;   /* +0x30  sz=4 rw=r types=ptr */
};
```