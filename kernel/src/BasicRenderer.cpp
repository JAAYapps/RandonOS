#include "BasicRenderer.h"

BasicRenderer* GBR;

BasicRenderer::BasicRenderer(Framebuffer* framebuffer, PSF1_FONT* psf1_font)
{
    this->framebuffer = framebuffer;
    this->psf1_font = psf1_font;
    this->CursorPosition.X = 0;
    this->CursorPosition.Y = 0;
}

Framebuffer* BasicRenderer::GetFramebuffer()
{
    return this->framebuffer;
}

void BasicRenderer::Clear(uint32_t color)
{
    uint64_t fbBase = (uint64_t)this->framebuffer->BaseAddress;
    uint64_t bytesPerScanline = framebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = framebuffer->Height;
    uint64_t fbSize = framebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline++)
    {
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr++)
        {
            *pixPtr = color;
        }
        
    }
}

void BasicRenderer::ClearChar(unsigned int color)
{
    if(CursorPosition.X <= 0)
    {
        CursorPosition.X = framebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0)
        {
            CursorPosition.Y = 0;
            CursorPosition.X = 0;
        } 
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
            *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = color;
        }
    }

    CursorPosition.X -= 8;

    if(CursorPosition.X < 0)
    {
        CursorPosition.X = framebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0)
        {
            CursorPosition.Y = 0;
            CursorPosition.X = 0;
        } 
    }
}

void BasicRenderer::ChangeScreenCurserPosition(unsigned int X, unsigned int Y)
{
    this->CursorPosition.X = X;
    this->CursorPosition.Y = Y;
}

void BasicRenderer::PutChar(unsigned int color, char chr, unsigned int xOff, unsigned int yOff)
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

void BasicRenderer::Print(const char** str)
{
    this->Print(0xffffffff, str);
}

void BasicRenderer::Print(unsigned int color, const char** str)
{
    char* chr = (char*)str;
    unsigned int count = 0;
    while(*chr != 0 && count < 1000000000){
        this->PutChar(color, *chr, CursorPosition.X, CursorPosition.Y);
        NextCharSpace();
        chr++;
        count = count + 1;
    }
}

void BasicRenderer::GoToNextLine()
{
    this->CursorPosition.X = 0;
    this->CursorPosition.Y += 16;
}

void BasicRenderer::NextCharSpace()
{
    CursorPosition.X+=8;
    if(CursorPosition.X + 8 > framebuffer->Width)
    {
        CursorPosition.X = 0;
        CursorPosition.Y += 16;
    }
}

void BasicRenderer::PutChar(char chr)
{
    PutChar(0xffffffff ,chr, this->CursorPosition.X, this->CursorPosition.Y);
    NextCharSpace();
}

void BasicRenderer::PutPix(uint32_t x, uint32_t y, uint32_t color)
{
    *(uint32_t*)((uint64_t)framebuffer->BaseAddress + (x * 4) + (y * framebuffer->PixelsPerScanLine * 4)) = color;
}

uint32_t BasicRenderer::GetPix(uint32_t x, uint32_t y)
{
    return *(uint32_t*)((uint64_t)framebuffer->BaseAddress + (x * 4) + (y * framebuffer->PixelsPerScanLine * 4));
}

void BasicRenderer::ClearMouseCursor(uint8_t* mouseCursor, Point position)
{
    if (!mouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = framebuffer->Width - position.X;
    int differenceY = framebuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                if (MouseCursorBufferAfter[x + y * 16] == GetPix(position.X + x, position.Y + y))
                    PutPix(position.X + x, position.Y + y, MouseCursorBuffer[x + y * 16]);
            }
        }
        
    }
}

void BasicRenderer::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color)
{
    int xMax = 16;
    int yMax = 16;
    int differenceX = framebuffer->Width - position.X;
    int differenceY = framebuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;
    for (int y = 0; y < yMax; y++)
    {
        for (int x = 0; x < xMax; x++)
        {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                MouseCursorBuffer[x + y * 16] = GetPix(position.X + x, position.Y + y);
                PutPix(position.X + x, position.Y + y, color);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);
            }
        }
    }
    mouseDrawn = true;
}

