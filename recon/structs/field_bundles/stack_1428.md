### struct vsprintf_fmt_state_tmp  (G1-original)  cid=stack_1428

purpose: Stack-local 32-bit pair (local_70) inside vsprintf_impl (format width/precision or arg pointer/count).

This object is accessed by these functions (read their fully-named source):
  - vsprintf_impl  (as local_70)  ->  recon/readable_sources/app/library/vsprintf_impl.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct vsprintf_fmt_state_tmp {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```