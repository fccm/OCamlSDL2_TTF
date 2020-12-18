#ifndef _CAML_SDL_TTF_
#define _CAML_SDL_TTF_

TTF_Font * TTF_Font_val(value font)
{
    return (TTF_Font *) Nativeint_val(font);
}

value Val_TTF_Font(TTF_Font * p)
{
    return caml_copy_nativeint((intnat) p);
}

#endif /* _CAML_SDL_TTF_ */
