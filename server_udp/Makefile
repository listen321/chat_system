chat_server:chat_server.o   server.o data_pool.o
	g++ -o  $@   $^ -lpthread
%.o:%.cpp
	g++ -c  -o  $@  $^

.PHONY:clean
clean:
	rm -f *.o char_server
