### struct scanf_field_parse_ctx  (G1-original)  cid=global_1431

purpose: G1-original global scratch context holding parse parameters (base/width) for scanf_convert_integer_field.

This object is accessed by these functions (read their fully-named source):
  - scanf_convert_integer_field  (as 0x00079518)  ->  recon/readable_sources/app/g1/scanf_convert_integer_field.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct scanf_field_parse_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```