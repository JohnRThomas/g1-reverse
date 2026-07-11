/* Reconstructed FUN_0007c3d0 @ 0x7c3d0.
 * Complete ten-byte argument-shuffling tail wrapper; 0x7c3da starts the next
 * function.  Bit zero in 0x24e61 selects Thumb state for the 0x24e60 target. */
int FUN_0007c3d0(unsigned param_1, unsigned param_2)
{
    int (*target)(int, unsigned, unsigned) =
        (int (*)(int, unsigned, unsigned))0x24e61U;
    return target(3, param_1, param_2);
}
