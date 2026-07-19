### struct dynbuf_t  (G1-original)  cid=param_0750

purpose: G1-original growable byte buffer used by dynbuf_push_byte_grow (data ptr, len, cap).

This object is accessed by these functions (read their fully-named source):
  - dynbuf_push_byte_grow  (as param_2)  ->  recon/readable_sources/app/g1/dynbuf_push_byte_grow.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dynbuf_t {
    uint8_t *    data;  /* +0x34  rw=r sz=4 */
    uint32_t     len;  /* +0x38  rw=r sz=4 */
    uint32_t     cap;  /* +0x44  rw=r sz=4 */
    uint8_t      field_0x45;  /* +0x45  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x46;  /* +0x46  rw=r sz=1 */   <-- NAME ME
};
```