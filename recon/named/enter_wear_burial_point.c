/* named: enter_wear_burial_point */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed enter_wear_burial_point @ 0x4a890  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern unsigned get_current_burial_point_type(void);
extern unsigned long long k_uptime_get_10(void);
extern void DEBUG_PRINT(int,...);
extern void debug_print(int,...);
void enter_wear_burial_point(void){
  int iVar1; unsigned uVar2; unsigned long long uVar3;
  iVar1 = get_device_info();
  if (*(volatile unsigned char*)(iVar1+0x10ac) != 1){
    uVar2 = get_current_burial_point_type();
    if (uVar2 < 7){
      iVar1 = get_device_info();
      *(volatile unsigned char*)(iVar1+0x10ac) = 1;
      iVar1 = get_device_info();
      *(volatile unsigned char*)(iVar1+0x10ad) = (unsigned char)uVar2;
      iVar1 = get_device_info();
      uVar3 = k_uptime_get_10();
      *(volatile unsigned*)(iVar1+0x10b2) = (unsigned)(uVar3>>32);
      *(volatile unsigned*)(iVar1+0x10ae) = (unsigned)uVar3;
      iVar1 = get_device_info();
      iVar1 = uVar2*0xc + iVar1;
      *(volatile int*)(iVar1+0x10e6) = *(volatile int*)(iVar1+0x10e6) + 1;
      iVar1 = get_device_info();
      *(volatile int*)(iVar1+0x10ce) = *(volatile int*)(iVar1+0x10ce) + 1;
      if (1 < *(volatile int*)0x2000230cUL){
        if (*(volatile int*)0x20007554UL != 0){
          iVar1 = get_device_info();
          debug_print(0x000f0337,0x000f04a9,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
          return;
        }
        iVar1 = get_device_info();
        DEBUG_PRINT(0x000f0337,0x000f04a9,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
        return;
      }
    }
  }
  return;
}

