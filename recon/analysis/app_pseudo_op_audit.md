# CPUAPP pseudo-op audit

`ARCH_EXCEPT` is Zephyr's ARMv8-M Mainline in-body macro. The original
`FUN_00051164` clears `BASEPRI`, loads reason 3 into `r0`, and executes
`svc #2`, exactly matching NCS v2.5.1 `ARCH_EXCEPT(3)`.

`default_tail` is not a tail or a function. The default arm of
`FUN_00056a68` executes `mvn.w r0,#127` and returns, so its exact C result is
`-128`.

`display_debug_log_boundary` is not safe to define as a helper or no-op. It
stands for sixteen real machine-level logging paths. Every path selects
`debug_print` or `log_message` through `g_log_use_alt_sink`, and each supplies
its own format, module, and sometimes payload registers. The complete address,
literal, decoded-string, and payload inventory is in
`app_pseudo_op_audit.json`. The display reconstruction stays unchanged until
those machine paths are mapped exactly onto its shared readable-C branches.

Both lowerings pass the authoritative verifier: `FUN_00051164` passes its
terminal exception path and `FUN_00056a68` passes all seven CFG-directed cases.
The latter uses its corrected executable extent `[0x56a68,0x56ad0)`; a regression
test pins the default-arm bytes and the literal boundary at `0x56ad0`.
