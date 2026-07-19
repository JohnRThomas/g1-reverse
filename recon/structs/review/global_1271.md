## review group global_1271  (1 cluster(s), kinds=global)

### proposal for global_1271
struct_name: saadc_read_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Global SAADC (successive-approximation ADC) driver state / sample buffer used by saadc_start_read; large buffer region with two scalar status/result fields at the tail
fields:
  0x5f0  uint32_t     read_status  written by saadc_start_read; possibly busy/result flag
  0x62c  int32_t      last_sample  written; likely last converted ADC value or error code

<ground-truth bundle for global_1271>
### cluster global_1271  (global, 1 members, 2 fields, size>=0x630)

Global object at fixed address 0x0005f95c.

library hint: likely G1-original

members (1 shown of 1):
  - saadc_start_read @ 0x5f760  as 0x0005f95c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1271 {
    uint8_t    _pad_0x0[0x5f0];   /* +0x0 pad */
    uint32_t   field_0x5f0;   /* +0x5f0  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x5f4[0x38];   /* +0x5f4 pad */
    uint32_t   field_0x62c;   /* +0x62c  sz=4 rw=w types=int */
};
```
