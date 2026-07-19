### struct smp_pkt_ctx  (library:net_buf)  cid=param_0173

purpose: MCUmgr SMP request-packet processing context (length/data pair) passed to smp_process_request_packet.

This object is accessed by these functions (read their fully-named source):
  - smp_process_request_packet  (as param_1)  ->  recon/readable_sources/app/library/smp_process_request_packet.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_pkt_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```