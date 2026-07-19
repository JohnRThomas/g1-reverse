## review group global_0965  (5 cluster(s), kinds=global,param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_0965
struct_name: ble_chunk_send_table | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Fixed lookup/index table of uint32 parameters consumed by send_data_in_ble_chunks (chunk size/offset table for splitting outbound BLE payloads)
fields:
  0x4  uint32_t     field_0x4  idx4 read
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  

<ground-truth bundle for global_0965>
### cluster global_0965  (global, 1 members, 8 fields, size>=0x24)

Global object at fixed address 0x000338dc.

library hint: likely G1-original

members (1 shown of 1):
  - send_data_in_ble_chunks @ 0x3384c  as 0x000338dc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0965 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```

### proposal for global_1019
struct_name: scroll_text_frame_idx_table | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Fixed global table of index/offset values used when rendering scrolling text frames on the display
fields:
  0x4  uint32_t     idx_0  uniform 4-byte stride idx4 entries, likely an array element
  0x8  uint32_t     idx_1  
  0xc  uint32_t     idx_2  
  0x10  uint32_t     idx_3  
  0x14  uint32_t     idx_4  
  0x18  uint32_t     idx_5  
  0x1c  uint32_t     idx_6  
  0x20  uint32_t     idx_7  

<ground-truth bundle for global_1019>
### cluster global_1019  (global, 1 members, 8 fields, size>=0x24)

Global object at fixed address 0x000442b4.

library hint: likely G1-original

members (1 shown of 1):
  - ui_render_scroll_text_frame @ 0x440ec  as 0x000442b4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1019 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```

### proposal for global_1020
struct_name: scroll_text_render_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global render state/index table used by ui_render_scroll_text_frame for scroll text UI drawing
fields:
  0x4  uint32_t     field_0x4  idx-like read-only field, part of index table
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  

<ground-truth bundle for global_1020>
### cluster global_1020  (global, 1 members, 8 fields, size>=0x24)

Global object at fixed address 0x000442b8.

library hint: likely G1-original

members (1 shown of 1):
  - ui_render_scroll_text_frame @ 0x440ec  as 0x000442b8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1020 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0054
struct_name: ndef_record_build_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Context/parameter block for building and writing ST25DV NDEF records over NFC
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  

<ground-truth bundle for param_0054>
### cluster param_0054  (param, 1 members, 8 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - st25dv_build_and_write_ndef_records @ 0x250f8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0054 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0151
struct_name: stream_flash_ctx | is_library: True | library_name: stream_flash_ctx | is_array: None | confidence: medium
purpose: Stream-flash (DFU streaming write) context initialized by stream_flash_init, holding flash device/offset/buffer metadata
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  

<ground-truth bundle for param_0151>
### cluster param_0151  (param, 1 members, 8 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - stream_flash_init @ 0x4e2b4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0151 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```
