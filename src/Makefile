# OCamlSDL2_TTF - An OCaml interface to the SDL2_ttf library
# Copyright (C) 2013 Florent Monnier
#
# This software is provided "AS-IS", without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from
# the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely.


OCAMLFIND = ocamlfind
USEFIND = $(shell which $(OCAMLFIND) 2>/dev/null)

ifdef USEFIND
OCAMLC = $(OCAMLFIND) ocamlc
OCAMLOPT = $(OCAMLFIND) ocamlopt
OCSDLINC = -package sdl2
OCSDLDIR = $(shell $(OCAMLFIND) query sdl2)
else
OCAMLC = ocamlc
OCAMLOPT = ocamlopt
OCSDLINC = -I +sdl2
OCAMLDIR = $(shell $(OCAMLC) -where)
OCSDLDIR = $(OCAMLDIR)/sdl2
endif

OCAML = ocaml
OCAMLDOC = ocamldoc
OCAMLDEP = ocamldep
OCAMLMKLIB = ocamlmklib
CC = gcc
DIRSEP = $(shell $(OCAML) dir_sep.ml)

PKG_CONFIG = pkg-config
SDL_CONFIG = sdl2-config
CFLAGS = $(shell $(PKG_CONFIG) --cflags SDL2_ttf)
CFLAGS += -I$(OCSDLDIR)
LIBS_ = $(shell $(PKG_CONFIG) --libs SDL2_ttf)
LIBS = $(shell $(OCAML) prm.ml $(LIBS_))
SDL_PREFIX = $(shell $(SDL_CONFIG) --prefix)

BINDINGS_DIR = sdl2_ttf
PREFIX :=
DESTDIR := $(PREFIX)$(DIRSEP)$(OCAMLDIR)$(DIRSEP)$(BINDINGS_DIR)
UNINSTALL_DIR := rm -Rf
INSTALL_DIR := mkdir -p
INSTALL_FILES := cp -f

EDITOR = vim

.PHONY: all lib opt
all: lib opt
lib: sdl2_ttf.cma
opt: sdl2_ttf.cmxa

%.cmi: %.mli
	$(OCAMLC) -c $<

%.cmo: %.ml
	$(OCAMLC) -c $(OCSDLINC) $<

%.cmx: %.ml
	$(OCAMLOPT) -c $(OCSDLINC) $<

sdlttf_stub.o: sdlttf_stub.c
	$(OCAMLC) -ccopt "-static $(CFLAGS) -g -O " $<


sdl2_ttf.cma: sdlttf.cmo libsdl2ttf_stubs.a
	$(OCAMLMKLIB) -o sdl2_ttf -oc sdl2ttf_stubs sdlttf.cmo $(LIBS)

sdl2_ttf.cmxa: sdlttf.cmx libsdl2ttf_stubs.a
	$(OCAMLMKLIB) -o sdl2_ttf -oc sdl2ttf_stubs sdlttf.cmx $(LIBS)

libsdl2ttf_stubs.a: sdlttf_stub.o
	$(OCAMLMKLIB) -o sdl2_ttf -oc sdl2ttf_stubs sdlttf_stub.o $(LIBS)

.PHONY: edit
edit:
	$(EDITOR) sdlttf.ml sdlttf_stub.c \
	  $(SDL_PREFIX)/include/SDL2/SDL_ttf.h

.PHONY: clean
clean:
	$(RM) *.[oas] *.cm[ioxta] *.cmx[as] *.so *.dll *.opt *.exe

ifdef USEFIND
install:
	$(OCAMLFIND) install $(BINDINGS_DIR) META \
	  *.cm[aix] *.cmx[as] sdl2*.a *sdl2*_stubs.*
uninstall:
	$(OCAMLFIND) remove $(BINDINGS_DIR)
else
install:
	$(INSTALL_DIR) $(DESTDIR)
	$(INSTALL_FILES) \
	  *.cm[aix] *.cmx[as] sdl2*.a *sdl2*_stubs.* \
	  $(DESTDIR)
uninstall:
	$(UNINSTALL_DIR) $(DESTDIR)
endif

reinstall:
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) uninstall
	$(MAKE) install
