/* Reconstructed atomic_set_bit @ 0x83090  (CFG-directed candidate) */
typedef long atomic_t;
void atomic_set_bit(atomic_t *target, int bit)
{
    (void)__atomic_fetch_or(target, (atomic_t)1 << bit, __ATOMIC_SEQ_CST);
}
