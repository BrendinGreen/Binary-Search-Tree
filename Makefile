all: tApp

tApp: BST_Test_Driver.o BST.h BSTNode.h WordPair.o ElementAlreadyExistsInBSTException.o ElementDoesNotExistInBSTException.o
	g++ -Wall -std=c++11 -o BST_Test_Driver BST_Test_Driver.o WordPair.o ElementAlreadyExistsInBSTException.o ElementDoesNotExistInBSTException.o

BST_Test_Driver.o: BST_Test_Driver.cpp
	g++ -Wall -std=c++11 -c BST_Test_Driver.cpp
		
WordPair.o: WordPair.h WordPair.cpp
	g++ -Wall -std=c++11 -c WordPair.cpp

ElementDoesNotExistInBSTException.o: ElementDoesNotExistInBSTException.h ElementDoesNotExistInBSTException.cpp
	g++ -Wall -std=c++11 -c ElementDoesNotExistInBSTException.cpp

ElementAlreadyExistsInBSTException.o: ElementAlreadyExistsInBSTException.h ElementAlreadyExistsInBSTException.cpp
	g++ -Wall -std=c++11 -c ElementAlreadyExistsInBSTException.cpp
		
clean:
	rm -f BST_Test_Driver *.o