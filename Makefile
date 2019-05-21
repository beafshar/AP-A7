all: a.out

a.out: main.o UTflix.o command_handler.o Controller.o Customer.o Publisher.o Movie.o Filter.o Sale.o Message.o Comment.o NotFound.o PermissionDenied.o BadRequest.o
	g++ main.o UTflix.o command_handler.o Controller.o Customer.o Publisher.o Movie.o Filter.o Sale.o Message.o Comment.o NotFound.o PermissionDenied.o BadRequest.o
main.o: main.cpp UTflix.h
		g++ -std=c++11 -c main.cpp
UTflix.o: UTflix.cpp UTflix.h command_handler.h Message.h Filter.h
		g++ -std=c++11 -c UTflix.cpp
command_handler.o: command_handler.cpp command_handler.h Controller.h
		g++ -std=c++11 -c command_handler.cpp
Controller.o: Controller.cpp Controller.h
		g++ -std=c++11 -c Controller.cpp
Customer.o: Customer.cpp Customer.h Publisher.h Movie.h Message.h Filter.h
		g++ -std=c++11 -c Customer.cpp
Publisher.o: Publisher.cpp Publisher.h Movie.h Customer.h Message.h Filter.h
		g++ -std=c++11 -c Publisher.cpp
Movie.o: Movie.cpp Movie.h Comment.h
		g++ -std=c++11 -c Movie.cpp
Sale.o: Sale.cpp Sale.h
		g++ -std=c++11 -c Sale.cpp
Filter.o: Filter.cpp Filter.h
		g++ -std=c++11 -c Filter.cpp
Message.o: Message.cpp Message.h
		g++ -std=c++11 -c Message.cpp
Comment.o: Comment.cpp Comment.h
		g++ -std=c++11 -c Comment.cpp
NotFound.o: NotFound.cpp NotFound.h
		g++ -std=c++11 -c NotFound.cpp
PermissionDenied.o: PermissionDenied.cpp PermissionDenied.h
		g++ -std=c++11 -c PermissionDenied.cpp
BadRequest.o: BadRequest.cpp BadRequest.h
		g++ -std=c++11 -c BadRequest.cpp

.PHONY: clean
clean:
	rm *.o
	rm a.out
