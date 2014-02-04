/* OCamlSDL2_TTF - An OCaml interface to the SDL2_ttf library
 Copyright (C) 2013 Florent Monnier
 
 This software is provided "AS-IS", without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from
 the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely.
*/
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>

#include <SDL_ttf.h>
#include "sdlttf_stub.h"

CAMLprim value
caml_TTF_Init(value unit)
{
    int r = TTF_Init();
    if (r) caml_failwith("Sdlttf.init");
    return Val_unit;
}

CAMLprim value
caml_TTF_Quit(value unit)
{
    TTF_Quit();
    return Val_unit;
}

CAMLprim value
caml_TTF_WasInit(value unit)
{
    CAMLparam1(unit);
    CAMLreturn(Val_bool(TTF_WasInit()));
}

static void
error(char *text)
{
    char buf[1024];
    snprintf(buf, 1023,  "%s: %s", text, TTF_GetError());
    caml_failwith(buf);
}

CAMLprim value
caml_TTF_OpenFont(value file, value ptsize)
{
    CAMLparam2(file, ptsize);
    TTF_Font *font = TTF_OpenFont(String_val(file), Int_val(ptsize));
    if (!font) error("TTF_OpenFont");

    CAMLreturn(Val_TTF_Font(font));
}

CAMLprim value
caml_TTF_OpenFontIndex(value file, value ptsize, value index)
{
    CAMLparam3(file, ptsize, index);
    TTF_Font *font = TTF_OpenFontIndex(String_val(file), Int_val(ptsize), Int_val(index));
    if (!font) error("TTF_OpenFontIndex");
    CAMLreturn(Val_TTF_Font(font));
}

CAMLprim value
caml_TTF_CloseFont(value font)
{
    CAMLparam1(font);
    TTF_CloseFont(TTF_Font_val(font));
    CAMLreturn(Val_unit);
}

/* vim: set ts=4 sw=4 et: */
