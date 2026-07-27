/* Full reconstruction FUN_00026418 @ 0x26418, exact extent 320 bytes.
 * CFG_VERIFY_CALL_ARITIES=3,4,2 */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0005010c(uint32_t,uint32_t);
extern uint32_t FUN_000671d8(void*,void*,uintptr_t,uintptr_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t,uint32_t);
extern void FUN_00086c78(void*,int,uint32_t);
struct spi_map { uint32_t base, tag; };
unsigned FUN_00026418(uintptr_t event)
{
    struct spi_map mode3;
    mode3.base=0x5000c000u; *(uint8_t *)&mode3.tag=0;
    struct spi_map mode4;
    mode4.base=*(volatile uint32_t*)0x000883b0u;
    *(uint32_t*)((uint8_t*)&mode4+4)=*(volatile uint32_t*)0x000883b4u;
    uint32_t cfg[10];
    FUN_00086c78(&cfg,0,0x28);
    cfg[4]=0x00ff0700u;
    cfg[7]=0xffffffffu;
    cfg[8]=0x00020002u;
    if(*(volatile uint32_t*)(event+0x14)==1)return 0;
    cfg[5]=*(volatile uint8_t*)(event+0x1d)*1000000u;
    uint32_t mode=*(volatile uint8_t*)(event+0x18);
    cfg[0]=*(volatile uint8_t*)(event+0x19);
    cfg[1]=*(volatile uint8_t*)(event+0x1a);
    cfg[2]=*(volatile uint8_t*)(event+0x1b);
    cfg[3]=*(volatile uint8_t*)(event+0x1c);
    int level=*(volatile int*)0x2000230cu;
    struct spi_map *map;
    if(mode==3)map=&mode3; else if(mode==4)map=&mode4; else {
        if(level>0){int alt=*(volatile int*)0x20007554u;if(alt)FUN_00019c70(0x9fb89u,0x9fc4du);else DEBUG_PRINT(0x9fb89u,0x9fc4du);} return 0;
    }
    *(volatile uint32_t*)(event+0xc)=map->base;
    *(volatile uint32_t*)(event+0x10)=map->tag;
    if(level>2){
        if(*(volatile int*)0x20007554u)FUN_00019c70(0x9fb9fu,0x9fc4du,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
        else DEBUG_PRINT(0x9fb9fu,0x9fc4du,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
    }
    uintptr_t callback=mode==3?0x0007ca77u:0;
    uintptr_t callback_context=mode==3?event:0;
    if(FUN_000671d8((void*)(event+0xc),&cfg,callback,callback_context)!=0x0bad0000u){
        FUN_0007e2fa(0x99cbdu,0x9fc15u,0x9fbfdu,0x68);
        FUN_0007e2ec(0x9fbfdu,0x68);
    }
    volatile uint8_t *once=(volatile uint8_t*)(mode==3?0x20018c6cu:0x20018c6du);
    if(!*once){*once=1;FUN_0005010c(mode==3?12:10,6);}
    if(*(volatile int*)0x2000230cu>2){if(*(volatile int*)0x20007554u)FUN_00019c70(0x9fc2cu,0x9fc4du,mode);else DEBUG_PRINT(0x9fc2cu,0x9fc4du,mode);}
    *(volatile uint32_t*)(event+0x14)=1;
    return 0;
}
