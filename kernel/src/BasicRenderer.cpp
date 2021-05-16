#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(Framebuffer* framebuffer, PSF1_FONT* psf1_font)
{
    this->framebuffer = framebuffer;
    this->psf1_font = psf1_font;
    this->CursorPosition.X = 0;
    this->CursorPosition.Y = 0;
}

void BasicRenderer::ChangeScreenCurserPosition(unsigned int X, unsigned int Y)
{
    this->CursorPosition.X = X;
    this->CursorPosition.Y = Y;
}

void BasicRenderer::putChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = (char*)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = color;
                }

        }
        fontPtr++;
    }
}

void BasicRenderer::Print(const char str[])
{
    this->Print(0xffffffff, str);
}

void BasicRenderer::Print(unsigned int color, const char str[])
{
    char* chr = (char*)str;
    unsigned int count = 0;
    while(*chr != 0 && count < 1000000000){
        putChar(color, *chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > framebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        *chr++;
        count = count + 1;
    }
}

void BasicRenderer::testPsf1Font()
{
    putChar(0xffffffff, '1', 20, 20);
    putChar(0xffffffff, '2', 20, 40);
    putChar(0xffffffff, '3', 20, 60);
    putChar(0xffffffff, '4', 20, 80);
    putChar(0xffffffff, '5', 20, 100);
    putChar(0xffffffff, '6', 20, 120);
    putChar(0xffffffff, '7', 20, 140);
    putChar(0xffffffff, '8', 20, 180);
    putChar(0xffffffff, '9', 20, 200);
    putChar(0xffffffff, '0', 20, 240);
    putChar(0xffffffff, 'A', 40, 20);
    putChar(0xffffffff, 'B', 40, 40);
    putChar(0xffffffff, 'C', 40, 60);
    putChar(0xffffffff, 'D', 40, 80);
    putChar(0xffffffff, 'E', 40, 100);
    putChar(0xffffffff, 'F', 40, 120);
    putChar(0xffffffff, 'G', 40, 140);
    putChar(0xffffffff, 'H', 40, 180);
    putChar(0xffffffff, 'I', 40, 200);
    putChar(0xffffffff, 'J', 40, 220);
    putChar(0xffffffff, 'K', 40, 240);
    putChar(0xffffffff, 'L', 40, 260);
    putChar(0xffffffff, 'M', 40, 280);
    putChar(0xffffffff, 'N', 40, 300);
    putChar(0xffffffff, 'O', 40, 320);
    putChar(0xffffffff, 'P', 40, 340);
    putChar(0xffffffff, 'Q', 40, 380);
    putChar(0xffffffff, 'R', 40, 400);
    putChar(0xffffffff, 'S', 40, 420);
    putChar(0xffffffff, 'T', 40, 440);
    putChar(0xffffffff, 'U', 40, 460);
    putChar(0xffffffff, 'V', 40, 480);
    putChar(0xffffffff, 'W', 40, 500);
    putChar(0xffffffff, 'X', 40, 520);
    putChar(0xffffffff, 'Y', 40, 540);
    putChar(0xffffffff, 'Z', 40, 560);
    putChar(0xffffffff, 'a', 60, 20);
    putChar(0xffffffff, 'b', 60, 40);
    putChar(0xffffffff, 'c', 60, 60);
    putChar(0xffffffff, 'd', 60, 80);
    putChar(0xffffffff, 'e', 60, 100);
    putChar(0xffffffff, 'f', 60, 120);
    putChar(0xffffffff, 'g', 60, 140);
    putChar(0xffffffff, 'h', 60, 180);
    putChar(0xffffffff, 'i', 60, 200);
    putChar(0xffffffff, 'j', 60, 220);
    putChar(0xffffffff, 'k', 60, 240);
    putChar(0xffffffff, 'l', 60, 260);
    putChar(0xffffffff, 'm', 60, 280);
    putChar(0xffffffff, 'n', 60, 300);
    putChar(0xffffffff, 'o', 60, 320);
    putChar(0xffffffff, 'p', 60, 340);
    putChar(0xffffffff, 'q', 60, 380);
    putChar(0xffffffff, 'r', 60, 400);
    putChar(0xffffffff, 's', 60, 420);
    putChar(0xffffffff, 't', 60, 440);
    putChar(0xffffffff, 'u', 60, 460);
    putChar(0xffffffff, 'v', 60, 480);
    putChar(0xffffffff, 'w', 60, 500);
    putChar(0xffffffff, 'x', 60, 520);
    putChar(0xffffffff, 'y', 60, 540);
    putChar(0xffffffff, 'z', 60, 560);
}