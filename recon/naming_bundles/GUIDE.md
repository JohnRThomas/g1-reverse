# Naming task guide (CPUAPP unnamed functions)

You are naming reverse-engineered functions of the Even Realities G1 smart-glasses
firmware (Nordic nRF5340 CPUAPP, ARM Cortex-M33). Each function currently has only
a `FUN_<addr>` identity. Propose a concise, human-readable name based on the
function's *behavior*, its *callers*, its *callees*, and any *referenced strings*.

## Evidence, in priority order
1. **Self-name log strings** — the firmware logs `"%s(): ..."` with the caller's own
   name; a bare C identifier string inside a function is very likely its real name.
   If a bundle shows such a string, use it verbatim (it is ground truth).
2. **Referenced strings** — format strings, error text, BLE/subsystem tags reveal purpose.
3. **Callee names** — already-resolved readable callees (e.g. `lc3_encode`, `k_sem_take`,
   `nrfx_...`) tell you the subsystem and the operation.
4. **Callers** — a function called only by `battery_soc_from_curve` is battery logic.
5. **Control flow / operations** in the C body (loops, dispatch tables, MMIO, memcpy).

## Naming rules
- Valid C identifier, `snake_case`, lowercase, ASCII. No spaces, no leading digit.
- Descriptive but concise: `subsystem_verb_object`, e.g. `ble_notify_dashboard`,
  `imu_fifo_drain`, `lc3_frame_encode`, `batt_curve_lookup`.
- Must be UNIQUE — do not reuse a name in `existing_names.txt` or one you already
  proposed in this batch. If a stock-library function is obvious (memcpy, strlen,
  k_sem_give, nrfx_gpiote_*), you MAY use the canonical stock name.
- Do NOT invent a subsystem you cannot justify. If evidence is thin, still propose
  your best structural name but mark confidence `low`.
- Prefer nouns/verbs from the domain: BLE/GATT, ESB, LC3 audio codec, DMIC mic,
  IMU/accel, display/projector, battery/charger, touch, firmware update/DFU,
  cJSON, flash/settings, RPC/IPC, HCI.

## Output
Write ONE JSON file to the exact path you are told, mapping address -> proposal:

```json
{
  "0x0000c358": {
    "name": "batt_soc_kalman_estimate",
    "confidence": "high",
    "evidence": "Called only by battery_soc_from_curve; runs a 1-D Kalman update over a 201-point curve table (curve_table_interp_201pt) with expf/sqrtf; DAT constants are 0.9999 process / 1e-4 measurement noise."
  }
}
```

- `confidence`: `high` | `medium` | `low`.
- `evidence`: one specific sentence tying the name to concrete signals in the bundle.
- Include every address in your batch. If truly unnameable, still give a structural
  name with confidence `low` and say why in evidence.
- Output ONLY the JSON file. Return a one-line summary (counts by confidence).
