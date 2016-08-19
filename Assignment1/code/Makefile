BIN = mydraw 
GLLIBS = -lGL -lGLU -lglut

.SUFFIXES: .cpp .hpp

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

mydraw: clean
	g++ --std=c++11 mydraw_class.cpp mydraw.cpp -o $@ $(GLLIBS)


