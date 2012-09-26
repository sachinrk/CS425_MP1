#ifndef __MESSAGE_TYPES__
#define __MESSAGE_TYPES__

#include <stdint.h>
#include "debug.h"
#define FILE_PATH_LENGTH 200

typedef enum {
   MSG_HEARTBEAT = 0,
   MSG_FILE_TRANSFER,
   MSG_EXECUTE_SCRIPT
}messageType;

typedef struct 
{
   uint16_t length;
   uint16_t type;
   char payload[0]; 
}payloadBuf;

typedef struct 
{
    uint16_t heartbeatSeqNo;
}heartbeatPayload;

typedef struct
{   
    uint16_t transferId;
    uint16_t statusFlag;
    #define FTP_REQUEST  0x01
    #define FTP_RESPONSE 0x02
    #define FTP_START    0x04
    #define FTP_STOP     0x08
    #define FTP_SUCCESS  0x10
    char fileName[FILE_PATH_LENGTH];
    char filePayload[0];
}fileTransferPayload;

typedef struct
{
    char scriptName[FILE_PATH_LENGTH];
}executeScriptPayload;

typedef enum {
    RC_FAILURE = 0,
    RC_SUCCESS,
    RC_FILE_NOT_FOUND,
    RC_SOCKET_WRITE_FAILURE,
    RC_SOCKET_READ_FAILURE
}returnCode;
#endif
