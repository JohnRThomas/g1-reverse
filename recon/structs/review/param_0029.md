## review group param_0029  (1 cluster(s), kinds=param)

### proposal for param_0029
struct_name: gpio_pin_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: GPIO pin descriptor used by gpio_pin_set_checked: device pointer, pin number, and a secondary pointer (likely a spec/config struct)
fields:
  0x4  const struct device * port_dev  
  0x8  uint32_t     pin  
  0x10  void *       cfg_ptr  

<ground-truth bundle for param_0029>
### cluster param_0029  (param, 1 members, 3 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - gpio_pin_set_checked @ 0x17768  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0029 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=ptr */
};
```
