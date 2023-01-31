#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>

void error(char *msg) {
    write(2, msg, strlen(msg));
    exit(1);
}

void fatalCheck(int ret) {
    if (ret < 0)
        error("Fatal error\n");
}

int getServerSocket(int port) {
    int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	fatalCheck(sockfd);
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 
  
	// Binding newly created socket to given IP and verification 
	fatalCheck(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)));
	fatalCheck(listen(sockfd, 10) != 0);
    return sockfd;
}

typedef struct {
    int fd;
    int id;
    int isActive;
    void *next;  
} Client;

int last_id = 0;
Client *clients = NULL;

int getId(int fd) {
    for (Client * client = clients; client != NULL; client = client->next) {
        if (client->fd == fd)
            return client->id;
    }
    return -1;
}

Client *push_clinet(int fd) {
    Client *new = malloc(sizeof(Client));
    new->id = last_id++;
    new->fd = fd;
    new->isActive = 1;
    new->next = clients;
    clients = new;
    return new;
}

void acceptNewClient(int servSock, fd_set *current_sockets, fd_set *write_ready) {
    char message[10000] = {0};
    int clientFD = accept(servSock, 0, 0);
    fatalCheck(clientFD);
    int size = sprintf(message, "server: client %d just arrived\n", last_id);
    for (Client *client = clients; client != NULL; client = client->next) {
        if (!client->isActive || !FD_ISSET(client->fd, write_ready)) {
            continue;
        }
        write(client->fd, message, size);
    }
    push_clinet(clientFD);
    FD_SET(clientFD, current_sockets);
}

void servClient(Client *client, fd_set *current_socks, fd_set *write_ready) {
    char buff[10001] = {0};
    char message[10000] = {0};
    int fd=client->fd;
    int ret = read(client->fd, buff, 10000);
    fatalCheck(ret);
    if (ret == 0) {
        int size = sprintf(message, "server: client %d just left\n", getId(fd));
        for (Client *client = clients; client != NULL; client = client->next) {
            if (!client->isActive || !FD_ISSET(client->fd, write_ready) || fd == client->fd) {
                continue;
            }
            write(client->fd, message, size);
        } 
        FD_CLR(client->fd, current_socks);
        client->fd = -1;
        client->isActive = 0;
        return ;
    }
    int of = 0;
    for (int i = 0; i < ret; i++) {
        if (i == 0 || buff[i - 1] == '\n') {
            of += sprintf(message + of, "client %d: ", client->id);
        }
        of += sprintf(message + of, "%c", buff[i]);
    }
    for (Client *client = clients; client != NULL; client = client->next) {
        if (!client->isActive || !FD_ISSET(client->fd, write_ready) || fd == client->fd) {
            continue;
        }
        write(client->fd, message, strlen(message));
    } 
}

int main(int ac, char **av) {
    if (ac != 2) {
        error("Wrong number of arguments\n");
    }
    int servSock = getServerSocket(atoi(av[1]));
    fd_set current_socks, read_ready, write_ready;
    bzero(&current_socks, sizeof(current_socks));
    FD_SET(servSock, &current_socks);
    while (1337) {
        read_ready = write_ready = current_socks;
        int ret = select(FD_SETSIZE, &read_ready, &write_ready, NULL, NULL);
        fatalCheck(ret);
        if (ret == 0)
            continue;
        if (FD_ISSET(servSock, &read_ready)) {
            acceptNewClient(servSock, &current_socks, &write_ready);
        }
        for (Client *client = clients; client != NULL ;client = client->next) {
            if (!FD_ISSET(client->fd, &read_ready))
                continue;
            servClient(client, &current_socks, &write_ready);
        }
    }
}
