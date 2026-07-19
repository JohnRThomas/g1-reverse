### struct conn_tx_ctx  (G1-original)  cid=param_0206

purpose: Connection TX driver-submission context used by conn_tx_send_to_driver (BLE controller TX path): a short field and a buffer/callback pointer.

This object is accessed by these functions (read their fully-named source):
  - conn_tx_send_to_driver  (as param_3)  ->  recon/readable_sources/app/g1/conn_tx_send_to_driver.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct conn_tx_ctx {
    uint16_t     field_0x10;  /* +0x10  rw=r sz=2 */   <-- NAME ME
    void *       field_0x18;  /* +0x18  rw=rw sz=1,4 */   <-- NAME ME
};
```