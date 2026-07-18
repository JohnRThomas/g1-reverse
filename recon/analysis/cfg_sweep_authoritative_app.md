# Authoritative CPUAPP CFG sweep

This checkpoint covers every canonical CPUAPP function source in the frozen 2,113-function inventory and binds each verdict to its exact source SHA-256.

- Inventory digest: `61a7586b5c385b62dc69ee8a98f2776710c4790b9fef67b92a0cfb4af17b47ba`
- Baseline: 2081 PASS, 7 FAIL, 1 compile error, 2 other, 22 timeout
- Current overlay: 2113 PASS, 0 FAIL, 0 compile error, 0 other, 0 timeout
- Unresolved current inventory: **0**
- Post-baseline MMIO repairs rechecked PASS: `FUN_00050558`, `FUN_00066050`

## Confirmed FAIL


## Compile-error triage

`FUN_00081e2a` was classified as a compile error by the lane. The runner did not retain stderr. Reproduction with the stale raw entry name yields exactly:

```text
symbol FUN_00081e2a not found after link
```

The same unchanged source compiles as `att_chan_read` and now passes authoritative CFG verification; the baseline verdict remains preserved in the machine report.

## Timeout and verifier-error identities


## CPUNET status

The preserved 998-function CPUNET receipt is explicitly historical, not current. Its canonical inventory grew while net repair shards were active; a new net sweep is deferred until that source tree freezes.
