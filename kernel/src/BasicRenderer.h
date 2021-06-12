#pragma once

#include "Point.h"
#include "FrameBuffer.h"
#include "SimpleFonts.h"
#include <stdint.h>

class BasicRenderer{
    private:
        Point CursorPosition;
        Framebuffer* framebuffer; 
        PSF1_FONT* psf1_font;
        uint32_t MouseCursorBuffer[16 * 16];
        uint32_t MouseCursorBufferAfter[16 * 16];
        bool mouseDrawn;   
    public:
        BasicRenderer(Framebuffer* framebuffer, PSF1_FONT* psf1_font);
        void ChangeScreenCurserPosition(unsigned int X, unsigned int Y);
        void Print(const char** str);
        void Print(unsigned int color, const char** str);
        void PutPix(uint32_t x, uint32_t y, uint32_t color);
        uint32_t GetPix(uint32_t x, uint32_t y);
        void PutChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff);
        void PutChar(char chr);
        void NextCharSpace();
        void GoToNextLine();
        void testPsf1Font();
        Framebuffer* GetFramebuffer();
        void ClearChar(unsigned int color);
        void Clear(uint32_t color);
        void ClearMouseCursor(uint8_t* mouseCursor, Point position);
        void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color);
};

extern BasicRenderer* GBR;