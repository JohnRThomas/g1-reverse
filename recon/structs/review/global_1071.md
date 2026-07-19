## review group global_1071  (1 cluster(s), kinds=global)

### proposal for global_1071
struct_name: settings_handler_static | is_library: True | library_name: settings_handler_static | is_array: None | confidence: medium
purpose: Zephyr settings-subsystem handler descriptor object registered via settings_src_register (subsystem entry name + registration bookkeeping).
fields:
  0x0  void *       node_next  sys_snode_t linked-list next pointer (settings handler list)
  0x4  const char * name  handler subtree name pointer, read as idx4

<ground-truth bundle for global_1071>
### cluster global_1071  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x0004e3d8.

library hint: LIKELY LIBRARY (prefixes: settings; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - settings_src_register @ 0x4e3c0  as 0x0004e3d8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1071 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
