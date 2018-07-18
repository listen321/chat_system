ROOT_PATH=$(shell pwd)
COMM_PATH=$(ROOT_PATH)/comm
WINDOW_PATH=$(ROOT_PATH)/window
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
CLIENT_PATH=$(ROOT_PATH)/client_udp
SERVER_PATH=$(ROOT_PATH)/server_udp
LIB_PATH=$(ROOT_PATH)/lib
cc=g++

FLAGS=-I$(DATA_POOL_PATH) -I$(WINDOW_PATH) -I$(COMM_PATH) -I$(LIB_PATH)/include
LDFLAGS=-lpthread -lncurses


ser=server_chat
ser_obj=$(shell ls $(SERVER_PATH)/*.cpp $(DATA_POOL_PATH)/*.cpp $(COMM_PATH)/*.cpp $(LIB_PATH)/src/lib_json/*.cpp | sed 's/.cpp/.o/g' | sed 's/.*\///g')
#ser_obj=$(shell ls $(SERVER_PATH)/*.cpp | sed 's/.cpp/.o/g' )

cli=client_chat
cli_obj=$(shell ls $(CLIENT_PATH)/*.cpp $(WINDOW_PATH)/*.cpp $(COMM_PATH)/*.cpp $(LIB_PATH)/src/lib_json/*.cpp | sed 's/.cpp/.o/g' | sed 's/.*\///g' )

.PHONY:%all
all:$(ser) $(cli)

$(ser):$(ser_obj)
	@$(cc) -o $@ $^ $(LDFLAGS)
	@echo "Linking [$^] to [$@] ....done"
$(cli):$(cli_obj)
	@$(cc) -o $@ $^ $(LDFLAGS)
	@echo "Linking [$^] to [$@] ....done"

%.o :$(SERVER_PATH)/%.cpp
	@$(cc) -c $< -o $@ $(FLAGS) 
	@echo "Linking [$<] to [$@] ....done"
%.o :$(CLIENT_PATH)/%.cpp
	@$(cc) -c $< -o $@ $(FLAGS)
	@echo "Linking [$<] to [$@] ....done"
%.o :$(DATA_POOL_PATH)/%.cpp
	@$(cc) -c $< -o $@ $(FLAGS)
	@echo "Linking [$<] to [$@] ....done"
%.o :$(COMM_PATH)/%.cpp
	@$(cc) -c $< -o $@ $(FLAGS)
	@echo "Linking [$<] to [$@] ....done"
%.o :$(WINDOW_PATH)/%.cpp
	@$(cc) -c $< -o $@ $(FLAGS)
	@echo "Linking [$<] to [$@] ....done"
%.o :$(LIB_PATH)/src/lib_json/%.cpp
	@$(cc) -c $< -o $@  $(FLAGS)
	@echo "Linking [$<] to [$@] ....done"


.PHONY:clean
clean:
	rm -f *.o $(ser) $(cli)
	
.PHONY:debug
debug:
#	@echo $(ser_obj)
#	@echo $(cli_obj)
#	@echo $(COMM_PATH)
	@echo $(FLAGS)    
