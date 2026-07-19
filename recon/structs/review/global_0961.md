## review group global_0961  (1 cluster(s), kinds=global)

### proposal for global_0961
struct_name: pt_data_indices | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Two index/count fields read by process_pt_data; likely selects a lookup entry (index + secondary index) for point/track data processing.
fields:
  0x4  uint32_t     index_a  read as idx4
  0x8  uint32_t     index_b  read as idx4

<ground-truth bundle for global_0961>
### cluster global_0961  (global, 1 members, 2 fields, size>=0xc)

Global object at fixed address 0x000332a4.

library hint: likely G1-original

members (1 shown of 1):
  - process_pt_data @ 0x330ec  as 0x000332a4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0961 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
