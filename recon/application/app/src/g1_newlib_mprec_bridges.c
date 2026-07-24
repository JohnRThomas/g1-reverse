/* Library-displacement Batch 1 caller wiring (goal G2).
 *
 * Batch 1 excludes 52 leaf libc / lib-os / zcbor / arch reconstructions whose
 * upstream bodies are already in the cohesive link (see
 * recon/ownership/library_displacement_report.md §4 and the Batch 1 block at
 * the end of that file).  Twelve of them are newlib-nano `mprec`/`stdio`
 * primitives that are still called *by name* from recovered newlib TUs which
 * are NOT part of Batch 1 (`dtoa_r.c`, `i2b.c`, `bignum_div_trial_subtract.c`,
 * `stdio_fclose.c`, `_sbrk_r.c`).  A displaced body leaves those call sites
 * undefined, so each historical identity is re-expressed here as a one-line
 * forward onto the genuine newlib symbol — the same mechanism Batch 0 used in
 * g1_gpio_header_bridges.c.
 *
 * Argument lists are taken from the *proven* reconstruction prototypes (see
 * recon/app/src/<name>.c); trailing Ghidra-artifact parameters that the
 * shipped code never reads are accepted and dropped.  AAPCS makes the forward
 * exact: r0..r3 (and d0 for __d2b) are already in place.
 *
 * newlib's mprec.h is not exported by the SDK, so the upstream entry points
 * are declared here with their documented signatures; `struct _reent` and
 * `_Bigint` are opaque to a pure forwarder.
 */

extern void *_Balloc(void *reent, int k);
extern void _Bfree(void *reent, void *bigint);
extern void *__multadd(void *reent, void *bigint, int m, int a);
extern void *__pow5mult(void *reent, void *bigint, int k);
extern void *__multiply(void *reent, void *a, void *b);
extern void *__lshift(void *reent, void *bigint, int k);
extern void *__mdiff(void *reent, void *a, void *b);
extern int __hi0bits(unsigned long value);
extern int __mcmp(void *a, void *b);
extern void *__d2b(void *reent, double value, int *exponent, int *bits);
extern void *_sbrk(int increment);
extern void __smakebuf_r(void *reent, void *stream);

unsigned int *Balloc(int param_1, unsigned int param_2)
{
    return (unsigned int *)_Balloc((void *)(unsigned long)param_1,
                                   (int)param_2);
}

void Bfree(int param_1, unsigned int *param_2)
{
    _Bfree((void *)(unsigned long)param_1, param_2);
}

int multadd(int param_1, int param_2, int param_3, unsigned param_4)
{
    return (int)(unsigned long)__multadd((void *)(unsigned long)param_1,
                                         (void *)(unsigned long)param_2,
                                         param_3, (int)param_4);
}

unsigned int pow5mult(int param_1, unsigned int param_2, unsigned param_3,
                      unsigned int param_4)
{
    (void)param_4;
    return (unsigned int)(unsigned long)__pow5mult(
        (void *)(unsigned long)param_1, (void *)(unsigned long)param_2,
        (int)param_3);
}

void bigint_mult(unsigned param_1, int param_2, int param_3)
{
    __multiply((void *)(unsigned long)param_1, (void *)(unsigned long)param_2,
               (void *)(unsigned long)param_3);
}

int lshift(unsigned int param_1, int param_2, unsigned int param_3)
{
    return (int)(unsigned long)__lshift((void *)(unsigned long)param_1,
                                        (void *)(unsigned long)param_2,
                                        (int)param_3);
}

int bigint_diff(int param_1, int param_2, int param_3, int param_4)
{
    (void)param_4;
    return (int)(unsigned long)__mdiff((void *)(unsigned long)param_1,
                                       (void *)(unsigned long)param_2,
                                       (void *)(unsigned long)param_3);
}

int clz32(unsigned int param_1)
{
    return __hi0bits(param_1);
}

int bignum_compare_abs(int param_1, int param_2)
{
    return __mcmp((void *)(unsigned long)param_1,
                  (void *)(unsigned long)param_2);
}

int d2b_decompose(unsigned a0, unsigned a1, unsigned a2, double input)
{
    return (int)(unsigned long)__d2b((void *)(unsigned long)a0, input,
                                     (int *)(unsigned long)a1,
                                     (int *)(unsigned long)a2);
}

int sbrk_impl(int param_1)
{
    return (int)(unsigned long)_sbrk(param_1);
}

void smakebuf_r(int param_1, int *param_2, int param_3)
{
    (void)param_3;
    __smakebuf_r((void *)(unsigned long)param_1, param_2);
}
