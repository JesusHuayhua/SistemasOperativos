#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/fibonacci_unix.sock"
#define BUFFER_SIZE 1024

// Función para calcular los números de Fibonacci
void fibonacci(int n, int *result) {
    result[0] = 0;
    result[1] = 1;
    for (int i = 2; i < n; i++) {
        result[i] = result[i - 1] + result[i - 2];
    }
}

// Función para manejar la conexión con cada cliente
void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    int n;

    // Recibir el valor de n
    recv(client_sock, buffer, BUFFER_SIZE, 0);
    n = atoi(buffer);

    // Verificar que n sea válido
    if (n <= 0) {
        snprintf(buffer, BUFFER_SIZE, "Invalid input");
        send(client_sock, buffer, strlen(buffer), 0);
        close(client_sock);
        exit(1);
    }

    // Calcular la secuencia de Fibonacci
    int *result = malloc(n * sizeof(int));
    fibonacci(n, result);

    // Enviar los resultados al cliente
    memset(buffer, 0, BUFFER_SIZE);
    for (int i = 0; i < n; i++) {
        char num_str[20];
        snprintf(num_str, 20, "%d ", result[i]);
        strcat(buffer, num_str);
    }

    send(client_sock, buffer, strlen(buffer), 0);
    free(result);
    close(client_sock);
    exit(0);
}

// Configuración del servidor UNIX
int main() {
    int server_sock, client_sock;
    struct sockaddr_un server_addr;

    // Crear un socket UNIX
    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Eliminar el archivo de socket si ya existe
    unlink(SOCKET_PATH);

    // Configurar la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Asociar el socket con la dirección
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones
    if (listen(server_sock, 5) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Servidor UNIX escuchando en %s\n", SOCKET_PATH);

    // Aceptar múltiples conexiones de clientes
    while (1) {
        client_sock = accept(server_sock, NULL, NULL);
        if (client_sock == -1) {
            perror("Accept failed");
            continue;
        }

        // Crear un proceso hijo para manejar al cliente
        if (fork() == 0) {
            close(server_sock);
            handle_client(client_sock);
        }
        close(client_sock);
    }

    close(server_sock);
    unlink(SOCKET_PATH);
    return 0;
}
