/* Reconstructed prepare_quick_note_mode @ 0x7cdb6  (parity: 300/300 trials, PROVEN) */

extern int check_battery_critical(void);
extern void update_persist_task_status_to_idle(void);
extern void memset_bytes(void);
extern void send_event_status(void);

void prepare_quick_note_mode(unsigned char *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1 = check_battery_critical();
    if ((iVar1 != 0) && ((param_1[0xd5]==6) || (param_1[0xd5]==4))) {
        if (param_2 != 0) {
            send_event_status();
        }
        update_persist_task_status_to_idle();
        memset_bytes();
        return;
    }
    return;
}

