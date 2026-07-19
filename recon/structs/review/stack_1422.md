## review group stack_1422  (1 cluster(s), kinds=stack)

### proposal for stack_1422
struct_name: float_render_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local mantissa/exponent pair used by printf_render_float while formatting a floating-point value for printf-style output.
fields:
  0x0  uint32_t     mantissa  read-only idx4
  0x8  uint32_t     exponent  read-only idx4

<ground-truth bundle for stack_1422>
### cluster stack_1422  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in printf_render_float (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - printf_render_float @ 0x7712c  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1422 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
