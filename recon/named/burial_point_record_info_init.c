/* named: burial_point_record_info_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed burial_point_record_info_init @ 0x4ab3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int get_device_info(void);
extern void memset_bytes(void);

void burial_point_record_info_init(void)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    int iVar1 = get_device_info();
    (void)iVar1;
    memset_bytes();
    iVar1 = get_device_info();
    (void)iVar1;
    memset_bytes();
}

