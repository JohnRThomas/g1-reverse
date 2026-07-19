### struct libc_FILE  (library:FILE (picolibc/newlib _sFILE))  cid=param_0418

purpose: C library FILE stream object used by _fflush_r/smakebuf_r/_vfprintf_r/libc_putc_buffered: buffer pointers, cookie, and flags.

This object is accessed by these functions (read their fully-named source):
  - _fflush_r  (as param_1)  ->  recon/readable_sources/app/library/_fflush_r.c
  - smakebuf_r  (as param_1)  ->  recon/readable_sources/app/library/smakebuf_r.c
  - _vfprintf_r  (as param_1)  ->  recon/readable_sources/app/library/_vfprintf_r.c
  - libc_putc_buffered  (as param_1)  ->  recon/readable_sources/app/library/libc_putc_buffered.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct libc_FILE {
    unsigned char* _p;  /* +0x4  rw=r sz=4 */
    unsigned char* _base;  /* +0x8  rw=r sz=4 */
    void*        _cookie;  /* +0xc  rw=r sz=4 */
    int32_t      _flags;  /* +0x18  rw=r sz=4 */
    uint32_t     field_0x28;  /* +0x28  rw=w sz=4 */   <-- NAME ME
};
```