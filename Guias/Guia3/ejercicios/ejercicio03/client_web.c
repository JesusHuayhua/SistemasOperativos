#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"  // Dirección IP del servidor (localhost)
#define SERVER_PORT 8080       // Puerto en el que escucha el servidor
#define BUFFER_SIZE 4096

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Crear el socket del cliente
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Dirección IP no válida o no soportada");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar al servidor");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    printf("Conectado al servidor en %s:%d\n", SERVER_IP, SERVER_PORT);

    // Solicitud HTTP GET mínima
    const char *http_request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";

    // Enviar la solicitud HTTP al servidor
    send(client_sock, http_request, strlen(http_request), 0);

    // Recibir la respuesta del servidor
    int bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Error al recibir datos");
    } else {
        buffer[bytes_received] = '\0';  // Añadir el terminador de cadena
        printf("Respuesta del servidor:\n%s\n", buffer);
    }

    // Cerrar el socket del cliente
    close(client_sock);
    return 0;
}
