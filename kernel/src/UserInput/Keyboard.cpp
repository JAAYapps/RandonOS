#include "Keyboard.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;
void HandleKeyboard(uint8_t scancode)
{
    switch (scancode)
    {
    case LeftShift:
        isLeftShiftPressed = true;
        return;
    case LeftShift + 0x80:
        isLeftShiftPressed = false;
        return;
    case RightShift:
        isRightShiftPressed = true;
        return;
    case RightShift + 0x80:
        isRightShiftPressed = false;
        return;
    case Enter:
        GBR->GoToNextLine();
        return;
    case Spacebar:
        GBR->PutChar(' ');
        return;
    case BackSpace:
        GBR->ClearChar(0x00000000);
        return;
    }



    char ascii = Keyboards::QWERTYKeyboard::Translate(scancode, isLeftShiftPressed || isRightShiftPressed);

    if (ascii != 0)
        GBR->PutChar(ascii);
}