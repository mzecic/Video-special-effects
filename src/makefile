# Dwarf compiler
CC = /Applications/Xcode.app/Contents/Developer/usr/bin/g++
# CC = /usr/bin/g++

CXX = $(CC)

# OSX include paths (for MacPorts)
#CFLAGS = -I/opt/local/include -I../include

# OSX include paths (for homebrew, probably)
CFLAGS = -Wc++11-extensions -std=c++17 -I/opt/homebrew/Cellar/opencv/4.10.0_18/include/opencv4 -I../include -DENABLE_PRECOMPILED_HEADERS=OFF

# Dwarf include paths
#CFLAGS = -I../include # opencv includes are in /usr/include
CXXFLAGS = $(CFLAGS)

# OSX Library paths (if you use MacPorts)
#LDFLAGS = -L/opt/local/lib
# Compiler
CC = /Applications/Xcode.app/Contents/Developer/usr/bin/g++
CXX = $(CC)

# Compiler Flags
CFLAGS = -Wc++11-extensions -std=c++17 -I/opt/homebrew/Cellar/opencv/4.10.0_18/include/opencv4 -DENABLE_PRECOMPILED_HEADERS=OFF
CXXFLAGS = $(CFLAGS)

# Linker Flags
LDFLAGS = -L/opt/homebrew/Cellar/opencv/4.10.0_18/lib
LDFLAGS += -L/opt/homebrew/Cellar/opencv/4.10.0_18/lib -L/opt/homebrew/Cellar/onnxruntime/1.20.1_1/lib

# Libraries
LDLIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lonnxruntime

# Output Directory
BINDIR = ../bin

# Source Files
PROGRAMS = imgDisplay vidDisplay faceDetect imgMod macbeth

# Default Target: Build all programs
all: $(PROGRAMS)

# Individual Targets
imgDisplay: imgDisplay.o
	$(CC) $(CXXFLAGS) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

vidDisplay: vidDisplay.o
	$(CC) $(CXXFLAGS) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

faceDetect: faceDetect.o
	$(CC) $(CXXFLAGS) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

imgMod: imgMod.o
	$(CC) $(CXXFLAGS) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

macbeth: macbeth.o
	$(CC) $(CXXFLAGS) $^ -o $(BINDIR)/$@ $(LDFLAGS) $(LDLIBS)

# Rule to Compile .cpp to .o
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -f *.o *~ $(BINDIR)/*
