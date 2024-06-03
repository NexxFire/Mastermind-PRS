#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "serverData.h"
#include "clientData.h"


#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}
#define PAUSE(msg)	printf("%s [Appuyez sur entrée pour continuer]", msg); getchar();


#define MSG_SIZE 10

struct mbuf {
    long mtype;
    char mtext[MSG_SIZE];
}; typedef struct mbuf mbuf_t;

void getUserInput(char *buffer, size_t size);
void clearBuffer ();

void sendData(int msgid, char *data, int expectedCode);
void receiveData(int msgid, char *data, int validationCode);
int acceptClient(int msgid);
int connectToServer(key_t serverKey);