/* Full reconstruction brightness_level @ 0x23844, CFG-correct extent 464 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=20 */
#include <stdint.h>
extern void FUN_000234e8(void);
extern void FUN_000235dc(void);
extern void FUN_00023634(uintptr_t);
extern void FUN_00072908(uintptr_t,uintptr_t,uint32_t,uint32_t);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00023014(void);
extern void FUN_000365ec(void);
extern void FUN_00074844(uint32_t,uint32_t);
extern void change_work_mode_to(uint32_t);
extern void FUN_0007cbfe(uintptr_t,uint32_t);
extern void FUN_0007c34a(uintptr_t,uint32_t);
extern uint64_t thunk_FUN_00074f68(void);
extern void DEBUG_PRINT(uintptr_t,...);
extern void FUN_00019c70(uintptr_t,...);

typedef void (*brightness_callback)(uintptr_t text, uintptr_t value,
                                    uint32_t style);

void brightness_level(uintptr_t context)
{
    FUN_000234e8();
    FUN_000235dc();
    uint32_t completion_flag = 0;
    for (;;) {
        FUN_00072908(context + 0x80,0,0xffffffffu,0xffffffffu);
        uint32_t drained = 0;
        while (*(volatile uint32_t *)0x200079c4u != 0) {
            FUN_00023634(context);
            drained = 1;
        }
        uint32_t mode = *(volatile uint32_t *)(context + 0x104c);
        if (mode == 0x15 || drained)
            continue;

        brightness_callback callback =
            *(brightness_callback *)(context + 0x1040);
        uintptr_t text = 0;
        uintptr_t value = 0;
        uint32_t style = 0;
        uint32_t invoke = 0;
        switch (mode) {
        case 1:
            text=0x0009e21fu; value=context+0xed5; style=1; invoke=1; break;
        case 2:
            text=0x0009e230u; value=context+0xf60; style=1; invoke=1; break;
        case 3:
            text=0x0009e23cu; value=context+0xfea; style=1; invoke=1; break;
        case 6:
            text=0x0009e1deu; value=*(volatile uintptr_t*)(context+0xfec);
            style=0x6a; invoke=1; break;
        case 7:
            text=0x0009e201u; value=*(volatile uintptr_t*)(context+0xff0);
            style=7; invoke=1; break;
        case 8:
            text=0x0009e249u; value=*(volatile uintptr_t*)(context+0xff4);
            style=0x16a; invoke=1; break;
        case 0xb:
            text=0x0009e259u; value=context+0xef4; style=1; invoke=1; break;
        case 0x11:
            FUN_00074844(0x50000,0);
            change_work_mode_to(7);
            break;
        case 0x16:
            if (*(volatile uint32_t*)0x200079d4u == 0x1c0000u) {
                FUN_000365ec();
                uintptr_t owner=FUN_000167a8();
                uint8_t level=*(volatile uint8_t*)owner==1?0x0d:0x0c;
                owner=FUN_000167a8();
                uintptr_t slot=*(volatile uintptr_t*)(owner+0x100c);
                *(volatile uint8_t*)slot=level;
            }
            *(volatile uint32_t*)0x200079d4u=0;
            *(volatile uint32_t*)0x200079d8u=0;
            *(volatile uint32_t*)0x200079e0u=0;
            *(volatile uint32_t*)0x200079dcu=0;
            continue;
        case 0x17:
            FUN_0007cbfe(context,0);
            change_work_mode_to(1);
            continue;
        case 0x19:
        case 0x1a:
            completion_flag=1;
            break;
        case 0x3e:
            FUN_000167a8();
            FUN_00023014();
            goto wait_for_frame;
        default:
            break;
        }
        if (invoke) {
            callback(text,value,style);
        } else if (mode != 0x19 && mode != 0x1a && mode != 0x3e) {
            if (*(volatile int*)0x2000230cu > 2) {
                int alternate=*(volatile int*)0x20007554u;
                if (alternate)
                    FUN_00019c70(0x0009e8afu,0x0009e8cfu,0,(uint32_t)alternate);
                else
                    DEBUG_PRINT(0x0009e8afu,0x0009e8cfu,0,0);
            }
        }

wait_for_frame:
        do {
            uint64_t before=thunk_FUN_00074f68();
            FUN_00072908(context+0x80,0,0x28000u,0);
            uint64_t after=thunk_FUN_00074f68();
            before=(before*1000u)>>15;
            after=(after*1000u)>>15;
            if ((int64_t)(after-before)>=5000)
                break;
        } while (1);
        *(volatile uint32_t*)(context+0x104c)=0;
        FUN_0007c34a(context,completion_flag);
    }
}
