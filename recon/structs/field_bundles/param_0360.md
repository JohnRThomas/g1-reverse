### struct metal_device_region_view  (library:metal_device)  cid=param_0360

purpose: param_1 of metal_register_generic_device (libmetal): region/attribute block within struct metal_device (four consecutive words).

This object is accessed by these functions (read their fully-named source):
  - metal_register_generic_device  (as param_1)  ->  recon/readable_sources/app/library/metal_register_generic_device.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct metal_device_region_view {
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
};
```