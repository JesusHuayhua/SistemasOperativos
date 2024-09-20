#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

#define SOCKET_PATH "/tmp/prime_server_socket"
#define BUFFER_SIZE 1024

int es_primo(int num){
    if (num <= 0) return 0;
    for (int i = 2; i*i < num; i++) {
        if ( num % i == 0) return 0;
    }
    return  1;
}

void handle_client(int client_socket){
    char buffer[BUFFER_SIZE];
    int number;
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if(bytes_read < 0){
        perror("Error al leer del cliente");
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';
    number = atoi(buffer);
    es_primo(number) ? write(client_socket, "yes\n", 4) : write(client_socket, "no\n", 4);
    close(client_socket);
}

int main(){
    int server_socket , client_socket;
    struct sockaddr_un server_addr;
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    // Verificamos la creacion del socket
    if (server_socket < 0 ){
        perror("Error al crear el socket");
        exit(1);
    }

    unlink(SOCKET_PATH); // Elimina el socket en caso ya exista
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;// domino a utilizar
    strncpy(server_addr.sun_path, SOCKET_PATH,sizeof(server_addr.sun_path) - 1);

    if (bind(server_socket, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("Error al enlazar el scoket");
        close(server_socket); // cerramos la conexion
        exit(1);
    }

    if (listen(server_socket,5) < 0) {
        perror("Error al escuchar en el socket");
        close(server_socket);
        exit(1);
    }

    puts("Servidor UNIX corriendo y esperando clientes...\n");

    while(1){
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Error al aceptar la conexion");
            continue;
        }
        if(fork() == 0){
            close(server_socket); // El hijo no necesita el socket del servidor
            handle_client(client_socket);
            exit(0);
        }
        close(client_socket);
    }
    close(server_socket);
    unlink(SOCKET_PATH);
}
