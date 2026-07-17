/* readable reconstruction; identity: FUN_0102e284 @ 0x0102e284
 * public-name: z_impl_z_log_msg_static_create
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103aacd                           @ 0x0103aacd
 *   rodata_103c07c                           @ 0x0103c07c
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d676                           @ 0x0103d676
 *   rodata_103d6b5                           @ 0x0103d6b5
 */
/* net-core z_impl_z_log_msg_static_create @ 0x0102e284
 * Raw/address back-map: FUN_0102e284 / 0x0102e284.
 */
#include <stdint.h>
typedef struct { void *buf; uint32_t size; uint32_t off; } cbprintf_buf_desc_t;
extern int FUN_0102bfe4(void*,uint32_t,void*,cbprintf_buf_desc_t*,uint32_t,uint16_t*,uint32_t);
extern void *FUN_0102def4(uint32_t);
extern void FUN_0103a2f8(void*,const void*,uint32_t,const void*);
extern void assert_print(const char*,...);
extern void FUN_01039bb0(const char*,uint32_t);
void z_impl_z_log_msg_static_create(const void *source,uint32_t descriptor,void *package,const void *data){
 uint32_t original_package_len=(descriptor>>9)&0x7ffu, package_len=original_package_len, data_len=descriptor>>20; void *message;
 if(package_len){ uint16_t string_lengths[4]; cbprintf_buf_desc_t output={0,0,0}; int converted_len=FUN_0102bfe4(package,package_len,0,&output,10,string_lengths,4);
  if((uint32_t)converted_len>0x7ffu){ uint32_t warning_package[5]={0x01000004u,0x0103d676u,((uint32_t*)package)[1],0x7ffu,0x200u}; z_impl_z_log_msg_static_create((void*)0x0103c07c,0x2480,warning_package,0); return; }
  package_len=(uint32_t)converted_len&0x7ffu; message=FUN_0102def4((data_len+23u+(uint32_t)converted_len&~7u)>>2); descriptor=(descriptor&0xfff001ffu)|(package_len<<9);
  if(message){output.buf=(uint8_t*)message+16;output.size=(uint32_t)converted_len;output.off=0;if(FUN_0102bfe4(package,original_package_len,(void*)0x0103aacd,&output,10,string_lengths,4)<0){assert_print((void*)0x0103d2a7,(void*)0x0103d6b5,0x59);FUN_01039bb0((void*)0x0103d6b5,0x59);}}
 } else {message=FUN_0102def4((data_len+23u&~7u)>>2);package_len=0;}
 descriptor=(descriptor&0xfff001ffu)|(package_len<<9);FUN_0103a2f8(message,source,descriptor,data);}
