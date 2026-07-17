# CFG baseline-70 closure

The 70 functions in `cfg_baseline70.json` are the complete historical
`other`/`timeout` backlog recovered after the volatile scratch ledgers were
lost.  This is now a closed, fail-closed partition:

| Current status | Count | Durable evidence |
|---|---:|---|
| Authoritative CFG PASS | 55 | recovery wave `6fd0218` |
| Authoritative CFG PASS | 1 | LC3 TNS recovery `de85940` (`7` cases) |
| Authoritative CFG PASS | 13 | final verification wave `0157de4` |
| Interior identity owned by a CFG-PASS function | 1 | `FUN_010333e4` is inside `FUN_010333b4`; owner PASS (`8` cases) in `0157de4` |
| Unresolved | **0** | validator-enforced |

The final `0157de4` verification receipt contains 15 functions: the 13 direct
baseline resolutions, the `FUN_010333b4` owner, and `FUN_000778d4` (an adjacent
non-baseline reconstruction verified in the same wave).  Per-function case
counts are stored in the JSON ledger.

Several raw filenames from the first wave no longer exist because those
functions were renamed to their human-readable canonical filenames.  The
validator resolves raw identity through `function_names_{app,net}.json` before
checking the canonical source, so a rename cannot silently look like a missing
proof or create a duplicate identity.

`cfg_sweep_fails.json` remains a historical snapshot of the interrupted
whole-corpus discovery sweep.  Its old counters are useful provenance, but are
not a current resolution status and are not the source of truth for this
70-entry backlog.

Validate from outside the repository (to avoid the local `struct.py` shadow):

```sh
PYTHONSAFEPATH=1 .venv/bin/python tools/validate_cfg_baseline70.py
```
