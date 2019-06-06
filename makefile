CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template
UTFLIX_DIR = UTflix

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: $(UTFLIX_DIR)/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(UTFLIX_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: $(UTFLIX_DIR)/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(UTFLIX_DIR)/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: $(UTFLIX_DIR)/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(UTFLIX_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/UTflix.o: $(UTFLIX_DIR)/UTflix.cpp $(UTFLIX_DIR)/UTflix.h  $(UTFLIX_DIR)/Customer.h $(UTFLIX_DIR)/Publisher.h $(UTFLIX_DIR)/Message.h $(UTFLIX_DIR)/BadRequest.h
			$(CC) -c $(UTFLIX_DIR)/UTflix.cpp -o $(BUILD_DIR)/UTflix.o
$(BUILD_DIR)/Customer.o: $(UTFLIX_DIR)/Customer.cpp $(UTFLIX_DIR)/Customer.h $(UTFLIX_DIR)/Publisher.h $(UTFLIX_DIR)/Message.h $(UTFLIX_DIR)/BadRequest.h
			$(CC) -c $(UTFLIX_DIR)/Customer.cpp -o $(BUILD_DIR)/Customer.o
$(BUILD_DIR)/Publisher.o: $(UTFLIX_DIR)/Publisher.cpp $(UTFLIX_DIR)/Publisher.h  $(UTFLIX_DIR)/Customer.h
			$(CC) -c $(UTFLIX_DIR)/Publisher.cpp -o $(BUILD_DIR)/Publisher.o
$(BUILD_DIR)/Controller.o: $(UTFLIX_DIR)/Controller.cpp $(UTFLIX_DIR)/Controller.h  server/server.hpp
			$(CC) -c $(UTFLIX_DIR)/Controller.cpp -o $(BUILD_DIR)/Controller.o
$(BUILD_DIR)/Movie.o: $(UTFLIX_DIR)/Movie.cpp $(UTFLIX_DIR)/Movie.h  $(UTFLIX_DIR)/Sale.h server/server.hpp $(UTFLIX_DIR)/Comment.h
			$(CC) -c $(UTFLIX_DIR)/Movie.cpp -o $(BUILD_DIR)/Movie.o
$(BUILD_DIR)/Sale.o: $(UTFLIX_DIR)/Sale.cpp $(UTFLIX_DIR)/Sale.h
			$(CC) -c $(UTFLIX_DIR)/Sale.cpp -o $(BUILD_DIR)/Sale.o
$(BUILD_DIR)/BadRequest.o: $(UTFLIX_DIR)/BadRequest.cpp $(UTFLIX_DIR)/BadRequest.h
			$(CC) -c $(UTFLIX_DIR)/BadRequest.cpp -o $(BUILD_DIR)/BadRequest.o
$(BUILD_DIR)/Recommender_System.o: $(UTFLIX_DIR)/Recommender_System.cpp $(UTFLIX_DIR)/Recommender_System.h
				$(CC) -c $(UTFLIX_DIR)/Recommender_System.cpp -o $(BUILD_DIR)/Recommender_System.o
$(BUILD_DIR)/Filter.o: $(UTFLIX_DIR)/Filter.cpp $(UTFLIX_DIR)/Filter.h $(UTFLIX_DIR)/Movie.h
				$(CC) -c $(UTFLIX_DIR)/Filter.cpp -o $(BUILD_DIR)/Filter.o
$(BUILD_DIR)/Message.o: $(UTFLIX_DIR)/Message.cpp $(UTFLIX_DIR)/Message.h
			  $(CC) -c $(UTFLIX_DIR)/Message.cpp -o $(BUILD_DIR)/Message.o
$(BUILD_DIR)/Comment.o: $(UTFLIX_DIR)/Comment.cpp $(UTFLIX_DIR)/Comment.h $(UTFLIX_DIR)/Message.h
				$(CC) -c $(UTFLIX_DIR)/Comment.cpp -o $(BUILD_DIR)/Comment.o
$(BUILD_DIR)/web_interface.o: $(UTFLIX_DIR)/web_interface.cpp $(UTFLIX_DIR)/Filter.h $(UTFLIX_DIR)/Movie.h $(UTFLIX_DIR)/Movie.h $(UTFLIX_DIR)/Recommender_System.h $(UTFLIX_DIR)/Customer.h $(UTFLIX_DIR)/Publisher.h $(UTFLIX_DIR)/Message.h
					$(CC) -c $(UTFLIX_DIR)/web_interface.cpp -o $(BUILD_DIR)/web_interface.o
myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/UTflix.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Controller.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Recommender_System.o $(BUILD_DIR)/Sale.o $(BUILD_DIR)/Movie.o $(BUILD_DIR)/web_interface.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Message.o $(BUILD_DIR)/BadRequest.o
			$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/UTflix.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Controller.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Recommender_System.o $(BUILD_DIR)/Sale.o $(BUILD_DIR)/Movie.o $(BUILD_DIR)/web_interface.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/BadRequest.o $(BUILD_DIR)/Message.o -o myserver.out
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
