#!/usr/bin/env python3
"""Rank NCS upstream functions for one firmware function without renaming it.

Examples (run from /tmp: the repository has a local struct.py):
  cd /tmp
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/rank_upstream.py \
      --core app --va 0x4d588 --top 10
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/rank_upstream.py \
      --core app --name FUN_00052760 --extent 0x76 --json /tmp/rank.json
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/rank_upstream.py \
      --core app --self-test

The output is evidence only.  It never edits catalogs, worklists, or sources;
a candidate must still be reconstructed and passed to cfg_verify.
"""
import argparse
import difflib
import gzip
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
from build_upstream_index import extract_features

BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCR = ("/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
       "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad")
WEIGHTS = {"exact": .15, "opcode": .30, "shape": .20, "length": .10,
           "calls": .10, "literals": .10, "signature": .05}


def _load_catalog(name):
    scratch = os.path.join(SCR, name + ".json")
    if os.path.exists(scratch):
        return json.load(open(scratch))
    backup = os.path.join(BASE, "recon", "catalogs", name + ".json.gz")
    with gzip.open(backup, "rt") as stream:
        return json.load(stream)


def _function_maps(core):
    path = os.path.join(BASE, "recon", "catalogs",
                        "function_names_%s.json" % core)
    return json.load(open(path))


def _resolve_target(core, va=None, name=None):
    funcs = _load_catalog("app_funcs" if core == "app" else "net_funcs")["functions"]
    names = _function_maps(core)
    if va is None:
        if re.fullmatch(r"(?:FUN_|sub_)[0-9a-fA-F]+", name or ""):
            va = int(name.split("_")[-1], 16) & ~1
        else:
            value = names.get("by_name", {}).get(name)
            if value:
                va = int(value, 16)
    if va is None:
        raise SystemExit("cannot resolve function name: %s" % name)
    row = next((f for f in funcs if (int(f["entry"]) & ~1) == (va & ~1)), None)
    if row is None:
        # Catalog-missing/swallowed entries can still be ranked with --extent.
        row = {"entry": va & ~1, "entry_hex": "0x%x" % (va & ~1),
               "size": 0, "signature": "", "name": "FUN_%08x" % (va & ~1),
               "callees": []}
    return row


def _true_extent(core, va, catalog_size, explicit=None):
    if explicit is not None:
        return explicit
    try:
        import cfg_verify
        return cfg_verify.TRUE_SIZE_OVERRIDES.get((core, va), catalog_size)
    except Exception:
        return catalog_size


def _firmware_bytes(core, va, extent):
    if core == "app":
        import extract
        return extract.read(va, extent)
    import net_extract
    return net_extract.read(va, extent)


def _arity(signature):
    match = re.search(r"\((.*)\)", signature or "")
    if not match:
        return None
    body = match.group(1).strip()
    if not body or body == "void":
        return 0
    if body in ("unknown", "..."):
        return None
    return len([part for part in body.split(",") if part.strip() and part.strip() != "..."])


def _return_class(signature):
    text = (signature or "").split("(", 1)[0].lower()
    if not text:
        return None
    if "void" in text and "*" not in text:
        return "void"
    if "float" in text or "double" in text:
        return "float"
    if "*" in text:
        return "pointer"
    return "integer"


def _candidate_signature(record):
    signature = record.get("signature")
    if not signature:
        return None, None
    params = signature.get("params")
    ret = (signature.get("return") or "").lower()
    if "void" == ret:
        retclass = "void"
    elif "float" in ret or "double" in ret:
        retclass = "float"
    elif "*" in ret:
        retclass = "pointer"
    else:
        retclass = "integer"
    return len(params) if params is not None else None, retclass


def _sequence_score(left, right):
    if not left and not right:
        return 1.0
    if not left or not right:
        return 0.0
    return difflib.SequenceMatcher(None, left, right, autojunk=False).ratio()


def _call_tokens(calls):
    return [row.get("target") or "?" for row in calls]


def _literal_tokens(literals):
    return ["%s:%s" % (row.get("width"), row.get("class")) for row in literals]


def _firmware_calls(core, va):
    graph = _load_catalog("refgraph_%s" % core).get("functions", {})
    node = graph.get("0x%x" % va, {})
    names = _function_maps(core).get("by_address", {})
    out = []
    for target in node.get("calls", []):
        address = int(target, 16) & ~1
        record = names.get("0x%08x" % address)
        out.append((record or {}).get("name", "?"))
    return out