void BasicRenderer::testPsf1Font()
{
    PutChar(0xffffffff, '1', 20, 20);
    PutChar(0xffffffff, '2', 20, 40);
    PutChar(0xffffffff, '3', 20, 60);
    PutChar(0xffffffff, '4', 20, 80);
    PutChar(0xffffffff, '5', 20, 100);
    PutChar(0xffffffff, '6', 20, 120);
    PutChar(0xffffffff, '7', 20, 140);
    PutChar(0xffffffff, '8', 20, 180);
    PutChar(0xffffffff, '9', 20, 200);
    PutChar(0xffffffff, '0', 20, 240);
    PutChar(0xffffffff, 'A', 40, 20);
    PutChar(0xffffffff, 'B', 40, 40);
    PutChar(0xffffffff, 'C', 40, 60);
    PutChar(0xffffffff, 'D', 40, 80);
    PutChar(0xffffffff, 'E', 40, 100);
    PutChar(0xffffffff, 'F', 40, 120);
    PutChar(0xffffffff, 'G', 40, 140);
    PutChar(0xffffffff, 'H', 40, 180);
    PutChar(0xffffffff, 'I', 40, 200);
    PutChar(0xffffffff, 'J', 40, 220);
    PutChar(0xffffffff, 'K', 40, 240);
    PutChar(0xffffffff, 'L', 40, 260);
    PutChar(0xffffffff, 'M', 40, 280);
    PutChar(0xffffffff, 'N', 40, 300);
    PutChar(0xffffffff, 'O', 40, 320);
    PutChar(0xffffffff, 'P', 40, 340);
    PutChar(0xffffffff, 'Q', 40, 380);
    PutChar(0xffffffff, 'R', 40, 400);
    PutChar(0xffffffff, 'S', 40, 420);
    PutChar(0xffffffff, 'T', 40, 440);
    PutChar(0xffffffff, 'U', 40, 460);
    PutChar(0xffffffff, 'V', 40, 480);
    PutChar(0xffffffff, 'W', 40, 500);
    PutChar(0xffffffff, 'X', 40, 520);
    PutChar(0xffffffff, 'Y', 40, 540);
    PutChar(0xffffffff, 'Z', 40, 560);
    PutChar(0xffffffff, 'a', 60, 20);
    PutChar(0xffffffff, 'b', 60, 40);
    PutChar(0xffffffff, 'c', 60, 60);
    PutChar(0xffffffff, 'd', 60, 80);
    PutChar(0xffffffff, 'e', 60, 100);
    PutChar(0xffffffff, 'f', 60, 120);
    PutChar(0xffffffff, 'g', 60, 140);
    PutChar(0xffffffff, 'h', 60, 180);
    PutChar(0xffffffff, 'i', 60, 200);
    PutChar(0xffffffff, 'j', 60, 220);
    PutChar(0xffffffff, 'k', 60, 240);
    PutChar(0xffffffff, 'l', 60, 260);
    PutChar(0xffffffff, 'm', 60, 280);
    PutChar(0xffffffff, 'n', 60, 300);
    PutChar(0xffffffff, 'o', 60, 320);
    PutChar(0xffffffff, 'p', 60, 340);
    PutChar(0xffffffff, 'q', 60, 380);
    PutChar(0xffffffff, 'r', 60, 400);
    PutChar(0xffffffff, 's', 60, 420);
    PutChar(0xffffffff, 't', 60, 440);
    PutChar(0xffffffff, 'u', 60, 460);
    PutChar(0xffffffff, 'v', 60, 480);
    PutChar(0xffffffff, 'w', 60, 500);
    PutChar(0xffffffff, 'x', 60, 520);
    PutChar(0xffffffff, 'y', 60, 540);
    PutChar(0xffffffff, 'z', 60, 560);
}