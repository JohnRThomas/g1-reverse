/* readable reconstruction; identity: FUN_0007712c @ 0x0007712c
 * public-name: printf_render_float
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_dcmpeq                           <= FUN_0000ddc8 @ 0x0000ddc8
 *   __aeabi_dcmplt                           <= FUN_0000dddc @ 0x0000dddc
 *   __aeabi_dcmple                           <= FUN_0000ddf0 @ 0x0000ddf0
 *   double_is_unordered                      <= FUN_0000de2c @ 0x0000de2c
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   printf_render_float                      <= FUN_0007712c @ 0x0007712c
 *   get_static_ctx_ptr                       <= FUN_00078590 @ 0x00078590
 *   dtoa_format_cvt                          <= FUN_00086cda @ 0x00086cda
 *   itoa_signed_exponent                     <= FUN_00086daa @ 0x00086daa
 *   vfprintf_emit_padded_field               <= FUN_00086e1c @ 0x00086e1c
 * address symbols (name @ address):
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Reconstructed FUN_0007712c @ 0x7712c  (parity: 1/1 trials, PROVEN) */
typedef unsigned int u32;
typedef int (*outfn)(u32, u32, u32, int);

extern u32 *get_static_ctx_ptr(void);
extern u32  strlen(u32);
extern int  double_is_unordered(u32, u32, u32, u32);
extern int  __aeabi_dcmple(u32, u32, u32, u32);
extern int  __aeabi_dcmplt(u32, u32, u32, u32);
extern int  __aeabi_dcmpeq(u32, u32, u32, u32);
extern u32 *dtoa_format_cvt(u32 p1, u32 prec, u32 flags, char *sign, double val,
                         u32 *pdec, u32 conv, u32 *pnd, u32 zero);
extern u32  itoa_signed_exponent(u32 *buf, u32 dec, u32 conv);
extern int  vfprintf_emit_padded_field(u32 p1, u32 *p2, u32 *pw, u32 p3, outfn fn);

#define ADD3NEG(x) (((long long)(int)(x) + 3) < 0)

