#include "utils.h"


/**
 * \brief Get user input from stdin
 * \param buffer The buffer where the input will be stored
 * \param size The size of the buffer
 * \details This function will get the user input from stdin and store it in the buffer. If the input is too long, the buffer will be filled and the rest of the input will be discarded.
*/
void getUserInput(char *buffer, size_t size) {
    fgets(buffer, size, stdin);
    if (strlen(buffer) == size - 1 && buffer[size - 2] != '\n') {
        clearBuffer();
    }
    strtok(buffer, "\n");
}

/**
 * \brief Clear the input buffer
 * \details This function will clear the input buffer by reading all the characters until the end of the line or the end of the file.
*/
void clearBuffer () {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/**
 * \brief Send data to the server and check the response code
 * \param socket The socket to send the data to
 * \param data The data to send
 * \param expectedCode The expected response code from the server
 * \details This function will send the data to the server using the given socket. It will then receive the response code from the server and check if it matches the expected code. If the response code does not match the expected code, an error message will be displayed.
*/
void sendData(int msgid, char *data, int expectedCode) {
    mbuf_t buffer;
    strcpy(buffer.mtext, data);
    buffer.mtype = 1;
    int receivedCode;
    CHECK(msgsnd(msgid, &buffer, sizeof(buffer), 0), "Error: could not send validation code to server.");
    CHECK(msgrcv(msgid, &buffer, sizeof(buffer), 2, 0), "Error: could not receive data from server.");
    sscanf(buffer.mtext, "ok:%d", &receivedCode);
    CHECK((receivedCode == expectedCode) -1, "Error: code received from server is not the expected one. Bad client-server synchronization.");
}

/**
 * \brief Receive data from the server and send a validation code
 * \param socket The socket to receive the data from
 * \param data The buffer where the received data will be stored
 * \param validationCode The validation code to send to the server
 * \details This function will receive data from the server using the given socket and store it in the data buffer. It will then send the validation code to the server.
*/
void receiveData(int msgid, char *data, int validationCode) {
    mbuf_t buffer;
    CHECK(msgrcv(msgid, &buffer, sizeof(buffer), 1, 0), "Error: could not receive data from server.");
    strcpy(data, buffer.mtext);
    sprintf(buffer.mtext, "ok:%d", validationCode);
    buffer.mtype = 2;
    CHECK(msgsnd(msgid, &buffer, sizeof(buffer), 0), "Error: could not send validation code to server.");
}

int acceptClient(int msgid) {
    char buffer[10];
    int clientId;
    receiveData(msgid, buffer, 0);
    sscanf(buffer, "%d", &clientId);
    return msgget(ftok("client", clientId), 0666 | IPC_CREAT);
}

int connectToServer(key_t serverKey) {
    char buffer[10];
    int serverMsgid = msgget(serverKey, 0666 | IPC_CREAT);
    sprintf(buffer, "%d", getpid());
    sendData(serverMsgid, buffer, 0);
    return msgget(ftok("client", getpid()), 0666 | IPC_CREAT);
}