def rank(core, target, extent, index, top=10, length_tolerance=.60):
    va = int(target["entry"]) & ~1
    code = _firmware_bytes(core, va, extent)
    firmware = extract_features(code, va)
    firmware_call_names = _firmware_calls(core, va)
    if firmware_call_names:
        firmware["calls"] = [{"target": name} for name in firmware_call_names]
    else:
        name_map = _function_maps(core).get("by_address", {})
        for call in firmware.get("calls", []):
            address = call.get("address")
            record = name_map.get("0x%08x" % address) if address is not None else None
            if record:
                call["target"] = record.get("name", call["target"])
    fw_arity = _arity(target.get("signature"))
    fw_ret = _return_class(target.get("signature"))
    rows = []
    for candidate in index.get("records", []):
        clen = max(1, int(candidate.get("executable_instruction_count",
                                       candidate.get("instruction_count", 0))))
        flen = max(1, int(firmware.get("executable_instruction_count",
                                      firmware.get("instruction_count", 0))))
        length = min(clen, flen) / max(clen, flen)
        if length < length_tolerance:
            continue
        candidate_opcodes = candidate.get("mnemonics", [])[:clen]
        candidate_shapes = candidate.get("operand_shapes", [])[:clen]
        firmware_opcodes = firmware.get("mnemonics", [])[:flen]
        firmware_shapes = firmware.get("operand_shapes", [])[:flen]
        components = {
            "exact": 1.0 if candidate_shapes == firmware_shapes else 0.0,
            "opcode": _sequence_score(firmware_opcodes, candidate_opcodes),
            "shape": _sequence_score(firmware_shapes, candidate_shapes),
            "length": length,
            "calls": _sequence_score(_call_tokens(firmware.get("calls", [])),
                                     _call_tokens(candidate.get("calls", []))),
            "literals": _sequence_score(_literal_tokens(firmware.get("literals", [])),
                                        _literal_tokens(candidate.get("literals", []))),
        }
        cand_arity, cand_ret = _candidate_signature(candidate)
        signature_parts = []
        if fw_arity is not None and cand_arity is not None:
            signature_parts.append(1.0 if fw_arity == cand_arity else 0.0)
        if fw_ret is not None and cand_ret is not None:
            signature_parts.append(1.0 if fw_ret == cand_ret else 0.0)
        components["signature"] = (sum(signature_parts) / len(signature_parts)
                                   if signature_parts else None)
        active = {key: value for key, value in components.items() if value is not None}
        denominator = sum(WEIGHTS[key] for key in active)
        score = sum(WEIGHTS[key] * value for key, value in active.items()) / denominator
        rows.append({
            "score": round(score, 6),
            "components": {key: (None if value is None else round(value, 6))
                           for key, value in components.items()},
            "name": candidate["name"], "id": candidate["id"],
            "object": candidate.get("object"), "source": candidate.get("source"),
            "section": candidate.get("section"),
            "symbol_size": candidate.get("symbol_size"),
            "instruction_count": candidate.get("instruction_count"),
            "signature": candidate.get("signature"),
            "calls": candidate.get("calls", []),
            "literals": candidate.get("literals", []),
        })
    rows.sort(key=lambda row: (-row["score"], row["id"]))
    selected = rows[:top]
    gap = ((selected[0]["score"] - selected[1]["score"])
           if len(selected) > 1 else None)
    return {
        "schema": 1, "core": core, "address": "0x%08x" % va,
        "raw_name": "FUN_%08x" % va, "catalog_name": target.get("name"),
        "catalog_signature": target.get("signature"), "extent": extent,
        "firmware_features": firmware,
        "weights": WEIGHTS, "runner_up_gap": gap,
        "warning": "ranking evidence only; no rename/exclusion/proof is implied",
        "candidates": selected,
        "cfg_verify_next": "reconstruct candidate as raw-identity C, then call cfg_verify.verify(core, raw_name, source_override=source)",
    }


def _print_report(report):
    print("%s %s extent=0x%x candidates=%d runner_up_gap=%s" %
          (report["core"], report["address"], report["extent"],
           len(report["candidates"]), report["runner_up_gap"]))
    for index, row in enumerate(report["candidates"], 1):
        comp = " ".join("%s=%s" % (key, value)
                        for key, value in row["components"].items())
        print("%2d. %.4f %-36s %s" % (index, row["score"], row["name"], comp))
        print("    source=%s" % (row.get("source") or "?"))
        print("    object=%s" % row["object"])
    print("WARNING:", report["warning"])


def self_test(core, index_path):
    data = json.load(open(index_path))
    known = ((0x0004d588, "z_log_msg_pending", 0x06) if core == "app" else
             (0x010315f0, "rtc_nrf_isr", None))
    target = _resolve_target(core, va=known[0])
    extent = _true_extent(core, known[0], int(target.get("size", 0)), known[2])
    report = rank(core, target, extent, data, top=20, length_tolerance=.35)
    matches = [row for row in report["candidates"] if row["name"] == known[1]]
    assert matches, "%s absent from top 20" % known[1]
    again = rank(core, target, extent, data, top=20, length_tolerance=.35)
    assert report["candidates"] == again["candidates"]
    print("rank_upstream self-test: PASS %s -> %s rank=%d" %
          (report["address"], known[1], report["candidates"].index(matches[0]) + 1))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--core", choices=("app", "net"), required=True)
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--va", type=lambda value: int(value, 0))
    group.add_argument("--name")
    parser.add_argument("--extent", type=lambda value: int(value, 0))
    parser.add_argument("--index")
    parser.add_argument("--top", type=int, default=10)
    parser.add_argument("--length-tolerance", type=float, default=.60)
    parser.add_argument("--json")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    index_path = args.index or "/tmp/g1_upstream_index_%s.json" % args.core
    if args.self_test:
        self_test(args.core, index_path)
        if args.va is None and args.name is None:
            return
    if args.va is None and args.name is None:
        parser.error("one of --va/--name is required")
    target = _resolve_target(args.core, args.va, args.name)
    va = int(target["entry"]) & ~1
    extent = _true_extent(args.core, va, int(target.get("size", 0)), args.extent)
    if not extent:
        parser.error("no extent for catalog-missing function; pass --extent")
    data = json.load(open(index_path))
    report = rank(args.core, target, extent, data, args.top,
                  args.length_tolerance)
    _print_report(report)
    if args.json:
        with open(args.json, "w") as stream:
            json.dump(report, stream, indent=1)
            stream.write("\n")


if __name__ == "__main__":
    main()
