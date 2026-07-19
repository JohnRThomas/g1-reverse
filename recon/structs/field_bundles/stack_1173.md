### struct hci_static_addr_locals  (G1-original)  cid=stack_1173

purpose: Local buffer holding an HCI static-address response record in hci_read_static_addresses (local_34).

This object is accessed by these functions (read their fully-named source):
  - hci_read_static_addresses  (as local_34)  ->  recon/readable_sources/app/g1/hci_read_static_addresses.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct hci_static_addr_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```