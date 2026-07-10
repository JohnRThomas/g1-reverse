/*
 * Even phone<->glasses BLE application protocol (G1).
 *
 * The wire protocol is shared across the Even.app ecosystem. The packet framing
 * and the 2-byte service-ID registry below are cross-referenced from the
 * community project evenRealities-openCFW (MIT-licensed, documents the G2), and
 * VERIFIED against this G1 image: the same service subsystems (Dashboard,
 * Notification, Teleprompter, Navigation, Onboarding, Translate, Auth) appear
 * as named handlers in the G1 firmware strings and reconstructed functions.
 *
 * NOTE: only the phone<->glasses protocol carries over. The G2 runs on Ambiq
 * Apollo510b + EM9305; this G1 target is the nRF5340 dual-core, and the L/R
 * (master/slave) synchronisation runs over Nordic ESB — that layer is G1-
 * specific and reconstructed directly from this binary, not from openCFW.
 *
 * Attribution: service/packet definitions adapted from
 *   https://github.com/kalanihelekunihi/evenRealities-openCFW  (MIT License)
 */
#ifndef G1_EVEN_PROTOCOL_H
#define G1_EVEN_PROTOCOL_H

#include <stdint.h>

/* ---- packet framing --------------------------------------------------------
 * [8-byte header][variable payload][2-byte CRC-16/CCITT little-endian]
 *   0    magic          0xAA
 *   1    type           0x21 phone->glasses, 0x12 glasses->phone
 *   2    sequence       0..255
 *   3    length         payload length + 2
 *   4    packet_total   fragments in message
 *   5    packet_serial  current fragment (1..N)
 *   6    service_hi
 *   7    service_lo
 * CRC-16/CCITT: poly 0x1021, init 0xFFFF, over payload only (skip 8-byte hdr).
 */
#define EVEN_MAGIC        0xAAu
#define EVEN_TYPE_PH2GL   0x21u
#define EVEN_TYPE_GL2PH   0x12u
#define EVEN_HDR_LEN      8u
#define EVEN_CRC16_POLY   0x1021u
#define EVEN_CRC16_INIT   0xFFFFu

struct even_pkt_hdr {
	uint8_t magic;
	uint8_t type;
	uint8_t sequence;
	uint8_t length;
	uint8_t packet_total;
	uint8_t packet_serial;
	uint8_t service_hi;
	uint8_t service_lo;
};

/* ---- 2-byte service IDs (hi<<8 | lo) --------------------------------------- */
#define SVC_DASHBOARD          0x0120u
#define SVC_GESTURE_STATUS     0x0101u
#define SVC_NOTIFICATION       0x0220u
#define SVC_NOTIFICATION_RESP  0x0200u
#define SVC_MENU               0x0320u
#define SVC_DISPLAY_WAKE       0x0420u
#define SVC_DISPLAY_WAKE_RESP  0x0400u
#define SVC_DEVINFO_RESP       0x0401u
#define SVC_TRANSLATE          0x0520u
#define SVC_TELEPROMPTER       0x0620u
#define SVC_TELEPROMPTER_ACK   0x0600u
#define SVC_TELEPROMPTER_PROG  0x0601u
#define SVC_EVENAI             0x0720u
#define SVC_EVENAI_RESP        0x0700u
#define SVC_EVENAI_STATUS      0x0701u
#define SVC_NAVIGATION         0x0820u
#define SVC_DEVICE_INFO        0x0900u
#define SVC_DEVICE_INFO_RESP   0x0901u
#define SVC_SESSION_INIT       0x0A20u
#define SVC_CONVERSATE         0x0B20u
#define SVC_CONVERSATE_ACK     0x0B00u
#define SVC_CONVERSATE_NOTIFY  0x0B01u
#define SVC_QUICKLIST_HEALTH   0x0C20u
#define SVC_CONFIGURATION      0x0D00u
#define SVC_DEVICE_CONFIG      0x0D20u
#define SVC_CONFIG_GESTURE     0x0D01u
#define SVC_DISPLAY_CONFIG     0x0E20u
#define SVC_LOGGER             0x0F20u
#define SVC_ONBOARDING         0x1020u
#define SVC_MODULE_CONFIGURE   0x2020u
#define SVC_SYSTEM_ALERT       0x2120u
#define SVC_SYSTEM_CLOSE       0x2220u
#define SVC_AUTH               0x8000u /* 0x80-xx family */
#define SVC_BOXDETECT_TRIGGER  0x8120u
#define SVC_RING_RELAY         0x9120u
#define SVC_FILE_XFER_CMD      0xC400u
#define SVC_FILE_XFER_DATA     0xC500u
#define SVC_EVENHUB            0xE020u
#define SVC_SYSTEM_MONITOR     0xFF20u

#endif /* G1_EVEN_PROTOCOL_H */
