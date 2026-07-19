## review group stack_1525  (1 cluster(s), kinds=stack)

### proposal for stack_1525
struct_name: smp_ah_output_buf | is_library: True | library_name:  | is_array: True | confidence: medium
purpose: 16-byte AES-ECB output buffer (plus trailing byte) used by bt_smp_ah to compute a resolvable-address hash
fields:
  0x0  uint8_t      byte_0  r, idx1
  0x11  uint8_t      byte_last  r, idx1

<ground-truth bundle for stack_1525>
### cluster stack_1525  (stack, 1 members, 2 fields, size>=0x12)

Stack-frame local auStack_1d in bt_smp_ah (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_smp_ah @ 0x80ca0  as auStack_1d  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1525 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x10];   /* +0x1 pad */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=r types=idx1 */
};
```
