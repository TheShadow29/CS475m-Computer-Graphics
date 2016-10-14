BIN = lighting 
GLLIBS = -lGL -lGLU -lglut 

.SUFFIXES: .cpp .hpp

all: $(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

lighting: clean
	g++ lighting_class.cpp lighting.cpp  -o $@ $(GLLIBS)


