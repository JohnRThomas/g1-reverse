#!/usr/bin/env python3
"""Build, apply, sign, and verify the read-only BLE QSPI exporter patch."""

from __future__ import annotations

import argparse
import hashlib
import json
import shutil
import struct
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
ORIGINAL = ROOT / "app_update.bin"
ORIGINAL_SHA256 = "e0614feb3609fc2f251a00c16ca66f01c9fb8153de81ca1818cab5f79b42fd3b"
KEY = Path.home() / "ncs251/bootloader/mcuboot/root-rsa-2048.pem"
TOOLCHAIN = Path.home() / "zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin"
AS = TOOLCHAIN / "arm-zephyr-eabi-as"
LD = TOOLCHAIN / "arm-zephyr-eabi-ld"
OBJCOPY = TOOLCHAIN / "arm-zephyr-eabi-objcopy"
OBJDUMP = TOOLCHAIN / "arm-zephyr-eabi-objdump"

MCUBOOT_MAGIC = 0x96F3B83D
TLV_MAGIC = 0x6907
HEADER_SIZE = 0x200
SLOT_END_FILE_OFFSET = 0xF0000
HOOK_VA = 0x0001A710
HOOK_FILE_OFFSET = HOOK_VA - 0xC000
HOOK_EXPECTED = bytes.fromhex("0d 4b 1b 68")
HOOK_REPLACEMENT = bytes.fromhex("e0 f0 96 b9")  # b.w 0x000faa40
HANDLER_VA = 0x000FAA40
HANDLER_FILE_OFFSET = HANDLER_VA - 0xC000
APP_LOAD_VA = 0x0000C200
KEYHASH_EXPECTED = bytes.fromhex(
    "fc5701dc6135e1323847bdc40f04d2e5"
    "bee5833b23c29f93593d00018cfa9994"
)


def run(*args: object, capture: bool = False) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [str(arg) for arg in args], check=True, text=True,
        capture_output=capture,
    )


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def public_key_hash(key: Path, public_der: Path) -> bytes:
    with public_der.open("wb") as output:
        subprocess.run(
            ["openssl", "rsa", "-in", str(key), "-RSAPublicKey_out",
             "-outform", "DER"], check=True, stdout=output,
             stderr=subprocess.DEVNULL,
        )
    return hashlib.sha256(public_der.read_bytes()).digest()


def assemble(out: Path) -> bytes:
    obj = out / "handler.o"
    elf = out / "handler.elf"
    binary = out / "handler.bin"
    run(AS, "-mcpu=cortex-m33", "-mthumb", "-o", obj, HERE / "handler.S")
    run(LD, f"-Ttext=0x{HANDLER_VA:x}", "-e", "qspi_ble_exporter",
        "-o", elf, obj)
    run(OBJCOPY, "-O", "binary", elf, binary)
    disassembly = run(OBJDUMP, "-d", elf, capture=True).stdout
    (out / "handler.disasm.txt").write_text(disassembly)
    return binary.read_bytes()


def parse_original(image: bytes) -> tuple[bytearray, dict[str, int]]:
    values = struct.unpack_from("<IIHHIIBBHI", image, 0)
    names = ("magic", "load_addr", "hdr_size", "protected_tlv_size",
             "img_size", "flags", "major", "minor", "revision", "build")
    header = dict(zip(names, values))
    if header["magic"] != MCUBOOT_MAGIC:
        raise ValueError("unexpected MCUboot magic")
    if header["hdr_size"] != HEADER_SIZE:
        raise ValueError("unexpected MCUboot header size")
    if header["protected_tlv_size"] != 0 or header["flags"] != 0:
        raise ValueError("unexpected protected TLVs or image flags")
    body_end = header["hdr_size"] + header["img_size"]
    if image[body_end:body_end + 2] != struct.pack("<H", TLV_MAGIC):
        raise ValueError("original regular TLV header not found")
    return bytearray(image[:body_end]), header


def sign_body(body: bytes, key: Path, out: Path) -> tuple[bytes, bytes, bytes]:
    digest = hashlib.sha256(body).digest()
    signature_path = out / "signature.bin"
    with signature_path.open("wb") as output:
        subprocess.run(
            ["openssl", "dgst", "-sha256", "-sign", str(key)],
            input=body, check=True, stdout=output,
        )
    signature = signature_path.read_bytes()
    if len(signature) != 256:
        raise ValueError(f"expected 256-byte RSA signature, got {len(signature)}")
    keyhash = public_key_hash(key, out / "public-rsa2048.der")
    if keyhash != KEYHASH_EXPECTED:
        raise ValueError("signing key does not match the installed image key hash")

    records = b"".join((
        struct.pack("<BBH", 0x10, 0, len(digest)) + digest,
        struct.pack("<BBH", 0x01, 0, len(keyhash)) + keyhash,
        struct.pack("<BBH", 0x20, 0, len(signature)) + signature,
    ))
    tlv = struct.pack("<HH", TLV_MAGIC, 4 + len(records)) + records
    return body + tlv, digest, keyhash


