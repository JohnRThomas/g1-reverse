# COLLISION-35 Zephyr net_buf_simple adoption

The assertion-enabled NCS 2.5.1 `subsys/net/buf_simple.c` implementations of `net_buf_simple_reserve`, `net_buf_simple_push`, and `net_buf_simple_add` are relocation-masked byte-exact over their firmware code extents. The older collision catalog measured stale assertion-free objects; the pinned configured object restores the firmware's assert branches, strings, source lines and callees.

The required normal-link delta is **22 -> 19**, removing only these three symbols and adding none. The two embedded SVC continuations remain the complete unresolved set. The corrected GPPI identity at `0x000850dc` is unchanged.
