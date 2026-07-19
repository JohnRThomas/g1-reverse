## review group stack_1538  (1 cluster(s), kinds=stack)

### proposal for stack_1538
struct_name: smp_c1_locals | is_library: True | library_name: bt_smp c1 locals | is_array: True | confidence: low
purpose: Zephyr BT SMP 'c1' confirm-value computation local bytes (p1/p2 preauthentication buffer bytes) inside smp_c1.
fields:
  0x0  uint8_t      byte_0  read-only
  0x1  uint8_t      byte_1  read-only
  0x2  uint8_t      byte_2  read-only

<ground-truth bundle for stack_1538>
### cluster stack_1538  (stack, 1 members, 3 fields, size>=0x3)

Stack-frame local local_38 in smp_c1 (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_c1 @ 0x8323a  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1538 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
