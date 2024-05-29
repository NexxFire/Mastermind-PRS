#include "socketSession.h"
#include "socketData.h"


void getUserInput(char *buffer, size_t size);
void clearBuffer ();

void sendData(socket_t *socket, char *data, int expectedCode);
void receiveData(socket_t *socket, char *data, int validationCode);