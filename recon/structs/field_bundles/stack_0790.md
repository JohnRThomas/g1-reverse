### struct hci_vs_init_locals  (G1-original)  cid=stack_0790

purpose: Stack-local temporaries in hci_vs_init used to build a Bluetooth HCI vendor-specific command.

This object is accessed by these functions (read their fully-named source):
  - hci_vs_init  (as local_30)  ->  recon/readable_sources/app/g1/hci_vs_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct hci_vs_init_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```