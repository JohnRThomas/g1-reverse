### struct gatt_find_by_type_rsp_locals  (G1-original)  cid=stack_1232

purpose: Stack-local scratch in gatt_parse_find_by_type_rsp holding a start/end handle byte pair.

This object is accessed by these functions (read their fully-named source):
  - gatt_parse_find_by_type_rsp  (as local_5c)  ->  recon/readable_sources/app/library/gatt_parse_find_by_type_rsp.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_find_by_type_rsp_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```