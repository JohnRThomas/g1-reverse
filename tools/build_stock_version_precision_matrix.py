#!/usr/bin/env python3
"""Build the fail-closed stock component/version precision matrix."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
SDK = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1")
OUTPUT = ROOT / "recon/catalogs/stock_version_precision_matrix.json"

RELEASES = ("v2.4.2", "v2.5.0", "v2.5.1", "v2.5.2", "v2.6.0")
ARCHIVES = {
    "mpsl_net": "mpsl/lib/cortex-m33+nodsp/soft-float/libmpsl.a",
    "sdc_multirole_net": (
        "softdevice_controller/lib/cortex-m33+nodsp/soft-float/"
        "libsoftdevice_controller_multirole.a"),
    "oberon_3_0_13_net": (
        "crypto/nrf_oberon/lib/cortex-m33+nodsp/soft-float/"
        "liboberon_3.0.13.a"),
    "oberon_3_0_14_net": (
        "crypto/nrf_oberon/lib/cortex-m33+nodsp/soft-float/"
        "liboberon_3.0.14.a"),
    "cc312_0_9_18_app": (
        "crypto/nrf_cc312_platform/lib/cortex-m33/hard-float/no-interrupts/"
        "libnrf_cc312_platform_0.9.18.a"),
    "cc312_0_9_19_app": (
        "crypto/nrf_cc312_platform/lib/cortex-m33/hard-float/no-interrupts/"
        "libnrf_cc312_platform_0.9.19.a"),
}
IMPORTED_PROJECTS = {
    "hal_nordic": NCS / "modules/hal/nordic",
    "liblc3": NCS / "modules/lib/liblc3",
    "libmetal": NCS / "modules/hal/libmetal",
    "open-amp": NCS / "modules/lib/open-amp",
    "tinycrypt": NCS / "modules/crypto/tinycrypt",
    "zcbor": NCS / "modules/lib/zcbor",
}


def run(*args, binary=False, check=True):
    result = subprocess.run(args, check=check, stdout=subprocess.PIPE,
                            stderr=subprocess.DEVNULL)
    return result.stdout if binary else result.stdout.decode().strip()


def git(repo, *args, binary=False, check=True):
    return run("git", "-C", str(repo), *args, binary=binary, check=check)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def file_sha(path):
    return sha256(path.read_bytes())


def manifest_revision(text, project):
    match = re.search(
        r"^\s*- name: " + re.escape(project) +
        r"\s*$.*?^\s*revision:\s*(\S+)\s*$", text,
        flags=re.MULTILINE | re.DOTALL)
    if not match:
        raise ValueError("missing %s revision" % project)
    return match.group(1)


def object_exists(repo, spec):
    result = subprocess.run(
        ("git", "-C", str(repo), "cat-file", "-e", spec),
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return result.returncode == 0


def build():
    manifest = json.loads((ROOT / "manifest.json").read_text())
    reported = manifest["firmware"]
    nrf_repo = NCS / "nrf"
    zephyr_repo = NCS / "zephyr"
    nrfxlib_repo = NCS / "nrfxlib"

    releases = []
    archive_rows = []
    for release in RELEASES:
        west = git(nrf_repo, "show", "%s:west.yml" % release)
        zephyr_revision = manifest_revision(west, "zephyr")
        nrfxlib_revision = manifest_revision(west, "nrfxlib")
        zephyr_west = git(
            zephyr_repo, "show", "%s^{}:west.yml" % zephyr_revision)
        modules = {}
        for project, repo in IMPORTED_PROJECTS.items():
            revision = manifest_revision(zephyr_west, project)
            modules[project] = {
                "revision": revision,
                "commit": git(repo, "rev-parse", "%s^{}" % revision),
            }
        releases.append({
            "ncs_release": release,
            "nrf_commit": git(nrf_repo, "rev-parse", "%s^{}" % release),
            "zephyr_revision": zephyr_revision,
            "zephyr_commit": git(
                zephyr_repo, "rev-parse", "%s^{}" % zephyr_revision),
            "nrfxlib_revision": nrfxlib_revision,
            "nrfxlib_commit": git(
                nrfxlib_repo, "rev-parse", "%s^{}" % nrfxlib_revision),
            "zephyr_imported_modules": modules,
        })
        hashes = {}
        for name, path in ARCHIVES.items():
            spec = "%s:%s" % (nrfxlib_revision, path)
            if object_exists(nrfxlib_repo, spec):
                hashes[name] = sha256(git(
                    nrfxlib_repo, "show", spec, binary=True))
        archive_rows.append({
            "ncs_release": release,
            "nrfxlib_revision": nrfxlib_revision,
            "archives": hashes,
        })

    app_libc = (SDK / "arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/"
                "v8-m.main+fp/hard/libc_nano.a")
    app_libm = (SDK / "arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/"
                "v8-m.main+fp/hard/libm_nano.a")
    net_libc = (SDK / "arm-zephyr-eabi/picolibc/arm-zephyr-eabi/lib/thumb/"
                "v8-m.main/nofp/libc.a")
    picolibc_h = SDK / "arm-zephyr-eabi/picolibc/include/picolibc.h"
    picolibc_text = picolibc_h.read_text()
    picolibc_version = re.search(
        r'^#define _PICOLIBC_VERSION "([^"]+)"', picolibc_text,
        re.MULTILINE).group(1)

    zcbor_repo = NCS / "modules/lib/zcbor"
    zcbor_interval = (
        "e01ea4efa176398ab180230567dadba9df30c011",
        "c9d2c8d29dff31d52be8157b7156766b968612b2",
        "67fd8bb88d3136738661fa8bb5f9989103f4599e",
    )
    if not all(object_exists(zcbor_repo, commit) for commit in zcbor_interval):
        raise ValueError("zcbor source-body interval is unavailable")
    img_mgmt_tags = (
        "v3.4.99-ncs1-1", "v3.4.99-ncs1-2", "v3.4.99-ncs1-3")
    img_mgmt_path = "subsys/mgmt/mcumgr/grp/img_mgmt/src/img_mgmt.c"
    img_mgmt_blobs = {
        git(zephyr_repo, "rev-parse", "%s^{}:%s" % (tag, img_mgmt_path))
        for tag in img_mgmt_tags
    }
    if img_mgmt_blobs != {"305cad41c4459b1e5fea46b9ce06383a535a20dc"}:
        raise ValueError("img_mgmt source-body family changed")

    mpsl_hash = archive_rows[1]["archives"]["mpsl_net"]
    sdc_hash = archive_rows[1]["archives"]["sdc_multirole_net"]
    return {
        "schema": 1,
        "claim_model": [
            "firmware_reported_identity",
            "public_manifest_baseline",
            "archive_blob_identity",
            "selected_member_or_section_identity",
            "binary_equivalence_family",
            "source_body_interval",
            "configuration_and_abi",
        ],
        "firmware_identity": {
            "nrf_reported_revision": reported["nrf"]["revision"],
            "zephyr_reported_revision": reported["zephyr"]["revision"],
            "zephyr_reported_commit_available_locally": object_exists(
                zephyr_repo,
                reported["zephyr"]["revision"].removesuffix("-dirty")),
            "public_ncs_2_5_1_zephyr_baseline":
                "83980fe1679441be9b0e1db556a353f6118fe14f",
            "interpretation": (
                "The private dirty Zephyr identity is firmware-reported. "
                "The public NCS 2.5.1 Zephyr checkout is a configured "
                "comparison baseline, not the firmware manifest pin."),
        },
        "adjacent_ncs_manifests": releases,
        "nrfxlib_archive_matrix": archive_rows,
        "binary_equivalence_families": {
            "mpsl_net_exact_archive": {
                "sha256": mpsl_hash,
                "ncs_releases": ["v2.5.0", "v2.5.1"],
                "excludes_sampled": ["v2.4.2", "v2.5.2", "v2.6.0"],
            },
            "sdc_multirole_net_exact_archive": {
                "sha256": sdc_hash,
                "ncs_releases": ["v2.5.0", "v2.5.1"],
                "excludes_sampled": ["v2.4.2", "v2.5.2", "v2.6.0"],
                "adoption_authority": "report_only_private_sdc",
            },
            "oberon_3_0_13_archive": {
                "sha256": archive_rows[0]["archives"]["oberon_3_0_13_net"],
                "ncs_releases": [
                    "v2.4.2", "v2.5.0", "v2.5.1", "v2.5.2"],
                "firmware_proof": (
                    "nine selected P-256 bodies; not whole-archive identity"),
            },
            "cc312_0_9_18_archive": {
                "sha256": archive_rows[1]["archives"]["cc312_0_9_18_app"],
                "ncs_releases": ["v2.5.0", "v2.5.1", "v2.5.2"],
                "firmware_proof": "89 selected sections across 31 members",
            },
        },
        "toolchain_by_core": {
            "app": {
                "sdk_package": "Zephyr SDK 0.16.5-1",
                "compiler": "GCC 12.2.0",
                "libc": "newlib-nano 3.3.0",
                "abi": "Cortex-M33, hard-float, -Os",
                "libc_archive": str(app_libc.relative_to(SDK)),
                "libc_archive_sha256": file_sha(app_libc),
                "libm_archive": str(app_libm.relative_to(SDK)),
                "libm_archive_sha256": file_sha(app_libm),
                "proof": "exact archive members and selected sections",
            },
            "net": {
                "sdk_package": "Zephyr SDK 0.16.5-1",
                "compiler": "GCC 12.2.0",
                "libc": "picolibc %s" % picolibc_version,
                "abi": "Cortex-M33+nodsp, soft-float, -Os",
                "reference_libc_archive": str(net_libc.relative_to(SDK)),
                "reference_libc_archive_sha256": file_sha(net_libc),
                "proof": (
                    "configured-reference link members plus exact normalized "
                    "function bodies; no firmware whole-archive proof"),
            },
        },
        "source_body_intervals": {
            "zcbor_process_backup": {
                "repository": "modules/lib/zcbor",
                "first_identical_commit_inclusive":
                    zcbor_interval[0],
                "first_changed_commit_exclusive":
                    zcbor_interval[1],
                "manifest_commit":
                    zcbor_interval[2],
                "interpretation": (
                    "body interval contains the manifest commit but does not "
                    "uniquely identify it"),
            },
            "zephyr_img_mgmt_c": {
                "repository": "zephyr",
                "git_blob": "305cad41c4459b1e5fea46b9ce06383a535a20dc",
                "identical_tags": list(img_mgmt_tags),
                "interpretation": (
                    "exact configured bodies cannot select one of these "
                    "public patch tags"),
            },
        },
        "policy": {
            "manifest_pin_is_not_binary_unique": True,
            "public_zephyr_baseline_is_not_private_dirty_identity": True,
            "archive_hash_is_not_selected_member_proof": True,
            "body_match_is_not_whole_archive_identity": True,
            "private_sdc_report_only": True,
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=1, sort_keys=False) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise SystemExit("stock version precision matrix is stale")
        print("stock version precision matrix is current")
    else:
        OUTPUT.write_text(rendered)
        print("wrote %s" % OUTPUT)


if __name__ == "__main__":
    main()
