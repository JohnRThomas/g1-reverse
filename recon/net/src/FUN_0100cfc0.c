/* net-core FUN_0100cfc0 @ 0x100cfc0  (CFG-directed candidate) */
extern unsigned int controller_typed_handle_lookup(unsigned int, unsigned int); /* FUN_01009d18 @ 0x01009d18 */

unsigned int FUN_0100cfc0(unsigned int handle, unsigned char *out)
{
    unsigned int found = controller_typed_handle_lookup(handle, 0);
    *(unsigned int *)(out + 4) = found;
    if (found != 0) {
        out[0] = 0;
        return 0;
    }
    found = controller_typed_handle_lookup(handle, 1);
    *(unsigned int *)(out + 4) = found;
    if (found != 0) {
        out[0] = 1;
        return 0;
    }
    return 2;
}
