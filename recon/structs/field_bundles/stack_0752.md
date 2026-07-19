### struct batt_soc_calc_tmp  (G1-original)  cid=stack_0752

purpose: Stack-local temporary pair inside battery_model_state_update (intermediate SOC/voltage calculation results).

This object is accessed by these functions (read their fully-named source):
  - battery_model_state_update  (as local_254)  ->  recon/readable_sources/app/g1/battery_model_state_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct batt_soc_calc_tmp {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```