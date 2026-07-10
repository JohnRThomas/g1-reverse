/* named: img_mgmt_state_read_51c98 */
/* Reconstructed img_mgmt_state_read_51c98 @ 0x51c98  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int img_mgmt_state_encode_image(int,unsigned,int);
extern unsigned FUN_00051c38(void);
extern unsigned k_heap_alloc(int,unsigned,int,unsigned,int);
extern unsigned FUN_000809b0(int,int);
extern void nullsub_4(void);
extern void nullsub_5(void);
extern unsigned FUN_00080a46(int);
extern int cbor_encode_int32(int,int);
extern unsigned cbor_encode_array_indef_start(int,int);
extern int cbor_encode_break(int,int);

unsigned img_mgmt_state_read_51c98(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
  unsigned uVar1, uVar2, uVar3, uVar4, uVar10;
  int iVar5, iVar7, iVar8, iVar9;
  int iVar6;
  unsigned uStack_24;

  iVar6 = *(int *)(param_1 + 8) + 4;
  uStack_24 = param_2;
  uVar2 = k_heap_alloc(iVar6, 0x000f275f, 6, param_4, param_1);
  if (uVar2 != 0) {
    uVar2 = cbor_encode_array_indef_start(iVar6, 4);
  }
  iVar7 = 0;
  uVar2 = uVar2 & 1;
  nullsub_4();
  do {
    if (uVar2 == 0) {
LAB_00051cde:
      nullsub_5();
      return 7;
    }
    if (iVar7 == 2) {
      iVar7 = cbor_encode_break(iVar6, 4);
      if (((iVar7 != 0) && (iVar7 = k_heap_alloc(iVar6, 0x000f2766, 0xb, 0, 0), iVar7 != 0)) &&
         (iVar6 = cbor_encode_int32(iVar6, 0), iVar6 != 0)) {
        nullsub_5();
        return 0;
      }
      goto LAB_00051cde;
    }
    uStack_24 = uStack_24 & 0xffffff;
    uVar3 = FUN_000809b0(iVar7, (int)&uStack_24 + 3);
    uVar4 = FUN_00080a46(iVar7);
    uVar2 = uVar4;
    if (3 < uVar4) {
      uVar2 = FUN_00051c38();
    }
    uVar1 = uStack_24 >> 0x18;
    uVar10 = uVar2 ^ 1;
    if (uVar1 == 2) {
      iVar8 = 1;
      iVar5 = iVar8;
      if (uVar3 != uVar2) goto LAB_00051d30;
LAB_00051d1e:
      iVar9 = 0;
      iVar8 = iVar5;
    }
    else {
      iVar8 = 5;
      iVar5 = 5;
      if ((uVar3 == uVar2) || (iVar5 = iVar8, 2 < uVar1)) goto LAB_00051d1e;
LAB_00051d30:
      iVar9 = (int)*(volatile int8_t *)(0x000f27cc + uVar1);
    }
    if ((int)uVar4 < (int)uVar10) {
      iVar5 = img_mgmt_state_encode_image(iVar6, uVar4, iVar8);
    }
    else {
      iVar5 = img_mgmt_state_encode_image(iVar6, uVar10, iVar9);
      uVar10 = uVar4;
      iVar9 = iVar8;
    }
    if (iVar5 == 0) goto LAB_00051cde;
    uVar2 = img_mgmt_state_encode_image(iVar6, uVar10, iVar9);
    iVar7 = iVar7 + 1;
  } while( 1 );
}

