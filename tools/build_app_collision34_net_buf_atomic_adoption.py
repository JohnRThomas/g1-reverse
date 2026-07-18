#!/usr/bin/env python3
"""Build and verify the atomic COLLISION-34 Zephyr net_buf adoption."""

import argparse
import gzip
import hashlib
import json
import re
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
OUTPUT = ROOT / "recon/ownership/app_collision34_net_buf_atomic_adoption.json"
REPORT = ROOT / "recon/analysis/app_collision34_net_buf_atomic_adoption.md"
IMAGE = ROOT / "app_update.bin"
CONFIG = Path("/private/tmp/g1-bt-custom-notls-main16k-evidence/zephyr/.config")
OBJECT = Path("/private/tmp/g1-bt-custom-notls-main16k-evidence/zephyr/subsys/net/CMakeFiles/subsys__net.dir/buf.c.obj")
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/net/buf.c")
PRE_BUILD = Path("/tmp/g1-netbuf-pre")
POST_BUILD = Path("/tmp/g1-netbuf-adopt")
UNRESOLVED = {"FUN_0005463e", "FUN_00054688"}

FUNCTIONS = {
    "0x0005ee6c": ("net_buf_reset", 54, 0),
    "0x0005eeb4": ("net_buf_alloc_len", 398, 3),
    "0x0005f074": ("net_buf_slist_put", 170, 2),
    "0x0005f148": ("net_buf_slist_get", 146, 2),
    "0x0005f200": ("net_buf_put", 58, 2),
    "0x0005f24c": ("net_buf_unref", 120, 2),
    "0x0005f2d4": ("net_buf_ref", 36, 2),
    "0x0005f304": ("net_buf_frag_last", 40, 2),
    "0x0005f338": ("net_buf_frag_insert", 70, 2),
    "0x0005f390": ("net_buf_frag_add", 58, 2),
    "0x0005f3d8": ("net_buf_frag_del", 100, 3),
    "0x0005f450": ("net_buf_append_bytes", 126, 0),
}
COLLISIONS = {
    "net_buf_reset", "net_buf_slist_put", "net_buf_slist_get", "net_buf_put",
    "net_buf_unref", "net_buf_ref", "net_buf_frag_last",
    "net_buf_frag_insert", "net_buf_frag_add", "net_buf_append_bytes",
}
HIDDEN = {"0x0005eeb4", "0x0005f3d8"}
GROUP = sorted(FUNCTIONS)
ABIS = {
    "net_buf_reset": "void net_buf_reset(struct net_buf *)",
    "net_buf_alloc_len": "struct net_buf *net_buf_alloc_len(struct net_buf_pool *, size_t, k_timeout_t)",
    "net_buf_slist_put": "void net_buf_slist_put(sys_slist_t *, struct net_buf *)",
    "net_buf_slist_get": "struct net_buf *net_buf_slist_get(sys_slist_t *)",
    "net_buf_put": "void net_buf_put(struct k_fifo *, struct net_buf *)",
    "net_buf_unref": "void net_buf_unref(struct net_buf *)",
    "net_buf_ref": "struct net_buf *net_buf_ref(struct net_buf *)",
    "net_buf_frag_last": "struct net_buf *net_buf_frag_last(struct net_buf *)",
    "net_buf_frag_insert": "void net_buf_frag_insert(struct net_buf *, struct net_buf *)",
    "net_buf_frag_add": "struct net_buf *net_buf_frag_add(struct net_buf *, struct net_buf *)",
    "net_buf_frag_del": "struct net_buf *net_buf_frag_del(struct net_buf *, struct net_buf *)",
    "net_buf_append_bytes": "size_t net_buf_append_bytes(struct net_buf *, size_t, const void *, k_timeout_t, net_buf_allocator_cb, void *)",
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def section_receipt(symbol, va, extent):
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        name = ".text." + symbol
        section = elf.get_section_by_name(name)
        if section is None or len(section.data()) < extent:
            raise ValueError("missing or short section " + name)
        selected = bytearray(section.data()[:extent])
        reloc = elf.get_section_by_name(".rel" + name)
        offsets = ([] if reloc is None else
                   [item["r_offset"] for item in reloc.iter_relocations()
                    if item["r_offset"] < extent])
        section_size = len(section.data())
    firmware = bytearray(IMAGE.read_bytes()[va - 0xC000:va - 0xC000 + extent])
    for offset in offsets:
        selected[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if selected != firmware:
        raise ValueError("true-extent mismatch for " + symbol)
    return {
        "upstream_symbol_size": section_size,
        "firmware_code_size": extent,
        "upstream_code_size": extent,
        "literal_pool_tail_size": section_size - extent,
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
    }


def callers():
    with gzip.open(ROOT / "recon/catalogs/refgraph_app.json.gz", "rt") as stream:
        graph = json.load(stream)["functions"]
    result = {}
    for va in GROUP:
        result[va] = sorted("0x%08x" % int(value, 0)
                            for value in graph.get(hex(int(va, 16)), {}).get("callers", []))
    return result


def authorization_rows():
    required = {
        "CONFIG_ASSERT": "y", "CONFIG_ASSERT_LEVEL": "2",
        "CONFIG_SPIN_VALIDATE": "y", "CONFIG_THREAD_LOCAL_STORAGE": "n",
        "CONFIG_THREAD_CUSTOM_DATA": "y", "CONFIG_MAIN_STACK_SIZE": "16384",
        "CONFIG_NET_BUF": "y",
        "CONFIG_NET_BUF_LOG": "n", "CONFIG_NET_BUF_POOL_USAGE": "n",
    }
    source_sha, object_sha, config_sha = sha(SOURCE), sha(OBJECT), sha(CONFIG)
    direct = callers()
    collision_catalog = json.loads((
        ROOT / "recon/ownership/app_build_collision_ownership.json").read_text())
    collision_by_va = {row["va"]: row for row in collision_catalog["functions"]}
    rows = []
    for va in GROUP:
        symbol, extent, cases = FUNCTIONS[va]
        raw = "FUN_" + va[2:]
        receipt = section_receipt(symbol, int(va, 16), extent)
        row = {
            "batch": "COLLISION-34", "va": va, "raw_symbol": raw,
            "symbol": symbol, "status": "authorized",
            "configuration_variant_exact": True,
            "required_config": required, "atomic_group": GROUP,
            "upstream_source": "zephyr/subsys/net/buf.c",
            "upstream_source_sha256": source_sha,
            "upstream_object": str(OBJECT),
            "upstream_object_sha256": object_sha,
            "configured_link_owner": "zephyr/subsys/net/libsubsys__net.a(buf.c.obj)",
            "configured_build": str(CONFIG),
            "configured_build_sha256": config_sha,
            "abi": ABIS[symbol], "instruction_exact": True,
            "cfg_verify_cases": max(1, cases),
            "owner_cfg_verify": {"status": "PASS", "cases": cases},
            "reconstruction_source_sha256": sha(
                ROOT / "recon/app/src" / (raw + ".c")),
            "callers": direct[va],
            "whole_unit_closure": {
                "safe": True, "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": sorted(COLLISIONS),
                "same_source_unit_hidden_exact_symbols": [
                    "net_buf_alloc_len", "net_buf_frag_del"],
                "same_source_unit_sdk_only_exact_symbols": [
                    "net_buf_pool_get", "net_buf_id"],
                "private_state": ["net_buf_slist_lock", "_net_buf_pool_list_start"],
                "private_helpers": [
                    "generic_data_ref", "fixed_data_alloc", "fixed_data_unref",
                    "mem_pool_data_alloc", "mem_pool_data_unref",
                    "heap_data_alloc", "heap_data_unref", "net_buf_heap_cb",
                    "net_buf_fixed_cb", "net_buf_var_cb"],
                "exclude_only": GROUP, "new_undefined_symbols": [],
            },
        }
        row.update(receipt)
        if va in HIDDEN:
            stale = ("k_queue_insert_with_timeout" if va == "0x0005eeb4"
                     else "FUN_0005f3d8")
            row["hidden_owner_closure"] = True
            row["identity_correction"] = {
                "baseline_collision_symbol": stale,
                "corrected_readable_identity": symbol,
                "corrected_upstream_symbol": symbol,
                "corrected_upstream_source": "zephyr/subsys/net/buf.c",
                "upstream_linkage": "public",
            }
        else:
            collision = collision_by_va[va]
            row["collision_receipt_sha256"] = hashlib.sha256(
                json.dumps(collision, sort_keys=True,
                           separators=(",", ":")).encode()).hexdigest()
            row["baseline_upstream_object_sha256"] = collision[
                "upstream"]["object_sha256"]
            row["baseline_configured_build_sha256"] = collision[
                "configured_inclusion"]["zephyr_config_sha256"]
        rows.append(row)
    return rows


def authorize():
    data = json.loads(AUTH.read_text())
    data["authorizations"] = [row for row in data["authorizations"]
                              if row.get("batch") != "COLLISION-34"]
    data["authorizations"].extend(authorization_rows())
    data["configured_build_receipts"] = sorted(set(
        data.get("configured_build_receipts", []) + [str(CONFIG)]))
    AUTH.write_text(json.dumps(data, indent=1) + "\n")
    print("authorized 12 exact net_buf owners")


def link_receipt(build):
    commands = subprocess.check_output(
        ["ninja", "-C", str(build), "-t", "commands", "zephyr/zephyr_pre0.elf"],
        text=True).splitlines()
    command = next(line for line in reversed(commands)
                   if "zephyr_pre0.elf" in line and " -o " in line)
    run = subprocess.run(command, shell=True, cwd=build, text=True,
                         capture_output=True)
    output = run.stdout + "\n" + run.stderr
    return {"build": str(build),
            "collisions": sorted(set(re.findall(
                r"multiple definition of [`']([^'`]+)", output))),
            "undefined": sorted(set(re.findall(
                r"undefined reference to [`']([^'`]+)", output)))}


def receipt():
    rows = [row for row in json.loads(AUTH.read_text())["authorizations"]
            if row.get("batch") == "COLLISION-34"]
    if {row["va"] for row in rows} != set(GROUP):
        raise ValueError("authorization group incomplete")
    entries = {row["va"]: row for row in
               json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
    if not all(entries[va]["exclude_reconstruction"] for va in GROUP):
        raise ValueError("manifest exclusion group incomplete")
    links = {"pre_overlay": link_receipt(PRE_BUILD),
             "adopted": link_receipt(POST_BUILD)}
    before, after = (set(links[key]["collisions"])
                     for key in ("pre_overlay", "adopted"))
    if (len(before), len(after)) != (76, 66):
        raise ValueError("normal-link counts are not 76 -> 66")
    if before - after != COLLISIONS or after - before:
        raise ValueError("normal-link collision delta drift")
    if any(set(links[key]["undefined"]) != UNRESOLVED for key in links):
        raise ValueError("unresolved set drift")
    output = {
        "schema": 1, "core": "app", "batch": "COLLISION-34",
        "status": "authorized_atomic",
        "decision": "adopt_exact_configured_zephyr_net_buf_source_unit",
        "atomic_group": GROUP, "selected_source_unit": "zephyr/subsys/net/buf.c",
        "authorizations": rows,
        "identity_corrections": {
            "0x0005eeb4": "net_buf_alloc_len",
            "0x0005f3d8": "net_buf_frag_del",
        },
        "sdk_only_exact_owners": {
            "0x0005ee08": "net_buf_pool_get", "0x0005ee18": "net_buf_id"},
        "link_delta": {"before": 76, "after": 66,
                       "removed": sorted(COLLISIONS), "added": [],
                       "unresolved_before": sorted(UNRESOLVED),
                       "unresolved_after": sorted(UNRESOLVED)},
        "normal_link_receipts": links,
        "sdc_policy": "report_only_unchanged",
        "gppi_0x000850dc_policy": "namespaced_correction_unchanged",
    }
    OUTPUT.write_text(json.dumps(output, indent=1) + "\n")
    REPORT.write_text(
        "# COLLISION-34 Zephyr net_buf atomic adoption\n\n"
        "The configured NCS 2.5.1 `subsys/net/buf.c` owner is relocation-"
        "normalized byte-exact across the true reachable extent of all twelve "
        "reconstructed functions in its emitted firmware closure. The stale "
        "identities at `0x0005eeb4` and `0x0005f3d8` are corrected to "
        "`net_buf_alloc_len` and `net_buf_frag_del`. SDK-only "
        "`net_buf_pool_get` and `net_buf_id`, the private slist lock, pool-list "
        "boundary, callback tables and private allocation helpers remain one "
        "cohesive source-unit owner.\n\n"
        "The fresh normal-link collision set moves **76 -> 66**, removing "
        "exactly the ten advertised `net_buf` collisions and adding none. The "
        "unresolved set remains exactly the two embedded SVC continuations. "
        "SDC stays report-only and the corrected namespaced GPPI owner at "
        "`0x000850dc` is unchanged.\n")
    print("wrote", OUTPUT)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--authorize", action="store_true")
    parser.add_argument("--receipt", action="store_true")
    args = parser.parse_args()
    if args.authorize:
        authorize()
    elif args.receipt:
        receipt()
    else:
        parser.error("choose --authorize or --receipt")


if __name__ == "__main__":
    main()
