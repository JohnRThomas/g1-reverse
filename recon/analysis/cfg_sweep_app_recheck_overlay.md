# CPUAPP CFG post-baseline overlay

This exact-hash overlay preserves the frozen 2,113-source CPUAPP baseline and covers the two added thread entries, the corrected slave-thread entry, and the repaired DMIC capture loop.

- Frozen baseline SHA-256: `1eab0c590c62edc0d22c5f9eb540155f8958014a8dd2a8846b4ef21bf0be51b2`
- Execution HEAD: `f49a3b8628a3f2cb458d9853fc7e63c6a3272735`
- Current source inventory digest: `89c4bfc5bf5f9072c696b2cacebe497d9f6903e34805637dfb9d33eb1bde8537`
- Aggregate: **2,115 PASS; 0 unresolved; 0 unverified drift**

| Identity | Address | Change | Directed cases | Prefix events | Source SHA-256 |
|---|---:|---|---:|---:|---|
| `master_display_thread` | `0x0002692c` | added | 1 | 50 | `7586718e0412a196e9aa518f70a49c7c22afada42d7ab8a341235565ef510f1a` |
| `slave_display_thread` | `0x00027cfc` | changed | 38 | 50 | `a1135f28160eec5e3e489091b427714eb6e7905756513ad5822b5ad700978977` |
| `aging_mode_thread` | `0x00032420` | added | 0 | 50 | `71c7341f1c497effac26e5714820718348638f3d583f063ef9558f77139d29ab` |
| `FUN_0002f080` | `0x0002f080` | changed | 2 | — | `7f11a0004fb33e4e5448742af345bb5acc8b0564ea82bd343a2e49e025a80a66` |

Every other current source is byte-identical to its PASS-bound entry in the frozen authoritative baseline.
