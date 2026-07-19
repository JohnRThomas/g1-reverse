## review group global_0793  (1 cluster(s), kinds=global)

### proposal for global_0793
struct_name: dtoa_r_scratch | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Fixed global scratch/workspace object used by the double-to-ASCII (dtoa_r) conversion routine; trailing words look like array index/length counters into an internal digit buffer.
fields:
  0x20  uint32_t     digit_index  read as array index (idx4) into dtoa digit buffer
  0x24  uint32_t     digit_count  read as array index/length (idx4)

<ground-truth bundle for global_0793>
### cluster global_0793  (global, 1 members, 2 fields, size>=0x28)

Global object at fixed address 0x00015100.

library hint: likely G1-original

members (1 shown of 1):
  - dtoa_r @ 0x14b60  as 0x00015100  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0793 {
    uint8_t    _pad_0x0[0x20];   /* +0x0 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
};
```
