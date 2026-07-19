## review group param_0398  (1 cluster(s), kinds=param)

### proposal for param_0398
struct_name: audio_sync_ringbuf | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: G1-original audio sync ring-buffer with write/read cursor fields, queried by sync_buffer_available_space
fields:
  0x94  uint32_t     write_idx  r
  0xa0  uint32_t     read_idx  r

<ground-truth bundle for param_0398>
### cluster param_0398  (param, 1 members, 2 fields, size>=0xa4)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - sync_buffer_available_space @ 0x71314  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0398 {
    uint8_t    _pad_0x0[0x94];   /* +0x0 pad */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=r types=int */
    uint8_t    _pad_0x98[0x8];   /* +0x98 pad */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=r types=int */
};
```
