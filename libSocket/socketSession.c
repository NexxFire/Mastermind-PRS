#include "socketSession.h"



/**
 *	\fn			void adr2struct (struct sockaddr_in *addr, char *adrIP, short port)
 *	\brief		Transformer une adresse au format humain en structure SocketBSD
 *	\param		addr : structure d'adressage BSD d'une socket INET
 *	\param		adrIP : adresse IP de la socket créée
 *	\param		port : port de la socket créée
 *	\note		Le domaine dépend du mode choisi (TCP/UDP)
 *	\result		paramètre *adr modifié
 */
void _adr2struct (struct sockaddr_in *addr, char *adrIP, short port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = inet_addr(adrIP);
    memset(addr->sin_zero, 0, 8);
}

/**
 *	\fn			socket_t creerSocket (int mode)
 *	\brief		Création d'une socket de type DGRAM/STREAM
 *	\param		mode : mode connecté (STREAM) ou non (DGRAM)
 *	\result		socket créée selon le mode choisi
 */
socket_t creerSocket (int mode) {
    CHECK((mode == SOCK_DGRAM || mode == SOCK_STREAM) - 1, "Mode de socket inconnu");
    socket_t sock;
    CHECK(sock.fd = socket(AF_INET, mode, 0), "Erreur lors de la création de la socket");
    sock.mode = mode;
    int true = 1;
    setsockopt(sock.fd,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int));
    return sock;
}

/**
 *	\fn			socket_t creerSocketAdr (int mode, char *adrIP, short port)
 *	\brief		Création d'une socket de type DGRAM/STREAM
 *	\param		mode : adresse IP de la socket créée
 *	\param		adrIP : adresse IP de la socket créée
 *	\param		port : port de la socket créée
 *	\result		socket créée dans le domaine choisi avec l'adressage fourni
 */
socket_t creerSocketAdr (int mode, char *adrIP, short port) {
    socket_t sock = creerSocket(mode);
    _adr2struct(&sock.addrLoc, adrIP, port);
    CHECK(bind(sock.fd, (struct sockaddr *)&(sock.addrLoc), sizeof(sock.addrLoc)), "Erreur lors de l'association de l'adressage à la socket"); 
    return sock;
}

/**
 *	\fn			creerSocketEcoute (char *adrIP, short port)
 *	\brief		Création d'une socket d'écoute avec l'adressage fourni en paramètre
 *	\param		adrIP : adresse IP du serveur à mettre en écoute
 *	\param		port : port TCP du serveur à mettre en écoute
 *	\result		socket créée avec l'adressage fourni en paramètre et dans un état d'écoute
 *	\note		Le domaine est nécessairement STREAM
 */
socket_t creerSocketEcoute (char *adrIP, short port) {
    socket_t sockEcoute = creerSocketAdr(SOCK_STREAM, adrIP, port);
    
    CHECK(listen(sockEcoute.fd, 5), "Erreur lors de la mise en écoute de la socket");
    return sockEcoute;
}

/**
 *	\fn			socket_t accepterClt (const socket_t sockEcoute)
 *	\brief		Acceptation d'une demande de connexion d'un client
 *	\param		sockEcoute : socket d'écoute pour réception de la demande
 *	\result		socket (dialogue) connectée par le serveur avec un client
 */
socket_t accepterClt (const socket_t sockEcoute) {
    CHECK((sockEcoute.mode == SOCK_STREAM) -1, "Mode de socket inadapté pour l'acceptation de client");
    // create socket for dialogue with the information of sock listenning socket
    socket_t sockDialog = creerSocket(SOCK_STREAM);
    socklen_t cltLen = sizeof(sockDialog.addrDst);
    sockDialog.addrLoc = sockEcoute.addrLoc;
    CHECK(sockDialog.fd = accept(sockEcoute.fd, (struct sockaddr *)&sockDialog.addrDst, &cltLen), "Erreur lors de l'acceptation du client");
    return sockDialog;
}

/**
 *	\fn			socket_t connecterClt2Srv (char *adrIP, short port)
 *	\brief		Crétaion d'une socket d'appel et connexion au seveur dont
 *				l'adressage est fourni en paramètre
 *	\param		adrIP : adresse IP du serveur à connecter
 *	\param		port : port TCP du serveur à connecter
 *	\result		socket connectée au serveur fourni en paramètre
 */
socket_t connecterClt2Srv (char *adrIP, short port) {
    socket_t sockClt = creerSocket(SOCK_STREAM);
    _adr2struct(&sockClt.addrDst, adrIP, port);
    CHECK(connect(sockClt.fd, (struct sockaddr *)&sockClt.addrDst, sizeof(sockClt.addrDst)), "Erreur lors de la connexion au serveur");
    return sockClt;
}