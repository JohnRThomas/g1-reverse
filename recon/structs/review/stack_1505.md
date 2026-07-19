## review group stack_1505  (1 cluster(s), kinds=stack)

### proposal for stack_1505
struct_name: scratch_pair_0007e83a | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local pair of 16-bit index values in FUN_0007e83a separated by a 6-byte gap.
fields:
  0x0  uint16_t     field_0x0  read-only short, idx2
  0x8  uint16_t     field_0x8  read-only short, idx2

<ground-truth bundle for stack_1505>
### cluster stack_1505  (stack, 1 members, 2 fields, size>=0xa)

Stack-frame local local_50 in FUN_0007e83a (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0007e83a @ 0x7e83a  as local_50  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1505 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x6];   /* +0x2 pad */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=r types=idx2 */
};
```
