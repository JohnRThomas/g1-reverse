# Exact NCS 2.5.1 mcumgr atomic adoption

The configured `mgmt.c`, mcumgr `smp.c`, transport `smp.c`, and mandatory `smp_reassembly.c` source units are adopted as one atomic closure. All 20 recovered owners are relocation-normalized byte-exact at their firmware addresses.

The exact variant requires `CONFIG_ZCBOR_STOP_ON_ERROR=y`, `CONFIG_MCUMGR_TRANSPORT_BT_REASSEMBLY=y`, and `CONFIG_MCUMGR_TRANSPORT_NETBUF_SIZE=2475`. Only recovered owners with address-keyed C sources are excluded; SDK-only init/drop owners remain ordinary upstream sections. Raw `FUN_` identities remain reversible aliases in the durable function-name catalog. SDC remains report-only and unchanged.
