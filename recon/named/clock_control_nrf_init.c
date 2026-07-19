/* readable reconstruction; identity: FUN_0006058c @ 0x0006058c
 * public-name: clock_control_nrf_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_priority_set                    <= FUN_0005010c @ 0x0005010c
 *   clock_control_nrf_init                   <= FUN_0006058c @ 0x0006058c
 *   nrfx_clock_init                          <= FUN_00065190 @ 0x00065190
 *   nrfx_clock_enable                        <= FUN_000651d8 @ 0x000651d8
 *   onoff_manager_init                       <= FUN_0007e212 @ 0x0007e212
 * address symbols (name @ address):
 *   rodata_60635                             @ 0x00060635
 *   rodata_8b5fc                             @ 0x0008b5fc
 *   REG_5000555c                             @ 0x5000555c
 */
/* Reconstructed FUN_0006058c @ 0x6058c  (parity: 300/300 trials, PROVEN) */

extern void arch_irq_priority_set(int,int,int,unsigned,unsigned);
extern int nrfx_clock_init(unsigned);
extern void nrfx_clock_enable(void);
extern int onoff_manager_init(int,unsigned);
int clock_control_nrf_init(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned uVar1; int iVar2,iVar3,iVar4;
  arch_irq_priority_set(5,1,0,param_4,param_4);
  iVar2=nrfx_clock_init(0x60635);
  if(iVar2==0x0bad0000){
    *(volatile unsigned*)0x5000555cUL=0x9ba5;
    nrfx_clock_enable();
    uVar1=0x8b5fc; iVar2=0;
    do{
      iVar4=*(int*)(param_1+0x10);
      iVar3=onoff_manager_init(iVar4+iVar2*0x20,uVar1);
      if(iVar3<0) return iVar3;
      iVar3=iVar2*0xc; iVar2=iVar2+1;
      *(unsigned*)(iVar3+iVar4+0x88)=1;
    } while(iVar2!=4);
    iVar2=0;
  } else { iVar2=-5; }
  return iVar2;
}
