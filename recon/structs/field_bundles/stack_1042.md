### struct proxy_thread_locals  (G1-original)  cid=stack_1042

purpose: Stack-local struct in proxy_thread_handler holding two state/flag bytes.

This object is accessed by these functions (read their fully-named source):
  - proxy_thread_handler  (as local_40)  ->  recon/readable_sources/app/g1/proxy_thread_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct proxy_thread_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```