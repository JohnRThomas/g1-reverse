### struct cc_trng_state  (library:CryptoCell RND/TRNG state (opaque))  cid=global_1465

purpose: CryptoCell/Oberon TRNG source state object (0x7a9ac) accessed by getTrngSource; large opaque region with two trailing status/count words.

This object is accessed by these functions (read their fully-named source):
  - getTrngSource  (as 0x0007a9ac)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cc_trng_state {
    uint32_t     field_0x130;  /* +0x130  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x138;  /* +0x138  rw=r sz=4 */   <-- NAME ME
};
```