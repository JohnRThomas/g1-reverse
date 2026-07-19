## review group global_1218  (1 cluster(s), kinds=global)

### proposal for global_1218
struct_name: bt_gatt_cb | is_library: True | library_name: bt_gatt_cb | is_array: None | confidence: medium
purpose: Zephyr Bluetooth GATT registered-callback node (bt_gatt_cb_register linked-list entry)
fields:
  0x0  struct bt_gatt_cb * _node  sys_slist_t / next pointer (list node)
  0x4  void *       att_mtu_updated  callback function pointer, offset differs across zephyr versions

<ground-truth bundle for global_1218>
### cluster global_1218  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x0005a9f0.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_gatt_cb_register @ 0x5a9d8  as 0x0005a9f0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1218 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
