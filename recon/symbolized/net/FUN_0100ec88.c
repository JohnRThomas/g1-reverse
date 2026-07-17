#include "g1_net_symbols.h"
/* net-core FUN_0100ec88 @ 0x100ec88  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(unsigned int a, unsigned int b) __attribute__((noreturn));
extern int  FUN_01009d64(unsigned short a, int b);
extern int  FUN_0100a17c(unsigned short a);
extern int  FUN_01018c58(void);
extern int  FUN_0101b74c(void);
extern void FUN_01026c94(int a, int b);
extern unsigned int g1_irq_lock(void);
extern void g1_irq_unlock(unsigned int key);

typedef void (*cb3)(unsigned int, char *, int);
typedef void (*cb16)(unsigned short, char *);
typedef void (*nf2)(unsigned int, char *);
typedef unsigned int (*nf2r)(unsigned int, char *);
typedef void (*nf1)(unsigned int);

unsigned int FUN_0100ec88(char *param_1)
{
    /* Queue head removal and completion-state clearing use the platform IRQ
     * lock interface because portable C cannot directly represent PRIMASK. */
    unsigned int s5  = ((unsigned long)&g_net_pending_work_list) /*=0x21000ec8*/;
    unsigned int s6  = ((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
    volatile unsigned int *p5  = (volatile unsigned int *)((unsigned long)&g_21000058) /*=0x21000058*/;
    volatile unsigned int *p6  = (volatile unsigned int *)((unsigned long)&g_2100005c) /*=0x2100005c*/;
    volatile unsigned int *pc4 = (volatile unsigned int *)((unsigned long)&g_21000054) /*=0x21000054*/;
    unsigned int node = 0;
    int typ = 0;
    unsigned int uVar7 = 0;
    unsigned int primask;

LOOP:
    if (*(volatile unsigned char *)(*(volatile unsigned int *)(s5 + 8) + 8) == 0x10) {
        if (*(volatile unsigned char *)(s6 + 0x17) != 0 &&
            *(volatile short *)(s6 + 0x18) == 0)
            return 0;
    }
INNER:
    node = *(volatile unsigned int *)(s5 + 0x14);
    if (node != 0 && *(volatile unsigned char *)(node + 8) != 0)
        goto PROCESS;
    node = *(volatile unsigned int *)(s5 + 8);
    if (*(volatile unsigned char *)(node + 8) == 1)
        return 0;
    primask = g1_irq_lock();
    *(volatile unsigned int *)(s5 + 8) =
        *(volatile unsigned int *)(*(volatile unsigned int *)(s5 + 8));
    g1_irq_unlock(primask);
    if (*(volatile unsigned char *)(node + 8) == 0)
        goto INNER;
    *(volatile unsigned int *)(s5 + 0x14) = node;

PROCESS:
    typ = *(volatile unsigned char *)(node + 8);
    *(volatile unsigned char *)(node + 8) = 5;
    switch (typ) {
    case 2: {
        unsigned int f = *(volatile unsigned int *)(node + 4);
        if (f == 0) FUN_01008d00(0x10, 0x1c0);
        ((nf2)f)(node, param_1);
        uVar7 = 4;
        goto FINALIZE;
    }
    case 3: {
        unsigned int f = *(volatile unsigned int *)(node + 4);
        if (f == 0) FUN_01008d00(0x10, 0x1c9);
        unsigned int uVar9 = ((nf2r)f)(node, param_1);
        uVar7 = uVar9 & 0xff;
        if (((uVar9 >> 8) & 0xff) != 1)
            goto FINALIZE;
        *(volatile unsigned char *)(node + 8) = 3;
        if (uVar7 != 0)
            return uVar7;
        goto LOOP;
    }
    case 4: {
        unsigned int f = *(volatile unsigned int *)(node + 4);
        if (f == 0) FUN_01008d00(0x10, 0x1d3);
        ((nf1)f)(node);
        uVar7 = 0;
        goto FINALIZE;
    }
    case 6: {
        unsigned int f = *(volatile unsigned int *)(node + 4);
        if (f == 0) FUN_01008d00(0x10, 0x20e);
        ((nf2)f)(node, param_1);
        if (FUN_0101b74c() != 0 || FUN_01018c58() != 0)
            goto L_e6a;
        goto L_d96;
    }
    case 7: case 9: case 12: case 13: case 14: {
        unsigned int f = *p5;
        if (f == 0)
            goto L_d96;
        ((cb3)f)(*(volatile unsigned int *)(node + 4), param_1, typ);
        if (typ == 0x0d)
            goto L_e6a;
        goto L_d24;
    }
    case 8: {
        unsigned int f = *(volatile unsigned int *)(node + 4);
        if (f == 0) FUN_01008d00(0x10, 0xe3);
        unsigned short uVar1 = *(volatile unsigned short *)f;
        int iv = FUN_0100a17c(uVar1);
        if (iv == 0) FUN_01008d00(0x10, 0xc5);
        *(volatile unsigned short *)(param_1 + 3) = uVar1;
        *param_1 = 0x0d;
        param_1[6] = 0;
        param_1[5] = 1;
        param_1[2] = 1;
        FUN_01026c94(iv, 0);
        *(volatile unsigned int *)(s5 + 0x14) = 0;
        return 4;
    }
    case 10: case 11: {
        unsigned int f = *p6;
        if (f == 0)
            goto L_d96;
        unsigned int node4 = *(volatile unsigned int *)(node + 4);
        ((cb3)f)(node4, param_1, typ);
        unsigned char pc0 = *(volatile unsigned char *)param_1;
        if (pc0 == 0x1d ||
            (pc0 == 0x1a && *(volatile unsigned char *)(param_1 + 2) != 0)) {
            if (FUN_01009d64(*(volatile unsigned short *)(node4 + 8), 4) != 0)
                FUN_01008d00(0x10, 0x1e8);
            goto L_e6a;
        }
        goto L_d24;
    }
    case 15:
        *param_1 = 0x1e;
        *(volatile unsigned int *)(param_1 + 3) =
            *(volatile unsigned int *)(node + 9);
        goto L_d24;
    case 16: {
        unsigned int f = *pc4;
        if (f != 0) {
            unsigned int node4 = *(volatile unsigned int *)(node + 4);
            if (node4 == 0) FUN_01008d00(0x10, 0x23d);
            ((cb16)f)(*(volatile unsigned short *)node4, param_1);
        }
        *(volatile unsigned int *)(s5 + 0x14) = 0;
        return 2;
    }
    default:
        FUN_01008d00(0x10, 0x247);
    }

L_d24:
    uVar7 = 4;
FINALIZE:
    primask = g1_irq_lock();
    {
        unsigned char st = *(volatile unsigned char *)(node + 8);
        if (st == 5 || st == 0)
            goto CLEAR;
    }
    g1_irq_unlock(primask);
    goto LOOP;

CLEAR:
    *(volatile unsigned char *)(node + 8) = 0;
    *(volatile unsigned int *)(s5 + 0x14) = 0;
    g1_irq_unlock(primask);
    if (uVar7 != 0)
        return uVar7;
    goto LOOP;

L_d96:
    uVar7 = 0;
    goto FINALIZE;

L_e6a:
    *(volatile unsigned int *)(s5 + 0x14) = 0;
    return 4;
}
