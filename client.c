#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

int main()
{
	int socket_desc;
	int r=10,i;
	struct sockaddr_in server_addr;
	char server_message[200], client_message[200];

	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

		if(socket_desc < 0)
		{
			printf("Unable to create socket\n");
			return -1;
		}
		printf("Socket created successfully\n");

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(2000);
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		{
			printf("Unable to connect\n");
			return -1;
		}
		printf("Connected\n");

		while(1)
		{
			printf("Enter message: ");
			scanf("%s",client_message);
			
			if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
			{
				printf("Unable to send message\n");
				return -1;
			}

			if(strcmp(client_message, "exit") == 0)
			{			
				printf("exit client\n");
				
				close(socket_desc);
				break;
			}

			if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
			{
				printf("Error while receiving server's msg\n");
				return -1;
			}

			if(strcmp(server_message, "exit") == 0)
			{			
				printf("exit client\n");
				close(socket_desc);
				break;

			}
			printf("Server's response: %s\n",server_message);
		}
	close(socket_desc);
	return 0;
}
