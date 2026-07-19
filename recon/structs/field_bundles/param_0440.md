### struct mbedtls_entropy_context  (library:mbedtls_entropy_context)  cid=param_0440

purpose: mbed TLS entropy context used by entropy gather and cc_mbedtls_entropy_func (source_count, mutex/ctx ptr, accumulator words).

This object is accessed by these functions (read their fully-named source):
  - entropy_gather_internal_part_0  (as param_1)  [no source file]
  - cc_mbedtls_entropy_func  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct mbedtls_entropy_context {
    uint32_t     source_count;  /* +0xf8  rw=r sz=4 */
    void*        mutex_or_ctx;  /* +0xfc  rw=r sz=4 */
    uint32_t     field_0x100;  /* +0x100  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x104;  /* +0x104  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x108;  /* +0x108  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10c;  /* +0x10c  rw=r sz=4 */   <-- NAME ME
};
```