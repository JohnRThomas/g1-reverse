# Authoritative CPUAPP CFG sweep

This checkpoint covers every canonical CPUAPP function source in the frozen 2,113-function inventory and binds each verdict to its exact source SHA-256.

- Inventory digest: `e6fa134dd35017c19316cbc127686b54f3d301395697a07ed8210edc94972225`
- Baseline: 2081 PASS, 7 FAIL, 1 compile error, 2 other, 22 timeout
- Current overlay: 2082 PASS, 7 FAIL, 0 compile error, 2 other, 22 timeout
- Unresolved: **31**

## Confirmed FAIL

- `FUN_0004ea28`
- `FUN_0004ea78`
- `FUN_00053580`
- `FUN_000536b8`
- `FUN_00054444`
- `FUN_000548b8`
- `FUN_0008503c`

## Compile-error triage

`FUN_00081e2a` was classified as a compile error by the lane. The runner did not retain stderr. Reproduction with the stale raw entry name yields exactly:

```text
symbol FUN_00081e2a not found after link
```

The same unchanged source compiles as `att_chan_read` and now passes authoritative CFG verification; the baseline verdict remains preserved in the machine report.

## Timeout and verifier-error identities

- timeout: `FUN_000184f0`
- timeout: `FUN_0002316c`
- timeout: `FUN_0002360c`
- timeout: `FUN_00023acc`
- timeout: `FUN_000243fc`
- timeout: `FUN_00035f28`
- timeout: `FUN_000361d8`
- timeout: `FUN_00040794`
- timeout: `FUN_0004382c`
- timeout: `FUN_0004d6ec`
- timeout: `FUN_00060a5c`
- timeout: `FUN_00086668`
- timeout: `FUN_00086c04`
- timeout: `FUN_0008705a`
- timeout: `FUN_0008768e`
- timeout: `check_battery_critical`
- timeout: `gui_string_draw`
- timeout: `now_has_persist_task`
- timeout: `ui_even_ai_task`
- timeout: `update_persist_task_status_to_idle`
- timeout: `update_persist_task_status_to_wait_blow_head`
- timeout: `update_temp_task_status`
- other: `FUN_00036030`
- other: `ble_process_put_req`

## CPUNET status

The preserved 998-function CPUNET receipt is explicitly historical, not current. Its canonical inventory grew while net repair shards were active; a new net sweep is deferred until that source tree freezes.
