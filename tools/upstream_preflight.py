#!/usr/bin/env python3
"""Read-only identity and ABI preflight for pinned upstream firmware inputs.

The check deliberately uses the manifests at their pinned commits, rather
than trusting a dirty working-tree manifest or a coincidentally compatible
tag.  It never fetches, checks out, or modifies an SDK repository.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_NCS_ROOT = Path("/Users/freedomcoder/ncs251")
DEFAULT_SDK_ROOT = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1")
PROVENANCE_CATALOG = REPO_ROOT / "recon/catalogs/upstream_library_provenance.json"
DEFAULT_READELF = Path(
    "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
    "arm-zephyr-eabi-readelf"
)

NCS_COMMIT = "87355af5914e498f449b7a68bb5641031a7b8885"
NCS_TAG_OBJECT = "7c67e402e5241d3cb2986980990966af13f4ea59"
EXPECTED_PROJECTS = {
    "zephyr": {
        "path": "zephyr",
        "revision": "v3.4.99-ncs1-1",
        "commit": "83980fe1679441be9b0e1db556a353f6118fe14f",
        "tag_object": "8a1e36784e9a499c8d2a748ef9136964e149f383",
        "manifest": "nrf",
    },
    "liblc3": {
        "path": "modules/lib/liblc3",
        "revision": "448f3de31f49a838988a162ef1e23a89ddf2d2ed",
        "commit": "448f3de31f49a838988a162ef1e23a89ddf2d2ed",
        "manifest": "zephyr",
    },
    "libmetal": {
        "path": "modules/hal/libmetal",
        "revision": "b91611a6f47dd29fb24c46e5621e797557f80ec6",
        "commit": "b91611a6f47dd29fb24c46e5621e797557f80ec6",
        "manifest": "zephyr",
        "manifest_project": "libmetal",
    },
    "openamp": {
        "path": "modules/lib/open-amp",
        "revision": "42b7c577714b8f22ce82a901e19c1814af4609a8",
        "commit": "42b7c577714b8f22ce82a901e19c1814af4609a8",
        "manifest": "zephyr",
        "manifest_project": "open-amp",
    },
    "hal_nordic": {
        "path": "modules/hal/nordic",
        "revision": "9784731461018d3e983604698fbbed6af2bea801",
        "commit": "9784731461018d3e983604698fbbed6af2bea801",
        "manifest": "zephyr",
    },
    "tinycrypt": {
        "path": "modules/crypto/tinycrypt",
        "revision": "3e9a49d2672ec01435ffbf0d788db6d95ef28de0",
        "commit": "3e9a49d2672ec01435ffbf0d788db6d95ef28de0",
        "manifest": "zephyr",
    },
    "mbedtls": {
        "path": "modules/crypto/mbedtls",
        "revision": "v3.3.0-ncs2-1",
        "tag_object": "40fbf20133b2943cd19ca7f2725ec588fb44cbd2",
        "commit": "acea48fc8a5eb227033b55e6ec012731218e257f",
        "manifest": "nrf",
    },
    "nrfxlib": {
        "path": "nrfxlib",
        "revision": "v2.5.1",
        "tag_object": "fd77d02ef285522c2361207d500b0758f423ca04",
        "commit": "ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7",
        "manifest": "nrf",
    },
    "trusted-firmware-m": {
        "path": "modules/tee/tf-m/trusted-firmware-m",
        "revision": "v1.8.0-ncs1-1",
        "tag_object": "5d54c71cf081e3e4f491dff9251886c0e2f11ed9",
        "commit": "1ceee76478554927bbe18dd206dfac5ea40ff100",
        "manifest": "nrf",
    },
}

ARCHIVES = {
    "cc312_platform": {
        "relative_path": (
            "nrfxlib/crypto/nrf_cc312_platform/lib/cortex-m33/"
            "hard-float/no-interrupts/libnrf_cc312_platform_0.9.18.a"
        ),
        "sha256": "80a253291ae78f26b2d38cdccac20c8420f1545b85a476c3029eb92286d9159e",
        "catalog": "recon/catalogs/cc312_archive_ownership.json",
        "catalog_component": None,
        "member_count": 59,
        "abi": "cortex-m33-hard-float",
    },
    "softdevice_controller": {
        "relative_path": (
            "nrfxlib/softdevice_controller/lib/cortex-m33+nodsp/soft-float/"
            "libsoftdevice_controller_multirole.a"
        ),
        "sha256": "f218b3dc4badd8f534f4aa00db678f54a1d4795d7d39721f28401fb49e880e81",
        "catalog": "recon/catalogs/upstream_crypto_ownership.json",
        "catalog_component": "softdevice_controller",
        "member_count": 1,
        "abi": "cortex-m33-soft-float-nodsp-multirole",
    },
    "oberon_net": {
        "relative_path": (
            "nrfxlib/crypto/nrf_oberon/lib/cortex-m33+nodsp/soft-float/"
            "liboberon_3.0.13.a"
        ),
        "sha256": "466f575748e64a8a170ed796a4edcd8a489517b5dd108b0f4295eea8ebb082f6",
        "member_count": None,
        "abi": "cortex-m33-soft-float-nodsp",
        "check_nodsp_attributes": False,
    },
    "mpsl_net": {
        "relative_path": (
            "nrfxlib/mpsl/lib/cortex-m33+nodsp/soft-float/libmpsl.a"
        ),
        "sha256": "127d76d156af342f8cb0e0bea7f6cc2712368f8219e6c9d3d24fe972a327e8af",
        "member_count": 1,
        "abi": "cortex-m33-soft-float-nodsp",
    },
}


def run(*args: str, cwd: Path | None = None) -> str:
    proc = subprocess.run(
        args, cwd=cwd, text=True, stdout=subprocess.PIPE,
        stderr=subprocess.PIPE, check=False,
    )
    if proc.returncode:
        detail = proc.stderr.strip() or proc.stdout.strip()
        raise RuntimeError(f"{' '.join(args)} failed: {detail}")
    return proc.stdout.strip()


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def project_revision(manifest: str, project: str) -> str | None:
    """Extract one project's revision from the restricted west YAML shape."""
    lines = manifest.splitlines()
    wanted_indent: int | None = None
    for index, line in enumerate(lines):
        match = re.match(r"^(\s*)-\s+name:\s*([^\s#]+)", line)
        if not match or match.group(2) != project:
            continue
        wanted_indent = len(match.group(1))
        for following in lines[index + 1 :]:
            next_project = re.match(r"^(\s*)-\s+name:\s*", following)
            if next_project and len(next_project.group(1)) <= wanted_indent:
                return None
            revision = re.match(r"^\s+revision:\s*([^\s#]+)", following)
            if revision:
                return revision.group(1).strip("'\"")
        return None
    return None


