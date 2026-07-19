## review group param_0084  (1 cluster(s), kinds=param)

### proposal for param_0084
struct_name: opt3007_init_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Initialization context for the OPT3007 ambient light sensor driver
fields:
  0xc  uint32_t     i2c_addr_or_cfg  idx4
  0x1c  uint32_t     init_flags  idx4

<ground-truth bundle for param_0084>
### cluster param_0084  (param, 1 members, 2 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - opt3007_init_ctx_setup @ 0x2e8fc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0084 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0xc];   /* +0x10 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
};
```
