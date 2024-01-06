#include <stdint.h>
#include <limine.h>
#include <nighterm/nighterm.h>

#include "cpu.h"
#include "serial.h"
#include "printf.h"
#include "idt.h"

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, 
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 1
};


void _start(void) {
    dprintf("\033c");

    static struct limine_framebuffer framebuffer_response;
    struct limine_file* font = mod_request.response->modules[0];
    char psf2buf = font->address;
    psf2Hdr hdr = *(psf2Hdr *)font->address;
    psf2buf += hdr.headerSize;

    init_idt();
    dprintf("Initialized IDT\n");

    dprintf("* Loaded %u module(s)\n", mod_request.internal_module_count + 1);
    
    int nstatus = nighterm_initialize(font->address,
                framebuffer_response.address,
                framebuffer_response.width,
                framebuffer_response.height,
                framebuffer_response.pitch,
                framebuffer_response.bpp,
                NULL);

    dprintf("Initialized Nighterm with status: %s", nighterm_get_error_name(nstatus));
    printf("Hello, World!\n");
    hlt();
}
