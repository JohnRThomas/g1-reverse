## review group param_0030  (1 cluster(s), kinds=param)

### proposal for param_0030
struct_name: gpio_dev_ctx | is_library: True | library_name: struct device (Zephyr, partial) | is_array: None | confidence: low
purpose: GPIO device context passed to gpio_pin_get_raw_checked: driver API pointer plus a pin/config word.
fields:
  0x4  void*        api_or_data_ptr  
  0x8  uint32_t     pin_or_config  

<ground-truth bundle for param_0030>
### cluster param_0030  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - gpio_pin_get_raw_checked @ 0x177c4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0030 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
};
```
