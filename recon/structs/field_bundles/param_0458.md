### struct opt_node_header  (G1-original)  cid=param_0458

purpose: Small header read by opt_node_header_len: two size/length words.

This object is accessed by these functions (read their fully-named source):
  - opt_node_header_len  (as param_1)  ->  recon/readable_sources/app/g1/opt_node_header_len.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct opt_node_header {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```