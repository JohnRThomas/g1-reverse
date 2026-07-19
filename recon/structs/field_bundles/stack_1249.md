### struct smp_pairing_req_local  (library:bt_smp_pairing)  cid=stack_1249

purpose: Stack local (local_38) in smp_pairing_req: partial view of an SMP pairing-request PDU (io_capability byte at 0, key-distribution/reserved word at 0x10).

This object is accessed by these functions (read their fully-named source):
  - smp_pairing_req  (as local_38)  ->  recon/readable_sources/app/library/smp_pairing_req.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_pairing_req_local {
    uint8_t      io_capability;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```