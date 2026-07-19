## review group param_0102  (1 cluster(s), kinds=param)

### proposal for param_0102
struct_name: whitelist_chunk_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small write-only byte pair used by send_whitelist_json_chunked to track chunk-transmission state (e.g. chunk index / terminator flag).
fields:
  0x1  uint8_t      chunk_flag  
  0x2  uint8_t      terminator  

<ground-truth bundle for param_0102>
### cluster param_0102  (param, 1 members, 2 fields, size>=0x3)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - send_whitelist_json_chunked @ 0x35498  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0102 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=w types=char,undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=w types=char */
};
```
