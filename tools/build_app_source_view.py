#!/usr/bin/env python3
"""Build the human-readable, G1-owned CPUAPP source view.

The parity corpus in recon/named intentionally contains both product code and
statically linked dependencies.  This tool creates recon/application/src as a
symlink view containing only sources currently attributed to the G1 product.
"""

from __future__ import annotations

import argparse
import gzip
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
NAMED = ROOT / "recon" / "named"
DEST = ROOT / "recon" / "application" / "src"
MANIFEST = ROOT / "recon" / "application" / "application_sources.json"

# These families are unambiguously owned by the pinned toolchain, Zephyr/NCS,
# or bundled third-party libraries.  This supplements the older classifier,
# which incorrectly called several statically linked library bodies APPLICATION.
STOCK_PREFIXES = (
    "_",
    "arm_core_mpu_",
    "arm_fault_",
    "arm_mpu_",
    "att_",
    "bigint_",
    "bignum_",
    "bt_att_",
    "bt_conn_",
    "bt_gatt_",
    "bt_hci_",
    "bt_keys_",
    "bt_le_",
    "bt_security_",
    "bt_settings_",
    "bt_smp_",
    "cbor_decode_",
    "cbor_encode_",
    "cjson_",
    "gatt_",
    "gpiote_",
    "gpio_manage_",
    "gpio_nrfx_",
    "gpio_pin_",
    "k_",
    "l2cap_",
    "lc3_",
    "libc_",
    "mbedtls_",
    "md5_",
    "metal_",
    "net_buf_",
    "nrf_gpio_",
    "nrf_gpiote_",
    "nrfx_",
    "nvs_",
    "ocrypto_",
    "psa_",
    "pthread_",
    "rpmsg_",
    "sched_",
    "settings_nvs_",
    "smp_",
    "stdio_",
    "strtod_",
    "tc_",
    "vdprintf_",
    "vfprintf_",
    "virtqueue_",
    "vsnprintf_",
    "vsprintf_",
    "z_",
    "zcbor_",
)

STOCK_EXACT_NAMES = {
    "Balloc",
    "Bfree",
    "alloc_chunk",
    "alloc_zeroed_node",
    "asinf",
    "atanf",
    "calloc",
    "crc32_table_init",
    "crc32_update",
    "d2b",
    "dcmp_negate_rhs",
    "dtoa",
    "dtoa_format_cvt",
    "exp",
    "expf",
    "fabsf",
    "fmaxf",
    "fminf",
    "free",
    "malloc",
    "malloc_impl",
    "memcmp",
    "memcpy",
    "memmove",
    "memset",
    "mutex_lock_wait_forever",
    "mutex_lock_wait_forever_dup",
    "mutex_unlock_syscall_handler",
    "nan",
    "posix_stub_enosys",
    "posix_stub_zero",
    "printf",
    "rand",
    "random",
    "realloc",
    "scalbn",
    "sqrtf",
    "strcpy",
    "strlen",
    "strncmp",
    "strncpy",
    "strtol",
    "strtoul",
    "sys_dlist_init",
    "sys_rand32_get",
    "vprintf",
    "log_dropped",
    "log_msg_commit",
    "log_msg_pool_init",
    "log_process",
    "settings_invalid_index_log",
}

# This is G1 product integration code despite calling the stock LC3 library.
PRODUCT_OVERRIDES = {"app_codec_lc3_test"}


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    h.update(path.read_bytes())
    return h.hexdigest()


def load_inputs() -> tuple[dict, dict, dict[str, dict]]:
    classified_path = ROOT / "recon" / "catalogs" / "classified.json.gz"
    names_path = ROOT / "recon" / "catalogs" / "function_names_app.json"
    adoption_path = ROOT / "recon" / "ownership" / "adoption_manifest.json"
    with gzip.open(classified_path, "rt") as stream:
        classified = json.load(stream)
    names = json.loads(names_path.read_text())
    adoption = json.loads(adoption_path.read_text())
    return classified, names, {
        entry["va"].lower(): entry for entry in adoption["cores"]["app"]["entries"]
    }


