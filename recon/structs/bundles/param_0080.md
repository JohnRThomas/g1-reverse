### cluster param_0080  (param, 1 members, 6 fields, size>=0x13)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - process_for_message_show @ 0x2c714  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0080 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x2[0x5];   /* +0x2 pad */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=rw types=byte,char,undefined1 */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=byte */
    uint8_t    _pad_0xa[0x1];   /* +0xa pad */
    uint32_t   field_0xb;   /* +0xb  sz=4 rw=r types=undefined4 */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=r types=byte */
    uint8_t    _pad_0x10[0x3];   /* +0x10 pad */
};
```