/* readable reconstruction; identity: FUN_0101132c @ 0x0101132c
 * public-name: FUN_0101132c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_ble_address_equal                    <= FUN_0100aa3c @ 0x0100aa3c
 *   controller_packet_config_apply_if_active <= FUN_0100cb4c @ 0x0100cb4c
 *   sdc_controller_random_get                <= FUN_0100f63c @ 0x0100f63c
 *   sdc_llcp_release_rx_context              <= FUN_0101fca8 @ 0x0101fca8
 *   sdc_llcp_stop_rx_timeout                 <= FUN_010208b0 @ 0x010208b0
 * address symbols (name @ address):
 *   rodata_1011f29                           @ 0x01011f29
 *   rodata_101205d                           @ 0x0101205d
 *   ADDR_FUN_01012438_THUMB                  @ 0x01012439
 *   g_net_own_addr_info                      @ 0x21000f20
 *   g_net_selected_peer_addr                 @ 0x21000f41
 *   g_net_selected_peer_id                   @ 0x21000f45
 */
/* net-core FUN_0101132c @ 0x101132c  (parity 200 trials PROVEN) */
/* net-core FUN_0101132c @ 0x101132c  (parity 300 trials PROVEN) */
extern int FUN_01020738(int);
extern int FUN_010203d0(void);
extern int sdc_llcp_stop_rx_timeout(void);
extern int sdc_llcp_release_rx_context(void);
extern int FUN_010204e0(int);
extern int FUN_0102072c(int);
extern int FUN_01025c44(int);
extern int FUN_010129e8(int);
extern int FUN_010129f4(int);
extern int FUN_010204f4(void);
extern int FUN_010202fc(int,int);
extern int FUN_010204d4(int);
extern int FUN_010212ec(int,int);
extern int FUN_01027ed4(int,int);
extern int FUN_01027ef2(int,int);
extern unsigned long long controller_time_now(void);
extern unsigned int FUN_0100c738(void);
extern int FUN_0101124c(int,int);
extern int controller_packet_config_apply_if_active(int);
extern int FUN_01009dd8(int*);
extern int sdc_ble_address_equal(int,int,int,int);
extern unsigned int sdc_controller_random_get(void);

#define PB ((volatile unsigned char*)0x21000f20)
#define PW(off) (*(volatile unsigned int*)(0x21000f20+(off)))
#define PH(off) (*(volatile unsigned short*)(0x21000f20+(off)))

struct controller_init_descriptor { unsigned int words[4]; };
struct controller_iterator { int current; unsigned int control; };
_Static_assert(sizeof(struct controller_init_descriptor) == 16,
               "controller init descriptor layout");
_Static_assert(sizeof(struct controller_iterator) == 8,
               "controller iterator layout");

