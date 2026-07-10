/* named: send_pairing_rsp */
/* Reconstructed send_pairing_rsp @ 0x830ee  (parity: 300/300 trials, PROVEN) */

extern int smp_create_pdu(int, int, unsigned int, unsigned int, unsigned int);
extern void *net_buf_simple_add(int, int);
extern void bt_smp_send_pdu(int, int, int);

unsigned int send_pairing_rsp(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int uVar3;
  iVar1 = smp_create_pdu(param_1, 2, param_3, param_4, param_4);
  if (iVar1 == 0) {
    uVar3 = 8;
  } else {
    puVar2 = (unsigned int *)net_buf_simple_add(iVar1 + 0xc, 6);
    *puVar2 = *(unsigned int *)(param_1 + 0x11);
    *(unsigned short *)(puVar2 + 1) = *(unsigned short *)(param_1 + 0x15);
    bt_smp_send_pdu(param_1, iVar1, 0);
    uVar3 = 0;
  }
  return uVar3;
}

