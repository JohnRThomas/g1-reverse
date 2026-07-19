## review group param_0482  (1 cluster(s), kinds=param)

### proposal for param_0482
struct_name: log_timestamp_fields | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: Array of integer date/time components (month, day, hour, minute, etc.) read by format_log_timestamp_mmdd_hhmm to render an MM/DD HH:MM log timestamp string.
fields:
  0x4  uint32_t     field_0  date/time component, read
  0x8  uint32_t     field_1  date/time component, read
  0xc  uint32_t     field_2  date/time component, read
  0x10  uint32_t     field_3  date/time component, read
  0x14  uint32_t     field_4  date/time component, read
  0x18  uint32_t     field_5  date/time component, read
  0x1c  uint32_t     field_6  date/time component, read
  0x20  uint32_t     field_7  date/time component, read
  0x24  uint32_t     field_8  date/time component, read
  0x28  uint32_t     field_9  date/time component, read
  0x2c  uint32_t     field_10  date/time component, read
  0x30  uint32_t     field_11  date/time component, read

<ground-truth bundle for param_0482>
### cluster param_0482  (param, 1 members, 12 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - format_log_timestamp_mmdd_hhmm @ 0x7ca80  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0482 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
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
};
```
