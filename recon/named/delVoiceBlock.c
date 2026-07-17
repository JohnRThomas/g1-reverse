/* readable reconstruction; identity: FUN_0002f4a8 @ 0x0002f4a8
 * public-name: delVoiceBlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   delVoiceBlock                            <= FUN_0002f4a8 @ 0x0002f4a8
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_8a050                             @ 0x0008a050
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9eba7                             @ 0x0009eba7
 *   rodata_9ebc6                             @ 0x0009ebc6
 *   rodata_a420e                             @ 0x000a420e
 *   rodata_a4233                             @ 0x000a4233
 *   rodata_a4253                             @ 0x000a4253
 *   rodata_a427e                             @ 0x000a427e
 *   rodata_a48fa                             @ 0x000a48fa
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_voice_block_dir_buf                    @ 0x20018daa
 */
/* Reconstructed FUN_0002f4a8 @ 0x2f4a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned, ...);
extern int get_device_info(void);
extern void debug_print(unsigned, ...);
extern int z_device_is_ready(int);
extern void memcpy(uintptr_t, int, int);
extern void memset_bytes(uintptr_t, int, int);

#define PUVAR3 0x20018daaUL
#define LOG_MODE (*mode_address)
#define DBG2(msg, ctx) do { int mode_ = LOG_MODE; if (mode_ == 0) log_message((msg), (ctx)); else debug_print((msg), (ctx)); } while (0)
#define DBG4(msg, ctx, v2) do { int mode_ = LOG_MODE; if (mode_ == 0) log_message((msg), (ctx), (v2), mode_); else debug_print((msg), (ctx), (v2), mode_); } while (0)
#define DBGT(msg, ctx, v2) do { int mode_ = LOG_MODE; if (mode_ == 0) log_message((msg), (ctx), (v2), param_4); else debug_print((msg), (ctx), (v2), param_4); } while (0)

typedef int (*fn4)(int,int,int,int);

void delVoiceBlock(unsigned param_1, int param_2, int param_3, int param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000230c;
    volatile int * volatile mode_address = (volatile int*)0x20007554;
    int i5;

    if (2 < *piVar1) { DBG2(0x000a420e, 0x000a48fa); }

    if (((param_1 - 5) & 0xff) < 0xfa || param_1 == 0) {
        if (0 < *piVar1) { DBGT(0x000a4233, 0x000a48fa, param_3); }
        return;
    }

    i5 = z_device_is_ready(0x00087bf0);
    if (i5 == 0) {
        if (0 < *piVar1) { DBGT(0x0009e9ea, 0x000a48fa,
                                *(volatile int*)0x00087bf0); }
        return;
    }

    memset_bytes(PUVAR3, 0, 0x1000);

    { int b = get_device_info(); int fn = *(volatile int*)(b + 0x1030);
      int object = get_device_info();
      i5 = ((fn4)(intptr_t)fn)(object, 0x400000, PUVAR3, 0x1000); }
    if (i5 != 0) {
        if (0 < *piVar1) { DBGT(0x0009ea0a, 0x000a48fa, 0x400000); }
        return;
    }

    { int b = get_device_info(); int fn = *(volatile int*)(b + 0x1038);
      int object = get_device_info();
      i5 = ((fn4)(intptr_t)fn)(object, 0x400000, 0x1000, 0x1000); }
    if (i5 != 0) {
        if (2 < *piVar1) { DBGT(0x0009eba7, 0x000a48fa, i5); }
        return;
    }

    *(volatile uint8_t*)(PUVAR3 + 1) = 0xaa;
    *(volatile uint8_t*)(PUVAR3 + 0) = 0x5a;
    *(volatile uint8_t*)(PUVAR3 + 2) = 0xa5;
    *(volatile uint8_t*)(PUVAR3 + 3) = 0x5a;
    *(volatile uint8_t*)(PUVAR3 + 4) = 0;
    *(volatile uint8_t*)(PUVAR3 + 5) = 0;
    *(volatile uint8_t*)(PUVAR3 + 6) = 0;
    *(volatile uint8_t*)(PUVAR3 + 7) = 0;
    {
        int lvl = *piVar1;
        if (param_1 < 5) {
            unsigned iVar6 = param_1 - 1;
            uintptr_t base = PUVAR3 + iVar6 * 0x14;
            *(volatile uint8_t*)(base + 8) = 0;
            *(volatile uint8_t*)(base + 9) = 0;
            *(volatile uint8_t*)(base + 0xa) = 0;
            *(volatile uint8_t*)(base + 0xb) = 0;
            *(volatile uint8_t*)(base + 0x14) = 0;
            *(volatile uint8_t*)(base + 0x15) = 0;
            *(volatile uint8_t*)(base + 0x16) = 0;
            *(volatile uint8_t*)(base + 0x17) = 0;
            if (2 < lvl) { DBG4(0x000a4253, 0x000a48fa, param_1); }
        } else {
            memcpy(PUVAR3, 0x0008a050, 0x58);
            if (2 < lvl) { DBG4(0x000a427e, 0x000a48fa, 0x58); }
        }
    }

    { int b = get_device_info(); int fn = *(volatile int*)(b + 0x1034);
      int object = get_device_info();
      i5 = ((fn4)(intptr_t)fn)(object, 0x400000, PUVAR3, 0x1000); }
    if (i5 == 0) {
        if (2 < *piVar1) { DBGT(0x000a42a5, 0x000a48fa, i5); }
    } else {
        if (0 < *piVar1) { DBGT(0x0009ebc6, 0x000a48fa, i5); }
    }
    return;
}
