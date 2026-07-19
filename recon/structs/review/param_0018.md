## review group param_0018  (1 cluster(s), kinds=param)

### proposal for param_0018
struct_name: g1_ui_box_state | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: UI 'box' element state used across box presence/animation/config-default functions: presence/visibility flags, config bytes, and an animation step value.
fields:
  0x1  uint8_t      presence_flag  
  0x2  uint8_t      box_flags  
  0x5  uint8_t      config_byte_5  
  0x7  uint8_t      config_byte_7  
  0xb  uint8_t      config_byte_b  
  0xc  uint8_t      config_byte_c  
  0x13  uint8_t      status_byte  
  0x30  uint16_t     animation_step  

<ground-truth bundle for param_0018>
### cluster param_0018  (param, 3 members, 8 fields, size>=0x32)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - update_box_presence_flag @ 0x254a0  as param_1  [APPLICATION]
  - init_config_fields_default9 @ 0x7c3c2  as param_1  [APPLICATION]
  - box_placement_animation_step @ 0xfcf0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0018 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=rw types=char,undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x3[0x2];   /* +0x3 pad */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=rw types=undefined1 */
    uint8_t    _pad_0x6[0x1];   /* +0x6 pad */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x8[0x3];   /* +0x8 pad */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=rw types=byte,char,undefined1 */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xd[0x6];   /* +0xd pad */
    uint8_t    field_0x13;   /* +0x13  sz=1 rw=r types=byte */
    uint8_t    _pad_0x14[0x1c];   /* +0x14 pad */
    uint16_t   field_0x30;   /* +0x30  sz=2 rw=w types=undefined2 */
};
```
