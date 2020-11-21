open Sdlevent
open Sdl

let proc_events = function
  | KeyDown { keycode = Keycode.Q }
  | KeyDown { keycode = Keycode.Escape }
  | Quit _ ->
      Sdlttf.quit ();
      Sdl.quit ();
      exit 0
  | e -> ()

let rec event_loop () =
  match Event.poll_event () with
  | None -> ()
  | Some ev ->
      proc_events ev;
      event_loop ()


let () =
  let width, height = (640, 480) in
  Sdl.init [`VIDEO];
  Sdlttf.init ();
  let window =
    Window.create
      ~pos:(`centered, `centered)
      ~dims:(width, height)
      ~title:"SDL2 Sprite Surface"
      ~flags:[Window.Resizable]
  in
  let screen = Window.get_surface window in

  let file = "/usr/share/fonts/TTF/VeraMono.ttf" in
  let font = Sdlttf.open_font ~file ~ptsize:40 in
  let color = { Sdlttf.r = 255; g = 0; b = 0; a = 0 } in
  let text = "Hello SDL2_TTF" in
  let surf = Sdlttf.render_text_solid font ~text ~color in

  let w, h = Surface.get_dims surf in
  Printf.printf "surface dimensions: %d %d\n%!" w h;

  let screen_rect = Rect.make4 0 0 width height in
  let src_rect = Rect.make4 0 0 width height in
  let dst_rect = Rect.make4 0 200 w h in

  let render t =
    Surface.fill_rect
      ~dst:screen ~rect:screen_rect
      ~color:0xFFFF00l;
    let x = (t / 10) mod width in
    let dst_rect = { dst_rect with Rect.x } in
    let _ =
      Surface.blit_surface
        ~src:surf ~dst:screen
        ~src_rect ~dst_rect
    in
    Window.update_surface window;
  in
  let rec main_loop () =
    event_loop ();
    let t = Timer.get_ticks () in
    render t;
    Timer.delay 40;
    main_loop ()
  in
  main_loop ()
