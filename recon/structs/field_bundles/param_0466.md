### struct opt_record  (G1-original)  cid=param_0466

purpose: Option record value-binding structure passed to opt_record_bind_value (param_2).

This object is accessed by these functions (read their fully-named source):
  - opt_record_bind_value  (as param_2)  ->  recon/readable_sources/app/g1/opt_record_bind_value.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct opt_record {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```