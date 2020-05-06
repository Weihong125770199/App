#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#ifndef IAP2_H
#define IAP2_H

#define MAX_PLAYLOAD_LEN   65525
#define MAX_READBUFF_SIZE    1024
#define PACKET_START   0xff55
#define MAX_CERTIFICATE_DATA 1280

#define CONTROL_BYTE_SYN 0x80
#define CONTROL_BYTE_ACK 0x40
#define CONTROL_BYTE_EAK 0x20
#define CONTROL_BYTE_RST 0x10
#define CONTROL_BYTE_SLP 0x08


typedef struct _st_apacket apacket;
typedef struct _st_amessage amessage;
typedef struct _st_playload playload;
typedef struct _st_control_session_parameters  parameter;
typedef struct _st_control_session_amessage ctrl_session_msg;

struct _st_amessage
{
        unsigned char startMSL;
        unsigned char startLSB;
        unsigned char lengthMSL;
        unsigned char lengthLSB;
        unsigned char ctrl;
        unsigned char sequenceNum;
        unsigned char ackNum;
    unsigned char sessionID;
        unsigned char headerCheckSum;
};
struct _st_playload
{
        unsigned char playload[MAX_PLAYLOAD_LEN];
};

struct _st_apacket
{
        amessage msg;
        playload    data;
};

struct _st_control_session_parameters
{
        unsigned char lengthMSL;
        unsigned char lengthLSB;
        unsigned char idMSB;
        unsigned char idLSB;
        unsigned char data[MAX_CERTIFICATE_DATA];
        //parameter *next;
};
struct _st_control_session_amessage
{
        unsigned char startMSL;
        unsigned char startLSB;
        unsigned char lengthMSL;
        unsigned char lengthLSB;
        unsigned char idMSB;
        unsigned char idLSB;
        parameter  ctrl_session_param;
};

void printf_package(u_int8_t *buffer, u_int16_t length);

#endif
