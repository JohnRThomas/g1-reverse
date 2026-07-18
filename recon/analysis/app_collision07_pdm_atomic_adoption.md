# COLLISION-07: atomic nrfx PDM adoption

The five public PDM collisions are adopted as one pinned NCS 2.5.1 source
unit.  Partial adoption is forbidden because `nrfx_pdm_irq_handler` and the
five public entry points share the translation-unit-local 24-byte `m_cb`.

| Firmware VA | Public symbol | Live bytes | Normalized code SHA-256 |
|---:|---|---:|---|
| `0x0006615c` | `nrfx_pdm_init` | 94 | `6d00c9a56e1fe2294ca1bd6ba86c520d40f50378e36593412d33723cb21aa6ce` |
| `0x000661dc` | `nrfx_pdm_uninit` | 46 | `83b92aae823aac10a74b7d3b0273f1523c27a3a2c50660bedaafb017744dcb34` |
| `0x00066214` | `nrfx_pdm_start` | 62 | `3adfa6ea2b5a8a103120609877c9bb08ab46ff4d16622f18eef48ac66107941e` |
| `0x00066270` | `nrfx_pdm_buffer_set` | 118 | `4af09b3f71e28cddced7f4c5e4af5a8dc2c123568b01f572645d3b0ef0a31dce` |
| `0x00066300` | `nrfx_pdm_stop` | 80 | `b82ac6bc3eda1411be735c2e0ce875d3fb517db3285d407aed3cf7c5acf1b89f` |

For every row, truncating the configured SDK symbol to the firmware live
extent produces identical instruction count, mnemonic sequence, operand-shape
sequence, and normalized hash.  The adjacent firmware body
`0x0006636c..0x00066477` is 0x10c bytes, exactly the configured
`nrfx_pdm_irq_handler` size, providing whole-unit closure evidence.

## Fail-closed configuration

Adoption is forbidden unless the generated CPUAPP `.config` contains all of:

```text
CONFIG_ASSERT=y
CONFIG_ASSERT_LEVEL=2
# CONFIG_SPIN_VALIDATE is not set
```

The first two settings preserve the shipped `__ASSERT_NO_MSG` branches and
their exact nrfx source-line metadata.  Spin validation is explicitly disabled
because enabling it introduces three public Zephyr helpers absent from the
firmware collision inventory.

Pinned evidence:

- SDK source: `/Users/freedomcoder/ncs251/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c`
- source SHA-256: `536619a4d27007214c840f512c33a43a26a2528ac4d66c0792bd16891d5beb9c`
- configured object: `/private/tmp/g1-app-pdm-assert-0718g/modules/hal_nordic/nrfx/CMakeFiles/modules__hal_nordic__nrfx.dir/Users/freedomcoder/ncs251/modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c.obj`
- object SHA-256: `393327a07436ac1bbabde22f569be56c9ace210385e727e446eb50498fff60a6`
- configured `.config`: `/private/tmp/g1-app-pdm-assert-0718g/zephyr/.config`
- config SHA-256: `a61727317580f6fa371b5cef19fd10569b4f7133a95070d4988efcd5351706c1`
- pre-adoption log: `/private/tmp/g1-app-pdm-assert-0718g.log` — exactly 96
  strong collisions and only `FUN_0005463e`/`FUN_00054688` unresolved.
- post-adoption log: `/private/tmp/g1-app-pdm-post-0718h.log` — exactly 91
  strong collisions; the removed set is exactly the five symbols in the table,
  no collision was added, and the unresolved set is unchanged.

Reproduction commands are the normal pinned build and authoritative CFG
verifier:

```sh
cd /tmp
PYTHONSAFEPATH=1 PYTHONPATH=/Users/freedomcoder/ncs251/zephyr/scripts/kconfig:/Users/freedomcoder/ncs251/zephyr/scripts/dts:/Users/freedomcoder/ncs251/nrf/scripts \
  ZEPHYR_BASE=/Users/freedomcoder/ncs251/zephyr west build \
  -b nrf5340dk_nrf5340_cpuapp -d /private/tmp/g1-app-pdm-assert-0718g \
  /Users/freedomcoder/Projects/G1disasm2/recon/application/app -- \
  -DG1_INTEGRATION_PROBE_RETAIN_ALL=ON
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/cfg_verify.py app FUN_0006615c
```

Direct caller closure is `0x0005fc7c`, `0x0005fb30`, `0x0005fb8c`, and
`0x0005ffa4`; all four and all five owners pass `cfg_verify` (18 directed
cases in total).  No caller retarget is required: their readable public calls
resolve to the selected SDK owner after the atomic exclusion.
