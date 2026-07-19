### struct device_settings_blob  (G1-original)  cid=param_0042

purpose: Large shared settings/status blob (>=0x1078 bytes) read by load_sys_setting and build_and_send_device_status_report; many scalar config fields across a big buffer.

This object is accessed by these functions (read their fully-named source):
  - build_and_send_device_status_report  (as param_1)  ->  recon/readable_sources/app/g1/build_and_send_device_status_report.c
  - load_sys_setting  (as param_1)  ->  recon/readable_sources/app/g1/load_sys_setting.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct device_settings_blob {
    uint8_t      field_0x2;  /* +0x2  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x3;  /* +0x3  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xed4;  /* +0xed4  rw=rw sz=1 */   <-- NAME ME
    uint16_t     field_0xeda;  /* +0xeda  rw=rw sz=2 */   <-- NAME ME
    uint32_t     field_0xedc;  /* +0xedc  rw=rw sz=2,4 */   <-- NAME ME
    uint16_t     field_0xede;  /* +0xede  rw=rw sz=2 */   <-- NAME ME
    uint32_t     field_0xf64;  /* +0xf64  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xf94;  /* +0xf94  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xfa0;  /* +0xfa0  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xfa4;  /* +0xfa4  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xfa8;  /* +0xfa8  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xfac;  /* +0xfac  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0xfb0;  /* +0xfb0  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xfb4;  /* +0xfb4  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0x1050;  /* +0x1050  rw=w sz=4 */   <-- NAME ME
    uint16_t     field_0x1072;  /* +0x1072  rw=rw sz=2 */   <-- NAME ME
    uint16_t     field_0x1074;  /* +0x1074  rw=rw sz=2 */   <-- NAME ME
};
```