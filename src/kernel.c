#include <stdint.h>
#include <limine.h>
#include <nighterm/nighterm.h>

#include "cpu.h"
#include "serial.h"
#include "printf.h"

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, 
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 1
};


void _start(void) {
    static struct limine_framebuffer framebuffer_response;
    struct limine_file* font = mod_request.response->modules[0];
    char *psf2buf = font->address;
    psf2Hdr hdr = *(psf2Hdr *)font->address;
    psf2buf += hdr.headerSize;

    dprintf("\033c");
    nighterm_initialize(font->address,
                framebuffer_request.response->framebuffers[0]->address,
                framebuffer_request.response->framebuffers[0]->width,
                framebuffer_request.response->framebuffers[0]->height,
                framebuffer_request.response->framebuffers[0]->pitch,
                framebuffer_request.response->framebuffers[0]->bpp,
                NULL);
    printf("Hello, World!");
    hlt();
}
