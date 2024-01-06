#include <stdint.h>
#include <limine.h>
#include <nighterm/nighterm.h>

#include "cpu.h"
#include "serial.h"
#include "printf.h"

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, .revision = 0};


void _start(void) {
    struct limine_file* font = mod_request.response->modules[0];
    char *psf2buf = font->address;
    psf2Hdr hdr = *(psf2Hdr *)font->address;
    psf2buf += hdr.headerSize;

    dprintf("\033c");
    hlt();
}
