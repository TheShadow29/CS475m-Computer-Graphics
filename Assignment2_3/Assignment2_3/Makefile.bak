BIN = animate 
GLLIBS = -lGL -lGLU -lglut

.SUFFIXES: .cpp .hpp

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

animate: clean
	g++ animate_class.cpp animate.cpp -o $@ $(GLLIBS)