def attribute_blocks(output: str) -> list[dict[str, str]]:
    blocks: list[dict[str, str]] = []
    current: dict[str, str] | None = None
    for line in output.splitlines():
        if line.startswith("File: "):
            current = {"file": line[6:].strip()}
            blocks.append(current)
            continue
        match = re.match(r"\s+(Tag_[^:]+):\s*(.*)", line)
        if current is not None and match:
            current[match.group(1)] = match.group(2)
    return blocks


def check_item(checks: list[dict[str, Any]], name: str, expected: Any,
               actual: Any, detail: str = "") -> None:
    checks.append({
        "name": name,
        "status": "pass" if actual == expected else "fail",
        "expected": expected,
        "actual": actual,
        "detail": detail,
    })


def load_catalog_archive(component: str, spec: dict[str, Any]) -> tuple[str, str]:
    data = json.loads((REPO_ROOT / spec["catalog"]).read_text())
    if spec["catalog_component"] is None:
        return data["archive"], data["archive_sha256"]
    component_data = data["components"][spec["catalog_component"]]
    return component_data["archive"], component_data["sha256"]


def perform_checks(ncs_root: Path, readelf: Path,
                   sdk_root: Path = DEFAULT_SDK_ROOT) -> dict[str, Any]:
    checks: list[dict[str, Any]] = []
    nrf = ncs_root / "nrf"

    try:
        provenance = json.loads(PROVENANCE_CATALOG.read_text())
        ota = json.loads((REPO_ROOT / "manifest.json").read_text())
        firmware = provenance["firmware_manifest"]
        check_item(checks, "provenance.schema", 1, provenance.get("schema"))
        check_item(checks, "ota.ncs.reported_revision",
                   firmware["ncs_reported_revision"],
                   ota["firmware"]["nrf"]["revision"])
        check_item(checks, "ota.zephyr.reported_revision",
                   firmware["zephyr_reported_revision"],
                   ota["firmware"]["zephyr"]["revision"])
        check_item(checks, "ota.zephyr.public_baseline_is_not_firmware_commit",
                   True,
                   firmware["zephyr_base_commit"] !=
                   firmware["zephyr_public_ncs_baseline"])
        check_item(checks, "policy.private_sdc_report_only", True,
                   provenance["policy"].get("private_sdc_report_only"))
    except (OSError, KeyError, json.JSONDecodeError) as error:
        provenance = {}
        checks.append({"name": "provenance.load", "status": "fail",
                       "detail": str(error)})

    try:
        local_pin = project_revision((REPO_ROOT / "recon/west.yml").read_text(), "sdk-nrf")
        check_item(checks, "recon_manifest.sdk-nrf.revision", NCS_COMMIT, local_pin)
        check_item(checks, "ncs.checkout.head", NCS_COMMIT,
                   run("git", "rev-parse", "HEAD", cwd=nrf))
        check_item(checks, "ncs.tag.v2.5.1.object", NCS_TAG_OBJECT,
                   run("git", "rev-parse", "v2.5.1", cwd=nrf))
        check_item(checks, "ncs.tag.v2.5.1.commit", NCS_COMMIT,
                   run("git", "rev-parse", "v2.5.1^{}", cwd=nrf))
        nrf_manifest = run("git", "show", f"{NCS_COMMIT}:west.yml", cwd=nrf)
        zephyr_manifest = run(
            "git", "show", f"{EXPECTED_PROJECTS['zephyr']['commit']}:west.yml",
            cwd=ncs_root / "zephyr",
        )
    except (OSError, RuntimeError) as error:
        checks.append({"name": "manifest.load", "status": "fail", "detail": str(error)})
        nrf_manifest = ""
        zephyr_manifest = ""

    for name, spec in EXPECTED_PROJECTS.items():
        repo = ncs_root / spec["path"]
        manifest = nrf_manifest if spec["manifest"] == "nrf" else zephyr_manifest
        manifest_project = spec.get("manifest_project", name)
        check_item(checks, f"manifest.{name}.revision", spec["revision"],
                   project_revision(manifest, manifest_project))
        if not repo.is_dir():
            checks.append({"name": f"repo.{name}.exists", "status": "fail",
                           "expected": True, "actual": False, "detail": str(repo)})
            continue
        try:
            head = run("git", "rev-parse", "HEAD", cwd=repo)
            check_item(checks, f"repo.{name}.head", spec["commit"], head, str(repo))
            revision_object = run("git", "rev-parse", spec["revision"], cwd=repo)
            peeled = run("git", "rev-parse", f"{spec['revision']}^{{}}", cwd=repo)
            check_item(checks, f"repo.{name}.revision_commit", spec["commit"], peeled)
            if "tag_object" in spec:
                check_item(checks, f"repo.{name}.tag_object", spec["tag_object"],
                           revision_object)
            elif re.fullmatch(r"[0-9a-f]{40}", spec["revision"]):
                check_item(checks, f"repo.{name}.revision_object", spec["commit"],
                           revision_object)
        except RuntimeError as error:
            checks.append({"name": f"repo.{name}.git", "status": "fail",
                           "detail": str(error)})
        catalog_name = {"openamp": "openamp"}.get(name, name)
        if catalog_name in {"liblc3", "libmetal", "openamp", "hal_nordic",
                            "tinycrypt", "mbedtls", "nrfxlib"}:
            try:
                catalog_project = provenance["source_projects"][catalog_name]
                check_item(checks, f"provenance.{name}.path", spec["path"],
                           catalog_project["path"])
                check_item(checks, f"provenance.{name}.commit", spec["commit"],
                           catalog_project["commit"])
            except (KeyError, TypeError) as error:
                checks.append({"name": f"provenance.{name}", "status": "fail",
                               "detail": str(error)})

    for component, spec in ARCHIVES.items():
        archive = ncs_root / spec["relative_path"]
        if "catalog" in spec:
            try:
                catalog_path, catalog_sha = load_catalog_archive(component, spec)
                check_item(checks, f"archive.{component}.catalog_path", str(archive), catalog_path)
                check_item(checks, f"archive.{component}.catalog_sha256", spec["sha256"], catalog_sha)
            except (OSError, KeyError, json.JSONDecodeError) as error:
                checks.append({"name": f"archive.{component}.catalog", "status": "fail",
                               "detail": str(error)})
        try:
            catalog_archive = provenance["prebuilt_archives"][component]
            check_item(checks, f"archive.{component}.provenance_path",
                       spec["relative_path"], catalog_archive["path"])
            check_item(checks, f"archive.{component}.provenance_sha256",
                       spec["sha256"], catalog_archive["sha256"])
        except (KeyError, TypeError) as error:
            checks.append({"name": f"archive.{component}.provenance",
                           "status": "fail", "detail": str(error)})
        if not archive.is_file():
            checks.append({"name": f"archive.{component}.exists", "status": "fail",
                           "expected": True, "actual": False, "detail": str(archive)})
            continue
        check_item(checks, f"archive.{component}.sha256", spec["sha256"], sha256(archive))
        try:
            blocks = attribute_blocks(run(str(readelf), "-A", str(archive)))
            if spec.get("member_count") is not None:
                check_item(checks, f"archive.{component}.member_count",
                           spec["member_count"], len(blocks))
            cpu_ok = bool(blocks) and all(
                block.get("Tag_CPU_arch") == "v8-M.mainline" and
                block.get("Tag_CPU_arch_profile") == "Microcontroller"
                for block in blocks
            )
            check_item(checks, f"archive.{component}.cortex_m33_attributes", True, cpu_ok)
            if "hard-float" in spec["abi"]:
                hard_float = bool(blocks) and all(
                    block.get("Tag_ABI_VFP_args") == "VFP registers" and
                    "FPv5/FP-D16" in block.get("Tag_FP_arch", "")
                    for block in blocks
                )
                check_item(checks, f"archive.{component}.hard_float_abi", True, hard_float)
                check_item(checks, f"archive.{component}.variant_path", True,
                           "/hard-float/no-interrupts/" in archive.as_posix())
            else:
                soft_float = bool(blocks) and all(
                    "Tag_ABI_VFP_args" not in block and "Tag_FP_arch" not in block
                    for block in blocks
                )
                nodsp = bool(blocks) and all("Tag_DSP_extension" not in block for block in blocks)
                check_item(checks, f"archive.{component}.soft_float_abi", True, soft_float)
                if spec.get("check_nodsp_attributes", True):
                    check_item(checks, f"archive.{component}.nodsp_attributes", True, nodsp)
                check_item(checks, f"archive.{component}.nodsp_variant_path", True,
                           "/cortex-m33+nodsp/soft-float/" in archive.as_posix())
                if component == "softdevice_controller":
                    check_item(checks, f"archive.{component}.multirole_variant_path", True,
                               archive.name.endswith("_multirole.a"))
        except (OSError, RuntimeError) as error:
            checks.append({"name": f"archive.{component}.attributes", "status": "fail",
                           "detail": str(error)})

    try:
        toolchain = provenance["toolchain"]
        gcc = sdk_root / toolchain["gcc_path"]
        libc = sdk_root / toolchain["libc_nano_path"]
        check_item(checks, "toolchain.gcc.sha256", toolchain["gcc_sha256"],
                   sha256(gcc))
        check_item(checks, "toolchain.libc_nano.sha256",
                   toolchain["libc_nano_sha256"], sha256(libc))
        version_header = (sdk_root / "arm-zephyr-eabi/arm-zephyr-eabi/include/"
                          "_newlib_version.h").read_text()
        match = re.search(r'#define\s+_NEWLIB_VERSION\s+"([^"]+)"',
                          version_header)
        check_item(checks, "toolchain.newlib.version",
                   toolchain["newlib_version"], match.group(1) if match else None)
        gcc_version = run(str(gcc), "-dumpfullversion")
        check_item(checks, "toolchain.gcc.version",
                   toolchain["gcc_version"], gcc_version)
    except (OSError, KeyError, RuntimeError) as error:
        checks.append({"name": "toolchain.identity", "status": "fail",
                       "detail": str(error)})

    failed = sum(check["status"] == "fail" for check in checks)
    return {
        "schema": 1,
        "tool": "tools/upstream_preflight.py",
        "mode": "read-only",
        "ncs_root": str(ncs_root),
        "provenance_catalog": str(PROVENANCE_CATALOG),
        "summary": {"checks": len(checks), "passed": len(checks) - failed, "failed": failed},
        "checks": checks,
    }


