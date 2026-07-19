.syntax unified
.cpu cortex-m33
.thumb

/*
 * Read-only QSPI exporter entered from ble_process_get_req's default arm.
 *
 * Entry state at the patched 0x0001a710 site:
 *   r2 = command
 *   r4 = BLE context (post_to_host callback at +0x0c)
 *   r5 = assembled request
 *   r6 = four-byte packet header (declared length at +2)
 *   sp + 0x110 = existing 244-byte GET work buffer
 *
 * Diagnostic request (command 0x2f):
 *   request[1:3]  declared length, must match packet[2:4]
 *   request[5:9]  little-endian QSPI byte offset
 *   request[9]    requested byte count, 1..180
 *
 * Response:
 *   [0] command, [1] 0xc9/0xca, [2] status, [3] byte count,
 *   [4:8] offset, [8:] data
 */

.equ ORIGINAL_DEFAULT_RESUME, 0x0001a714
.equ ORIGINAL_EPILOGUE,       0x0001a0d0
.equ FLASH_SETTINGS_READ,     0x000225b4
.equ LOG_LEVEL_ADDRESS,       0x2000230c
.equ QSPI_SIZE,               0x02000000
.equ MAX_CHUNK,               180

.equ STATUS_OK,               0
.equ STATUS_INVALID_REQUEST,  1
.equ STATUS_READ_FAILED,      2

.section .text.qspi_ble_exporter, "ax", %progbits
.balign 4
.global qspi_ble_exporter
.type qspi_ble_exporter, %function
.thumb_func
qspi_ble_exporter:
    cmp     r2, #0x2f
    beq     .Ldiagnostic

    /* Recreate the two instructions replaced by the four-byte hook. */
    ldr     r3, =LOG_LEVEL_ADDRESS
    ldr     r3, [r3]
    b.w     ORIGINAL_DEFAULT_RESUME

.Ldiagnostic:
    add.w   r8, sp, #0x110
    movs    r3, #0x2f
    strb    r3, [r8, #0]
    movs    r3, #0xca
    strb    r3, [r8, #1]
    movs    r3, #STATUS_INVALID_REQUEST
    strb    r3, [r8, #2]
    movs    r3, #0
    strb    r3, [r8, #3]
    str     r3, [r8, #4]

    /* Require the complete ten-byte diagnostic request envelope. */
    ldrh    r3, [r6, #2]
    cmp     r3, #10
    blo     .Lsend_header
    ldrh    r0, [r5, #1]
    cmp     r0, r3
    bne     .Lsend_header

    ldr     r6, [r5, #5]
    ldrb    r7, [r5, #9]
    str     r6, [r8, #4]
    cmp     r7, #1
    blo     .Lsend_header
    cmp     r7, #MAX_CHUNK
    bhi     .Lsend_header

    /* Overflow-safe bounds check: offset < 32 MiB and len <= size-offset. */
    ldr     r3, =QSPI_SIZE
    cmp     r6, r3
    bhs     .Lsend_header
    subs    r3, r3, r6
    cmp     r7, r3
    bhi     .Lsend_header

    mov     r0, r6
    add.w   r1, r8, #8
    mov     r2, r7
    bl      FLASH_SETTINGS_READ
    cbnz    r0, .Lread_failed

    movs    r3, #0xc9
    strb    r3, [r8, #1]
    movs    r3, #STATUS_OK
    strb    r3, [r8, #2]
    strb    r7, [r8, #3]
    adds    r1, r7, #8
    b       .Lpost

.Lread_failed:
    movs    r3, #STATUS_READ_FAILED
    strb    r3, [r8, #2]

.Lsend_header:
    movs    r1, #8

.Lpost:
    ldr     r3, [r4, #0x0c]
    mov     r0, r8
    blx     r3
    b.w     ORIGINAL_EPILOGUE

.size qspi_ble_exporter, . - qspi_ble_exporter
.ltorg
