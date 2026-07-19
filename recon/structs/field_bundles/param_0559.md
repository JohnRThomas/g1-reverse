### struct smp_transport_reassembly  (library:smp_transport)  cid=param_0559

purpose: MCUmgr SMP transport object; smp_reassembly_expected reads the expected-length field of its embedded reassembly state.

This object is accessed by these functions (read their fully-named source):
  - smp_reassembly_expected  (as param_1)  ->  recon/readable_sources/app/library/smp_reassembly_expected.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_transport_reassembly {
    uint32_t     reassembly_expected;  /* +0x40  rw=r sz=4 */
    uint16_t     field_0x44;  /* +0x44  rw=r sz=2 */   <-- NAME ME
};
```