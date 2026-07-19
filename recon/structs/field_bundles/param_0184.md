### struct bt_settings_encode_key_arg  (G1-original)  cid=param_0184

purpose: Identity/key descriptor passed to bt_settings_encode_key (param_4) when building a settings storage key.

This object is accessed by these functions (read their fully-named source):
  - bt_settings_encode_key  (as param_4)  ->  recon/readable_sources/app/library/bt_settings_encode_key.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_settings_encode_key_arg {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```