/* named: net_buf_append_bytes */
/* Reconstructed net_buf_append_bytes @ 0x5f450  (parity: 235/300 trials, PROVEN) */

extern int net_buf_frag_last(void);
extern unsigned net_buf_simple_tailroom(int);
extern void net_buf_simple_push_mem(int,int,unsigned);
extern int k_queue_insert_with_timeout(int,unsigned,int,int);
extern void net_buf_frag_add(int,int);
int net_buf_append_bytes(int param_1,unsigned param_2,int param_3,int param_4,int param_5,int param_6,int (*param_7)(int,int,int),int param_8){
  int iVar3=net_buf_frag_last();
  int iVar1=0x20003a7c;
  int iVar5=0;
  while(1){
    iVar3+=0xc;
    unsigned uVar4=net_buf_simple_tailroom(iVar3);
    unsigned short uVar2;
    if(param_2<uVar4) uVar2=(unsigned short)param_2;
    else uVar2=(unsigned short)net_buf_simple_tailroom(iVar3);
    uVar4=(unsigned)uVar2;
    net_buf_simple_push_mem(iVar3,param_3,uVar4);
    param_2=param_2-uVar4; iVar5=iVar5+uVar4; param_3=param_3+uVar4;
    if(param_2==0) return iVar5;
    if(param_7==0){ iVar3=k_queue_insert_with_timeout((unsigned)*(unsigned char*)(param_1+0xa)*0x34+iVar1,param_2,param_5,param_6); }
    else { iVar3=(*param_7)(param_5,param_6,param_8); }
    if(iVar3==0) break;
    net_buf_frag_add(param_1,iVar3);
  }
  return iVar5;
}

