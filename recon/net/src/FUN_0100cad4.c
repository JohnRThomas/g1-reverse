/* net-core FUN_0100cad4 @ 0x100cad4  (CFG-directed candidate) */
extern void sdc_llcp_stop_rx_timeout(void); /* FUN_010208b0 @ 0x010208b0 */
extern void sdc_llcp_release_rx_context(void); /* FUN_0101fca8 @ 0x0101fca8 */
extern void FUN_0101fc40(unsigned int, unsigned int, unsigned int);
extern void FUN_0101fcf4(void);

unsigned int FUN_0100cad4(unsigned int arg, int select)
{
    volatile unsigned char *s = (volatile unsigned char *)0x21000d18u;
    unsigned int active;
    sdc_llcp_stop_rx_timeout();
    sdc_llcp_release_rx_context();
    active = s[0x18a];
    if (active != 0) {
        unsigned int count = s[1];
        if (count != 0) {
            volatile unsigned char *ctx = s + 2;
            if (select == 0) ctx = s + 0x82;
            FUN_0101fc40((unsigned int)ctx, count, arg);
            FUN_0101fcf4();
            return active;
        }
        active = 0;
    }
    return active;
}
