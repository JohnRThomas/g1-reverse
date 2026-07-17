# CPUAPP `k_sem_take` ownership

The shipped public entry at `0x0007cb48` is the exact four-byte Thumb tail
branch `f5f7debe` to retained `z_impl_k_sem_take` at `0x00072908`.

The pinned NCS v2.5.1 / Zephyr 3.4.99 build has `CONFIG_USERSPACE=n`, so the
generated public wrapper performs only a compiler barrier and returns the
implementation result. Its ABI is `struct k_sem *` in `r0`, alignment padding
in `r1`, and the 64-bit `k_timeout_t` in `r2:r3`. Therefore the directional
link alias preserves both behavior and ABI; it does not replace the distinct
configured implementation with the non-matching SDK body.

- References resolved: 6
- Strong owner: `recon/symbolized/app/z_impl_k_sem_take.c`
- Non-selected SDK body: renamed locally to `g1_displaced_sdk_z_impl_k_sem_take`
- Weak stubs, absolute-address aliases, and guessed semantics: none
- Raw back-map retained: `k_sem_take` `0x0007cb48` -> `z_impl_k_sem_take` `0x00072908`
