/* readable reconstruction; identity: FUN_0005cff0 @ 0x0005cff0
 * public-name: FUN_0005cff0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_pub_key_is_debug                      <= FUN_00055cf0 @ 0x00055cf0
 *   bt_keys_get_addr                         <= FUN_0005e6a8 @ 0x0005e6a8
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4eb1                             @ 0x000f4eb1
 *   g_smp_local_public_key                   @ 0x2000af48
 */
/* Reconstructed FUN_0005cff0 @ 0x5cff0  owned extent: 0xae bytes */

extern int  FUN_0005cac0(void);
extern int  bt_pub_key_is_debug(void);
extern void FUN_00083074(unsigned a, unsigned b, void *c);
extern int  atomic_set_bit(unsigned a, unsigned b);
extern unsigned bt_keys_get_addr(unsigned char a, unsigned b);
extern int  FUN_0005ce6c(int p);

int FUN_0005cff0(int param_1, int param_2){
    unsigned *src, *dst, *end;
    int iVar4;
    FUN_0005cac0();
    src = *(unsigned **)(param_2 + 0xc);
    dst = (unsigned *)(param_1 + 0x57);
    end = src + 8;
    do { *dst++ = *src++; } while (src != end);
    { unsigned *s2 = src, *d2 = (unsigned*)(param_1 + 0x77), *e2 = s2 + 8;
      do { *d2++ = *s2++; } while (s2 != e2); }
    iVar4 = bt_pub_key_is_debug();
    if (iVar4 != 0){
        int local_18 = 2; unsigned local_14 = 0xf4eb1u; (void)local_14;
        FUN_00083074(0x88180u, 0x10c0u, &local_18);
        atomic_set_bit((unsigned)(param_1 + 4), 0xe);
        {
            int p = *(int*)(param_1 + 0xf0);
            if (*(int*)(p + 0xc0) == 0){
                unsigned uVar5 = bt_keys_get_addr(*(unsigned char*)(p + 8), (unsigned)(p + 0x90));
                *(unsigned*)(p + 0xc0) = uVar5;
            }
            {
                int q = *(int*)(p + 0xc0);
                if (q != 0 && (*(unsigned short*)(q + 0xe) & 0x24) != 0
                    && (int)((unsigned)*(unsigned char*)(q + 0xd) << 0x1e) >= 0){
                    return 3;
                }
            }
        }
    }
    if (*(int*)0x2000af48 == 0){
        atomic_set_bit((unsigned)(param_1 + 4), 6);
        return 0;
    }
    return FUN_0005ce6c(param_1);
}
