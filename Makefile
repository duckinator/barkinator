include config.mk

SRCFILES = fuck.c

FILE_NAME=fuck

CC := gcc

LINUX_EXE=${FILE_NAME}
WINDOWS_EXE=${FILE_NAME}.exe

# ===== Flags =====

LINUX_SDL2_CFLAGS  := $(shell ${SDL2_CONFIG} --cflags)
LINUX_SDL2_LDFLAGS := $(shell ${SDL2_CONFIG} --static-libs)

WINDOWS_SDL2_CFLAGS := $(shell ${WINDOWS_SDL2_CONFIG} --cflags)
WINDOWS_SDL2_LDFLAGS := $(shell ${WINDOWS_SDL2_CONFIG} --static-libs)

# Copypasta from Faulty.
override COMPILER_FLAGS += -std=c11 -Wall -g -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings -Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration -gdwarf-2 -pedantic-errors -O0

override LINKER_FLAGS += ${SDL2_LDFLAGS}

LINUX_COMPILER_FLAGS := ${COMPILER_FLAGS} ${LINUX_SDL2_CFLAGS}
LINUX_LINKER_FLAGS   := ${LINKER_FLAGS} ${LINUX_SDL2_LDFLAGS}

WINDOWS_COMPILER_FLAGS := ${COMPILER_FLAGS} ${WINDOWS_SDL2_CFLAGS}
WINDOWS_LINKER_FLAGS   := ${LINKER_FLAGS} ${WINDOWS_SDL2_LDFLAGS}

# ===== Targets =====

all: linux windows

prereqs: config.mk

linux: prereqs ${LINUX_EXE}

${LINUX_EXE}:
	${CC} ${COMPILER_FLAGS} ${LINKER_FLAGS} ${SRCFILES} -o ${LINUX_EXE} ${LINUX_SDL2_CFLAGS} ${LINUX_SDL2_LDFLAGS}

windows: prereqs ${WINDOWS_EXE}

${WINDOWS_EXE}:
	${WINDOWS_CC} ${COMPILER_FLAGS} ${LINKER_FLAGS} ${SRCFILES} -o ${WINDOWS_EXE} ${WINDOWS_SDL2_CFLAGS} ${WINDOWS_SDL2_LDFLAGS} --static

clean:
	@find . -name '*.o' -delete
	@rm -f fuck fuck.exe

.PHONY: all linux windows clean
