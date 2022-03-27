#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
    int listenfd = -1; //
    int new_socket = -1; 
    struct sockaddr_in server_addr, client_addr;
    char valsend[1024];
    char valread[1024];
    int stop = 1;
    int port;
    char addr[100];

    int addr_len = sizeof(client_addr);
    int new_socket_len = sizeof(new_socket);

    memset(valsend, 0 , sizeof(valsend)); // khoi tao vung nho cho cac bien
    memset(valread, 0 , sizeof(valread));
	memset(&server_addr, 0 , sizeof(server_addr));
    memset(&client_addr, 0 , sizeof(client_addr));

    listenfd = socket(AF_INET, SOCK_STREAM, 0); // tao socket
    if(listenfd<0)
    {
        printf("Socket failed\n"); //thoa neu loi
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;  // truong family
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.217"); // dia chi server
    server_addr.sin_port = htons(5000); // port server

    if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0) // dinh kem dia chi va port sever vao socket
    {
        printf("Bind failed\n"); // thoat neu loi
        exit(EXIT_FAILURE);
    }
    listen(listenfd, 10); // lang nghe, hang doi toi da la 10

    printf("Waiting for client: \n");
    new_socket = accept(listenfd, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len); // accept ket noi cua client va tao ra socket moi laf new_socket, dong thoi luu thong tin cua client vao client_addr
    if (new_socket<0)
    {
        printf("Accept failed\n"); // thoat neu loi
        exit(EXIT_FAILURE);
    }   
    //getsockname(listenfd, (struct sockaddr*)&new_socket,&(new_socket_len));
    strcpy(addr ,inet_ntoa(client_addr.sin_addr)); // copy dia chi IP cua client vao addr
    port = ntohs(client_addr.sin_port); // gan port cua client vao port
    printf("%s:%d connected\n", addr, port);

    while (stop!=0)
    {        
        recv(new_socket, valread, sizeof(valread), 0); // cho nhan  thong tin tu client
        printf("Client (%s:%d): %s", addr, port, valread); // in ra thong tin cua client
        //printf("Client: %s", valread);
        printf("Server: ");
        fgets(valsend, sizeof(valsend), stdin); // nhap thong tin can gui den client 
        fflush(stdin);         
        send(new_socket, valsend, sizeof(valsend), 0); // gui thong tin den client
        stop = strcmp(valread, "x\n");    //neu gia tri nhan duoc la x thi thoat  
    }
    
    close(new_socket); // dong socket
    close(listenfd);
    exit(EXIT_SUCCESS);
}
