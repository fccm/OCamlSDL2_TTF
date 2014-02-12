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
#include "sdlsurface_stub.h"

CAMLprim value
caml_SDL_TTF_Init(value unit)
{
    int r = TTF_Init();
    if (r) caml_failwith("Sdlttf.init");
    return Val_unit;
}

CAMLprim value
caml_SDL_TTF_Quit(value unit)
{
    TTF_Quit();
    return Val_unit;
}

CAMLprim value
caml_SDL_TTF_WasInit(value unit)
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
caml_SDL_TTF_OpenFont(value file, value ptsize)
{
    CAMLparam2(file, ptsize);
    TTF_Font *font =
        TTF_OpenFont(
                String_val(file), Int_val(ptsize));

    if (!font) error("Sdlttf.open_font");

    CAMLreturn(Val_TTF_Font(font));
}

CAMLprim value
caml_SDL_TTF_OpenFontIndex(value file, value ptsize, value index)
{
    CAMLparam3(file, ptsize, index);
    TTF_Font *font =
        TTF_OpenFontIndex(
                String_val(file), Int_val(ptsize), Int_val(index));

    if (!font) error("Sdlttf.open_font_index");

    CAMLreturn(Val_TTF_Font(font));
}

CAMLprim value
caml_SDL_TTF_CloseFont(value font)
{
    CAMLparam1(font);
    TTF_CloseFont(TTF_Font_val(font));
    CAMLreturn(Val_unit);
}

SDL_Color SDL_Color_val(value color)
{
    SDL_Color c =
        {
            Int_val(Field(color, 0)),
            Int_val(Field(color, 1)),
            Int_val(Field(color, 2)),
            Int_val(Field(color, 3))
        };
    return c;
}

#define TTF_Render_Solid(t, l)                                     \
CAMLprim value                                                     \
caml_SDL_TTF_Render##t##_Solid(value font, value text, value c)    \
{                                                                  \
    CAMLparam3(font, text, c);                                     \
    SDL_Color color = SDL_Color_val(c);                            \
    SDL_Surface *surface;                                          \
    surface = TTF_Render##t##_Solid(TTF_Font_val(font),            \
                                    String_val(text),              \
                                    color);                        \
    if (!surface) error("sdlttf.render_" #l "_solid");             \
    CAMLreturn(Val_SDL_Surface(surface));                          \
}

TTF_Render_Solid(Text, text);
TTF_Render_Solid(UTF8, utf8);

#define TTF_Render_Shaded(t, l)                                    \
CAMLprim value                                                     \
caml_SDL_TTF_Render##t##_Shaded(                                   \
        value font, value text, value fg, value bg)                \
{                                                                  \
    CAMLparam4(font, text, fg, bg);                                \
    SDL_Color fgc = SDL_Color_val(fg);                             \
    SDL_Color bgc = SDL_Color_val(bg);                             \
    SDL_Surface *surface;                                          \
    surface = TTF_Render##t##_Shaded(TTF_Font_val(font),           \
                                    String_val(text),              \
                                    fgc, bgc);                     \
    if (!surface) error("sdlttf.render_" #l "_shaded");            \
    CAMLreturn(Val_SDL_Surface(surface));                          \
}

TTF_Render_Shaded(Text, text);
TTF_Render_Shaded(UTF8, utf8);

#define TTF_Render_Blended(t, l)                                   \
CAMLprim value                                                     \
caml_SDL_TTF_Render##t##_Blended(value font, value text, value c)  \
{                                                                  \
    CAMLparam3(font, text, c);                                     \
    SDL_Color color = SDL_Color_val(c);                            \
    SDL_Surface *surface;                                          \
    surface = TTF_Render##t##_Blended(TTF_Font_val(font),          \
                                    String_val(text),              \
                                    color);                        \
    if (!surface) error("sdlttf.render_" #l "_blended");           \
    CAMLreturn(Val_SDL_Surface(surface));                          \
}

TTF_Render_Blended(Text, text);
TTF_Render_Blended(UTF8, utf8);

#define TTF_Size(t)                                                \
CAMLprim value                                                     \
caml_SDL_TTF_Size##t(value font, value text)                       \
{                                                                  \
    CAMLparam2(font, text);                                        \
    CAMLlocal1(tup);                                               \
    int w, h;                                                      \
    TTF_Size##t(TTF_Font_val(font), String_val(text), &w, &h);     \
    tup = caml_alloc_tuple(2);                                     \
    Store_field(tup, 0, Val_int(w));                               \
    Store_field(tup, 1, Val_int(h));                               \
    CAMLreturn(tup);                                               \
}

TTF_Size(Text);
TTF_Size(UTF8);

static inline int
SDL_TTF_STYLE_Flags_ml2c(v)
{
    if (v == caml_hash_variant("normal"))       return TTF_STYLE_NORMAL;
    if (v == caml_hash_variant("bold"))         return TTF_STYLE_BOLD;
    if (v == caml_hash_variant("italic"))       return TTF_STYLE_ITALIC;
    if (v == caml_hash_variant("underline"))    return TTF_STYLE_UNDERLINE;
    if (v == caml_hash_variant("strikethrough")) return TTF_STYLE_STRIKETHROUGH;
}

/* vim: set ts=4 sw=4 et: */
