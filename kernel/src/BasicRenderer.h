#pragma once

#include "Point.h"
#include "FrameBuffer.h"
#include "SimpleFonts.h"

class BasicRenderer{
    private:
        Point CursorPosition;
        Framebuffer* framebuffer; 
        PSF1_FONT* psf1_font;
        void putChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff);
    public:
        BasicRenderer(Framebuffer* framebuffer, PSF1_FONT* psf1_font);
        void ChangeScreenCurserPosition(unsigned int X, unsigned int Y);
        void Print(const char** str);
        void Print(unsigned int color, const char** str);
        void GoToNextLine();
        void testPsf1Font();
};
