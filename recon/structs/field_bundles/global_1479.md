### struct hash_drv_context  (library:CryptoCell (cc3xx) hash driver context)  cid=global_1479

purpose: Large (0xb10-byte) CryptoCell hash-driver context/state global manipulated by ProcessHashDrv: scattered status/length scalars around a big internal buffer.

This object is accessed by these functions (read their fully-named source):
  - ProcessHashDrv  (as 0x0007b3d8)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct hash_drv_context {
    int32_t      status;  /* +0x650  rw=rw sz=4 */
    int32_t      field_0x65c;  /* +0x65c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x7c8;  /* +0x7c8  rw=w sz=4 */   <-- NAME ME
    int32_t      field_0x7cc;  /* +0x7cc  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x910;  /* +0x910  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xb0c;  /* +0xb0c  rw=w sz=4 */   <-- NAME ME
};
```