u32 printf_render_float(u32 param_1, u32 *param_2, u32 param_3, outfn param_4, int *param_5)
{
  u32 uVar1, uVar3, uVar7, *puVar2, *puVar8, *puVar9, uVar10, uVar11, uVar13;
  int iVar4, iVar5, iVar6;
  unsigned char bVar12;
  char local_35;
  u32 local_34, local_30, local_2c[2];
  unsigned char *pb = (unsigned char *)param_2;

  puVar2 = get_static_ctx_ptr();
  uVar7 = *puVar2;
  uVar3 = strlen(uVar7);
  local_30 = 0;
  bVar12 = (unsigned char)param_2[6];
  uVar13 = *param_2;
  puVar8 = (u32 *)((*param_5 + 7U) & 0xfffffff8);
  *param_5 = (int)(puVar8 + 2);
  uVar1 = 0x7fefffffU;
  uVar10 = *puVar8;
  uVar11 = puVar8[1];
  param_2[0x12] = uVar10;
  param_2[0x13] = uVar11;
  iVar4 = double_is_unordered(uVar10, uVar11 & 0x7fffffff, 0xffffffff, uVar1);
  if ((iVar4 == 0) &&
      (iVar4 = __aeabi_dcmple(uVar10, uVar11 & 0x7fffffff, 0xffffffff, 0x7fefffffU), iVar4 == 0)) {
    iVar4 = __aeabi_dcmplt(uVar10, uVar11, 0, 0);
    puVar8 = (u32 *)0x000f8b7cU;
    puVar9 = (u32 *)0x000f0f69U;
    if (iVar4 != 0) {
      pb[0x43] = 0x2d;
      puVar8 = (u32 *)0x000f8b7cU;
      puVar9 = (u32 *)0x000f0f69U;
    }
LAB_000771b6:
    if (0x47 < bVar12) {
      puVar8 = puVar9;
    }
    uVar10 = 0;
    param_2[4] = 3;
    *param_2 = uVar13 & 0xfffffffb;
  }
  else {
    iVar4 = double_is_unordered(uVar10, uVar11, uVar10, uVar11);
    puVar8 = (u32 *)0x000f8b80U;
    if (iVar4 != 0) {
      puVar9 = (u32 *)0x000f8b84U;
      if ((int)uVar11 < 0) {
        pb[0x43] = 0x2d;
        puVar9 = (u32 *)0x000f8b84U;
      }
      goto LAB_000771b6;
    }
    if (param_2[1] == 0xffffffff) {
      uVar11 = 6;
LAB_00077214:
      param_2[1] = uVar11;
    }
    else if (((bVar12 & 0xdf) == 0x47) && (param_2[1] == 0)) {
      uVar11 = 1;
      goto LAB_00077214;
    }
    uVar13 = uVar13 | 0x400;
    *param_2 = uVar13;
    {
      union { u32 w[2]; double d; } _u;
      _u.w[0] = param_2[0x12];
      _u.w[1] = param_2[0x13];
      puVar8 = dtoa_format_cvt(param_1, param_2[1], uVar13, &local_35, _u.d,
                            &local_34, (u32)bVar12, &local_30, 0);
    }
    if (bVar12 == 0x67) {
      if ((ADD3NEG(local_34)) || ((int)param_2[1] < (int)local_34)) {
        bVar12 = 0x65;
        goto LAB_0007728c;
      }
LAB_0007724e:
      if ((int)local_34 < (int)local_30) {
        if ((int)local_34 < 1) {
          iVar4 = 2 - (int)local_34;
        }
        else {
          iVar4 = 1;
        }
        uVar13 = local_30 + iVar4;
LAB_000772e6:
        param_2[4] = uVar13;
      }
      else {
        param_2[4] = local_34;
        if ((int)(*param_2 << 0x1f) < 0) {
          uVar13 = local_34 + 1;
          goto LAB_000772e6;
        }
      }
LAB_000772e8:
      uVar10 = 0;
      param_2[0x16] = local_34;
    }
    else {
      if (bVar12 == 0x47) {
        if ((!ADD3NEG(local_34)) && ((int)local_34 <= (int)param_2[1])) {
          bVar12 = 0x67;
          goto LAB_0007724e;
        }
        bVar12 = 0x45;
      }
      else if (0x65 < bVar12) {
        if (bVar12 != 0x66) goto LAB_0007724e;
        uVar13 = param_2[1];
        if ((int)local_34 < 1) {
          if ((uVar13 == 0) && (-1 < (int)(*param_2 << 0x1f))) {
            uVar13 = 1;
          }
          else {
            uVar13 = uVar13 + 2;
          }
        }
        else {
          param_2[4] = local_34;
          if ((uVar13 == 0) && (-1 < (int)(*param_2 << 0x1f))) goto LAB_000772e8;
          uVar13 = uVar13 + 1 + local_34;
        }
        goto LAB_000772e6;
      }
LAB_0007728c:
      local_34 = local_34 - 1;
      uVar10 = itoa_signed_exponent(param_2 + 0x14, local_34, bVar12);
      param_2[4] = local_30 + uVar10;
      if ((1 < (int)local_30) || ((int)(*param_2 << 0x1f) < 0)) {
        param_2[4] = local_30 + uVar10 + 1;
      }
    }
    if (local_35 != '\0') {
      pb[0x43] = 0x2d;
    }
  }
  iVar4 = vfprintf_emit_padded_field(param_1, param_2, local_2c, param_3, param_4);
  uVar13 = local_30;
  if (iVar4 == -1) {
    return 0xffffffff;
  }
  if ((int)(*param_2 << 0x15) < 0) {
    if (bVar12 < 0x66) {
      if (((int)local_30 < 2) && (-1 < (int)(*param_2 << 0x1f))) {
        iVar6 = 1;
LAB_0007752c:
        iVar4 = (*param_4)(param_1, param_3, (u32)puVar8, iVar6);
        if (iVar4 == -1) {
          return 0xffffffff;
        }
      }
      else {
        iVar4 = (*param_4)(param_1, param_3, (u32)puVar8, 1);
        if (iVar4 == -1) {
          return 0xffffffff;
        }
        iVar4 = (*param_4)(param_1, param_3, uVar7, uVar3);
        if (iVar4 == -1) {
          return 0xffffffff;
        }
        iVar6 = uVar13 - 1;
        iVar4 = __aeabi_dcmpeq(param_2[0x12], param_2[0x13], 0, 0);
        if (iVar4 == 0) {
          puVar8 = (u32 *)((int)puVar8 + 1);
          goto LAB_0007752c;
        }
        for (iVar4 = 0; iVar4 < iVar6; iVar4 = iVar4 + 1) {
          iVar5 = (*param_4)(param_1, param_3, (u32)pb + 0x1a, 1);
          if (iVar5 == -1) {
            return 0xffffffff;
          }
        }
      }
      puVar8 = param_2 + 0x14;
    }
    else {
      iVar4 = __aeabi_dcmpeq(param_2[0x12], param_2[0x13], 0, 0);
      uVar13 = local_30;
      if (iVar4 != 0) {
        iVar4 = (*param_4)(param_1, param_3, 0x000f7a30U, 1);
        uVar13 = local_30;
        if (iVar4 == -1) {
          return 0xffffffff;
        }
        if (((int)local_34 < (int)local_30) || ((int)(*param_2 << 0x1f) < 0)) {
          iVar4 = (*param_4)(param_1, param_3, uVar7, uVar3);
          if (iVar4 == -1) {
            return 0xffffffff;
          }
          for (iVar4 = 0; iVar4 < (int)(uVar13 - 1); iVar4 = iVar4 + 1) {
            iVar6 = (*param_4)(param_1, param_3, (u32)pb + 0x1a, 1);
            if (iVar6 == -1) {
              return 0xffffffff;
            }
          }
        }
        goto LAB_0007737a;
      }
      if (0 < (int)local_34) {
        uVar10 = param_2[0x16];
        if ((int)local_30 <= (int)param_2[0x16]) {
          uVar10 = local_30;
        }
        if ((0 < (int)uVar10) &&
            (iVar4 = (*param_4)(param_1, param_3, (u32)puVar8, uVar10), iVar4 == -1)) {
          return 0xffffffff;
        }
        for (iVar4 = 0; uVar11 = param_2[0x16],
             iVar4 < (int)(uVar11 - (uVar10 & ~((int)uVar10 >> 0x1f))); iVar4 = iVar4 + 1) {
          iVar6 = (*param_4)(param_1, param_3, (u32)pb + 0x1a, 1);
          if (iVar6 == -1) {
            return 0xffffffff;
          }
        }
        if ((((int)local_34 < (int)uVar13) || ((int)(*param_2 << 0x1f) < 0)) &&
            (iVar4 = (*param_4)(param_1, param_3, uVar7, uVar3), iVar4 == -1)) {
          return 0xffffffff;
        }
        uVar10 = uVar13 - local_34;
        if ((int)(uVar13 - uVar11) <= (int)(uVar13 - local_34)) {
          uVar10 = uVar13 - uVar11;
        }
        if ((0 < (int)uVar10) &&
            (iVar4 = (*param_4)(param_1, param_3, uVar11 + (u32)puVar8, uVar10), iVar4 == -1)) {
          return 0xffffffff;
        }
        for (iVar4 = 0; iVar4 < (int)((uVar13 - local_34) - (uVar10 & ~((int)uVar10 >> 0x1f)));
             iVar4 = iVar4 + 1) {
          iVar6 = (*param_4)(param_1, param_3, (u32)pb + 0x1a, 1);
          if (iVar6 == -1) {
            return 0xffffffff;
          }
        }
        goto LAB_0007737a;
      }
      iVar4 = (*param_4)(param_1, param_3, 0x000f7a30U, 1);
      uVar10 = local_30;
      if (iVar4 == -1) {
        return 0xffffffff;
      }
      if ((local_30 == 0 && local_34 == 0) && (-1 < (int)(*param_2 << 0x1f))) goto LAB_0007737a;
      iVar4 = (*param_4)(param_1, param_3, uVar7, uVar3);
      if (iVar4 == -1) {
        return 0xffffffff;
      }
      for (iVar4 = 0; -iVar4 != (int)local_34 && iVar4 <= (int)-local_34; iVar4 = iVar4 + 1) {
        iVar6 = (*param_4)(param_1, param_3, (u32)pb + 0x1a, 1);
        if (iVar6 == -1) {
          return 0xffffffff;
        }
      }
    }
  }
  else {
    uVar10 = param_2[4];
  }
  iVar4 = (*param_4)(param_1, param_3, (u32)puVar8, uVar10);
  if (iVar4 == -1) {
    return 0xffffffff;
  }
LAB_0007737a:
  if ((int)(*param_2 << 0x1e) < 0) {
    for (iVar4 = 0; iVar4 < (int)(param_2[3] - local_2c[0]); iVar4 = iVar4 + 1) {
      iVar6 = (*param_4)(param_1, param_3, (u32)pb + 0x19, 1);
      if (iVar6 == -1) {
        return 0xffffffff;
      }
    }
  }
  if ((int)param_2[3] < (int)local_2c[0]) {
    return local_2c[0];
  }
  return param_2[3];
}
