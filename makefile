all:  prot config socket db user rela mess photo  svr cln

prot:
	cd ./proto && make
config:
	g++ -c -o config.o Config.cpp
socket:
	g++ -c -o socket.o Socket.cpp
db:
	g++ -c -o db.o DbManager.cpp 
user:
	g++ -c -o userI.o UserInfo.cpp
	g++ -c -o userM.o  UserManager.cpp
rela:
	g++ -c -o relaI.o RelationInfo.cpp
	g++ -c -o relaM.o RelationManager.cpp
mess:
	g++ -c -o mess.o MessageManager.cpp
photo:
	g++ -c -o photo.o PhotoManager.cpp
dbt:
	g++ -o dbtest proto/*.o db.o userI.o userM.o dbmain.cpp -lprotobuf -lmysqlclient
svr:
	g++ -o server_ssp ./proto/*.o *.o  main.cpp -lprotobuf -lmysqlclient #-D _D
cln:
	g++ -o client_ssp ./proto/*.o config.o socket.o 2.client.cpp -lprotobuf
clean:
	rm -f *.o ./proto/*.o ./proto/*.pb.cc ./proto/*.pb.h server_ssp client_ssp

	

