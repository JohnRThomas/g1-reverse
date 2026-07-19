## review group param_0150  (3 cluster(s), kinds=param,stack)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0150
struct_name: stream_flash_ctx | is_library: True | library_name: stream_flash_ctx | is_array: False | confidence: medium
purpose: Zephyr DFU stream_flash streaming context shared by stream_flash_erase_page/flush_buffer/buffered_write
fields:
  0x0  uint8_t *    buf  pointer read as code-like (buf pointer)
  0x4  size_t       buf_len  
  0x8  size_t       bytes_written  
  0xc  off_t        offset  
  0x10  const struct flash_area * fa  
  0x14  size_t       callback_counter  
  0x18  stream_flash_callback_t callback  
  0x1c  uint32_t     bytes_erased  
  0x20  bool         erase_enabled  rw flag

<ground-truth bundle for param_0150>
### cluster param_0150  (param, 3 members, 9 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - stream_flash_erase_page @ 0x4e124  as param_1  [APPLICATION]
  - stream_flash_flush_buffer @ 0x4e1ac  as param_1  [APPLICATION]
  - stream_flash_buffered_write @ 0x7f088  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0150 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4,int,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int */
};
```

### proposal for param_0321
struct_name: cjson_printbuffer | is_library: True | library_name: cJSON printbuffer | is_array: None | confidence: low
purpose: cJSON printbuffer/parse_buffer style growable-buffer context shared by cjson_print_string, cjson_print_value, and a generic cursor/growbuf utility
fields:
  0x0  void*        buffer_or_fn  typed as code by Ghidra — possibly buffer ptr misclassified, or a hook fn ptr
  0x4  size_t       length  rw candidate
  0x8  size_t       offset  rw candidate
  0xc  size_t       depth  rw candidate
  0x10  int32_t      noalloc  
  0x14  int32_t      format  
  0x18  void*        hooks  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  

<ground-truth bundle for param_0321>
### cluster param_0321  (param, 4 members, 9 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/4 members are LIBRARY-class)

members (4 shown of 4):
  - cjson_print_string @ 0x644f8  as param_2  [APPLICATION]
  - cjson_print_value @ 0x646c0  as param_2  [APPLICATION]
  - cursor_advance_past_cstring @ 0x84f16  as param_1  [APPLICATION]
  - growbuf_ensure_capacity @ 0x84f58  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0321 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_0756
struct_name: battery_model_state_locals | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local working buffer in battery_model_state_update holding a sequence of intermediate readings (voltage/current/soc samples) used during battery model computation.
fields:
  0x0  uint32_t     sample_0  
  0x4  uint32_t     sample_1  
  0x8  uint32_t     sample_2  
  0xc  uint32_t     sample_3  
  0x10  uint32_t     sample_4  
  0x14  uint32_t     sample_5  
  0x18  uint32_t     sample_6  
  0x1c  uint32_t     sample_7  
  0x20  uint32_t     sample_8  

<ground-truth bundle for stack_0756>
### cluster stack_0756  (stack, 1 members, 9 fields, size>=0x24)

Stack-frame local local_200 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_200  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0756 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
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
