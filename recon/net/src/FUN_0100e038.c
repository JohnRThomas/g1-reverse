/* net-core FUN_0100e038 @ 0x100e038  (CFG-directed candidate) */
void FUN_0100e038(unsigned char *p, unsigned int value)
{
    *p = (unsigned char)((*p & 0xbfu) | ((value << 6) & 0x40u));
}
