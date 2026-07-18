# Function recovery and CFG state — 2026-07-18

This is a fail-closed snapshot, not a claim that the full current corpus has
passed CFG verification.  Counts were derived from canonical `.c` headers,
the regenerated catalogs, and the adoption manifest; no worklist ledger was
used.

## Canonical source inventory

| Core | Canonical `.c` files / unique header VAs | Regenerated catalog VAs | Catalog VAs with a canonical header owner | Canonical VAs outside catalog |
|---|---:|---:|---:|---:|
| CPUAPP | 2,113 | 2,391 | 2,010 | 103 |
| CPUNET | 998 | 1,247 | 963 | 35 |

There are **zero** files under `recon/deferred/` and **zero** files under
`recon/blobs/`.

The 381 CPUAPP catalog VAs without a one-file canonical owner partition as 123
manifest-authorized stock exclusions and 258 identities not yet represented in
the adoption manifest.  The latter are an ownership/source-unit audit queue,
not 258 proven reconstruction gaps: many are recognizable libgcc, newlib,
Zephyr, or driver bodies.

The 284 CPUNET catalog VAs without a one-file canonical owner partition as 73
manifest-authorized stock exclusions, 210 retained entries, and one owned
interior identity (`FUN_010333e4`, owned by CFG-PASS `FUN_010333b4`).  The 210
retained entries comprise 147 private SDC report-only identities and 63
`net_sdk_or_glue` identities.  Stock-owner fingerprinting must precede any
decompilation of the 63.

Snapshot input hashes:

- `classified.json.gz`: `14a0dd8d0f18a33266e26cfa661cd1587608c94417ee6424840c133d5b29e8ee`
- `net_funcs.json.gz`: `a8da3fb4f9e647f900893f68c8e37652d47a7e82bda872e74d6cb555483fe78a`
- `adoption_manifest.json`: `cd1fafe9fefcde28a02145d03967be5c528009ad04e9461d95d5280c42452133`

## CFG evidence

The scratch `reverify_{app,net}_L0..L3.json` files completed the old 1,886 app
/ 806 net inventory.  They are not authoritative for the current tree: the
canonical inventory now has 239 additional app and 193 additional net files,
while 12 old app files and one old net file were consolidated or removed.
Many retained files were also edited after that sweep.

`cfg_sweep_fails.json` remains a historical partial-discovery snapshot.  Every
one of its 40 confirmed failures was rechecked against current source: **40
PASS, 0 FAIL**, covering 298 CFG-derived cases.  The source-hash-bound receipt
is `cfg_historical_fail40_closure.json` and is checked with:

```sh
cd /private/tmp
PYTHONSAFEPATH=1 \
PYTHONPATH=/Users/freedomcoder/Projects/G1disasm2/tools \
/Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/validate_cfg_historical_fail40.py
```

The historical 70-entry `other`/`timeout` partition remains closed: 69 direct
CFG passes plus one interior identity with a CFG-PASS owner, zero unresolved.
The 60-entry CPUAPP true-missing ledger still has 60 semantic CFG passes, but
12 receipt hashes became stale after later source cleanup.  All 12 changed
sources were freshly rechecked and passed; regenerate that receipt only after
the concurrently active ownership edits settle.

Therefore the current confirmed-failure count is **zero for the durable known
backlogs**, but the failure count for the full 3,111-file current corpus is
**unknown until a fresh sweep completes**.  Absence from the old FAIL list is
not proof.

## Next authoritative sweep

`tools/reverify.py` now rebuilds stale inventories and binds each lane receipt
to the exact todo digest, shard count, and shard index.  The refreshed scratch
inventory is 2,113 app / 998 net.  When compute capacity is available, run all
lanes from `/private/tmp` (four or eight in parallel according to host load):

```sh
REPO=/Users/freedomcoder/Projects/G1disasm2
for core in app net; do
  for lane in 0 1 2 3 4 5 6 7; do
    CFG_VERIFY_RECHECK=1 PYTHONSAFEPATH=1 PYTHONPATH="$REPO/tools" \
      "$REPO/.venv/bin/python" "$REPO/tools/reverify.py" \
      sweeplist "$core" "$lane" 8 \
      >"/private/tmp/g1_cfg_${core}_L${lane}.log" 2>&1 &
  done
done
wait
```

Aggregate only receipts carrying the same `_todo_digest` and
`_shard_count == 8`.  Redo every resulting `FAIL`; do not reinterpret
`compile-fail`, `other`, or timeout as success.

If ownership auditing proves the 63 retained `net_sdk_or_glue` identities are
not stock-owned, the first size-prioritized reconstruction batch is:
`0x01029b12` (18 B), `0x010283a4` (20 B), `0x01021790` (24 B),
`0x0103b38e` (24 B), and `0x010284a8` (26 B).  Preserve both readable names
and raw/address aliases, then require `cfg_verify` before saving.
