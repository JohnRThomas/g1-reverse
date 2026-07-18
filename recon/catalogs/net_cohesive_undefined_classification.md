# Cohesive CPUNET undefined-symbol classification

This is the unresolved surface of the actual Zephyr cohesive link, computed from its
archive/object inputs. Private SDC/MPSL identities remain report-only; this report
does not authorize aliases, removals, or source replacement for them.

- Undefined symbols: **150**
- Text relocation references: **374**
- Private SDC/MPSL report-only: **93**
- Stock SDK/glue: **55**
- Interior/anomalous: **2**
- Private MPSL manifest-policy conflicts: **29**
- MPSL rows / unique private archive identities: **29 / 28**

## Version discrimination

The selected SDC and MPSL archives and every selected private body are byte-identical in nrfxlib v2.5.0 and v2.5.1. The firmware bytes therefore select that two-tag interval; west manifest provenance selects v2.5.1. v2.4.2, v2.5.2/v2.5.3, and v2.6.0 are rejected as exact archive pairs.

| Tag | SDC archive exact | SDC selected same/different/missing | MPSL archive exact | MPSL selected same/different/missing |
|---|---|---:|---|---:|
| `v2.4.2` | False | 31/15/7 | False | 13/15/0 |
| `v2.5.0` | True | 53/0/0 | True | 28/0/0 |
| `v2.5.1` | True | 53/0/0 | True | 28/0/0 |
| `v2.5.2` | False | 46/7/0 | False | 26/2/0 |
| `v2.5.3` | False | 46/7/0 | False | 26/2/0 |
| `v2.6.0` | False | 15/38/0 | False | 12/15/1 |

## Prioritized non-SDC action queue

1. **P0** — restore private MPSL entries to report-only policy (29 symbols).
2. **P1** — include the already-reviewed readable alias fragment in the cohesive CPUNET link (33 symbols).
3. **P2** — replace raw caller identities with selected public/stock SDK provider symbols (22 symbols).
4. **P3** — resolve anomalous control-flow identities with assembly/relocation evidence (2 symbols).

## Per-symbol evidence

