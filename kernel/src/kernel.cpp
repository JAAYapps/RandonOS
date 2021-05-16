#include "BasicRenderer.h"
#include "cstr.h"
#include <stdint.h>

extern "C" char* _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font){
    BasicRenderer render = BasicRenderer(framebuffer, psf1_font);
    render.testPsf1Font();
    const char chr[] = "Renderer Loaded.";
    render.Print(0xff0025ff, chr);
    render.ChangeScreenCurserPosition(100, 400);
    render.Print(to_string((uint64_t)50512231));
    render.ChangeScreenCurserPosition(100, 420);
    render.Print(to_string((int64_t)-4312154));
    render.ChangeScreenCurserPosition(100, 440);
    render.Print(to_string((int64_t)431.154));
    render.ChangeScreenCurserPosition(100, 460);
    render.Print(to_string((double)431.154, 3));    
    return "Done!!!";
}