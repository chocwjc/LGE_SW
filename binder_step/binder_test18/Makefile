ALL: server.app client.app

server.app: 
	make -C ./server
	ln -s ./server/a.out server.app
	
client.app: 
	make -C ./client
	ln -s ./client/a.out client.app

.PHONY:clean
clean:
	rm -f server.app client.app
	make -C ./server clean
	make -C ./client clean