def render_text(report: dict[str, Any]) -> str:
    lines = []
    for check in report["checks"]:
        status = check["status"].upper()
        line = f"{status:4} {check['name']}"
        if status == "FAIL":
            line += f" expected={check.get('expected')!r} actual={check.get('actual')!r}"
        if check.get("detail") and status == "FAIL":
            line += f" ({check['detail']})"
        lines.append(line)
    summary = report["summary"]
    lines.append(
        f"SUMMARY checks={summary['checks']} passed={summary['passed']} failed={summary['failed']}"
    )
    return "\n".join(lines)


def self_test() -> None:
    sample = """projects:\n  - name: alpha\n    revision: abc123\n  - name: beta\n    path: x\n    revision: v1\n"""
    assert project_revision(sample, "alpha") == "abc123"
    assert project_revision(sample, "beta") == "v1"
    assert project_revision(sample, "missing") is None
    attrs = attribute_blocks(
        'File: x.a(one.o)\n  Tag_CPU_arch: v8-M.mainline\n'
        '  Tag_ABI_VFP_args: VFP registers\nFile: x.a(two.o)\n'
        '  Tag_CPU_arch: v8-M.mainline\n'
    )
    assert attrs == [
        {"file": "x.a(one.o)", "Tag_CPU_arch": "v8-M.mainline",
         "Tag_ABI_VFP_args": "VFP registers"},
        {"file": "x.a(two.o)", "Tag_CPU_arch": "v8-M.mainline"},
    ]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ncs-root", type=Path, default=DEFAULT_NCS_ROOT)
    parser.add_argument("--sdk-root", type=Path, default=DEFAULT_SDK_ROOT)
    parser.add_argument("--readelf", type=Path, default=DEFAULT_READELF)
    parser.add_argument("--json", action="store_true", help="emit deterministic JSON")
    parser.add_argument("--self-test", action="store_true", help="run parser self-tests first")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    report = perform_checks(args.ncs_root.resolve(), args.readelf.resolve(),
                            args.sdk_root.resolve())
    if args.json:
        print(json.dumps(report, indent=2, sort_keys=True))
    else:
        print(render_text(report))
    return 1 if report["summary"]["failed"] else 0


if __name__ == "__main__":
    sys.exit(main())
