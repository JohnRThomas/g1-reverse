### struct cbor_decoder_state  (library:CborValue / zcbor state)  cid=param_0715

purpose: CBOR decoder cursor/state object checked by cbor_decoder_at_end for end-of-buffer: remaining-bytes word and a type/flags byte.

This object is accessed by these functions (read their fully-named source):
  - cbor_decoder_at_end  (as param_1)  ->  recon/readable_sources/app/g1/cbor_decoder_at_end.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cbor_decoder_state {
    uint32_t     remaining;  /* +0xc  rw=r sz=4 */
    uint8_t      field_0x10;  /* +0x10  rw=r sz=1 */   <-- NAME ME
};
```