#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080  // Puerto donde el servidor escuchará
#define BUFFER_SIZE 1024

// Función para manejar la conexión del cliente
void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];

    // Leer la solicitud del cliente (request)
    recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
    printf("Solicitud recibida:\n%s\n", buffer);

    // Respuesta HTTP mínima
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, World!";

    // Enviar la respuesta al cliente
    send(client_sock, response, strlen(response), 0);

    // Cerrar la conexión con el cliente
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Crear el socket del servidor
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Asignar el socket a la dirección y puerto especificado
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al hacer bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Poner el servidor en modo de escucha
    if (listen(server_sock, 10) == -1) {
        perror("Error al poner en escucha");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Servidor web escuchando en el puerto %d...\n", PORT);

    // Aceptar conexiones de los clientes y manejarlas
    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == -1) {
            perror("Error al aceptar la conexión");
            continue;
        }

        // Manejar la conexión con el cliente
        handle_client(client_sock);
    }

    // Cerrar el socket del servidor (no se alcanzará en este ejemplo)
    close(server_sock);
    return 0;
}
