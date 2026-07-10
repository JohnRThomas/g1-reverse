/* named: cbor_decode_container_start */
/* Reconstructed cbor_decode_container_start @ 0x85f06  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085c38(unsigned*,unsigned);
extern int FUN_00085d70(unsigned*,int);
extern int cbor_decode_check_major_type(void);
extern int cbor_decode_extract_value(unsigned*,void*,int,unsigned,unsigned*);
int cbor_decode_container_start(unsigned* param_1, unsigned param_2, unsigned param_3){
  int r5; int iVar2; unsigned char bVar3; unsigned* puVar4;
  unsigned local_14, uStack_10;
  puVar4=param_1; local_14=param_2; uStack_10=param_3;
  r5=cbor_decode_check_major_type();
  if(r5==0) return 0;
  bVar3 = (*(unsigned char*)(*param_1)) & 0x1f;
  if(bVar3==0x1f){
    local_14=0xffffffef;
    if(param_1[2]==0){ FUN_00085d70(param_1,3); return 0; }
    *param_1 = *param_1 + 1;
    param_1[2] = param_1[2] - 1;
  } else {
    int t = cbor_decode_extract_value(param_1,&local_14,4,bVar3,puVar4);
    if(t==0) return 0;
    r5=0;
  }
  iVar2 = FUN_00085c38(param_1, local_14);
  if(iVar2!=0){
    *(char*)((int)param_1+0x10) = (char)r5;
    return iVar2;
  }
  *param_1 = param_1[1];
  param_1[2] = param_1[2] + 1;
  return 0;
}

