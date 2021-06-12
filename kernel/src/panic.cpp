#include "panic.h"
#include "BasicRenderer.h"

void Panic(const char** panicMessage)
{
    GBR->Clear(0x00004584);
    GBR->ChangeScreenCurserPosition(100, 100);
    GBR->Print(panicMessage);
}