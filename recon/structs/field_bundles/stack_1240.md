### struct gatt_find_info_elem  (library:ATT find-info-rsp element (host internal))  cid=stack_1240

purpose: Stack-local ATT Find-Information-Response element in gatt_parse_find_info_rsp: a handle/format byte and a following type byte.

This object is accessed by these functions (read their fully-named source):
  - gatt_parse_find_info_rsp  (as local_58)  ->  recon/readable_sources/app/library/gatt_parse_find_info_rsp.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_find_info_elem {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```