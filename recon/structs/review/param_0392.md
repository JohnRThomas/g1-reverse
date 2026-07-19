## review group param_0392  (1 cluster(s), kinds=param)

### proposal for param_0392
struct_name: lc3_tns_nbits_table | is_library: True | library_name: lc3 codec internal (TNS config table) | is_array: True | confidence: medium
purpose: Table of per-subframe bit-count values consumed uniformly by lc3_tns_get_nbits (LC3 TNS coding).
fields:
  0x1  uint8_t      flag_0x1  leading byte flag before table
  0x8  int32_t      nbits_0  array element
  0xc  int32_t      nbits_1  array element
  0x10  int32_t      nbits_2  array element
  0x14  int32_t      nbits_3  array element
  0x18  int32_t      nbits_4  array element
  0x1c  int32_t      nbits_5  array element
  0x20  int32_t      nbits_6  array element
  0x24  int32_t      nbits_7  array element
  0x28  int32_t      nbits_8  array element
  0x2c  int32_t      nbits_9  array element
  0x30  int32_t      nbits_10  array element
  0x34  int32_t      nbits_11  array element
  0x38  int32_t      nbits_12  array element
  0x3c  int32_t      nbits_13  array element
  0x40  int32_t      nbits_14  array element
  0x44  int32_t      nbits_15  array element
  0x48  int32_t      nbits_16  array element
  0x4c  int32_t      nbits_17  array element

<ground-truth bundle for param_0392>
### cluster param_0392  (param, 1 members, 19 fields, size>=0x50)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_tns_get_nbits @ 0x709d8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0392 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x6];   /* +0x2 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
};
```
