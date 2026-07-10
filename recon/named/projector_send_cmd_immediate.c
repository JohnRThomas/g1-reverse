/* named: projector_send_cmd_immediate */
/* Reconstructed projector_send_cmd_immediate @ 0x7d77c  (parity: 300/300 trials, PROVEN) */

extern int get_projector_controller(void);
extern void projector_bus_lock(unsigned int a, unsigned int b);
extern void projector_bus_unlock(void);

void projector_send_cmd_immediate(unsigned char param_1)
{
    int iVar1;
    unsigned char local_11[5];
    unsigned char local_c[4];

    local_c[0] = 0;
    local_11[0] = param_1;
    iVar1 = get_projector_controller();
    projector_bus_lock(0xffffffff, 0xffffffff);
    (*(void (**)(int, void *, int, void *, int))(*(volatile int *)(iVar1 + 0x374) + 8))(
        *(volatile int *)(iVar1 + 0x374), local_11, 1, local_c, 1);
    projector_bus_unlock();
}

