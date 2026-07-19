### struct lc3_attdet_state  (library:lc3 codec internal (attack-detector state))  cid=param_0364

purpose: LC3 codec attack-detector substate accessed by lc3_attdet_run (param_4): two state/index words.

This object is accessed by these functions (read their fully-named source):
  - lc3_attdet_run  (as param_4)  ->  recon/readable_sources/app/library/lc3_attdet_run.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_attdet_state {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```