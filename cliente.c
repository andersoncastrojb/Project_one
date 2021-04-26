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
    

    /*
    - PF_INET --> uso de la familia de protocolos TCP/IP
    - SOCK_STREAM uso del protocolo TCP o SOCK_DGRAM uso del protocolo UDP
    - 0 --> para utilizar protoclo UDP o TCP al final en el receptor, para TCP --> IPPROTO_TCP, para UDP --> IPPROTO_UDP  
    */
    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    /* - sin_family --> familia de protocolos a usar AF_INET --> TCP/IP
       - sin_addr.s_addr --> direccion IP (unsigned long)
       - sin_port --> puerto de conexion
       - inet_addr() --> IPv4 a valor numerico (unsigned long)
       - htons() --> bytes ordenados de host a bytes ordenados de red  
    */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(12000);

    conection = connect(socket_id, (struct sockaddr*) &server, sizeof(server));
    if(conection < 0){
        printf("Error al realizar la conexión\r\n");
        return(-1);
    }


    printf("Conexión realizada con éxito\r\n");
    //send(socket_id, msg, sizeof(msg), 0);
    close(socket_id);
    return(0);
}
