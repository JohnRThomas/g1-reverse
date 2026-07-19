### struct status_byte_packet_ctx  (G1-original)  cid=param_0513

purpose: param_2 of build_status_byte_packet: G1 status-byte packet building context (four words).

This object is accessed by these functions (read their fully-named source):
  - build_status_byte_packet  (as param_2)  ->  recon/readable_sources/app/g1/build_status_byte_packet.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct status_byte_packet_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```