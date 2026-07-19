## review group param_0117  (1 cluster(s), kinds=param)

### proposal for param_0117
struct_name: panel_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Display panel driver context manipulated by panel_on when powering the LCD panel.
fields:
  0x35c  uint32_t     field_0x35c  write-only, likely panel power/init state
  0x374  uint32_t     field_0x374  read-write status/counter

<ground-truth bundle for param_0117>
### cluster param_0117  (param, 1 members, 2 fields, size>=0x378)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - panel_on @ 0x46dd8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0117 {
    uint8_t    _pad_0x0[0x35c];   /* +0x0 pad */
    uint32_t   field_0x35c;   /* +0x35c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x360[0x14];   /* +0x360 pad */
    uint32_t   field_0x374;   /* +0x374  sz=4 rw=rw types=int,undefined4 */
};
```
