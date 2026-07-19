### struct gatt_rbt_rsp_cursor  (G1-original)  cid=stack_1237

purpose: Stack-local parse cursor (local_4c) in gatt_parse_read_by_type_rsp_128 (type-length byte + following byte).

This object is accessed by these functions (read their fully-named source):
  - gatt_parse_read_by_type_rsp_128  (as local_4c)  ->  recon/readable_sources/app/library/gatt_parse_read_by_type_rsp_128.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_rbt_rsp_cursor {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```