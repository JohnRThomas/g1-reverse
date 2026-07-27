/* readable reconstruction; identity: FUN_0007c1aa @ 0x0007c1aa
 * public-name: device_info_store_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   device_info_store_chunk                  <= FUN_0007c1aa @ 0x0007c1aa
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_0007c1aa @ 0x7c1aa  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int memcpy(unsigned int, unsigned int, unsigned int);

unsigned int device_info_store_chunk(unsigned int param_1, unsigned int param_2, unsigned char param_3, int param_4)
{
    unsigned int base;
    unsigned int uVar2;
    if (param_4 == 0) {
        base = get_device_info();
        uVar2 = *(volatile unsigned int*)(base + 0x1028UL);
    } else {
        base = get_device_info();
        uVar2 = *(volatile unsigned int*)(base + 0x1024UL);
    }
    unsigned int r0 = memcpy(uVar2, param_1, param_2);
    *(volatile unsigned char*)(r0 + 0x200UL) = param_3;
    return 0;
}
