### struct battery_model_state  (G1-original)  cid=param_0000

purpose: Large battery model/state structure (>=0x1778 bytes) passed to battery_model_state_update, holding voltage/current/capacity coefficients and history across several sub-regions.

This object is accessed by these functions (read their fully-named source):
  - battery_model_state_update  (as param_5)  ->  recon/readable_sources/app/g1/battery_model_state_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct battery_model_state {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x48;  /* +0x48  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4c;  /* +0x4c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x50;  /* +0x50  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x54;  /* +0x54  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x5c;  /* +0x5c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x128;  /* +0x128  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x12c;  /* +0x12c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x130;  /* +0x130  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x134;  /* +0x134  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x138;  /* +0x138  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x13c;  /* +0x13c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x140;  /* +0x140  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x144;  /* +0x144  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x148;  /* +0x148  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x464;  /* +0x464  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x5d3;  /* +0x5d3  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x65c;  /* +0x65c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x660;  /* +0x660  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x978;  /* +0x978  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x97c;  /* +0x97c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x980;  /* +0x980  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x984;  /* +0x984  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc9c;  /* +0xc9c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xca0;  /* +0xca0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1744;  /* +0x1744  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1748;  /* +0x1748  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1750;  /* +0x1750  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1754;  /* +0x1754  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1758;  /* +0x1758  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x175c;  /* +0x175c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1760;  /* +0x1760  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1764;  /* +0x1764  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1768;  /* +0x1768  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x176c;  /* +0x176c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1770;  /* +0x1770  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1774;  /* +0x1774  rw=r sz=4 */   <-- NAME ME
};
```