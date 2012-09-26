#ifndef __MESSAGE_DECODE__
#define __MESSAGE_DECODE__

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include "message_type.h"
#include "debug.h"

#define MAX_BUFFER_SIZE 1000
#define MAX_PAYLOAD_SIZE 1000

int message_decode(int socket, payloadBuf **packet);

#endif //__MESSAGE_DECODE__
