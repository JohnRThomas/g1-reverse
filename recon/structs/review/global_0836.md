## review group global_0836  (1 cluster(s), kinds=global)

### proposal for global_0836
struct_name: uid_enqueue_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state object read by enqueue_uid, holding a counter/id and a secondary index separated by 0x10 bytes of unused/opaque data.
fields:
  0x10  uint32_t     field_0x10  read-only int, possibly next-uid or queue depth
  0x24  uint32_t     field_0x24  read-only int, possibly tail index or checksum

<ground-truth bundle for global_0836>
### cluster global_0836  (global, 1 members, 2 fields, size>=0x28)

Global object at fixed address 0x00018ed8.

library hint: likely G1-original

members (1 shown of 1):
  - enqueue_uid @ 0x18e48  as 0x00018ed8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0836 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint8_t    _pad_0x14[0x10];   /* +0x14 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
};
```
