CC = clang
LIBS =
FLAGS = -Wall -Wextra -std=c99
DEFINES = -DKEXPORT
INCLUDES = -Iinclude -Iplatform/include
FILES = $(shell find ./src -type f -name "*.c")
OUT = ./krispy

EXTRAFLAGS =

# renderer specific variables
OPENGLINCLUDES = -Iopengl/include
OPENGLFILES = $(shell find ./opengl/src -type f -name "*.c")

# platform specific variables
LINUXOPENGLLIBS = -lGL
LINUXLIBS = -Lplatform/linux/lib/ -lglfw
LINUXFILES = $(shell find ./platform/linux -type f -name "*.c")

WINOPENGLLIBS = -lopengl32
WINCC = i686-w64-mingw32-gcc
WINLIBS = -Lplatform/windows/lib/mingw -lglfw3 -lgdi32 -lkernel32 -lm
WINFILES = $(shell find ./platform/windows -type f -name "*.c")

linux-opengl:
	$(CC) $(LINUXLIBS) $(LINUXOPENGLLIBS) $(LIBS) $(FLAGS) $(DEFINES) $(INCLUDES) $(FILES) $(OPENGLINCLUDES) $(OPENGLFILES) $(LINUXFILES) -o $(OUT) $(EXTRAFLAGS)

win-opengl:
	$(WINCC) $(WINLIBS) $(WINOPENGLLIBS) $(LIBS) $(FLAGS) $(DEFINES) $(INCLUDES) $(FILES) $(OPENGLINCLUDES) $(OPENGLFILES) $(WINFILES) -o $(OUT) $(EXTRAFLAGS)