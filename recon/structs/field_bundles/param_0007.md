### struct app_shared_ctx_blob  (G1-original)  cid=param_0007

purpose: Very large (0x1578) object unified across 8 unrelated functions (random, PKCS7 parse, BLE dispatch, notify build, push_message, battery SOC curve init). Almost certainly a mis-merge of several distinct pointer objects, not one real struct.

This object is accessed by these functions (read their fully-named source):
  - random  (as param_2)  ->  recon/readable_sources/app/library/random.c
  - parse_receiver_pack_pkcs7  (as param_2)  ->  recon/readable_sources/app/g1/parse_receiver_pack_pkcs7.c
  - parse_receiver_msg_pack_pkcs7  (as param_2)  ->  recon/readable_sources/app/g1/parse_receiver_msg_pack_pkcs7.c
  - build_status_notify_packet  (as param_2)  ->  recon/readable_sources/app/g1/build_status_notify_packet.c
  - ble_process_req_dispatch  (as param_3)  ->  recon/readable_sources/app/g1/ble_process_req_dispatch.c
  - post_notification_cmd_process  (as param_3)  ->  recon/readable_sources/app/g1/post_notification_cmd_process.c
  - push_message  (as param_1)  ->  recon/readable_sources/app/g1/push_message.c
  - battery_soc_curve_model_init  (as param_7)  ->  recon/readable_sources/app/g1/battery_soc_curve_model_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct app_shared_ctx_blob {
    uint16_t     field_0x1;  /* +0x1  rw=r sz=1,2 */   <-- NAME ME
    uint8_t      field_0x3;  /* +0x3  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=1,4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=1,4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=1,4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x1b0;  /* +0x1b0  rw=r sz=4 */   <-- NAME ME
    float        soc_curve_pt0;  /* +0x324  rw=r sz=4 */
    float        soc_curve_pt1;  /* +0x328  rw=r sz=4 */
    float        soc_curve_pt2;  /* +0x32c  rw=r sz=4 */
    float        soc_curve_pt3;  /* +0x330  rw=r sz=4 */
    float        soc_curve_pt4;  /* +0x334  rw=r sz=4 */
    float        field_0x514;  /* +0x514  rw=r sz=4 */   <-- NAME ME
    float        field_0x11a8;  /* +0x11a8  rw=r sz=4 */   <-- NAME ME
    float        field_0x11ac;  /* +0x11ac  rw=r sz=4 */   <-- NAME ME
    float        field_0x1388;  /* +0x1388  rw=r sz=4 */   <-- NAME ME
    float        field_0x138c;  /* +0x138c  rw=r sz=4 */   <-- NAME ME
    float        field_0x1390;  /* +0x1390  rw=r sz=4 */   <-- NAME ME
    float        field_0x1394;  /* +0x1394  rw=r sz=4 */   <-- NAME ME
    float        field_0x1570;  /* +0x1570  rw=r sz=4 */   <-- NAME ME
    float        field_0x1574;  /* +0x1574  rw=r sz=4 */   <-- NAME ME
};
```