### struct ipc_ept_ctx  (G1-original)  cid=param_0059

purpose: IPC endpoint context shared across ipc_ept_op_a_locked_retry / ipc_send_len_prefixed_packet_locked_retry / pt_comm_transport_write (ipc instance pointer + endpoint id).

This object is accessed by these functions (read their fully-named source):
  - ipc_ept_op_a_locked_retry  (as param_1)  ->  recon/readable_sources/app/g1/ipc_ept_op_a_locked_retry.c
  - ipc_send_len_prefixed_packet_locked_retry  (as param_1)  ->  recon/readable_sources/app/g1/ipc_send_len_prefixed_packet_locked_retry.c
  - pt_comm_transport_write  (as param_2)  ->  recon/readable_sources/app/g1/pt_comm_transport_write.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ipc_ept_ctx {
    void *       ipc_instance_ptr;  /* +0x4  rw=r sz=4 */
    uint32_t     ept_id;  /* +0x8  rw=r sz=4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```