| Symbol | Analysis / runtime | Category | Kind | Refs | Callers | Provider |
|---|---|---|---|---:|---:|---|
| `FUN_0100ef08` | 0x0100ef08 /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_0100f86c` | 0x0100f86c / 0x0101006c | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_LHLPURQHSJUG4HIEP67V53OFTD4W5APB2YBT5HY` |
| `FUN_01010890` | 0x01010890 / 0x01011090 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_FZRZ4CL3JR4VYYKFPYJ3VMCNBL7BVDZZP4POIWA` |
| `FUN_01011664` | 0x01011664 /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_01012150` | 0x01012150 / 0x01012950 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_OAGVEJLAHKQB2YTTUDIS6TDHXZIVWZXKUMPIBHQ` |
| `FUN_0101233c` | 0x0101233c / 0x01012b3c | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_JIJASGQH4XEEPZL7D35VQHVPKKLANGDBS2M46NQ` |
| `FUN_01012694` | 0x01012694 / 0x01012e94 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_DG6VHZEFRVR44ESTRZM42ZEBJG4KXT7IVJESA4Y` |
| `FUN_010126c8` | 0x010126c8 / 0x01012ec8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_WE45Z7LOSJEAVMD3HUIMZMMRDD5BLMKOFVBGE4Y` |
| `FUN_01012714` | 0x01012714 / 0x01012f14 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_4FKJZF4AXR7RHM7IPPZMVUWU7W6MFHLX726TPNY` |
| `FUN_010129b8` | 0x010129b8 / 0x010131b8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_XD3FX5TVO57NBJG4QV33FUOBCL7SNGB4OOT7C3Y` |
| `FUN_01012ad4` | 0x01012ad4 / 0x010132d4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 3 | 1 | `sym_4U2RA2RXIRU5BEMWZTHT3PETZK6K62P2SAJVWHA` |
| `FUN_01013da8` | 0x01013da8 / 0x010145a8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_EPRPLWOAI3YMJ24HN6AZUGT5NWULVXEG6CTCI2Y` |
| `FUN_01016170` | 0x01016170 / 0x01016970 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_IYZQNCOB4T4XO27DREWRIWJFVHVS355NEDBEGEQ` |
| `FUN_01018df8` | 0x01018df8 /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_010199f4` | 0x010199f4 / 0x0101a1f4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 3 | 1 | `sym_N4ILSLKDZS6JBJI35QECDSPTA4MOGH57OAV3Z5Y` |
| `FUN_01019eb4` | 0x01019eb4 / 0x0101a6b4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_LAYK5IGLYEFQ5CM2XGZHPMQBISU3CLYKB6Y3VWY` |
| `FUN_01019ef8` | 0x01019ef8 / 0x0101a6f8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_OMJ3SW7NEDZYIEECEHTEY7EFLFDPDBULVOYOR3I` |
| `FUN_0101d890` | 0x0101d890 /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_0101ded0` | 0x0101ded0 / 0x0101e6d0 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_CRB5YCB3Z3AAZH7A5G7WM2JFASUE6SGAJROBYAA` |
| `FUN_0101e090` | 0x0101e090 / 0x0101e890 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_6DIMBYT25BJNPLTICY2FPQL5WJ7ZQACODXUAREQ` |
| `FUN_0101e1e4` | 0x0101e1e4 / 0x0101e9e4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_FHGZFWEAJHQUMCWG4E5CUD67QD7B6JGXN3SSXDY` |
| `FUN_0101e2fc` | 0x0101e2fc / 0x0101eafc | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_LDNWAOTSHYHHXS6GC3A5HYPBDRDBY4JBJAMZW7I` |
| `FUN_0101f624` | 0x0101f624 / 0x0101fe24 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_XQWU4MX22DPQIRRYTXBNWTH2DBYK7MH33FME7FI` |
| `FUN_010207cc` | 0x010207cc / 0x01020fcc | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_7CIQBS4FNO23MS6BAN7Q3LK45R62DBPT5FNCWOA` |
| `FUN_01020820` | 0x01020820 / 0x01021020 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_Y6HXZQJARJ7FDWKGPREPQGRRGDOQMXHDALUK6KY` |
| `FUN_01021940` | 0x01021940 / 0x01022140 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_QLJBNB55XHXGY3EZ4W3ZZ3U6AVPE2YGDOXRUZSQ` |
| `FUN_01021ac0` | 0x01021ac0 / 0x010222c0 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 3 | 2 | `sym_4RNEPYYQOFM4LAOGLN2TB27X7L3XBISTGAWYOHQ` |
| `FUN_01022a30` | 0x01022a30 / 0x01023230 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 2 | 2 | `sym_RWBLK2534FJMTER76IYUPZQ3YF74JEALZ2OBIDI` |
| `FUN_01022a50` | 0x01022a50 / 0x01023250 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 4 | 4 | `sym_4FXF7BZT2IZ3YRYSE3Z2XCICKWZPGDZTXL2ECZQ` |
| `FUN_01022e34` | 0x01022e34 / 0x01023634 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 4 | 4 | `sym_RPHL2J7CVNKM6GKLDIFI4NVAPZE2FHTYW4VJSJI` |
| `FUN_01022ea8` | 0x01022ea8 / 0x010236a8 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 3 | 3 | `sym_MGCUANL7Q2CUPWKYBFLWSWSNXIEEYBPZTHT2VZI` |
| `FUN_01022f0c` | 0x01022f0c / 0x0102370c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 2 | 2 | `sym_W447CEMR6K6QRW3N63PRPIR7NK6ENOSBFXLCPRQ` |
| `FUN_01023ac4` | 0x01023ac4 / 0x010242c4 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 5 | 4 | `sym_F77FUTRRLLWPYDS7BBANG2WE3C4EDMYMAPNI54A` |
| `FUN_01023d38` | 0x01023d38 / 0x01024538 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 8 | 7 | `sym_URFU24FFGR2HYB6CCPIPKPNZNMTWHKDYOATUJNY` |
| `FUN_01023e88` | 0x01023e88 / 0x01024688 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 8 | 6 | `sym_HVFGTYCGAECGUJHOFSPMGUV2G4PTWWUYTJVAPNA` |
| `FUN_01024440` | 0x01024440 / 0x01024c40 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 7 | 6 | `sym_XYQTP7YX2XFVREW5KFDH2NNPGRIPEHKIO2RURYI` |
| `FUN_0102445c` | 0x0102445c / 0x01024c5c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 2 | 2 | `sym_V6OT7EKSQC3XEJK5ZWNACQF7LLICCSE7X3C3ECY` |
| `FUN_010245d8` | 0x010245d8 / 0x01024dd8 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 6 | 4 | `sym_PITJNQC6YSCEFAH23N5QRORZDKCSKOAUGBUS6GA` |
| `FUN_01024c6c` | 0x01024c6c / 0x0102546c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 4 | 3 | `sym_2ZDZA75WOMRNSQ6XL7IZWAQKYFFSRJOGBGKPTIQ` |
| `FUN_0102524c` | 0x0102524c / 0x01025a4c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 12 | 4 | `sym_TSYEIN5CZPQE3YK6VECZD5C2M4LMXKKH6O7LNAY` |
| `FUN_010256dc` | 0x010256dc / 0x01025edc | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 35 | 23 | `sym_S2UAPMFVIQXDUOA6CV7GJMB33TYHEUH5D6LHO5Q` |
| `FUN_010257e4` | 0x010257e4 / 0x01025fe4 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_W7ROFHNOSDKPIRUKDGIZZ5YR3MC3DAM2YLJOUIA` |
| `FUN_0102590c` | 0x0102590c / 0x0102610c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_525JLJ5JEQ6FEZGTSIW74UTOCUZ2F4YECMQ6KVQ` |
| `FUN_01025998` | 0x01025998 / 0x01026198 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 14 | 8 | `sym_DQONLUECJTIEYFOFJXXAPJO4POIAJKJNKBGVN5A` |
| `FUN_01025a84` | 0x01025a84 / 0x01026284 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 12 | 12 | `sym_VSILKYHVQ5DVF6LG5MG267DQVA3A2XZQ6FSCLXA` |
| `FUN_01025c44` | 0x01025c44 / 0x01026444 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 4 | 3 | `sym_GNQQQFEWM5SWEGVB5JHP7HYAZGI4CDQXSGHR4SQ` |
| `FUN_01025c9c` | 0x01025c9c / 0x0102649c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 6 | 4 | `sym_H2AKPOL4Q6GKGQJVBUBWLPO3RBNKXXQE2HSOELQ` |
| `FUN_01025cc8` | 0x01025cc8 / 0x010264c8 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_24DWUIEE2POS3GYSEVA4IAL4G7TGCCCJXT6D5AA` |
| `FUN_01025d0c` | 0x01025d0c / 0x0102650c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_UCUZCD3IIQBIFBTQEAMBH3ROVF42G3OC6HCQXWQ` |
| `FUN_01025d38` | 0x01025d38 / 0x01026538 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `__udivmoddi4` |
| `FUN_0102665c` | 0x0102665c /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_0102693a` | 0x0102693a / 0x0102713a | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 4 | 4 | `sym_A7PVZLRTORLFMETW3GOBE4DG32WTH46LP2SW5QQ` |
| `FUN_010269ce` | 0x010269ce / 0x010271ce | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_XCF2HHS4DO2JW2ILCF4RJW66HXXYOROBK7NUPMY` |
| `FUN_01026a7e` | 0x01026a7e / 0x0102727e | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 4 | 4 | `sym_E56LW5YVGUG6HP2OML5URHI7K2KCWX5ULQKQOKY` |
| `FUN_01026acc` | 0x01026acc / 0x010272cc | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_TDLIKQLE652KPCFAMYL33G6BKGPHRLYLWNEOTHQ` |
| `FUN_01026b58` | 0x01026b58 / 0x01027358 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_47GVMLF7NXDJBYC2TPU2ES3ZL6CP4GIPWKYYWBI` |
| `FUN_01026bfe` | 0x01026bfe / 0x010273fe | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_UOYZDE3MDLGPDL5S5WKUFLPYH4DJIMF3BJSBDYA` |
| `FUN_01026d16` | 0x01026d16 / 0x01027516 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_B62EJKCCJ4JFC5I4BFTUJG7GNOKGWQ4KKFBS6RI` |
| `FUN_01026dae` | 0x01026dae / 0x010275ae | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_4WKKRRMMNLQOCTRGC2MVIREG5QOCFUEL67TBUQY` |
| `FUN_01027044` | 0x01027044 / 0x01027844 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_RZ3AO5KZJYCPFG5YW4CBZQF5SRGN3BPTEGBY47I` |
| `FUN_010270e8` | 0x010270e8 / 0x010278e8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_Q4EW623JZHY67RB7U4Z2L2SMI5ENWIDFL23JZHQ` |
| `FUN_01027302` | 0x01027302 / 0x01027b02 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_JTNP7UFMKYWSFCHJEA5IASO3QVW3HK4YV6YOJYQ` |
| `FUN_010273c6` | 0x010273c6 / 0x01027bc6 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_B627VJPECYREV5OY4VJ652ISBA4XGPKVOUJ747A` |
| `FUN_01027846` | 0x01027846 / 0x01028046 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_WDNTHBFS7DQM3AR7WDCR7ZEICFH5ZM5PJ35BRPY` |
| `FUN_01027a4a` | 0x01027a4a / 0x0102824a | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_EOUZIDBP3HL2GT63FUCLAQVGISX2MLIV4MK5FZY` |
| `FUN_01027a94` | 0x01027a94 / 0x01028294 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_5RQ4FZRNKDUYW7D36K54TV4FI3NLNURNJPSLJOY` |
| `FUN_01027ed4` | 0x01027ed4 / 0x010286d4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_VPXIA5P4C72CY3ME4ZVXBADOKEG5S4C7Z7QZZFA` |
| `FUN_01027ef2` | 0x01027ef2 / 0x010286f2 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_VPXIA5P4C72CY3ME4ZVXBADOKEG5S4C7Z7QZZFA` |
| `FUN_010280be` | 0x010280be / 0x010288be | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_RIJIFYF46ZRKFDPA3GKV7WCH2VGEUEP6MVN4JFI` |
| `FUN_010280d8` | 0x010280d8 / 0x010288d8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_RIJIFYF46ZRKFDPA3GKV7WCH2VGEUEP6MVN4JFI` |
| `FUN_01028256` | 0x01028256 / 0x01028a56 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_DP474BSWQ6W7M27XE2M7XMGWSDEQ3KL66B2SR5Q` |
| `FUN_0102894a` | 0x0102894a / 0x0102914a | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_FQNF6KMIBMQDKYS2BJP6ZB7BLEET53WUIWQK6FA` |
| `FUN_010292ec` | 0x010292ec /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_0102941c` | 0x0102941c / 0x01029c1c | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_J2SUO2NMPPNDQZAGB2FE5TAXJFMJ5FZXKAPNVFQ` |
| `FUN_0102961a` | 0x0102961a / 0x01029e1a | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_JU742LCDLL7PZRKE4HZMDATVAWDO5RTNLQEGJHI` |
| `FUN_0102971e` | 0x0102971e / 0x01029f1e | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_3AWAQCNCZH4MEGKKMZLZXM2OFWJS4TFUCWUEKRI` |
| `FUN_010297b4` | 0x010297b4 / 0x01029fb4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_RRC5YHH6YM3SHNGPFUCE3YX5LDRJC7YUGPWWYHQ` |
| `FUN_01029882` | 0x01029882 / 0x0102a082 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_6NVBTUP3F2K4CR6EQ2CJTT2FVJIBKKWMISPRCSI` |
| `FUN_010298a8` | 0x010298a8 / 0x0102a0a8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 1 | `sym_5J2UTKCNVYPTFCXPLA7CPFQ4IMONW6EIFWRNNZI` |
| `FUN_01029b38` | 0x01029b38 / 0x0102a338 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_2RDISJXERNPMBLAROCL4JWHLKVABCMPSEI3SYLQ` |
| `FUN_0102a1e0` | 0x0102a1e0 /  | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `uncatalogued_private_controller_entry` |
| `FUN_0102a244` | 0x0102a244 / 0x0102aa44 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 2 | 1 | `strcmp` |
| `FUN_0102d25c` | 0x0102d25c /  | `interior_or_anomalous_identity` | `anomalous_non_executable_target` | 1 | 1 | `no_valid_provider` |
| `FUN_0102eb2c` | 0x0102eb2c / 0x0102f32c | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 8 | 6 | `arch_irq_enable` |
| `FUN_0102fa84` | 0x0102fa84 / 0x01030284 | `interior_or_anomalous_identity` | `blocked_c_unexpressible` | 1 | 1 | `no_valid_provider` |
| `FUN_0102fbac` | 0x0102fbac / 0x010303ac | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `bt_hci_driver_register` |
| `FUN_0103175c` | 0x0103175c / 0x01031f5c | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 2 | 2 | `sys_clock_set_timeout` |
| `FUN_010353ec` | 0x010353ec / 0x01035bec | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 3 | 3 | `virtqueue_add_consumed_buffer` |
| `FUN_01038fa4` | 0x01038fa4 / 0x010397a4 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `ocrypto_mod_p256_from_bytes` |
| `FUN_0103ab0e` | 0x0103ab0e / 0x0103b30e | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 2 | 2 | `metal_io_block_write` |
| `FUN_0103ac50` | 0x0103ac50 / 0x0103b450 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 3 | 2 | `virtqueue_get_available_buffer` |
| `FUN_0103b1e2` | 0x0103b1e2 / 0x0103b9e2 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `z_queue_node_peek` |
| `FUN_0103b210` | 0x0103b210 / 0x0103ba10 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `k_queue_prepend` |
| `FUN_0103b304` | 0x0103b304 / 0x0103bb04 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `sys_timepoint_calc` |
| `FUN_0103b34c` | 0x0103b34c / 0x0103bb4c | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `sys_timepoint_timeout` |
| `FUN_0103b5c4` | 0x0103b5c4 / 0x0103bdc4 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `strnlen` |
| `FUN_0103b614` | 0x0103b614 / 0x0103be14 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 13 | 11 | `__aeabi_memcpy4` |
| `FUN_0103b62e` | 0x0103b62e / 0x0103be2e | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 17 | 15 | `memset` |
| `alloc_chunk` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01039874` |
| `assert_panic` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 2 | 1 | `FUN_01039bb0` |
| `assert_report` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 6 | 1 | `assert_print` |
| `atomic_inc` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0103a294` |
| `bytes_to_chunksz` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_010397c0` |
| `chunk_size` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01039768` |
| `controller_connection_config_get` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_010282a6` |
| `controller_default_bounds_build` | 0x010282fc / 0x01028afc | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_SJQK3XCDMHZEHLRZ5PBTRM4CNS5P2IXVJLCP4OA` |
| `controller_deferred_event_raise` | 0x0102583c / 0x0102603c | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 7 | 7 | `sym_GURZ3AH6X65RGSKYMYNWZVP6HM56LA5MRAQWT6Q` |
| `controller_entry_links_release` | 0x0101df84 / 0x0101e784 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_Y63OUE6TAGQSGRCWADOMH3US5WOUILUZMPZTGBI` |
| `controller_handle_lookup` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0100cfc0` |
| `controller_object_get` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_010282a2` |
| `controller_radio_time_mode2_to_mode2` | 0x01021634 / 0x01021e34 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_2EA2WBXQOKCTPMK7YNDR6QM6MTGHJCDTPZEXNNA` |
| `controller_timing_defaults_apply` | 0x0101e1e4 / 0x0101e9e4 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_FHGZFWEAJHQUMCWG4E5CUD67QD7B6JGXN3SSXDY` |
| `controller_transition_pending_check` | 0x01025cf0 / 0x010264f0 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_UCUZCD3IIQBIFBTQEAMBH3ROVF42G3OC6HCQXWQ` |
| `free_list_add` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01039972` |
| `ipc_static_vrings_shm_size` | 0x0103a056 / 0x0103a856 | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 2 | 1 | `ipc_static_vrings_shm_size` |
| `k_sem_give` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036824` |
| `k_timer_start` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01038448` |
| `k_timer_stop` |  /  | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `z_impl_k_timer_stop` |
| `log_process` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0102df2c` |
| `net_buf_destroy_from_pool` |  /  | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `k_queue_prepend` |
| `net_buf_free_get` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 2 | 1 | `FUN_01036774` |
| `prepare_thread_swap` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01037398` |
| `queue_insert` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036660` |
| `ready_remove` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0103735c` |
| `rtc_compare_event_clear` | 0x0103a6ae / 0x0103aeae | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `event_clear` |
| `schedule_node_tail_get` | 0x0101dda8 / 0x0101e5a8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_WVUR7FIOL24MFCJHZIBLTPA7O44X57VSRLSLAPQ` |
| `scheduler_reschedule_restore` |  /  | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `z_reschedule_irqlock` |
| `sdc_byte_lock_release` | 0x0102a208 / 0x0102aa08 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_OWJYSTADR5I36MIHWNPICVB7CMCWNSFIZPFXQ2Q` |
| `sdc_byte_lock_try_acquire` | 0x0102a1ea / 0x0102a9ea | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 1 | 1 | `sym_AR22FPVUFSZMVYMQBBXG7EEZNA2HPS2RLAKRPBA` |
| `sdc_conn_event_process` | 0x01014b18 / 0x01015318 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 2 | 2 | `uncatalogued_private_controller_entry` |
| `sdc_conn_recovery_state_restore` | 0x0101618c / 0x0101698c | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_HT64RIVISXSWFJE3LL26YHKQRTRRXKVEDBUUUOQ` |
| `sdc_conn_recovery_window_update` | 0x0100d6e8 / 0x0100dee8 | `private_sdc_mpsl_report_only` | `private_sdc_report_only` | 1 | 1 | `sym_OTIPANP3Q7VLW2BQGLZZUUDNR5HBSAYXJSFAKKA` |
| `sdc_conn_window_admit` | 0x010231c8 / 0x010239c8 | `private_sdc_mpsl_report_only` | `private_obfuscated_archive_identity` | 16 | 14 | `sym_NFDFVOR5BUFND4TNTGYIYR4ARXJRXWSQ4PVFUKY` |
| `set_chunk_used` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01039774` |
| `spin_lock` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 4 | 4 | `FUN_01036144` |
| `spin_lock_acquire` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036144` |
| `spin_lock_valid` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0103610c` |
| `spin_unlock` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 4 | 4 | `FUN_01036128` |
| `spin_unlock_valid` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036128` |
| `spin_validate` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 4 | 4 | `FUN_0103610c` |
| `spinlock_acquire` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036144` |
| `spinlock_release` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 3 | 1 | `FUN_01036128` |
| `spinlock_validate` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0103610c` |
| `split_chunks` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_010398e8` |
| `swap_current` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036f24` |
| `thread_can_swap` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01036e90` |
| `trace_sched_unlock` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_0103b2b4` |
| `update_cache` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 2 | 2 | `FUN_01036f74` |
| `z_except_reason` |  /  | `stock_sdk_or_glue` | `stock_provider_requires_call_identity_integration` | 1 | 1 | `z_except_reason` |
| `z_heap_aligned_alloc` |  /  | `stock_sdk_or_glue` | `existing_readable_alias_not_linked` | 1 | 1 | `FUN_01038958` |
