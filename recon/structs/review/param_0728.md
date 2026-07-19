## review group param_0728  (5 cluster(s), kinds=param,stack)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0728
struct_name: kmutex_dlist_node | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Kernel mutex/doubly-linked-list node initialized by kmutex_dlist_init: link pointers plus lock-count/owner fields.
fields:
  0x0  void *       next  write-only, dlist next pointer
  0x4  void *       prev  write-only, dlist prev pointer
  0x8  uint32_t     lock_count  write-only
  0xc  uint32_t     owner  write-only

<ground-truth bundle for param_0728>
### cluster param_0728  (param, 1 members, 4 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - kmutex_dlist_init @ 0x864c2  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0728 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
};
```

### proposal for stack_0980
struct_name: device_info_float_layout | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local layout/coordinate record of four uint32 words used by render_device_info_float_screen (likely x/y/w/h or similar screen-position values, mistyped as idx4 by the extractor).
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for stack_0980>
### cluster stack_0980  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local local_2c in render_device_info_float_screen (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - render_device_info_float_screen @ 0x361d8  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0980 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1074
struct_name: nvs_fs_local | is_library: True | library_name: struct nvs_fs (partial local copy, exact field mapping unresolved) | is_array: None | confidence: low
purpose: Local 16-byte, four-word filesystem state (offset/sector bookkeeping) built while mounting the settings NVS backend.
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for stack_1074>
### cluster stack_1074  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local local_20 in settings_nvs_backend_mount (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: settings; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - settings_nvs_backend_mount @ 0x4e83c  as local_20  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1074 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1128
struct_name: img_mgmt_upload_local | is_library: True | library_name: img_mgmt_upload_action | is_array: None | confidence: low
purpose: Local stack struct in img_mgmt_upload holding four 32-bit upload state fields (offset/size/len/flags)
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for stack_1128>
### cluster stack_1128  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local local_d4 in img_mgmt_upload (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - img_mgmt_upload @ 0x521fc  as local_d4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1128 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```

### proposal for stack_1560
struct_name: flash_padded_entry_buf | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: Local 16-byte stack buffer in flash_write_padded_entry used to assemble a padded flash entry (e.g. NVS/settings record) before writing.
fields:
  0x0  uint32_t     word_0  
  0x4  uint32_t     word_1  
  0x8  uint32_t     word_2  
  0xc  uint32_t     word_3  

<ground-truth bundle for stack_1560>
### cluster stack_1560  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local auStack_28 in flash_write_padded_entry (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - flash_write_padded_entry @ 0x84dea  as auStack_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1560 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
