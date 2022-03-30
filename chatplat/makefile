all:prot conf sock user rela mess photo svr cln

prot:
	cd ./proto && make
conf:
	g++ -c -o conf.o Config.cpp
sock:
	g++ -c -o sock.o Socket.cpp
user:
	g++ -c -o user.o UserManager.cpp
rela:
	g++ -c -o relaI.o RelationInfo.cpp
	g++ -c -o relaM.o RelationManager.cpp
mess:
	g++ -c -o mess.o MessageManager.cpp
photo:
	g++ -c -o photo.o PhotoManager.cpp
svr:
	g++ -o server_ssp proto/*.o *.o main.cpp -lprotobuf
cln:
	g++ -o client_ssp proto/*.o *.o 2client.cpp -lprotobuf
clean:
	rm -f ./proto/*.o ./proto/*.pb.cc ./proto/*.pb.h *.o server_ssp client_ssp

