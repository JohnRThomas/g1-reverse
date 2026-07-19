## review group global_1189  (1 cluster(s), kinds=global)

### proposal for global_1189
struct_name: bt_conn_auth_info_cb_reg | is_library: True | library_name: bt_conn_auth_info_cb | is_array: None | confidence: low
purpose: Static registration node for a Zephyr Bluetooth connection auth-info callback set (bt_conn_auth_info_cb_register argument), holding a callback/list-node pair.
fields:
  0x0  void *       cb_or_field0  function pointer or first cb slot
  0x4  void *       node_next  sys_snode_t linked-list link, idx4 access pattern

<ground-truth bundle for global_1189>
### cluster global_1189  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x00057354.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_conn_auth_info_cb_register @ 0x57330  as 0x00057354  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1189 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
