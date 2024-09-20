// inet_prime_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Función para verificar si un número es primo
int is_prime(int num) {
    if (num <= 1) return 0;  // No es primo
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;  // No es primo
    }
    return 1;  // Es primo
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int number;

    // Leer el número del cliente
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        perror("Error al leer del cliente");
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';  // Terminar la cadena

    // Convertir el número recibido a entero
    number = atoi(buffer);

    // Determinar si el número es primo y enviar la respuesta
    if (is_prime(number)) {
        write(client_socket, "yes\n", 4);
    } else {
        write(client_socket, "no\n", 3);
    }

    close(client_socket);  // Cerrar la conexión con el cliente
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Crear un socket TCP en el dominio AF_INET
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Configurar la estructura de la dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Escuchar en todas las interfaces de red
    server_addr.sin_port = htons(PORT);

    // Enlazar el socket al puerto especificado
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket");
        close(server_socket);
        exit(1);
    }

    // Escuchar conexiones entrantes
    if (listen(server_socket, 5) < 0) {
        perror("Error al escuchar en el socket");
        close(server_socket);
        exit(1);
    }

    printf("Servidor INET corriendo en el puerto %d y esperando clientes...\n", PORT);

    // Bucle principal para aceptar y manejar conexiones de clientes
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Error al aceptar la conexión");
            continue;
        }

        // Crear un proceso hijo para manejar el cliente
        if (fork() == 0) {
            close(server_socket);  // El hijo no necesita el socket del servidor
            handle_client(client_socket);
            exit(0);  // Terminar el proceso hijo
        }

        close(client_socket);  // El proceso padre cierra el socket del cliente
    }

    // Limpieza
    close(server_socket);
    return 0;
}
