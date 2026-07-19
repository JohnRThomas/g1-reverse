### struct param_0299_driver_data_collision  (G1-original)  cid=param_0299

purpose: COINCIDENTAL merge of distinct QSPI-NOR driver data and I2S driver data structs that share the same param slot; treat as generic per-driver runtime data (semaphore/ready/counter words at 0x4/0x10/0x14).

This object is accessed by these functions (read their fully-named source):
  - qspi_nor_acquire  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_acquire.c
  - qspi_nor_suspend_bus  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_suspend_bus.c
  - qspi_nor_pm_action  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_pm_action.c
  - qspi_nor_configure  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_configure.c
  - qspi_nor_erase  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_erase.c
  - qspi_nor_write  (as param_1)  ->  recon/readable_sources/app/g1/qspi_nor_write.c
  - storage_read_with_word_cache  (as param_1)  ->  recon/readable_sources/app/g1/storage_read_with_word_cache.c
  - audio_i2s_stop_and_reset_channels  (as param_1)  ->  recon/readable_sources/app/g1/audio_i2s_stop_and_reset_channels.c
  - audio_i2s_start_channels  (as param_1)  ->  recon/readable_sources/app/g1/audio_i2s_start_channels.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct param_0299_driver_data_collision {
    int32_t      state_or_flag;  /* +0x4  rw=r sz=4 */
    int32_t      field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```