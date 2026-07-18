/* FUN_00077a10 @ 0x00077a10; raw FUN_00077a10.
 * Newlib-nano strtod wrapper; noncontiguous raw target 0x00013f58 is
 * _strtod_l, retained here as an ordinary named SDK call for linking. */

typedef unsigned char byte;
typedef unsigned long long u64;
extern u64 _strtod_l(void *reent, byte *s, void *endptr, void *locale);
u64 FUN_00077a10(byte *param_1, void *param_2) {
    void *r = *(void **)0x20002d20;
    return _strtod_l(r, param_1, param_2, (void *)0x20002d84); /*=0x00013f58*/
}
