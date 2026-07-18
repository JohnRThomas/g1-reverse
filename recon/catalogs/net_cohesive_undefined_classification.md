# Cohesive CPUNET undefined-symbol classification

This is the unresolved surface of the actual Zephyr cohesive link, computed from its
archive/object inputs. Private SDC/MPSL identities remain report-only; this report
does not authorize aliases, removals, or source replacement for them.

- Undefined symbols: **0**
- Text relocation references: **0**
- Private SDC/MPSL report-only: **0**
- Stock SDK/glue: **0**
- Interior/anomalous: **0**
- Private MPSL manifest-policy conflicts: **0**
- MPSL rows / unique private archive identities: **0 / 0**

## Version discrimination

The selected SDC and MPSL archives and every selected private body are byte-identical in nrfxlib v2.5.0 and v2.5.1, so those archive bytes alone select only that two-tag interval. The shipped CPUNET image independently embeds the NCS v2.5.1 boot banner, selecting the released v2.5.1 west manifest. v2.4.2, v2.5.2/v2.5.3, and v2.6.0 are rejected as exact archive pairs.

- Firmware evidence: `*** Booting nRF Connect SDK v2.5.1 ***` at CPUNET image offset `0x363c4`.
- Released nrfxlib revision: `v2.5.1`.
- Released Zephyr revision: `v3.4.99-ncs1-1`.

| Tag | SDC archive exact | SDC selected same/different/missing | MPSL archive exact | MPSL selected same/different/missing |
|---|---|---:|---|---:|
| `v2.4.2` | False | 0/0/0 | False | 0/0/0 |
| `v2.5.0` | True | 0/0/0 | True | 0/0/0 |
| `v2.5.1` | True | 0/0/0 | True | 0/0/0 |
| `v2.5.2` | False | 0/0/0 | False | 0/0/0 |
| `v2.5.3` | False | 0/0/0 | False | 0/0/0 |
| `v2.6.0` | False | 0/0/0 | False | 0/0/0 |

## Prioritized non-SDC action queue

1. **P0** — restore private MPSL entries to report-only policy (0 symbols).
2. **P1** — include the already-reviewed readable alias fragment in the cohesive CPUNET link (0 symbols).
3. **P2** — replace raw caller identities with selected public/stock SDK provider symbols (0 symbols).
4. **P3** — resolve anomalous control-flow identities with assembly/relocation evidence (0 symbols).

## Per-symbol evidence

| Symbol | Analysis / runtime | Category | Kind | Refs | Callers | Provider |
|---|---|---|---|---:|---:|---|
