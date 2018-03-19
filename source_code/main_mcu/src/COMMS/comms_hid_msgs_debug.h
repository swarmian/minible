/*!  \file     comms_hid_msgs_debug.h
*    \brief    HID debug communications
*    Created:  06/03/2018
*    Author:   Mathieu Stephan
*/


#ifndef COMMS_HID_MSGS_DEBUG_H_
#define COMMS_HID_MSGS_DEBUG_H_

#include "comms_hid_msgs.h"

/* Defines */
#define HID_MESSAGE_START_CMD_ID_DBG    0x8000
// Command IDs
#define HID_CMD_ID_DBG_MSG              0x8000
#define HID_CMD_ID_OPEN_DISP_BUFFER     0x8001
#define HID_CMD_ID_SEND_TO_DISP_BUFFER  0x8002
#define HID_CMD_ID_CLOSE_DISP_BUFFER    0x8003

/* Prototypes */
int16_t comms_hid_msgs_parse_debug(hid_message_t* rcv_msg, uint16_t supposed_payload_length);


#endif /* COMMS_HID_MSGS_DEBUG_H_ */