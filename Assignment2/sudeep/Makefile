BIN = bicycle 
GLLIBS = -lGL -lGLU -lglut

.SUFFIXES: .cpp .hpp

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

bicycle: clean
	g++ bicycle_class.cpp bicycle.cpp -o $@ $(GLLIBS)


