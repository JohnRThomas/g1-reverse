## review group global_1075  (1 cluster(s), kinds=global)

### proposal for global_1075
struct_name: gatt_dm_attr_pool | is_library: True | library_name: bt_gatt_dm_attr (internal, Nordic GATT DM library) | is_array: False | confidence: low
purpose: Global buffer/pool used by gatt_dm_attr_alloc to allocate bt_gatt_dm discovery attribute records.
fields:
  0x150  uint32_t     pool_count  count/index near end of large pool region
  0x154  void*        pool_free_list  pointer, likely free-list head
  0x158  int32_t      pool_status  status/error code

<ground-truth bundle for global_1075>
### cluster global_1075  (global, 1 members, 3 fields, size>=0x15c)

Global object at fixed address 0x0004e960.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_dm_attr_alloc @ 0x4e8e8  as 0x0004e960  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1075 {
    uint8_t    _pad_0x0[0x150];   /* +0x0 pad */
    uint32_t   field_0x150;   /* +0x150  sz=4 rw=r types=uint */
    void *     field_0x154;   /* +0x154  sz=4 rw=r types=ptr */
    uint32_t   field_0x158;   /* +0x158  sz=4 rw=r types=int */
};
```