int FUN_0101132c(int param_1)
{
    int r6, r7, r8;
    struct controller_init_descriptor controller_init;

    controller_init.words[0] = 0x01012439u;
    controller_init.words[1] = 0x0101205du;
    controller_init.words[2] = 0x01011f29u;
    controller_init.words[3] = *(volatile unsigned int *)(PW(0x28) + 4u);

    PB[5] = 0;
    *(volatile unsigned char*)(param_1+0x79) = 0;
    PH(0x10) = 0;
    PW(8) = 0;
    PB[6] = 0;

    FUN_01020738((int)&controller_init);
    FUN_010203d0();
    sdc_llcp_stop_rx_timeout();
    sdc_llcp_release_rx_context();
    FUN_010204e0((int)0x8e89bed6u);
    FUN_0102072c(0x00555555);
    FUN_01025c44(0);
    FUN_010129e8(param_1+0x28);
    FUN_010129f4(param_1+0x28);
    FUN_010204f4();
    FUN_010202fc(0x25, *(volatile unsigned char*)(param_1+4));
    FUN_010204d4((int)*(volatile signed char*)(param_1+0x10));
    {
        int iVar5 = FUN_010212ec(0, *(volatile unsigned char*)(param_1+4));
        PW(0xc) = (unsigned int)iVar5;
        if (iVar5 == 0) {
            PB[4] = 1;
            return 0;
        }
    }

    r6 = FUN_01027ed4((int)*(volatile unsigned int*)(param_1+0x44), param_1+0x48);
    r7 = FUN_01027ef2((int)*(volatile unsigned int*)(param_1+0x44), param_1+0x50);

    if (r6 != 0 && *(volatile unsigned char*)(param_1+0x20) != 0) {
        r8 = 1;
    } else if (r7 != 0) {
        r8 = *(volatile unsigned char*)(param_1+0x21);
    } else {
        r8 = 0;
    }

    if ((*(volatile unsigned char*)(param_1+0x1a) != 0) ||
        ((int)((unsigned int)(*(volatile unsigned short*)(param_1+2)) << 0x1d) < 0)) {
        int special;
        if (*(volatile int*)(param_1+0x5c)==0x7fffffff && *(volatile int*)(param_1+0x58)==-1) {
            special = 1;
        } else {
            unsigned long long cur = controller_time_now();
            unsigned long long stored = (((unsigned long long)(unsigned int)*(volatile int*)(param_1+0x5c))<<32) |
                                          (unsigned int)*(volatile int*)(param_1+0x58);
            special = (cur < stored) ? 1 : 0;
        }
        if (!(special && r8 == 0)) {
            unsigned int uVar8 = FUN_0100c738();
            unsigned long long lVar13 = controller_time_now();
            unsigned long long sum = (unsigned long long)uVar8 * 1000000ULL + lVar13;
            *(volatile unsigned int*)(param_1+0x58) = (unsigned int)(sum & 0xffffffffu);
            *(volatile unsigned int*)(param_1+0x5c) = (unsigned int)(sum >> 32);
            FUN_0101124c(param_1, 1);
        }
        r8 = *(volatile unsigned char*)(param_1+0x7b);
    } else {
        r8 = *(volatile unsigned char*)(param_1+0x7b);
    }

    if (((((r6 | r7) & 0xff) != 0) || (r8 != 0)) &&
        (0 <= (int)((unsigned int)(*(volatile unsigned short*)(param_1+2)) << 0x1b))) {
        int iVar5b = *(volatile int*)(param_1+0x3c);
        unsigned int target = (((unsigned int)iVar5b) << 0xc) >> 0x14;
        unsigned int uVar6b;
        do {
            uVar6b = sdc_controller_random_get();
        } while (target == (uVar6b & 0xfff));
        *(volatile unsigned char*)(param_1+0x3d) = (unsigned char)uVar6b;
        *(volatile unsigned char*)(param_1+0x3e) =
            (unsigned char)((*(volatile unsigned char*)(param_1+0x3e) & 0xf0) | (unsigned char)((uVar6b << 0x14) >> 0x1c));
        *(volatile unsigned char*)(param_1+0x7b) = 0;
    }

    {
        unsigned int uVar4 = (unsigned int)controller_packet_config_apply_if_active((int)(PW(0) + 3));
        unsigned short uVar1 = *(volatile unsigned short*)(param_1+2);
        PB[0x12] = (unsigned char)uVar4;
        if ((int)((unsigned int)uVar1 << 0x1f) < 0) {
            int iVar5c;
            struct controller_iterator iterator = { 0, 0x10000u };
            int iVar9, iVar3;
            PB[0x20] = 0xff;
            iVar5c = *(volatile int*)(param_1+0x1c);
            for (;;) {
                iVar9 = FUN_01009dd8(&iterator.current);
                iVar3 = iterator.current;
                if (iVar9 != 0) return 0;
                if (iVar5c == iterator.current) continue;
                {
                    int r = sdc_ble_address_equal((int)*(volatile unsigned char*)(iVar3+9), iVar3+10,
                                          (int)*(volatile unsigned char*)(iVar5c+9), iVar5c+10);
                    if (r != 0) break;
                }
            }
            PB[0x20] = *(volatile unsigned char*)(iVar3+2);
            *(volatile unsigned int*)(0x21000f41) = *(volatile unsigned int*)(iVar3+3);
            *(volatile unsigned short*)(0x21000f45) = *(volatile unsigned short*)(iVar3+7);
        }
    }
    return 0;
}
