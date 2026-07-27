/* Reconstructed FUN_0007c6a0 @ 0x7c6a0  (parity: 300/300 trials, PROVEN)
 *
 * P4 iteration 40 -- DROPPED ARGUMENTS + STACK-OBJECT LAYOUT.  Three defects,
 * all in the class AGENTS.md lists as invisible to the harness:
 *
 *  (a) memcpy is a THREE-argument function and every copy here is the NDEF
 *      serializer writing the record type name, the record id and each payload
 *      fragment into the output buffer:
 *        0007c6e4 ldrb r2,[r5,#1] ; 0007c6ea ldr r0,[r4] ; 0007c6ec ldr r1,[r5,#4]
 *        0007c6ee add  r0,r6      ; 0007c6f0 bl #0x86c04
 *        0007c6f8 ldrb r2,[r5,#2] ; ...       0007c702 bl #0x86c04
 *        0007c738 ldr  r2,[sp,#0xc]; ...      0007c744 bl #0x86c04
 *      The previous body passed only (dst, src).
 *  (b) 0007c6ba `bl #0x7c41c` runs with r0 still the node; the total-length
 *      helper takes one argument and the previous body passed 0.
 *  (c) the two-word view handed to opt_node_serialize_7c5ba lived in TWO
 *      SEPARATE locals, so GCC was free to keep the length in a register.  It
 *      is one object; a struct makes that explicit.
 */
#include <stdint.h>
extern int FUN_0007c408(int);
extern int FUN_0007c41c(unsigned int);
extern unsigned FUN_0007c5ba(unsigned char*, int*);
extern int FUN_0007c670(int, int *, int);
extern void FUN_00086c04(int dst, int src, unsigned length);

/* The shipped code passes sp+0/sp+4 and sp+8/sp+0xc as ONE two-word object
 * each (the callee writes the second word back). */
struct g1_opt_view { int data; int length; };

int FUN_0007c6a0(int param_1, int *param_2){
    if (param_1==0 || param_2==0 || *param_2==0) return 7;
    unsigned uVar6 = param_2[1];
    unsigned uVar1 = FUN_0007c41c(param_1);
    if (uVar6 < uVar1){
        int iv = FUN_0007c41c(param_1);
        param_2[1] = iv;
        return 1;
    }
    struct g1_opt_view local;
    volatile struct g1_opt_view fragment;
    local.data = *param_2;
    local.length = param_2[1];
    int iVar3 = FUN_0007c5ba(param_1, &local);
    int iVar2 = local.length;
    if (iVar3 != 0) return iVar3;
    if (*(char*)(param_1+1) != 0){
        FUN_00086c04(*param_2 + iVar2, *(int*)(param_1+4),
                     *(unsigned char*)(param_1+1));
        iVar2 = iVar2 + *(unsigned char*)(param_1+1);
    }
    if (*(char*)(param_1+2) != 0){
        FUN_00086c04(*param_2 + iVar2, *(int*)(param_1+8),
                     *(unsigned char*)(param_1+2));
        iVar2 = iVar2 + *(unsigned char*)(param_1+2);
    }
    int iVar7 = *param_2;
    int iVar3b = param_2[1];
    uVar1 = FUN_0007c408(param_1);
    if ((unsigned)(iVar3b - iVar2) < uVar1){
        return 1;
    }
    int acc = 0;
    int uVar5 = 1;
    while (1){
        int iVar4 = FUN_0007c670(param_1, (void *)&fragment, uVar5);
        if (iVar4 == 0) break;
        if (fragment.length != 0){
            FUN_00086c04(iVar2 + acc + iVar7, fragment.data,
                         (unsigned)fragment.length);
        }
        uVar5 = 0;
        acc = acc + fragment.length;
    }
    param_2[1] = iVar2 + acc;
    return 0;
}
