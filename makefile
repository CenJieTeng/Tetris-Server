Server:Server.o message.pb.o
	g++ -std=c++11 Server.o message.pb.o -o Server -lboost_system -lprotobuf -lpthread -g

message.pb.o:message.pb.cc message.pb.h
	g++ -c -I/usr/local/include -std=c++11 message.pb.cc -o message.pb.o -g

Server.o:Server.cpp message.h  message.pb.h Logger.h
	g++ -c -std=c++11 Server.cpp -o Server.o -g

clean:
	rm -rf Server Server.o message.pb.o
