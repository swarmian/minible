/*!  \file     comms_hid_msgs.h
*    \brief    HID communications
*    Created:  06/03/2018
*    Author:   Mathieu Stephan
*/ 


#ifndef COMMS_HID_MSGS_H_
#define COMMS_HID_MSGS_H_

/* Defines */
#define HID_CMD_ID_PING     0x0001

/* Typedefs */
typedef struct
{
    uint16_t message_type;
    uint16_t payload_length;
    uint8_t payload[0];
} hid_message_t;

/* Prototypes */
int16_t comms_hid_msgs_parse(hid_message_t* rcv_msg, uint16_t supposed_payload_length, hid_message_t* possible_reply);


#endif /* COMMS_HID_MSGS_H_ */