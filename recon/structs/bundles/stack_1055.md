### cluster stack_1055  (stack, 1 members, 13 fields, size>=0x12)

Stack-frame local local_25 in float_to_ascii_signed_2dp (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - float_to_ascii_signed_2dp @ 0x4a300  as local_25  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1055 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=idx1 */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=idx1 */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=idx1 */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=r types=idx1 */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=idx1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=idx1 */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=r types=idx1 */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=idx1 */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0xd[0x4];   /* +0xd pad */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=r types=idx1 */
};
```