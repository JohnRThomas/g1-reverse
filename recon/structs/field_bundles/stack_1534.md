### struct ble_appearance_rsp  (G1-original)  cid=stack_1534

purpose: Local response buffer in read_appearance (local_12): a 16-bit appearance value and a second halfword.

This object is accessed by these functions (read their fully-named source):
  - read_appearance  (as local_12)  ->  recon/readable_sources/app/g1/read_appearance.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_appearance_rsp {
    uint16_t     appearance;  /* +0x0  rw=r sz=2 */
    uint16_t     field_0x6;  /* +0x6  rw=r sz=2 */   <-- NAME ME
};
```