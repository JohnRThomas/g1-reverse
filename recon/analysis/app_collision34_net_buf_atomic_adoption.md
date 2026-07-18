# COLLISION-34 Zephyr net_buf atomic adoption

The configured NCS 2.5.1 `subsys/net/buf.c` owner is relocation-normalized byte-exact across the true reachable extent of all twelve reconstructed functions in its emitted firmware closure. The stale identities at `0x0005eeb4` and `0x0005f3d8` are corrected to `net_buf_alloc_len` and `net_buf_frag_del`. SDK-only `net_buf_pool_get` and `net_buf_id`, the private slist lock, pool-list boundary, callback tables and private allocation helpers remain one cohesive source-unit owner.

The fresh normal-link collision set moves **76 -> 66**, removing exactly the ten advertised `net_buf` collisions and adding none. The unresolved set remains exactly the two embedded SVC continuations. SDC stays report-only and the corrected namespaced GPPI owner at `0x000850dc` is unchanged.
