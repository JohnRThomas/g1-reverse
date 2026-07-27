/* readable reconstruction; identity: FUN_00059f04 @ 0x00059f04
 * public-name: sc_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   sc_set                                   <= FUN_00059f04 @ 0x00059f04
 *   strtoul                                  <= FUN_00077c1c @ 0x00077c1c
 *   settings_name_next                       <= FUN_0007f1e8 @ 0x0007f1e8
 *   bt_settings_decode_key                   <= FUN_00080cf2 @ 0x00080cf2
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f2b65                             @ 0x000f2b65
 *   rodata_f472a                             @ 0x000f472a
 *   rodata_f4746                             @ 0x000f4746
 *   rodata_f4761                             @ 0x000f4761
 *   rodata_f4783                             @ 0x000f4783
 */
/* Reconstructed FUN_00059f04 @ 0x59f04  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int find_sc_cfg_59bcc(int,void*);
extern long unsigned int strtoul(const char * restrict,  char ** restrict,  int);
extern int settings_name_next(int, int);
extern int bt_settings_decode_key(int,void*);
extern void bt_addr_le_copy_828da(unsigned long*, unsigned long*);
extern int log_msg_create_3arg(int,int,void*);

int sc_set(int param_1, int param_2, codeptr param_3, int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  struct __attribute__((packed)) {
    unsigned int type;
    unsigned int label;
    int value;
    unsigned short flags;
  } diagnostic;
  struct { unsigned int type, label; } short_diagnostic;
  int iStack_50;
  int local_44;
  unsigned char auStack_40[24];

  if (param_1 == 0) {
    short_diagnostic.type = 2;
    short_diagnostic.label = 0xf2b65;
    log_msg_create_3arg(0x88128, 0x1040, &short_diagnostic);
  } else {
    iVar1 = bt_settings_decode_key(param_1, auStack_40);
    if (iVar1 == 0) {
      settings_name_next(param_1, &local_44);
      if (local_44 == 0 || (iStack_50 = strtoul(local_44, 0, 10), iStack_50 == 0)) {
        puVar2 = (unsigned int*)find_sc_cfg_59bcc(0, auStack_40);
        if (puVar2 == 0) {
          if (param_2 == 0) return 0;
          puVar2 = (unsigned int*)find_sc_cfg_59bcc(0, (void*)0xf2b3a);
          if (puVar2 == 0) {
            short_diagnostic.type = 2;
            short_diagnostic.label = 0xf4761;
            log_msg_create_3arg(0x88128, 0x1040, &short_diagnostic);
            return -0xc;
          }
          *(unsigned char*)puVar2 = 0;
          bt_addr_le_copy_828da((unsigned char*)puVar2 + 1, auStack_40);
        } else if (param_2 == 0) {
          puVar2[0] = 0; puVar2[1] = 0; puVar2[2] = 0;
          return 0;
        }
        iVar1 = (*param_3)(param_4, puVar2 + 2, 4);
        if (-1 < iVar1) return 0;
        diagnostic.type = 3;
        diagnostic.label = 0xf4783;
        diagnostic.value = iVar1;
        log_msg_create_3arg(0x88128, 0x1840, &diagnostic);
        return iVar1;
      }
      diagnostic.type = 3;
      diagnostic.label = 0xf4746;
      diagnostic.value = iStack_50;
      log_msg_create_3arg(0x88128, 0x1840, &diagnostic);
    } else {
      diagnostic.type = 0x1000003;
      diagnostic.label = 0xf472a;
      diagnostic.value = param_1;
      diagnostic.flags = 0x200;
      log_msg_create_3arg(0x88128, 0x1c40, &diagnostic);
    }
  }
  return -0x16;
}
