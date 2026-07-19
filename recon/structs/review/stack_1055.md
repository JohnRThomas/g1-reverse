## review group stack_1055  (1 cluster(s), kinds=stack)

### proposal for stack_1055
struct_name: ascii_digit_buffer | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: Local character buffer holding formatted ASCII digits produced by float_to_ascii_signed_2dp.
fields:
  0x1  uint8_t      digit_0  array element (ASCII digit/char)
  0x2  uint8_t      digit_1  array element
  0x3  uint8_t      digit_2  array element
  0x4  uint8_t      digit_3  array element
  0x5  uint8_t      digit_4  array element
  0x6  uint8_t      digit_5  array element
  0x7  uint8_t      digit_6  array element
  0x8  uint8_t      digit_7  array element
  0x9  uint8_t      digit_8  array element
  0xa  uint8_t      digit_9  array element
  0xb  uint8_t      digit_10  array element
  0xc  uint8_t      digit_11  array element
  0x11  uint8_t      digit_tail  trailing byte, e.g. null terminator

<ground-truth bundle for stack_1055>
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
