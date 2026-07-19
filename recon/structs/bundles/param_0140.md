### cluster param_0140  (param, 9 members, 10 fields, size>=0x70)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 4/9 members are LIBRARY-class)

members (9 shown of 9):
  - FUN_0004cce0 @ 0x4cce0  as param_2  [APPLICATION]
  - bound_cb @ 0x4cefc  as param_1  [LIBRARY]
  - rpmsg_send_offchannel_raw @ 0x70f1c  as param_1  [APPLICATION]
  - rpmsg_register_endpoint @ 0x70f74  as param_2  [LIBRARY]
  - rpmsg_create_ept @ 0x70fb4  as param_1  [LIBRARY]
  - ept_cb @ 0x7ecc4  as param_5  [LIBRARY]
  - FUN_00085846 @ 0x85846  as param_1  [APPLICATION]
  - rpmsg_send_ns_message @ 0x85898  as param_1  [APPLICATION]
  - FUN_00085974 @ 0x85974  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0140 {
    uint8_t    _pad_0x0[0x20];   /* +0x0 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=int,undefined4 */
    void *     field_0x38;   /* +0x38  sz=4 rw=rw types=int,ptr,undefined4 */
    uint8_t    _pad_0x3c[0x28];   /* +0x3c pad */
    uint8_t    field_0x64;   /* +0x64  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x65[0x3];   /* +0x65 pad */
    void *     field_0x68;   /* +0x68  sz=4 rw=r types=int,ptr */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=undefined4 */
};
```