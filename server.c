#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
	int listenfd = -1;  ///so mo ta socket
	int connfd = -1;
	struct sockaddr_in server_addr;  ///struct chua thong tin socket
	char send_buffer[1024];
	time_t ticks;

	memset(send_buffer, 0 , sizeof(send_buffer)); ///cap phat, khoi tao vung nho
	memset(&server_addr, 0 , sizeof(server_addr));
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0); ///thiet lap thong tin dia chi IP cua server
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(5000);

	bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); ///dong goi, kem dia chi vaf phan luong gui den may dich
	listen(listenfd, 10);

	while (1)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);  /// neu khong co phan tu nao thi block, co thi tra ve mot socket moi
		ticks = time(NULL);
		sprintf(send_buffer, "Server reply %s", ctime(&ticks));
		write(connfd, send_buffer, strlen(send_buffer)); /// gui thong tin
		close(connfd);
	}
	close(listenfd);
}
