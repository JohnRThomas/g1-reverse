/* readable reconstruction; identity: FUN_00051e9c @ 0x00051e9c
 * public-name: img_mgmt_state_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_add_cmd_err                          <= FUN_0005160c @ 0x0005160c
 *   img_mgmt_state_read                      <= FUN_00051c98 @ 0x00051c98
 *   img_mgmt_set_next_boot_slot              <= FUN_00051d8c @ 0x00051d8c
 *   img_mgmt_state_write                     <= FUN_00051e9c @ 0x00051e9c
 *   img_mgmt_take_lock                       <= FUN_00080a42 @ 0x00080a42
 *   img_mgmt_release_lock                    <= FUN_00080a44 @ 0x00080a44
 */
/* Reconstructed FUN_00051e9c @ 0x51e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int smp_add_cmd_err(int,int,uint32_t);
extern int img_mgmt_state_read(int);
extern int img_mgmt_set_next_boot_slot(int,int);
extern int FUN_00080872(int,void*,int,void*);
extern void img_mgmt_take_lock(void);
extern void img_mgmt_release_lock(void);
int img_mgmt_state_write(int param_1){
    uint8_t request[0x28];
    uint32_t result = 0;
    int iVar7=*(volatile int*)(param_1+8);
    int r4=*(volatile int*)(param_1+4);
    int iVar1=FUN_00080872(r4+4,request,2,&result);
    if(iVar1!=0) return 3;
    img_mgmt_take_lock();
    iVar1=smp_add_cmd_err(iVar7+4,1,0x18);
    img_mgmt_release_lock();
    if(iVar1!=0) return 0;
    return 7;
}
