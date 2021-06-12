#include "Interrupts.h"
#include "../panic.h"
#include "../IO.h"
#include "../UserInput/Keyboard.h"
#include "../UserInput/Mouse.h"

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame)
{
    Panic((const char**)&"Ouch, I just stepped on a page fault.");
    while(true);
}

__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame)
{
    Panic((const char**)&"No way!!! A double fault out in thw wild? ");
    while(true);
}

__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame* frame)
{
    Panic((const char**)&"HOLT, You have violated the General Protection law.");
    while(true);
}

__attribute__((interrupt)) void Keyboard_Handler(struct interrupt_frame* frame)
{
    uint8_t scancode = inb(0x60);
    HandleKeyboard(scancode);
    PIC_EndPrimary();
}

__attribute__((interrupt)) void Mouse_Handler(struct interrupt_frame* frame)
{
    uint8_t mouseData = inb(0x60);

    HandlePS2Mouse(mouseData);

    //GBR->PutChar('m');

    PIC_EndSecondary();
}

void RemapPIC()
{
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
}

void PIC_EndPrimary()
{
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSecondary()
{
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}