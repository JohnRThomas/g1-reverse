### struct storage_erase_range_tmp  (G1-original)  cid=stack_1131

purpose: Stack local (local_2c) in storage_erase_handler: erase range (address/size style pair).

This object is accessed by these functions (read their fully-named source):
  - storage_erase_handler  (as local_2c)  ->  recon/readable_sources/app/g1/storage_erase_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct storage_erase_range_tmp {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```