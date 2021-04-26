//Bibliotecas basicas
#include <stdio.h>// Biblioteca estandar Entradas/Salidas
#include <stdlib.h>

//Bilbiotecas para sockets 
#include <sys/socket.h>
#include <netinet/in.h>

int main(void){

    int conection = 0; //Verifica conexion 
    int socket_id = 0; //Socket
    char msg[] = "GET HTTP/1.1\r\n";//Mensaje / Peticion
    char buff[2000];
    
    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    // Pagina de ayudantias de la universidad del magdalena 
    // ayudantias.unimagdalena.edu.co
    server.sin_addr.s_addr = inet_addr("45.65.200.25");
    // Pueto 80 para protocolo HTTP
    server.sin_port = htons(80);

    conection = connect(socket_id, (struct sockaddr*) &server, sizeof(server));
    if(conection < 0){
        printf("Error al realizar la conexión\r\n");
        return(-1);
    }


    printf("Conexión realizada con éxito\r\n");

    // Enviar peticion GET
    send(socket_id, msg, sizeof(msg), 0);
    // recivir respuesta HTML
    recv(socket_id, buff, sizeof(buff), 0);
    
    printf("\n\r\n\r");
    printf("El HTML recivido es:\n\r\n\r%s\r\n",buff);
    printf("\n\r\n\r");

    close(socket_id);
    return(0);
}
