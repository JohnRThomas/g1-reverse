## review group param_0601  (1 cluster(s), kinds=param)

### proposal for param_0601
struct_name: att_notify_mult_ctx | is_library: True | library_name: bt_att (notify_mult params) | is_array: None | confidence: low
purpose: Zephyr BLE ATT notify-multiple internal parameter block (buffer/length pair)
fields:
  0xc  uint32_t     data_len  
  0x10  uint16_t     handle_or_count  

<ground-truth bundle for param_0601>
### cluster param_0601  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_notify_mult @ 0x81bf0  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0601 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
