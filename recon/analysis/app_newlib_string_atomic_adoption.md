# Exact Newlib-nano string-owner adoption

`strcmp` at `0x0000eefe` and `strlen` at `0x0000ef12` are byte-for-byte
identical to the emitted `.text` sections in the configured Cortex-M33
hard-float Newlib-nano archive:

| Firmware owner | Archive member | Bytes | SHA-256 |
|---|---|---:|---|
| `strcmp` | `lib_a-strcmp.o` | 20 | `2970d82d1d95f3e160c8304340fba61c52eeaca1401ac05920209c6dc463267e` |
| `strlen` | `lib_a-strlen.o` | 16 | `c0c3db0df44bb4ee3d99315dedec65280495b2bbedd50455938c114e3fdd180d` |

The archive is the pinned Zephyr SDK 0.16.5-1
`thumb/v8-m.main+fp/hard/libc_nano.a` with SHA-256
`c6a3f8bf0d33e395061c64e8f523e7fb11aaf7fb679c25ff0124e5cd77eaa5cc`.
Its recorded source provenance is Newlib 3.3.0 commit
`4e150303bcc1e44f4d90f3489a4417433980d5ff`.

The distinction matters: the manifest and archive hash prove the exact library
artifact used by this reconstruction. These very small generic function bodies
can persist unchanged across releases, so body equality alone is not claimed
as a unique Newlib patch-version fingerprint.

Both recovered C files remain durable evidence with their raw
`FUN_0000eefe`/`FUN_0000ef12` identities. They are removed only from generated
build inputs, allowing the configured stock archive members to own the public
symbols.