def verify_signature(body: bytes, signature: Path, public_der: Path) -> str:
    with tempfile.NamedTemporaryFile() as temporary:
        temporary.write(body)
        temporary.flush()
        result = run(
            "openssl", "dgst", "-sha256", "-verify", public_der,
            "-keyform", "DER", "-signature", signature, temporary.name,
            capture=True,
        )
    return result.stdout.strip()


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", type=Path, default=HERE / "build")
    args = parser.parse_args()
    out = args.out.resolve()
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)

    original = ORIGINAL.read_bytes()
    if sha256(original) != ORIGINAL_SHA256:
        raise ValueError("source image hash mismatch; refusing to patch")
    body, old_header = parse_original(original)
    if body[HOOK_FILE_OFFSET:HOOK_FILE_OFFSET + 4] != HOOK_EXPECTED:
        raise ValueError("hook preimage mismatch; refusing to patch")

    handler = assemble(out)
    if len(body) > HANDLER_FILE_OFFSET:
        raise ValueError("handler would overlap the original signed payload")
    body.extend(b"\0" * (HANDLER_FILE_OFFSET - len(body)))
    body.extend(handler)
    body[HOOK_FILE_OFFSET:HOOK_FILE_OFFSET + 4] = HOOK_REPLACEMENT

    new_img_size = len(body) - HEADER_SIZE
    if len(body) >= SLOT_END_FILE_OFFSET:
        raise ValueError("patched payload does not fit the MCUboot primary slot")
    struct.pack_into("<I", body, 12, new_img_size)

    signed, digest, keyhash = sign_body(bytes(body), KEY, out)
    output_image = out / "app_update_qspi_exporter.signed.bin"
    output_image.write_bytes(signed)
    verified = verify_signature(
        bytes(body), out / "signature.bin", out / "public-rsa2048.der")
    if verified != "Verified OK":
        raise ValueError(f"OpenSSL signature verification failed: {verified}")

    hook_disassembly = run(
        OBJDUMP, "-D", "-b", "binary", "-marm", "-Mforce-thumb",
        "--adjust-vma=0xc000", "--start-address=0x1a710",
        "--stop-address=0x1a718", output_image, capture=True,
    ).stdout
    (out / "hook.disasm.txt").write_text(hook_disassembly)

    manifest = {
        "schema": 1,
        "source_image": str(ORIGINAL),
        "source_sha256": sha256(original),
        "output_image": str(output_image),
        "output_sha256": sha256(signed),
        "signature_verification": verified,
        "signing_key": str(KEY),
        "public_key_sha256": keyhash.hex(),
        "old_img_size": old_header["img_size"],
        "new_img_size": new_img_size,
        "handler": {
            "address": f"0x{HANDLER_VA:08x}",
            "file_offset": f"0x{HANDLER_FILE_OFFSET:x}",
            "size": len(handler),
            "sha256": sha256(handler),
        },
        "in_place_patch": {
            "address": f"0x{HOOK_VA:08x}",
            "file_offset": f"0x{HOOK_FILE_OFFSET:x}",
            "before": HOOK_EXPECTED.hex(" "),
            "after": HOOK_REPLACEMENT.hex(" "),
            "meaning": f"b.w 0x{HANDLER_VA:08x}",
        },
        "signed_digest_sha256_tlv": digest.hex(),
        "slot_end_file_offset": f"0x{SLOT_END_FILE_OFFSET:x}",
        "remaining_slot_bytes_after_signed_image": SLOT_END_FILE_OFFSET - len(signed),
        "read_only_call_target": "flash_settings_read@0x000225b4",
        "protocol": {
            "command": "0x2f",
            "offset_field": "request[5:9] little-endian",
            "length_field": "request[9]",
            "maximum_chunk": 180,
            "qspi_bounds": "[0x00000000,0x02000000)",
        },
    }
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    patch_content = f"""# Exact generated patch content

Source SHA-256: `{manifest['source_sha256']}`

## Existing executable bytes replaced

```text
CPU address  {manifest['in_place_patch']['address']}
File offset  {manifest['in_place_patch']['file_offset']}
Before       {manifest['in_place_patch']['before']}
After        {manifest['in_place_patch']['after']}
Instruction  {manifest['in_place_patch']['meaning']}
```

## MCUboot header change

```text
img_size before  0x{old_header['img_size']:x} ({old_header['img_size']})
img_size after   0x{new_img_size:x} ({new_img_size})
header bytes     {old_header['img_size'].to_bytes(4, 'little').hex(' ')}
              -> {new_img_size.to_bytes(4, 'little').hex(' ')}
```

## Appended executable

```text
CPU address  0x{HANDLER_VA:08x}
File offset  0x{HANDLER_FILE_OFFSET:x}
Size         {len(handler)} bytes
SHA-256      {sha256(handler)}
Bytes        {handler.hex(' ')}
```

The old TLV block is replaced by a newly generated SHA-256 TLV, the matching
RSA-2048 key-hash TLV, and a new RSA-2048 signature TLV. OpenSSL result:
`{verified}`.
"""
    (out / "patch_content.md").write_text(patch_content)
    print(json.dumps(manifest, indent=2))


if __name__ == "__main__":
    main()
