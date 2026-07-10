/* named: __malloc_unlock */
/* globals referenced:
//   0x200037f0  g_malloc_lock                
*/
/* Reconstructed __malloc_unlock @ 0x785c8  (parity: 300/300 trials, PROVEN) */

extern void lock_release_or_fatal(void *p);
void __malloc_unlock(void)
{
    lock_release_or_fatal((void*)0x200037f0UL);
}

