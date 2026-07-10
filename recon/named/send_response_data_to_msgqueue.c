/* named: send_response_data_to_msgqueue */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed send_response_data_to_msgqueue @ 0x47b1c  (parity: 300/300 trials, PROVEN) */

extern void *get_device_info(void);
extern void memset_bytes(void*, int, int);
extern void memcpy(void*, void*, unsigned int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int send_response_data_to_msgqueue(void *param_1, unsigned int param_2)
{
    unsigned char *pcVar1;
    unsigned int uVar2;
    int iVar3;
    unsigned char stackbuf[28];

    pcVar1 = (unsigned char*)get_device_info();
    if (*pcVar1 == 2) {
        uVar2 = 0;
        return uVar2;
    }
    memset_bytes(stackbuf, 0, 0x18);
    if (param_2 < 0x15) {
        if (param_1 != 0) {
            memcpy(stackbuf + 4, param_1, param_2);
            *(unsigned short*)(stackbuf + 2) = (unsigned short)param_2;
        }
        iVar3 = k_msgq_put(*(volatile unsigned int*)0x2000392cUL, stackbuf, 0, 0);
        if (iVar3 == 0) {
            return 0;
        }
        DEBUG_PRINT(0xef058, 0xef750);
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xef01c, 0xef750, 0x14);
            } else {
                debug_print();
            }
        }
    }
    uVar2 = 0xffffffff;
    return uVar2;
}

