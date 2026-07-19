/* readable reconstruction; identity: FUN_0005c80c @ 0x0005c80c
 * public-name: bt_gatt_store_ccc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_ccc_bt_settings_store               <= FUN_00053050 @ 0x00053050
 *   bt_gatt_store_ccc                        <= FUN_0005c80c @ 0x0005c80c
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   rodata_5a329                             @ 0x0005a329
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4db4                             @ 0x000f4db4
 */
/* Reconstructed FUN_0005c80c @ 0x5c80c  (parity: 300/300 trials, PROVEN) */

extern int gatt_ccc_bt_settings_store(unsigned,unsigned,void*,int);
extern int log_msg_create_3arg(unsigned,unsigned,void*);
extern int bt_gatt_foreach_attr_0(int,unsigned,unsigned,void*);
int bt_gatt_store_ccc(unsigned param_1, unsigned param_2){
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
  bt_gatt_foreach_attr_0(1,0xffff,0x5a329,&frame.input);
  if(frame.count==0){ puVar1=0; iVar2=0; }
  else { iVar2=frame.count<<2; puVar1=frame.data; }
  iVar2=gatt_ccc_bt_settings_store(param_1,param_2,puVar1,iVar2);
  if(iVar2!=0){
    struct { unsigned level, message; int error; } log = { 3, 0x000f4db4, iVar2 };
    log_msg_create_3arg(0x88128,0x1840,&log);
  }
  return iVar2;
}
