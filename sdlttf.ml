(* OCamlSDL2_TTF - An OCaml interface to the SDL2_ttf library
 Copyright (C) 2013 Florent Monnier
 
 This software is provided "AS-IS", without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from
 the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely.
*)
(* TrueType Fonts library for SDL2 *)

type font

external init : unit -> unit
  = "caml_TTF_Init"

external quit : unit -> unit
  = "caml_TTF_Quit"

external was_init : unit -> bool
  = "caml_TTF_WasInit"

external open_font : file:string -> ptsize:int -> font
  = "caml_TTF_OpenFont"

external open_font_index :
  file:string -> ptsize:int -> index:int -> font
  = "caml_TTF_OpenFontIndex"

external close_font : font -> unit
  = "caml_TTF_CloseFont"

