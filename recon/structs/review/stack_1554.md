## review group stack_1554  (1 cluster(s), kinds=stack)

### proposal for stack_1554
struct_name: regulator_voltage_range_local | is_library: True | library_name: regulator (local) | is_array: None | confidence: low
purpose: Stack-local pair of bytes used inside Zephyr's regulator_set_voltage_range while validating a voltage range request.
fields:
  0x0  uint8_t      field_0x0  min/index byte
  0x6  uint8_t      field_0x6  max/index byte

<ground-truth bundle for stack_1554>
### cluster stack_1554  (stack, 1 members, 2 fields, size>=0x7)

Stack-frame local local_12 in regulator_set_voltage_range (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - regulator_set_voltage_range @ 0x84300  as local_12  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1554 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x5];   /* +0x1 pad */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=idx1 */
};
```
