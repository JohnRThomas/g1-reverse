/* Reconstructed get_glassbox_charge_percent @ 0x327c4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;typedef unsigned int u32;extern int DEBUG_PRINT();extern void sub_19c70(void);u8 get_glassbox_charge_percent(void){if(2<*(volatile int*)0x2000230cUL){if(*(volatile u32*)0x20007554UL==0)DEBUG_PRINT();else sub_19c70();}return *(volatile u8*)0x20019ef4UL & 0x7f;}
