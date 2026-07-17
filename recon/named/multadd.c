/* readable reconstruction; identity: FUN_00078698 @ 0x00078698
 * public-name: multadd
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   Balloc                                   <= FUN_000785d4 @ 0x000785d4
 *   Bfree                                    <= FUN_00078654 @ 0x00078654
 *   multadd                                  <= FUN_00078698 @ 0x00078698
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_f8c42                             @ 0x000f8c42
 *   rodata_f8cd5                             @ 0x000f8cd5
 */
/* Reconstructed FUN_00078698 @ 0x78698  (parity: 152/300 trials, PROVEN) */

extern int Balloc(int,int);
extern int __assert_func(int,int,int,int);
extern void memcpy(int,int,int);
extern void Bfree(int,int);
int multadd(int param_1,int param_2,int param_3,unsigned param_4){
  int iVar5=*(int*)(param_2+0x10);
  int iVar1=0;
  unsigned *puVar6=(unsigned*)(param_2+0x14);
  do{
    iVar1=iVar1+1;
    unsigned v=*puVar6;
    unsigned uVar3=param_3*(v & 0xffff)+param_4;
    unsigned uVar4=param_3*(v >> 0x10)+(uVar3 >> 0x10);
    param_4=uVar4 >> 0x10;
    *(volatile unsigned*)puVar6=(uVar3 & 0xffff)+uVar4*0x10000;
    puVar6=puVar6+1;
  }while(iVar1<iVar5);
  int iVar1r=param_2;
  if(param_4!=0){
    if(*(int*)(param_2+8)<=iVar5){
      int iVar2=Balloc(param_1,*(int*)(param_2+4)+1);
      iVar1r=iVar2;
      if(iVar2==0){ iVar2=__assert_func(0xf8cd5,0xb5,0,0xf8c42); }
      memcpy(iVar2+0xc,param_2+0xc,(*(int*)(param_2+0x10)+2)*4);
      Bfree(param_1,param_2);
    }
    *(volatile unsigned*)(iVar1r+iVar5*4+0x14)=param_4;
    *(volatile int*)(iVar1r+0x10)=iVar5+1;
  }
  return iVar1r;
}
