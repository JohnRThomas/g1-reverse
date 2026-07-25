/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_21000570[];
extern unsigned char g1_net_ram_blk_21004c98[];
#define G1N_21000580 ((unsigned long)(g1_net_ram_blk_21000570 + 0x10))
#define G1N_21004c9c ((unsigned long)(g1_net_ram_blk_21004c98 + 0x4))
#else
#define G1N_21000580 0x21000580ul
#define G1N_21004c9c 0x21004c9cul
#endif
/* net-core FUN_0102b15c @ 0x102b15c  (parity 300 trials PROVEN) */
extern void FUN_0103b62e(void *dst, int val, int len);
extern void FUN_0103b53a(void *dst, unsigned int a, unsigned int b, int len);
extern int FUN_0102a498(void);
extern int FUN_0102a468(void);
extern void FUN_0102a448(void *a, unsigned int b);
extern void FUN_01039722(int a, unsigned int b, int c);

unsigned int FUN_0102b15c(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    struct {
        unsigned int header;
        unsigned char payload[248];
    } packet;
    unsigned int uVar2;

    packet.header = 0;
    FUN_0103b62e(packet.payload, 0, sizeof(packet.payload));
    FUN_0103b53a(&packet, param_2, param_3, sizeof(packet));
    int iVar1 = FUN_0102a498();
    if (iVar1 == 1) {
        return 0;
    }
    if (param_3 < 0xfc) {
        iVar1 = FUN_0102a468();
        if (iVar1 == 0) {
            FUN_0102a448(&packet, param_3);
            *(volatile unsigned char *)G1N_21004c9c = 1;
            return 0;
        }
    } else if (0 < *(volatile int *)G1N_21000580) {
        FUN_01039722(0x103d11b, param_3, 0xfb);
    }
    uVar2 = 0xffffffff;
    return uVar2;
}
