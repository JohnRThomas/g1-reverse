## review group param_0683  (1 cluster(s), kinds=param)

### proposal for param_0683
struct_name: pmic_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: PMIC driver context/handle holding register-access pointers, used by pmic_write_reg7_enable.
fields:
  0x4  void*        i2c_dev  pointer to underlying I2C/bus device
  0x10  void*        regmap  pointer to register map or config

<ground-truth bundle for param_0683>
### cluster param_0683  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pmic_write_reg7_enable @ 0x84cb0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0683 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=ptr */
};
```
