// inet_prime_client.c
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Cambia esta IP si te conectas desde otra máquina
#define PORT 8080              // Puerto del servidor
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Crear un socket TCP en el dominio AF_INET
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Configurar la estructura de la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    //server_addr.sin_addr.s_addr = htonl(9734);
    // Convertir la IP del servidor a formato binario y configurarla en server_addr
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Error en la dirección del servidor");
        close(client_socket);
        exit(1);
    }

    // Conectar al servidor
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar con el servidor");
        close(client_socket);
        exit(1);
    }

    // Pedir al usuario que ingrese un número
    printf("Ingrese un número: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Enviar el número al servidor
    if (write(client_socket, buffer, strlen(buffer)) < 0) {
        perror("Error al enviar al servidor");
        close(client_socket);
        exit(1);
    }

    // Leer la respuesta del servidor
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Respuesta del servidor: %s", buffer);
    } else {
        perror("Error al leer la respuesta del servidor");
    }

    // Cerrar la conexión
    close(client_socket);
    return 0;
}
