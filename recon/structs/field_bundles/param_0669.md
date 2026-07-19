### struct dev_channel_mode  (G1-original)  cid=param_0669

purpose: Device channel-mode descriptor written by dev_write_channel_mode: a mode/index word.

This object is accessed by these functions (read their fully-named source):
  - dev_write_channel_mode  (as param_2)  ->  recon/readable_sources/app/g1/dev_write_channel_mode.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dev_channel_mode {
    uint32_t     mode;  /* +0x4  rw=r sz=4 */
    uint16_t     field_0x6;  /* +0x6  rw=r sz=2 */   <-- NAME ME
};
```