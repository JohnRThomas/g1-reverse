/* named: gui_bitmps_merge_draw */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a034  g_gui_active_canvas          
*/
/* Reconstructed gui_bitmps_merge_draw @ 0x43bd8  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern int  get_device_info(void);
extern void debug_print(void);
extern unsigned long long atomic_get_3_0(void);
extern void clean_fb_data(int,int,int,int,int,int);
extern void reflash_fb_data_to_lcd(int,int,int,int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

int gui_bitmps_merge_draw(unsigned int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 unsigned char param_7,unsigned char param_8){
  volatile int *lvl=(volatile int*)0x2000230cUL, *g8=(volatile int*)0x20007554UL;
  int iVar4,iVar6,iVar7,iVar11; unsigned int uVar3,uVar5,uVar8,uVar12; int uVar9;
  unsigned char bVar1,bVar2; int pbVar10, local_5c; unsigned int local_2c[2];
  unsigned long long uVar13;
  if ((param_3 < (int)param_1) || (param_4 < param_2) || (0xf < (param_7 | param_8))) {
    if (*lvl < 2) return -1;
    iVar4 = *g8; uVar9 = 0xaa96d;
  } else {
    if ((param_1 & 1) == 0) {
      iVar4 = param_3;
      uVar13 = atomic_get_3_0();
      if ((int)((unsigned int)uVar13 << 0x1e) < 0)
        clean_fb_data(VI(0x2000a034),(int)(param_1&1),(int)param_1,(int)(uVar13>>0x20),iVar4,param_4);
      iVar11 = 0;
      uVar5 = (unsigned int)((int)(param_3-(int)param_1) >> 3);
      iVar6 = VI(0x2000a034);
      for (iVar4 = 0; iVar4 < param_4 - param_2; iVar4++) {
        pbVar10 = param_6 + iVar11;
        local_5c = param_5 + iVar11;
        for (iVar7 = 0; iVar7 < (int)uVar5; iVar7++) {
          bVar1 = VB(local_5c); bVar2 = VB(pbVar10);
          uVar3 = 0; local_2c[0] = 0; uVar8 = 0;
          do {
            if ((((int)(unsigned int)bVar1 >> (uVar8 & 0xff)) & 1) != 0) {
              if ((int)(uVar8 << 0x1f) < 0) uVar3 |= param_7;
              else uVar3 |= (unsigned int)((param_7 & 0xf) << 4);
            }
            if ((((int)(unsigned int)bVar2 >> (uVar8 & 0xff)) & 1) != 0) {
              if ((int)(uVar8 << 0x1f) < 0) uVar3 |= param_8;
              else uVar3 |= (unsigned int)((param_8 & 0xf) << 4);
            }
            uVar12 = uVar8 + 1;
            if ((uVar12 & 1) == 0) { *((char*)local_2c + ((int)uVar8 >> 1)) = (char)uVar3; uVar3 = 0; }
            uVar8 = uVar12;
          } while (uVar12 != 8);
          *(volatile int*)(VI(iVar6 + param_2*4 + iVar4*4) + iVar7*4 + (int)param_1/2) = local_2c[0];
          pbVar10++; local_5c++;
        }
        iVar11 += (int)(uVar5 & ~((unsigned int)((int)(param_3-(int)param_1) >> 0x1f)));
      }
      iVar4 = (int)atomic_get_3_0();
      if ((int)((unsigned int)iVar4 << 0x1e) < 0) {
        iVar4 = get_device_info(); uVar9 = VI(iVar4+0xeb4);
        iVar4 = get_device_info(); reflash_fb_data_to_lcd(uVar9, VI(iVar4+0xeb8), (int)param_1, param_2, param_3, param_4);
        return 0;
      }
      return 0;
    }
    if (*lvl < 2) return -1;
    iVar4 = *g8; uVar9 = 0xaa9a3;
  }
  if (iVar4 == 0) DEBUG_PRINT(uVar9, 0xaacc8); else debug_print();
  return -1;
}

