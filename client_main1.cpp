#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
#include<netinet/in.h>
#include<unistd.h>
#define PORT 8098
int main(int argc , char *argv[])
{
        int socket_desc;
        struct sockaddr_in server;
                socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT );
        if (connect(socket_desc ,(struct sockaddr *)&server , sizeof(server))<0)
        {
                puts("connect error");
                return 1;
        }

        puts("Connected\n");
        
        time_t start=time(NULL),end=time(NULL);
        while(1){
        char message[2000]={} , server_reply[2000]={};
        puts("enter message : ");
        fgets(message,2000,stdin);
        end=time(NULL);
        if(difftime(end,start)<=10)
                send(socket_desc , message , strlen(message),0);
        else{
                send(socket_desc , message , strlen(message),0);
                break;
        }
         recv(socket_desc, server_reply , 2000 , 0);
        puts("reply : ");
        puts(server_reply);
        start=time(NULL);
        if(difftime(start,end)>=10)

                break;
        }
        return 0;
}
