## review group param_0123  (1 cluster(s), kinds=param)

### proposal for param_0123
struct_name: display_thread_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Large (>=0xb84) shared context passed to ui_refalsh_warp and display_thread_handler; holds display/UI thread state including flags and a trailing pointer, likely frame buffer or queue handle.
fields:
  0x1  uint8_t      field_0x1  flag/mode byte
  0xd5  uint8_t      field_0xd5  flag/status byte
  0xb80  void *       field_0xb80  trailing pointer, e.g. buffer/queue handle

<ground-truth bundle for param_0123>
### cluster param_0123  (param, 2 members, 3 fields, size>=0xb84)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - ui_refalsh_warp @ 0x48b5c  as param_1  [APPLICATION]
  - display_thread_handler @ 0x49090  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0123 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=char */
    uint8_t    _pad_0x2[0xd3];   /* +0x2 pad */
    uint8_t    field_0xd5;   /* +0xd5  sz=1 rw=r types=byte,char,undefined1 */
    uint8_t    _pad_0xd6[0xaaa];   /* +0xd6 pad */
    void *     field_0xb80;   /* +0xb80  sz=4 rw=r types=ptr */
};
```
