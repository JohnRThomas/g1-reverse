### struct flash_boot_swap_ate  (G1-original)  cid=param_0320

purpose: Flash boot-swap allocation-table entry read by flash_read_boot_swap_ate.

This object is accessed by these functions (read their fully-named source):
  - flash_read_boot_swap_ate  (as param_2)  ->  recon/readable_sources/app/g1/flash_read_boot_swap_ate.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct flash_boot_swap_ate {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```