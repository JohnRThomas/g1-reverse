### struct ble_privacy_id_state  (G1-original)  cid=global_1168

purpose: Global BLE privacy identity state (0x551dc) touched by ble_privacy_id_remove; two adjacent status bytes near +0x120.

This object is accessed by these functions (read their fully-named source):
  - ble_privacy_id_remove  (as 0x000551dc)  ->  recon/readable_sources/app/g1/ble_privacy_id_remove.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_privacy_id_state {
    uint8_t      field_0x120;  /* +0x120  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x121;  /* +0x121  rw=rw sz=1 */   <-- NAME ME
};
```