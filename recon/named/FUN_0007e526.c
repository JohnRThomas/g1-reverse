/* readable reconstruction; identity: FUN_0007e526 @ 0x0007e526
 * public-name: FUN_0007e526
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Full reconstruction FUN_0007e526 @ 0x7e526 (exact extent 24 bytes).
 * CFG_VERIFY_PREFIX_FIRST: the post-call BX LR branches to itself because the
 * BL replaced LR; this is an intentional one-call terminal loop. */

extern void FUN_0004c4d0(void);

/* The shipped wrapper raises BASEPRI_MAX to 0x20 and executes an ISB before
 * entering the scheduler boundary.  BASEPRI is architectural state rather
 * than C-visible memory; FUN_0004c4d0 is the observable platform boundary. */
void FUN_0007e526(void)
{
    FUN_0004c4d0();
    for (;;) {
    }
}
