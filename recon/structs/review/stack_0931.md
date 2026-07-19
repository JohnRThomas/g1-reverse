## review group stack_0931  (1 cluster(s), kinds=stack)

### proposal for stack_0931
struct_name: audio_stream_cache_flags | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small local flag pair in sendAudioStram2Cache controlling audio-stream-to-cache buffering
fields:
  0x0  uint8_t      cache_flag0  
  0x2  uint8_t      cache_flag1  

<ground-truth bundle for stack_0931>
### cluster stack_0931  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_dc in sendAudioStram2Cache (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - sendAudioStram2Cache @ 0x2f6b0  as local_dc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0931 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
