### struct app_id_config_stream_ctx  (G1-original)  cid=param_0159

purpose: Large application context shared by parse_app_id_config_stream and invoke_object_callback_864: a stream pointer at 0x864 and a cluster of flags/counters/ids at 0x8fc-0x928.

This object is accessed by these functions (read their fully-named source):
  - parse_app_id_config_stream  (as param_1)  ->  recon/readable_sources/app/g1/parse_app_id_config_stream.c
  - invoke_object_callback_864  (as param_1)  ->  recon/readable_sources/app/g1/invoke_object_callback_864.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct app_id_config_stream_ctx {
    void *       stream_ptr;  /* +0x864  rw=r sz=4 */
    int32_t      field_0x8fc;  /* +0x8fc  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x900;  /* +0x900  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0x904;  /* +0x904  rw=rw sz=4 */   <-- NAME ME
    uint8_t      field_0x908;  /* +0x908  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x909;  /* +0x909  rw=w sz=1 */   <-- NAME ME
    uint16_t     field_0x910;  /* +0x910  rw=rw sz=2 */   <-- NAME ME
    uint32_t     field_0x914;  /* +0x914  rw=rw sz=4 */   <-- NAME ME
    uint8_t      field_0x918;  /* +0x918  rw=w sz=1 */   <-- NAME ME
    int16_t      field_0x91c;  /* +0x91c  rw=rw sz=2 */   <-- NAME ME
    int32_t      field_0x920;  /* +0x920  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0x924;  /* +0x924  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x928;  /* +0x928  rw=w sz=4 */   <-- NAME ME
};
```