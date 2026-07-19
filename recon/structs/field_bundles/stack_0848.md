### struct ble_get_req_hdr_tmp  (G1-original)  cid=stack_0848

purpose: Stack-local parsed header bytes (local_1fa) in ble_process_get_req (command/sub-id + later flag byte).

This object is accessed by these functions (read their fully-named source):
  - ble_process_get_req  (as local_1fa)  ->  recon/readable_sources/app/g1/ble_process_get_req.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_get_req_hdr_tmp {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x1;  /* +0x1  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x6;  /* +0x6  rw=r sz=1 */   <-- NAME ME
};
```