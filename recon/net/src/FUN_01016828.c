/* Reconstructed net-core assertion wrapper @ 0x01016828. */
extern void FUN_01008d00(unsigned int module, unsigned int line);

void FUN_01016828(void)
{
    /* The production assertion backend is noreturn.  The differential oracle
     * returns, so retain the firmware's non-returning contract explicitly. */
    for (;;)
        FUN_01008d00(0x32, 0x439);
}
