#include<stdio.h>
#include<string.h>      //strlen
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>      //write
#include<netinet/in.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iostream>
#define PORT 6200
using namespace std;
int main(int argc , char *argv[])
{
        int socket_desc , new_socket , cp,c;
        struct sockaddr_in server , client;
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }
        int opt=1;
        if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
         {
             perror("setsockopt");
             exit(EXIT_FAILURE);
         }

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);

        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("bind failed");
                return 1;
        }
        puts("bind done");
        listen(socket_desc , 3);
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
        new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	char *client_ip=inet_ntoa(client.sin_addr);
        
        time_t start=time(NULL),end=time(NULL),mid;
        while(1){
                char message[2000]={},buffer[2000]={};
                puts("Reply : ");
                recv(new_socket,buffer,2000,0);
                puts(buffer);
                	ofstream fout;
                	ifstream fin;
                	fin.open("log.txt");
                	fout.open("log.txt",ios::app);
                	if(fin.is_open()){
                		fout<<client_ip<<"  ";
                		fout<<buffer;
                		fin.close();
                		fout.close();
                	}
                mid=time(NULL);
                if(difftime(mid,end)>=10)
                        break;
                start=time(NULL);
                puts("enter message : ");
                fgets(message,2000,stdin);
                	fin.open("log.txt");
                	fout.open("log.txt",ios::app);
                	if(fin.is_open()){
                		fout<<"server : ";
                		fout<<buffer;
                		fin.close();
                		fout.close();
                	}
 
                end=time(NULL);
                if(difftime(end,start)<=10)
                write(new_socket , message , strlen(message));
                
                else
                {
                        write(new_socket , message , strlen(message));
                        break;
                }

        }
        return 0;
}
                               
