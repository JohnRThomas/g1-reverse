### struct vfprintf_scan_ctx  (G1-original)  cid=param_0432

purpose: Format-field scanning context used by vfprintf_field_scan_match (param_2): output function pointer, a run of index fields, and a trailing flag near 0x180.

This object is accessed by these functions (read their fully-named source):
  - vfprintf_field_scan_match  (as param_2)  ->  recon/readable_sources/app/library/vfprintf_field_scan_match.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct vfprintf_scan_ctx {
    void*        out_fn;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     tail_flag;  /* +0x180  rw=r sz=4 */
};
```