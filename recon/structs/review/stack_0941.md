## review group stack_0941  (1 cluster(s), kinds=stack)

### proposal for stack_0941
struct_name: audio_stream_file_locals | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local scratch struct/buffer in audioStreamFileManagerHandler; likely a filename or path buffer with a leading type byte and trailing terminator byte.
fields:
  0x0  uint8_t      first_byte  
  0xcc  uint8_t      last_byte  

<ground-truth bundle for stack_0941>
### cluster stack_0941  (stack, 1 members, 2 fields, size>=0xcd)

Stack-frame local local_f0 in audioStreamFileManagerHandler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - audioStreamFileManagerHandler @ 0x2f94c  as local_f0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0941 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xcb];   /* +0x1 pad */
    uint8_t    field_0xcc;   /* +0xcc  sz=1 rw=r types=idx1 */
};
```