def build_manifest() -> dict:
    classified, names, adopted = load_inputs()
    by_address = names["by_address"]
    old_class = {
        f"0x{entry['entry']:08x}": entry for entry in classified["functions"]
    }
    rows = []
    # function_names_app also contains vector/table labels for which there is no
    # reconstructed body.  The readable corpus is the authoritative body set.
    for source in sorted(NAMED.glob("*.c")):
        name = source.stem
        address = names["by_name"].get(name)
        if address is None:
            raise RuntimeError(f"readable source has no durable identity: {source}")
        identity = by_address[address]

        reasons = []
        old = old_class.get(address.lower())
        if old and old.get("class") == "LIBRARY":
            reasons.append("legacy_classifier:LIBRARY")
        if address.lower() in adopted:
            owner = adopted[address.lower()]
            reasons.append(f"upstream_owner:{owner['component']}")
        if name not in PRODUCT_OVERRIDES:
            if name in STOCK_EXACT_NAMES:
                reasons.append("known_stock_symbol")
            prefix = next((p for p in STOCK_PREFIXES if name.startswith(p)), None)
            if prefix:
                reasons.append(f"known_stock_namespace:{prefix}")

        status = "excluded_library" if reasons else "included_g1_application"
        rows.append(
            {
                "address": address.lower(),
                "raw_symbol": identity["raw_name"],
                "readable_name": name,
                "source": f"recon/named/{source.name}",
                "status": status,
                "reasons": sorted(set(reasons)),
            }
        )

    included = sum(row["status"] == "included_g1_application" for row in rows)
    excluded = len(rows) - included
    inputs = [
        ROOT / "recon" / "catalogs" / "classified.json.gz",
        ROOT / "recon" / "catalogs" / "function_names_app.json",
        ROOT / "recon" / "ownership" / "adoption_manifest.json",
    ]
    return {
        "schema": 1,
        "core": "CPUAPP",
        "purpose": "G1-owned application source view; bundled/toolchain/Zephyr/NCS library bodies excluded",
        "canonical_source_root": "recon/named",
        "view_root": "recon/application/src",
        "policy": {
            "upstream_manifest_entries_are_library_even_when_the_build_temporarily_retains_a_reconstruction": True,
            "ambiguous_unclassified_functions_remain_application_candidates": True,
            "product_overrides": sorted(PRODUCT_OVERRIDES),
            "stock_prefixes": list(STOCK_PREFIXES),
            "stock_exact_names": sorted(STOCK_EXACT_NAMES),
        },
        "inputs": [
            {"path": str(path.relative_to(ROOT)), "sha256": sha256(path)} for path in inputs
        ],
        "summary": {
            "total_cpuapp_functions": len(rows),
            "included_g1_application": included,
            "excluded_library": excluded,
        },
        "functions": rows,
    }


def expected_links(manifest: dict) -> dict[str, str]:
    return {
        Path(row["source"]).name: f"../../named/{Path(row['source']).name}"
        for row in manifest["functions"]
        if row["status"] == "included_g1_application"
    }


def check(manifest: dict) -> None:
    expected_text = json.dumps(manifest, indent=2) + "\n"
    if not MANIFEST.is_file() or MANIFEST.read_text() != expected_text:
        raise SystemExit(f"stale or missing {MANIFEST.relative_to(ROOT)}")
    links = expected_links(manifest)
    actual = {p.name: str(p.readlink()) for p in DEST.glob("*.c") if p.is_symlink()}
    if actual != links:
        missing = sorted(set(links) - set(actual))
        extra = sorted(set(actual) - set(links))
        wrong = sorted(k for k in set(actual) & set(links) if actual[k] != links[k])
        raise SystemExit(f"source view mismatch: missing={missing[:8]} extra={extra[:8]} wrong={wrong[:8]}")
    regular_c = [p for p in DEST.glob("*.c") if not p.is_symlink()]
    if regular_c:
        raise SystemExit(f"unexpected copied sources: {regular_c[:8]}")


def write(manifest: dict) -> None:
    DEST.mkdir(parents=True, exist_ok=True)
    links = expected_links(manifest)
    for path in DEST.glob("*.c"):
        if path.is_symlink():
            path.unlink()
        else:
            raise SystemExit(f"refusing to remove non-symlink source: {path}")
    for filename, target in links.items():
        (DEST / filename).symlink_to(target)
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    manifest = build_manifest()
    if args.check:
        check(manifest)
    else:
        write(manifest)
        print(json.dumps(manifest["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
