"""Resolvable locations for the recon pipeline's volatile working directory.

WHY THIS EXISTS
---------------
Thirty-odd generators used to embed one literal absolute path::

    SCR = "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
          "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"

That directory belongs to a single, long-finished agent session inside
``/private/tmp``.  It is not part of the repository, it is not recreated by a
checkout, and macOS reclaims ``/private/tmp`` on its own schedule.  Two
concrete failures already followed from it:

* ``symbolize.py`` and ``gen_linker.py`` cannot run at all, because the
  ``symbol_map.json`` / ``symbol_map_net.json`` they read were never
  regenerated after the session that produced them ended;
* worse, ``cfg_verify``/``reverify`` load ``app_funcs.json`` /
  ``net_funcs.json`` / ``classified.json`` through ``try``/``except`` blocks.
  When those files are absent every function silently buckets into "other"
  and the sweep reports **PASS=0 with no error** -- a fake all-clear.

So the location has to be resolvable, and a missing catalog has to be an
exception rather than an empty dict.

RESOLUTION ORDER (first hit wins)
---------------------------------
1. ``$G1_SCRATCHPAD`` -- explicit override, always honoured.
2. The legacy session directory, **if it still exists**.  Its ``app_funcs``/
   ``classified``/``net_funcs`` are NEWER than the committed snapshots, so
   preferring it keeps every existing verdict bit-for-bit reproducible.
3. ``<repo>/recon/generated/cache`` -- repo-relative default, created on
   demand, for a clean checkout on a machine that never had the session.

CATALOG FALLBACK
----------------
``load_catalog(name)`` looks in the resolved scratchpad first and then in the
committed ``recon/catalogs/<name>.gz``.  It raises ``MissingCatalog`` when
neither exists, so a wiped scratchpad can never again be mistaken for an empty
corpus.
"""

import gzip
import json
import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CATALOGS = os.path.join(REPO, "recon", "catalogs")

# Kept as data, not as behaviour: the historical location is still the freshest
# copy on this machine, and naming it here is what lets the resolution order
# above be reproducible instead of accidental.
LEGACY_SCRATCHPAD = ("/private/tmp/claude-501/-Users-freedomcoder-Projects-"
                     "G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
DEFAULT_SCRATCHPAD = os.path.join(REPO, "recon", "generated", "cache")

# Catalogs that are committed (gzipped) and may therefore be recovered when the
# scratchpad is gone.  Names are the scratchpad-side filenames.
COMMITTED_CATALOGS = {
    "app_funcs.json": "app_funcs.json.gz",
    "net_funcs.json": "net_funcs.json.gz",
    "classified.json": "classified.json.gz",
    "refgraph_app.json": "refgraph_app.json.gz",
    "refgraph_net.json": "refgraph_net.json.gz",
    "ref_db.json": "ref_db.json.gz",
}


class MissingCatalog(RuntimeError):
    """A required pipeline input exists in neither the scratchpad nor the repo.

    Raised instead of returning an empty structure: an empty corpus looks
    exactly like a clean sweep, and that mistake has been made here before.
    """


_resolved = None


def scratchpad(create=False):
    """Absolute path of the working directory, resolved per the order above."""
    global _resolved
    if _resolved is None:
        override = os.environ.get("G1_SCRATCHPAD")
        if override:
            _resolved = os.path.abspath(os.path.expanduser(override))
        elif os.path.isdir(LEGACY_SCRATCHPAD):
            _resolved = LEGACY_SCRATCHPAD
        else:
            _resolved = DEFAULT_SCRATCHPAD
    if create:
        os.makedirs(_resolved, exist_ok=True)
    return _resolved


def path(*parts):
    """Join a path inside the resolved scratchpad."""
    return os.path.join(scratchpad(), *parts)


def catalog_path(name):
    """Where `name` actually lives right now, or None."""
    candidate = os.path.join(scratchpad(), name)
    if os.path.exists(candidate):
        return candidate
    committed = COMMITTED_CATALOGS.get(name)
    if committed:
        committed = os.path.join(CATALOGS, committed)
        if os.path.exists(committed):
            return committed
    return None


def load_catalog(name):
    """Parsed JSON for a pipeline catalog; raises MissingCatalog if absent."""
    found = catalog_path(name)
    if found is None:
        raise MissingCatalog(
            "%s is in neither the scratchpad (%s) nor recon/catalogs. "
            "Set $G1_SCRATCHPAD, or restore it from the committed .gz."
            % (name, scratchpad()))
    opener = gzip.open if found.endswith(".gz") else open
    with opener(found, "rb") as stream:
        return json.loads(stream.read().decode("utf-8"))


def describe():
    """One-line provenance string for receipts and reports."""
    rows = []
    for name in sorted(COMMITTED_CATALOGS):
        found = catalog_path(name)
        rows.append("%s=%s" % (name, "missing" if found is None else
                               ("committed" if found.endswith(".gz") else "scratchpad")))
    return "scratchpad=%s %s" % (scratchpad(), " ".join(rows))


if __name__ == "__main__":
    print(describe())
