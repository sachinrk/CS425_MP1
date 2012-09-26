#include<stdio.h>
#include"message_type.h"
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define MAX_BUFFER_SIZE 1000                       //Maximum application payload we support as of now is 1000 bytes. 
#define MAX_PAYLOAD_SIZE 1024

/************************************************************
** This is the message sending function. 
** It populates the relevant fields of the payload and sends.
** it over the socket.
** Arguments:
** socket  : socket on which the message has to be received
** msgType : Type of message
** payload : Payload from application layer
** length  : Length of application payload
**************************************************************/

int sendPayload(int socket, messageType msgType, char* payload, uint16_t length) {

    payloadBuf *buf;                                //Maximum payload we support as of now is 1000 bytes. 
    int bytesSent = 0;
    int rc = 0;
    int type = msgType;
    if (length > MAX_BUFFER_SIZE) {
        DEBUG(("\nWarning :: Payload lentgth > 1024 bytes. Truncating to 1000 bytes\n")); //Anything above 1000 bytes will be truncated.
        length = MAX_BUFFER_SIZE;
    } 
    buf = malloc(sizeof(payloadBuf) + length);
    if (buf == NULL) {
        return RC_FAILURE;
    }
    buf->type =  htons(type);
    buf->length = htons(length + sizeof(payloadBuf));
    memcpy(buf->payload, payload, length);
    DEBUG(("\n Printing below\n"));
    puts(payload);
    puts(buf->payload);
    
    int i;
    for(i=0;i<length;i++) {
      DEBUG(("%d,",*((char*)(buf + i))));
    }
    while (bytesSent < sizeof(payloadBuf) + length) {
        rc = write(socket, (buf+bytesSent), (sizeof(payloadBuf) + length) - bytesSent);
        if (rc < 0) {
            DEBUG(("Socket connection closed while trying to write"));
            return RC_SOCKET_WRITE_FAILURE;
        }
        else {
            bytesSent += rc;
        }
    }
    DEBUG(("\nFreeing memory here\n"));
    free(buf);
    return RC_SUCCESS;    
}
