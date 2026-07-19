### struct newlib_FILE  (library:FILE / struct __sFILE)  cid=param_0419

purpose: newlib stdio FILE (__sFILE) stream object initialized by newlib_stdio_init_stream (flags/fd, buffer base/size, and read/write/seek/close function-pointer table).

This object is accessed by these functions (read their fully-named source):
  - newlib_stdio_init_stream  (as param_1)  ->  recon/readable_sources/app/library/newlib_stdio_init_stream.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct newlib_FILE {
    uint16_t     _flags;  /* +0x3  rw=w sz=2 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     _r;  /* +0x8  rw=r sz=4 */
    uint16_t     _file;  /* +0xe  rw=w sz=2 */
    void *       _bf_base;  /* +0x10  rw=r sz=4 */
    uint32_t     _bf_size;  /* +0x14  rw=r sz=4 */
    uint32_t     _lbfsize;  /* +0x18  rw=r sz=4 */
    void *       _cookie;  /* +0x20  rw=r sz=4 */
    void *       _read_fn;  /* +0x24  rw=r sz=4 */
    void *       _write_fn;  /* +0x28  rw=r sz=4 */
    void *       _seek_fn;  /* +0x2c  rw=r sz=4 */
    void *       _close_fn;  /* +0x30  rw=r sz=4 */
    uint32_t     _lock_or_mbstate;  /* +0x64  rw=r sz=4 */
};
```