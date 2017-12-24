SYNTH_SRCFILES = src/synth/oscillators.c src/synth/audio.c src/synth/synth.c

SRCFILES = ${SYNTH_SRCFILES} src/main.c src/gui.c

FILE_NAME=fuck

# ===== Tool executables =====

# Native builds.
CC := gcc
SDL2_CONFIG ?= sdl2-config
PKG_CONFIG ?= pkg-config

# Cross-compiled Windows builds.
WINDOWS_CC  ?= x86_64-w64-mingw32-gcc
WINDOWS_SDL2_CONFIG ?= x86_64-w64-mingw32-sdl2-config
WINDOWS_PKG_CONFIG ?= x86_64-pc-linux-gnu-pkg-config

# ====================================================


LINUX_EXE=${FILE_NAME}
WINDOWS_EXE=${FILE_NAME}.exe

# ===== Flags =====

LINUX_SDL2_CFLAGS  := $(shell ${SDL2_CONFIG} --cflags)
LINUX_SDL2_LDFLAGS := $(shell ${SDL2_CONFIG} --static-libs)

LINUX_GLEW_CFLAGS  := $(shell ${PKG_CONFIG} --cflags glew)
LINUX_GLEW_LDFLAGS := $(shell ${PKG_CONFIG} --static --libs glew)

WINDOWS_SDL2_CFLAGS  := $(shell ${WINDOWS_SDL2_CONFIG} --cflags)
WINDOWS_SDL2_LDFLAGS := $(shell ${WINDOWS_SDL2_CONFIG} --static-libs)

WINDOWS_GLEW_CFLAGS  := $(shell ${WINDOWS_PKG_CONFIG} --cflags glew)
WINDOWS_GLEW_LDFLAGS := $(shell ${WINDOWS_PKG_CONFIG} --static --libs glew)

override COMPILER_FLAGS += -std=c11 -Wall -g -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wwrite-strings -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration -Wno-suggest-attribute=format -gdwarf-2 -pedantic-errors -O0
# The following have been removed because of excessive warnings from nuklea from nuklear.
# -Wfloat-equal -Wswitch-enum -Wconversion -Waggregate-return

override LINKER_FLAGS +=

LINUX_CFLAGS  := ${LINUX_SDL2_CFLAGS} ${LINUX_GLEW_CFLAGS}
LINUX_LDFLAGS := ${LINUX_SDL2_LDFLAGS} ${LINUX_GLEW_LDFLAGS}

WINDOWS_CFLAGS  := ${WINDOWS_SDL2_CFLAGS} ${WINDOWS_GLEW_CFLAGS}
WINDOWS_LDFLAGS := ${WINDOWS_SDL2_LDFLAGS} ${WINDOWS_GLEW_LDFLAGS}

# ===== Targets =====

all: linux windows

linux ${LINUX_EXE}:
	${CC} ${COMPILER_FLAGS} ${LINKER_FLAGS} ${SRCFILES} -o ${LINUX_EXE} ${LINUX_CFLAGS} ${LINUX_LDFLAGS}

windows ${WINDOWS_EXE}:
	${WINDOWS_CC} ${COMPILER_FLAGS} ${LINKER_FLAGS} ${SRCFILES} -o ${WINDOWS_EXE} ${WINDOWS_CFLAGS} ${WINDOWS_LDFLAGS} --static

clean:
	@find . -name '*.o' -delete
	@rm -f ${FILE_NAME} ${FILE_NAME}.exe

.PHONY: all linux windows clean
