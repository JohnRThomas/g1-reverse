### struct scanf_convert_ctx  (G1-original)  cid=param_0433

purpose: scanf integer-field conversion context/state for scanf_convert_integer_field: a callback/vtable word, several counters, and two trailer words.

This object is accessed by these functions (read their fully-named source):
  - scanf_convert_integer_field  (as param_2)  ->  recon/readable_sources/app/g1/scanf_convert_integer_field.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct scanf_convert_ctx {
    void*        callback_or_vtable;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x17c;  /* +0x17c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x180;  /* +0x180  rw=r sz=4 */   <-- NAME ME
};
```