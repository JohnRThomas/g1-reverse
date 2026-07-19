## review group param_0044  (1 cluster(s), kinds=param)

### proposal for param_0044
struct_name: device_info_persist_store | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Large (0x1044-byte) persistent device-info storage buffer; the accessed function only touches trailer fields (two counters and a pointer) beyond the main data area.
fields:
  0xfec  uint32_t     field_0xfec  
  0xff0  uint32_t     field_0xff0  
  0x1040  void *       tail_ptr  

<ground-truth bundle for param_0044>
### cluster param_0044  (param, 1 members, 3 fields, size>=0x1044)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - device_info_register_persistent_fields @ 0x23230  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0044 {
    uint8_t    _pad_0x0[0xfec];   /* +0x0 pad */
    uint32_t   field_0xfec;   /* +0xfec  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xff0;   /* +0xff0  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0xff4[0x4c];   /* +0xff4 pad */
    void *     field_0x1040;   /* +0x1040  sz=4 rw=r types=ptr */
};
```
