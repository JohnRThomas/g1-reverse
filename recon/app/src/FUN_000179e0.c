/* FUN_000179e0 @ 0x179e0: disable the device described at 0x889f8. */

extern void FUN_0007c084(unsigned int descriptor, unsigned int enable,
                         unsigned int arg2, unsigned int arg3);

void FUN_000179e0(unsigned int unused0, unsigned int unused1, unsigned int arg2, unsigned int arg3)
{
    (void)unused0;
    (void)unused1;
    FUN_0007c084(0x000889f8u, 0, arg2, arg3);
}
