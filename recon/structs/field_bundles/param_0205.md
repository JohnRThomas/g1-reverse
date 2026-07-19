### struct conn_tx_saadc_ctx  (G1-original)  cid=param_0205

purpose: Context shared by conn_tx_send_to_driver and saadc_start_read: header word plus data words; +0x10 accessed both as a word and as a byte.

This object is accessed by these functions (read their fully-named source):
  - conn_tx_send_to_driver  (as param_2)  ->  recon/readable_sources/app/g1/conn_tx_send_to_driver.c
  - saadc_start_read  (as param_2)  ->  recon/readable_sources/app/g1/saadc_start_read.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct conn_tx_saadc_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=1,4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x11;  /* +0x11  rw=r sz=1 */   <-- NAME ME
};
```