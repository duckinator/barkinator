NAME := barkinator

SYNTH_SRCFILES := src/synth/oscillators.c src/synth/audio.c src/synth/synth.c
SYNTH_OBJFILES := $(patsubst %.c,%.o,${SYNTH_SRCFILES})

GUI_SRCFILES := src/main.c src/gui.c
GUI_OBJFILES := $(patsubst %.c,%.o,${SRCFILES})

AR := ar
CC := clang
LD := ld

SDL2_CONFIG ?= sdl2-config
PKG_CONFIG ?= pkg-config

SDL2_CCFLAGS += $(shell ${SDL2_CONFIG} --cflags)
SDL2_LDFLAGS += $(shell ${SDL2_CONFIG} --static-libs)

override CCFLAGS += -std=c11 -pedantic-errors -gdwarf-2 \
					-fdiagnostics-show-option -Werror -Weverything \
					${SDL2_CCFLAGS} \
					-Wno-missing-prototypes -Wno-padded \
					-Wno-error=conversion -Wno-error=cast-align # HACK
#					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla
override LDFLAGS += -g --whole-archive \
					${SDL2_LDFLAGS}

all: ${NAME}.a

${NAME}.a: ${SYNTH_OBJFILES}
	${AR} rcs $@ $<

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

# Fetch all submodules.
fetch-submodules:
	git submodule update --recursive --init

# Update to the latest available versions of all submodules.
update-submodules:
	git submodule update --recursive --remote --init

clean:
	@find . '(' -name '*.o' -o -name '*.a' ')' -delete
	@rm -f ${NAME}

.PHONY: all linux windows clean
