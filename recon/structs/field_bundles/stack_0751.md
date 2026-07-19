### struct battery_model_sample  (G1-original)  cid=stack_0751

purpose: Stack local (local_258) in battery_model_state_update: intermediate battery-model sample bytes.

This object is accessed by these functions (read their fully-named source):
  - battery_model_state_update  (as local_258)  ->  recon/readable_sources/app/g1/battery_model_state_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct battery_model_sample {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x1;  /* +0x1  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```