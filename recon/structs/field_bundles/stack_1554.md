### struct regulator_volt_range_local  (G1-original)  cid=stack_1554

purpose: Stack local (local_12) in regulator_set_voltage_range: min/max index bytes while validating a voltage range.

This object is accessed by these functions (read their fully-named source):
  - regulator_set_voltage_range  (as local_12)  ->  recon/readable_sources/app/g1/regulator_set_voltage_range.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct regulator_volt_range_local {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x6;  /* +0x6  rw=r sz=1 */   <-- NAME ME
};
```