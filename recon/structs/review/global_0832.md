## review group global_0832  (1 cluster(s), kinds=global)

### proposal for global_0832
struct_name: ancs_queue_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Global state for the ANCS (Apple Notification Center Service) enqueue path, tracking indices into a notification queue/ring buffer.
fields:
  0x10  uint32_t     queue_write_idx  read-only access observed; likely write/enqueue cursor
  0x24  uint32_t     queue_read_idx  read-only access observed; likely read/dequeue cursor or count

<ground-truth bundle for global_0832>
### cluster global_0832  (global, 1 members, 2 fields, size>=0x28)

Global object at fixed address 0x00018c30.

library hint: likely G1-original

members (1 shown of 1):
  - enqueue_ancs @ 0x18bb4  as 0x00018c30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0832 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint8_t    _pad_0x14[0x10];   /* +0x14 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
};
```
