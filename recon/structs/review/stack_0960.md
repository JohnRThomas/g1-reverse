## review group stack_0960  (1 cluster(s), kinds=stack)

### proposal for stack_0960
struct_name: pt_data_pair | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local pair of related values (id/value) read in process_pt_data.
fields:
  0x0  int32_t      pt_id  first local value
  0x8  int32_t      pt_value  second local value

<ground-truth bundle for stack_0960>
### cluster stack_0960  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_1c in process_pt_data (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - process_pt_data @ 0x330ec  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0960 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
