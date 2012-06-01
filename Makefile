SRCS = OpenGLBase.cpp OpenGLWindow.cpp drawer.cpp drawFunctions.cpp
HEADERS = OpenGLWindow.hpp drawFunctions.hpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

ifeq ($(OS),Windows_NT)
# for Windows

else
UNAME = ${shell uname}

ifeq ($(UNAME),Linux)
# for Linux
CXX = g++
CXXFLAGS = -O2 -Wall
LDFLAGS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread
PROGRAM = openGLBase_lin

endif

ifeq ($(UNAME),Darwin)
# for MacOSX
#!/opt/local/bin/gmake
CXX = g++
CXXFLAGS = -O2 -Wall -I/opt/local/include/ -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lm
PROGRAM = openGLBase_mac
endif
endif


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	rm -f $@
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	rm -f $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

.cpp:
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# drawer.o: $(MAIN) drawer.cpp
# 	$(CXX) $(CXXFLAGS) -c drawer.cpp $(MAIN) 

# OpenGLBase.o: OpenGLBase.cpp drawer.cpp OpenGLWindow.cpp drawFunctions.cpp
# 	$(CXX) $(CXXFLAGS) -c OpenGLBase.cpp drawer.cpp

# drawer.o: drawFunctions.hpp
# drawFunctions.o: drawFunctions.hpp
# OpenGLBase.o: OpenGLWindow.hpp drawFunctions.hpp drawer.o
# OpenGLWindow.o: OpenGLWindow.hpp

.PHONY: clean
clean:
	rm $(PROGRAM) $(OBJS)