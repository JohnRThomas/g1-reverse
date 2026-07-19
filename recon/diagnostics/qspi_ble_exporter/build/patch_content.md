# Exact generated patch content

Source SHA-256: `e0614feb3609fc2f251a00c16ca66f01c9fb8153de81ca1818cab5f79b42fd3b`

## Existing executable bytes replaced

```text
CPU address  0x0001a710
File offset  0xe710
Before       0d 4b 1b 68
After        e0 f0 96 b9
Instruction  b.w 0x000faa40
```

## MCUboot header change

```text
img_size before  0xee83d (976957)
img_size after   0xee8d4 (977108)
header bytes     3d e8 0e 00
              -> d4 e8 0e 00
```

## Appended executable

```text
CPU address  0x000faa40
File offset  0xeea40
Size         148 bytes
SHA-256      674092f8ab6052470a928a7213aa23c18f48883a99b1287cccf1df7ef2d2892f
Bytes        2f 2a 03 d0 22 4b 1b 68 1f f7 64 be 0d f5 88 78 2f 23 88 f8 00 30 ca 23 88 f8 01 30 01 23 88 f8 02 30 00 23 88 f8 03 30 c8 f8 04 30 73 88 0a 2b 28 d3 b5 f8 01 00 98 42 24 d1 d5 f8 05 60 6f 7a c8 f8 04 60 01 2f 1d d3 b4 2f 1b d8 4f f0 00 73 9e 42 17 d2 9b 1b 9f 42 14 d8 30 46 08 f1 08 01 3a 46 27 f7 87 fd 50 b9 c9 23 88 f8 01 30 00 23 88 f8 02 30 88 f8 03 70 17 f1 08 01 03 e0 02 23 88 f8 02 30 08 21 e3 68 40 46 98 47 1f f7 00 bb 0c 23 00 20
```

The old TLV block is replaced by a newly generated SHA-256 TLV, the matching
RSA-2048 key-hash TLV, and a new RSA-2048 signature TLV. OpenSSL result:
`Verified OK`.
