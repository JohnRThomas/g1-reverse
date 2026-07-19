### struct ancs_handle_pair  (G1-original)  cid=stack_1080

purpose: Stack-local byte pair used while assigning ANCS GATT discovery-manager handles (ancs_gatt_dm_assign_handles local_a0).

This object is accessed by these functions (read their fully-named source):
  - ancs_gatt_dm_assign_handles  (as local_a0)  ->  recon/readable_sources/app/g1/ancs_gatt_dm_assign_handles.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ancs_handle_pair {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```