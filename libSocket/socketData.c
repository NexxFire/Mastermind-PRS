#include "socketData.h"
#include <stdarg.h>



/**
 *	\fn			void envoyer(socket_t *sockEch, generic quoi, pFct serial, ...)
 *	\brief		Envoi d'une requête/réponse sur une socket
 *	\param 		sockEch : socket d'échange à utiliser pour l'envoi
 *	\param 		quoi : requête/réponse à serialiser avant l'envoi
 *	\param 		serial : pointeur sur la fonction de serialisation d'une requête/réponse
 *	\note		si le paramètre serial vaut NULL alors quoi est une chaîne de caractères
 *	\note		Si le mode est DGRAM, l'appel nécessite en plus l'adresse IP et le port.
 *	\result		paramètre sockEch modifié pour le mode DGRAM
 */
void envoyer(socket_t *sockEch, generic quoi, pFct serial, ...) {
    char buffer[MAX_BUFFER];
    va_list ap;
    va_start(ap, serial);
    if (sockEch->mode == SOCK_DGRAM) {
        char *adrIP = va_arg(ap, char *);
        short port = va_arg(ap, int);
        _adr2struct(&sockEch->addrDst, adrIP, port);
    }
    va_end(ap);
    if (serial == NULL) {
        CHECK(sendto(sockEch->fd, quoi, strlen((char *)quoi)+1, 0, (struct sockaddr *)&sockEch->addrDst, sizeof(sockEch->addrDst)), "Can't send");
    } else {
        serial(quoi, buffer);
        CHECK(sendto(sockEch->fd, buffer, strlen(buffer)+1, 0, (struct sockaddr *)&sockEch->addrDst, sizeof(sockEch->addrDst)), "Can't send");
    }
}
/**
 *	\fn			void recevoir(socket_t *sockEch, generic quoi, pFct deSerial)
 *	\brief		Réception d'une requête/réponse sur une socket
 *	\param 		sockEch : socket d'échange à utiliser pour la réception
 *	\param 		quoi : requête/réponse reçue après dé-serialisation du buffer de réception
 *	\param 		deSerial : pointeur sur la fonction de dé-serialisation d'une requête/réponse
 *	\note		si le paramètre deSerial vaut NULL alors quoi est une chaîne de caractères
 *	\result		paramètre quoi modifié avec le requête/réponse reçue
 *				paramètre sockEch modifié pour le mode DGRAM
 */
void recevoir(socket_t *sockEch, generic quoi, pFct deSerial) {
    char buffer[MAX_BUFFER];
    socklen_t cltLen;
    cltLen = sizeof(sockEch->addrDst);
    CHECK(recvfrom(sockEch->fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sockEch->addrDst, &cltLen), "Can't receive");
    if (deSerial == NULL) {
        strcpy(quoi, buffer);
    } else {
        deSerial(buffer, quoi);
    }

}