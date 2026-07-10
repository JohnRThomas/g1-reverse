# imu_motion — RTOS wiring

## Summary
**This module defines NO RTOS objects of its own.** None of the proven bodies of
the 11 member functions contain a `K_THREAD_DEFINE`, `K_MSGQ_DEFINE`,
`k_sem_init`, `k_mutex_init`, `k_work_init`, or `k_timer_init` call. There is no
static thread, message queue, semaphore, mutex, work item, or timer created here.

## How the module participates in the RTOS (objects defined elsewhere)

### Work-item submit (kernel primitive, not defined here)
`update_imu_trigger_status` @0x2bcbc (recon/named/update_imu_trigger_status.c,
recon/verified/src/update_imu_trigger_status.c) submits a work/wait object on a
rising trigger while worn:

```
if (device_info[+0xfea] == 0x0a && state != 0 && device_info[+0xb0c] == 0) {
    device_info[+0xfe9] = 1;
    FUN_00072880(device_info + 0xaf4);   // submit / wake
}
```

- The submitted object lives **inside `device_info_t` at offset 0xaf4** (a
  `k_work` / `k_poll`-style struct), which is defined by the system/state
  module that owns `device_info_t`, not by imu_motion.
- `FUN_00072880` @0x72880 (recon/verified/src/FUN_00072880.c) is a **kernel
  scheduler primitive**: it runs under the global scheduler lock object at
  `0x2000b474` (basepri raise → `FUN_00072040/00072078` lock/unlock →
  `FUN_000744a4` unpend → `FUN_0008688e` ready → `FUN_000739f0` unlock). It
  belongs to the rtos/kernel module. imu_motion only calls it.

### Threads (none defined here; these are dispatch-table callbacks)
The module's "entry points" are **not** `K_THREAD_DEFINE` targets. They are
handler functions invoked synchronously from other modules' task loops:

| Entry point                     | addr    | invoked by (external)                    |
|---------------------------------|---------|------------------------------------------|
| register_imu_funsion_context    | 0x26250 | system-init dispatcher FUN_00016eb8      |
| imu_set_enabled                 | 0x2bd4c | work-mode handler       FUN_0002af4c     |
| ui_set_imu_pitch_task           | 0x46b80 | UI task dispatcher      FUN_00048b5c     |
| dump_template_gyro_info         | 0x36164 | (no in-module caller; debug/telemetry)   |

The owning thread/msgq/work objects for those dispatchers are defined in the
`rtos`, `system`, and `ui` modules respectively — capture them there.

## Objects to feed the wiring reconstruction
- **From imu_motion: NONE.** No `k_*_init` / `K_*_DEFINE` present.
- Cross-reference only: `device_info_t + 0xaf4` (IMU work/wait object, defined by
  the device_info/system module) and scheduler lock `0x2000b474` (rtos module).
