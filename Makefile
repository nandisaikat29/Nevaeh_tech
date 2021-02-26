output: server_main1.o client_main1.o
	g++ server_main1.o  -o server
	g++ client_main1.o -o client

server_main1.o:server_main1.cpp client_main1.cpp
	g++ -c server_main1.cpp
	g++ -c client_main1.cpp
clean:
	rm *.o server
	rm *.0 client
