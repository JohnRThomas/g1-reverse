/* Reconstructed FUN_0005c80c @ 0x5c80c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00053050(unsigned,unsigned,void*,int);
extern int FUN_00082a42(unsigned,unsigned,void*);
extern int FUN_00082c9c(int,unsigned,unsigned,void*);
int FUN_0005c80c(unsigned param_1, unsigned param_2){
  unsigned char* puVar1; int iVar2;
  struct request_frame {
    unsigned char reserved[4];
    unsigned input;
    unsigned char selector;
    unsigned char selector_pad[3];
    unsigned char data[192];
    int count;
  } frame;
  frame.selector=(unsigned char)param_1;
  frame.count=0;
  frame.input=param_2;
  FUN_00082c9c(1,0xffff,0x5a329,&frame.input);
  if(frame.count==0){ puVar1=0; iVar2=0; }
  else { iVar2=frame.count<<2; puVar1=frame.data; }
  iVar2=FUN_00053050(param_1,param_2,puVar1,iVar2);
  if(iVar2!=0){
    struct { unsigned level, message; int error; } log = { 3, 0x000f4db4, iVar2 };
    FUN_00082a42(0x88128,0x1840,&log);
  }
  return iVar2;
}
