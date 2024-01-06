static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

static void hlt(void) {
    asm ("hlt");
}