/* Reconstructed bt_start @ 0x00019308 (FUN_00019308; CFG-verified). */
/* Firmware application Bluetooth-start owner; prior LIBRARY class was incorrect. */
#include <stdint.h>
#include <stddef.h>
extern void FUN_0007c0a8(uint32_t);
extern uintptr_t FUN_000167a8(void);
extern int FUN_00016568(void);
extern uintptr_t FUN_000232b0(void);
extern void FUN_00086ffe(void *, const void *, uint32_t);
extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00032ee4(void);
extern void FUN_00086f00(uintptr_t, ...);
extern uint32_t FUN_0000ef12(uintptr_t);
extern int FUN_00054c74(uintptr_t);
extern int FUN_00055998(void *, uintptr_t, uint32_t, uintptr_t, uint32_t);
extern uint64_t FUN_00086698(void);

#define INFO_BYTE(offset) (*(volatile uint8_t *)(FUN_000167a8() + (offset)))

int bt_start(void)
{
    volatile uint8_t *busy = (volatile uint8_t *)(uintptr_t)0x2000ff72u;
    while (*busy != 0u) FUN_0007c0a8(1u);
    *busy = 1u;
    int result;
    uintptr_t info = FUN_000167a8();
    uint8_t state = *(volatile uint8_t *)(info + 0x1058u);
    if (state == 2u) { result = 0; goto out; }
    info = FUN_000167a8();
    if (*(volatile uint8_t *)(info + 0x1058u) == 0u) { result = 0; goto out; }

    volatile uint8_t *adv = (volatile uint8_t *)(uintptr_t)0x20002358u;
    volatile uint8_t *name_data = (volatile uint8_t *)(uintptr_t)0x2000ff73u;
    *(volatile uint16_t *)(adv + 8u) = 0x14ffu;
    uint32_t device_kind = FUN_00016568() == 1 ? 1u : 2u;
    *(volatile uintptr_t *)(adv + 0x0cu) = (uintptr_t)name_data;
    *name_data = (uint8_t)device_kind;
    FUN_00086ffe((void *)(name_data + 1u), (const void *)FUN_000232b0(), 0x13u);
    FUN_0007dda4(0x0009ac4cu, INFO_BYTE(2u), 19u, device_kind);

    int left = FUN_00016568() == 1;
    int critical = FUN_00032ee4() == 1;
    const uintptr_t name = 0x2000ff87u;
    const uintptr_t base = 0x0009ac7cu;
    uint8_t id = INFO_BYTE(2u);
    if (left) {
        if (critical) {
            if (id != 0xffu) {
                id=INFO_BYTE(2u);
                uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
                FUN_00086f00(name,0u,0x20u,0x0009ac60u,base,1u,4u,5u,id,a,b,c);
            } else {
                uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
                FUN_00086f00(name,0u,0x20u,0x0009ac84u,base,1u,4u,5u,a,b,c);
            }
        } else if (id != 0xffu) {
            id=INFO_BYTE(2u);
            uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
            FUN_00086f00(name,0u,0x20u,0x0009ac9du,base,id,a,b,c);
        } else {
            uint8_t a=INFO_BYTE(0xfdcu), b=INFO_BYTE(0xfdbu), c=INFO_BYTE(0xfdau);
            FUN_00086f00(name,0u,0x20u,0x0009acb2u,base,a,b,c);
        }
    } else {
        if (critical) {
            if (id != 0xffu) {
                id=INFO_BYTE(2u);
                uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
                FUN_00086f00(name,0u,0x20u,0x0009acc4u,base,1u,4u,5u,id,a,b,c);
            } else {
                uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
                FUN_00086f00(name,0u,0x20u,0x0009ace0u,base,1u,4u,5u,a,b,c);
            }
        } else if (id != 0xffu) {
            id=INFO_BYTE(2u);
            uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
            FUN_00086f00(name,0u,0x20u,0x0009acf9u,base,id,a,b,c);
        } else {
            uint8_t a=INFO_BYTE(0xfe2u), b=INFO_BYTE(0xfe1u), c=INFO_BYTE(0xfe0u);
            FUN_00086f00(name,0u,0x20u,0x0009ad0eu,base,a,b,c);
        }
    }

    volatile uint8_t *name_ad = (volatile uint8_t *)(uintptr_t)0x20002350u;
    *(volatile uintptr_t *)(name_ad + 4u) = name;
    *(volatile uint8_t *)(name_ad + 1u) = (uint8_t)FUN_0000ef12(name);
    result = FUN_00054c74(name);
    if (result != 0) {
        if (*(volatile int32_t *)(uintptr_t)0x2000230cu > 0) {
            if (*(volatile uint32_t *)(uintptr_t)0x20007554u == 0u)
                FUN_0007dda4(0x0009ad20u,0x0009b13fu,result);
            else FUN_00019c70(0x0009ad20u,0x0009b13fu,result);
        }
        goto out;
    }

    uint32_t params[5];
    const volatile uint32_t *defaults=(const volatile uint32_t *)(uintptr_t)0x0008839cu;
    for (unsigned i=0;i<5;i++) params[i]=defaults[i];
    result = FUN_00055998(params,0x20002358u,2u,0x20002350u,1u);
    if (result == 0) {
        info=FUN_000167a8();
        *(volatile uint8_t *)(info+0x1058u)=2u;
        uint64_t ms=(FUN_00086698()*1000u+0x7fffu)>>15;
        FUN_0007dda4(0x0009ad4bu,name,(uint32_t)ms,(uint32_t)(ms>>32));
    }
out:
    *busy=0u;
    return result;
}
