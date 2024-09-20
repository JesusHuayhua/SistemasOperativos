#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/prime_server_socket"
#define BUFFER_SIZE 1024

int main(){
    int client_socket;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    // Creamos el socket
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error al crear el socket");
        exit(1);
    }
    // Configuramos la conexion
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al conectar con el servidor");
        close(client_socket);
        exit(1);
    }

    puts("Ingrese un numero: ");
    fgets(buffer,sizeof(buffer),stdin);

    if (write(client_socket, buffer, sizeof(buffer)) < 0 ) {
        perror("Error al enviar al servidor");
        close(client_socket);
        exit(1);
    }

    int bytes_read = read(client_socket,buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Respuesta del servidor: %s", buffer);
    }
    close(client_socket);
    return 0;
}
