## review group stack_0934  (1 cluster(s), kinds=stack)

### proposal for stack_0934
struct_name: audio_stream_record_params | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local stack struct in startAudioStreamRecord holding two 16-bit audio parameters (e.g. sample rate/channel count)
fields:
  0x0  uint16_t     field_0x0  
  0x4  uint16_t     field_0x4  

<ground-truth bundle for stack_0934>
### cluster stack_0934  (stack, 1 members, 2 fields, size>=0x6)

Stack-frame local local_d8 in startAudioStreamRecord (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - startAudioStreamRecord @ 0x2f764  as local_d8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0934 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=idx2 */
};
```
