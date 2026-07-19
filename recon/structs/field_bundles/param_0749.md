### struct FILE  (library:FILE (__file))  cid=param_0749

purpose: picolibc/newlib FILE stream whose ungetc buffer is reset by stdio_reset_ungetc_buffer.

This object is accessed by these functions (read their fully-named source):
  - stdio_reset_ungetc_buffer  (as param_2)  ->  recon/readable_sources/app/library/stdio_reset_ungetc_buffer.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct FILE {
    uint16_t     flags;  /* +0x3  rw=rw sz=2 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    void *       read_ptr;  /* +0x10  rw=r sz=4 */
    uint32_t     field_0x34;  /* +0x34  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x3c;  /* +0x3c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x40;  /* +0x40  rw=r sz=4 */   <-- NAME ME
};
```