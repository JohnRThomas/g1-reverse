/* Reconstructed FUN_000521fc @ 0x521fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned undefined4;
extern void FUN_0004d944(unsigned a, unsigned b, void *c, unsigned d);
extern int FUN_0005160c(uintptr_t a, int b, uint c);
extern uint FUN_00051870(int a, int b, int c, int d);
struct decode_result {
    unsigned words[2];
    int amount;
    unsigned value;
    unsigned char present;
    unsigned char reserved[3];
    unsigned tail;
};
_Static_assert(sizeof(struct decode_result) == 24, "decoded result layout");
extern uint FUN_000518a8(void *a, struct decode_result *b);
extern void FUN_00051fe4(void);
extern unsigned FUN_00052000(unsigned a);
extern void FUN_00052038(int a, int b, void *c, void *d);
extern int FUN_00080872(uintptr_t a, void *b, int c, void *d);
extern void FUN_00086c1e(void *a, unsigned b, int c, int d);
extern void FUN_00086c78(void *a, int b, int c);

unsigned FUN_000521fc(int param_1)
{
    const uintptr_t owner_addr = (uintptr_t)(uint32_t)param_1;
    const uintptr_t state_addr = UINT32_C(0x2000ab7c);
    volatile uint32_t *puVar1;
    uint uVar2;
    int iVar3;
    uint32_t parser_handle, control_handle;
    unsigned uVar4;
    struct { unsigned kind, descriptor; uint value; } diagnostic;
    unsigned local_f4;
    struct decode_result decoded;
    struct {
        undefined1 text[4];
        int values[3];
        int count;
        unsigned length;
        int offset;
        undefined1 tail[4];
    } parsed;
    undefined1 auStack_b8[32];
    struct parser_field {
        unsigned tag;
        unsigned width;
        unsigned decoder;
        void *output;
        unsigned char optional;
    } cfg[6];
    _Static_assert(sizeof(parsed) == 32, "parsed configuration layout");
    _Static_assert(sizeof(struct parser_field) == 20, "parser field layout");

    parser_handle = *(volatile uint32_t *)(owner_addr + 4u);
    control_handle = *(volatile uint32_t *)(owner_addr + 8u);
    local_f4 = 0;
    FUN_00086c78(&parsed, 0, 0x20);
    parsed.values[0] = -1;
    parsed.values[1] = -1;
    cfg[0] = (struct parser_field){0x000f349f, 5, 0x00085f8d, parsed.text, 0};
    cfg[1] = (struct parser_field){0x000f3b6f, 4, 0x00085f97, &parsed.values[2], 0};
    cfg[2] = (struct parser_field){0x000f7c24, 3, 0x00085f93, &parsed.values[1], 0};
    cfg[3] = (struct parser_field){0x000a24e0, 3, 0x00085f93, &parsed.values[0], 0};
    cfg[4] = (struct parser_field){0x000f27df, 3, 0x00085f97, &parsed.length, 0};
    cfg[5] = (struct parser_field){0x000f27e3, 7, 0x00086007, parsed.tail, 0};
    iVar3 = FUN_00080872((uintptr_t)parser_handle + 4u,
                         cfg, 6, &local_f4);
    if (iVar3 != 0) {
        return 3;
    }
    uVar2 = FUN_000518a8(parsed.text, &decoded);
    iVar3 = parsed.values[0];
    puVar1 = (volatile uint32_t *)state_addr;
    uVar4 = 0;
    if (uVar2 == 0) {
        if (decoded.present == 0) {
            uVar4 = FUN_00052000(control_handle);
            return uVar4;
        }
        puVar1[0] = decoded.value;
        puVar1[2] = decoded.words[0];
        if (parsed.values[0] == 0) {
            uint32_t offset = (uint32_t)parsed.offset;
            puVar1[1] = 0;
            *(volatile char *)(state_addr + 12u) = (char)parsed.offset;
            FUN_00086c1e((void *)(state_addr + 13u), parsed.length,
                         parsed.offset, 0x23);
            FUN_00086c78((void *)(state_addr + 13u + offset), 0,
                         (int)(UINT32_C(0x20) - offset));
        }
        if (parsed.count == 0) {
            if (puVar1[2] == puVar1[1]) {
                FUN_00052038(1, 0, auStack_b8, (void *)0);
            }
        } else {
            uVar2 = FUN_00051870(
                iVar3, parsed.values[2], decoded.amount,
                (uint32_t)parsed.count + puVar1[1] == puVar1[2]);
            if (uVar2 != 0) {
                diagnostic.descriptor = 0xf280b;
                diagnostic.kind = 3;
                diagnostic.value = uVar2;
                FUN_0004d944(0x88208, 0x1840, &diagnostic, 0);
                goto LAB_00052300;
            }
            {
                uint32_t next_progress =
                    puVar1[1] + (uint32_t)decoded.amount;
                puVar1[1] = next_progress;
                if (next_progress == puVar1[2]) {
                    FUN_00052038(1, 0, auStack_b8, 0);
                    FUN_00052000(control_handle);
                    FUN_00051fe4();
                    return 0;
                }
            }
        }
        FUN_00052000(control_handle);
    } else {
        diagnostic.descriptor = 0xf27eb;
        diagnostic.kind = 3;
        diagnostic.value = uVar2;
        FUN_0004d944(0x88208, 0x1840, &diagnostic, 0);
LAB_00052300:
        iVar3 = FUN_0005160c((uintptr_t)control_handle + 4u, 1,
                            uVar2 & 0xffff);
        FUN_00052038(1, 0, auStack_b8, (void *)0);
        FUN_00051fe4();
        if (iVar3 == 0) {
            uVar4 = 7;
        }
    }
    return uVar4;
}
