# Exact Zephyr kernel/work.c adoption

The configured NCS 2.5.1 `kernel/work.c` source unit is the exact firmware owner for all 21 recovered bodies in this atomic group. Four additional source-local or already-SDK-only bodies are exact support closure. Relocation-normalized bytes, public ABIs, queue-thread layout, the work lock at `0x2000b480`, and pending-cancel state at `0x2000b478` converge. Explicitly disabling TRACING's weak THREAD_MONITOR and THREAD_NAME implications preserves the firmware's compact `k_thread` layout.

The real normal link moves **10 -> 3**, removing only the seven work collisions; the two embedded SVC continuations remain the sole unresolved symbols. Recovered C and raw-address backmaps remain committed as evidence. Private SDC remains report-only.
