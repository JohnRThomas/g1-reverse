## review group param_0118  (1 cluster(s), kinds=param)

### proposal for param_0118
struct_name: jdb_panel_cfg | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Display panel configuration/init object for jdb_panel_init, holding an init flag, a mode byte, and a status word
fields:
  0x35c  uint32_t     panel_init_flag  written during init
  0x369  uint8_t      panel_mode  read byte
  0x374  int32_t      panel_status  written during init

<ground-truth bundle for param_0118>
### cluster param_0118  (param, 1 members, 3 fields, size>=0x378)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - jdb_panel_init @ 0x46fc0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0118 {
    uint8_t    _pad_0x0[0x35c];   /* +0x0 pad */
    uint32_t   field_0x35c;   /* +0x35c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x360[0x9];   /* +0x360 pad */
    uint8_t    field_0x369;   /* +0x369  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x36a[0xa];   /* +0x36a pad */
    uint32_t   field_0x374;   /* +0x374  sz=4 rw=w types=int */
};
```
