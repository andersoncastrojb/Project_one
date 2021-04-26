//Bibliotecas basicas
#include <stdio.h> // Biblioteca estandar Entradas/Salidas
#include <stdlib.h>

//Bilbiotecas para sockets
#include <sys/socket.h>
#include <netinet/in.h>

#define restar 2208988800ull

//Una libreria mas
#include <time.h>

int main(void)
{
    int i = 0;
    unsigned long t_seconds = 0;
    int conection = 0; //Verifica conexion
    int socket_id = 0; //Socket
    int port = 123;    //Puerto para el protoclo NTP

    // Estructura para el protocolo NTP 48 bytes en total
    typedef struct
    {
        char li_vn_mode; // Eight bits. li, vn, and mode.
                            // li.   Two bits.   Leap indicator.
                            // vn.   Three bits. Version number of the protocol.
                            // mode. Three bits. Client will pick mode 3 for client.

        char stratum;   // Eight bits. Stratum level of the local clock.
        char poll;      // Eight bits. Maximum interval between successive messages.
        char precision; // Eight bits. Precision of the local clock.

        int rootDelay;      // 31 bits. Total round trip delay time.
        int rootDispersion; // 31 bits. Max error aloud from primary clock source.
        int refId;          // 31 bits. Reference clock identifier.

        int refTm_s; // 31 bits. Reference time-stamp seconds.
        int refTm_f; // 31 bits. Reference time-stamp fraction of a second.

        int origTm_s; // 31 bits. Originate time-stamp seconds.
        int origTm_f; // 31 bits. Originate time-stamp fraction of a second.

        int rxTm_s; // 31 bits. Received time-stamp seconds.
        int rxTm_f; // 31 bits. Received time-stamp fraction of a second.

        int txTm_s; // 31 bits and the most important field the client cares about Transmit time-stamp seconds.
        int txTm_f; // 31 bits. Transmit time-stamp fraction of a second.

    } ntp_protocol; // Total:  bits or 48 bytes.

    //Crea objeto ntp_protocol que es un paquete que contiene formato de cabecera del protocolo NTP
    ntp_protocol paquete = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //asignar ld = 0, vn = 4 , mode = 3 --> cliente
    paquete.li_vn_mode = (char)0b00100011;

    //printf("--> %d\n", paquete.li_vn_mode);

    //define socket UDP
    socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    //Error al crear socket
    if (socket_id < 0)
    {
        printf("Error al crear socket\n\r");
        return -1;
    }

    // Datos del servidor
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    // Server NTP colombiano
    //server.sin_addr.s_addr = inet_addr("200.118.21.37");
    server.sin_addr.s_addr = inet_addr("173.0.48.220");
    server.sin_port = htons(port);

    //Conectar cliente/server ntp
    conection = connect(socket_id, (struct sockaddr *)&server, sizeof(server));

    //Error al realizar conexion
    if (conection < 0)
    {
        printf("Error al realizar la conexión\r\n");
        return (-1);
    }

    printf("Conexión realizada con éxito\r\n");

    //Envia peticion al servidor ntp
    i = send(socket_id, (char *)&paquete, sizeof(ntp_protocol), 0);

    //Error en peticion
    if (i < 0)
    {
        printf("Error en peticion\n\r");
        return -1;
    }

    printf("Peticion enviada\r\n");

    //Recibir respuesta del servidor ntp
    i = recv(socket_id, (char *)&paquete, sizeof(ntp_protocol), 0);

    //Error al recibir la respuesta
    if (i < 0)
    {
        printf("Error al recibir la respuesta del servidor\n\r");
        return -1;
    }

    printf("Respuesta recibida\r\n");

    t_seconds = (unsigned long) ntohl( paquete.txTm_s ); // Time-stamp seconds.

    time_t tiempo = (time_t) (t_seconds - restar);

    printf("Segundos = %lu\n",t_seconds - restar);

    printf( "Time: %s", ctime( ( const time_t* ) &tiempo ) );


    close(socket_id);

    return (0);
}
