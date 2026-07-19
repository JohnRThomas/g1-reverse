### struct zcbor_state_t  (library:zcbor_state_t)  cid=param_0174

purpose: zcbor encoder state shared by smp_add_cmd_err and the cbor_encode_*/zcbor_bstr_encode helpers: payload cursor/end plus error/length fields.

This object is accessed by these functions (read their fully-named source):
  - smp_add_cmd_err  (as param_1)  ->  recon/readable_sources/app/library/smp_add_cmd_err.c
  - cbor_encode_set_error  (as param_1)  ->  recon/readable_sources/app/library/cbor_encode_set_error.c
  - cbor_encode_put_type_byte  (as param_1)  ->  recon/readable_sources/app/library/cbor_encode_put_type_byte.c
  - cbor_encode_length_header  (as param_1)  ->  recon/readable_sources/app/library/cbor_encode_length_header.c
  - zcbor_bstr_encode  (as param_1)  ->  recon/readable_sources/app/library/zcbor_bstr_encode.c
  - cbor_encode_bstr  (as param_1)  ->  recon/readable_sources/app/library/cbor_encode_bstr.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct zcbor_state_t {
    uint8_t*     payload;  /* +0x8  rw=r sz=4 */
    uint8_t*     payload_end;  /* +0xc  rw=r sz=4 */
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x30;  /* +0x30  rw=w sz=2 */   <-- NAME ME
    uint16_t     field_0x32;  /* +0x32  rw=w sz=2 */   <-- NAME ME
};
```