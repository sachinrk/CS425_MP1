#include "message_decode.h"
/*********************************************************
** This is the message decode function. 
** It converts a stream of bytes into payloads that 
** can be handled by the application Layer.
** Arguments:
** socket : socket on which the message has to be received
** packet : Packet returned to the calling function for
**          processing. 
***********************************************************/

int message_decode(int socket, payloadBuf **packet) {
    uint16_t length = 0;
    char *ptr = (char *)(&length);
    int size = sizeof(length);
    int bytesRead = 0;
    int rc;
    while (size > 0) {
        rc = read(socket, ptr, size);
        if (rc <= 0) {
        DEBUG(("Read failed in message decode. Socket may have been closed."));
        return rc;
        }
        bytesRead = rc;
        size -= bytesRead;
        ptr += bytesRead;    
    }
    length = ntohs(length);                               // Get the length of the packet
    size = length - sizeof(length);
    *packet = (payloadBuf *)malloc(length);
    (*packet)->length = length;
    ptr = (char*)((char*)(*packet) + sizeof(length));
    
    while (size > 0) {
        rc = read(socket, ptr, size);
        if (rc < 0) {
          DEBUG(("Read failed in message decode. Socket may have been closed."));
          return rc;
        }
        bytesRead = rc;
        size -= bytesRead;
        ptr += bytesRead;
    }
    (*packet)->type = ntohs((*packet)->type);
    DEBUG(("\nPacket type = %d\n", (*packet)->type));
    int i;
    for (i=0; i<length; i++ ) {
    DEBUG(("%d,",(*((char*)(*packet) +i))));
    }
    return RC_SUCCESS;
}
 
