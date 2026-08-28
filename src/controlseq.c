/****************************************************************************
** Copyright (C) 2002-2026 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#include <stdio.h>

#include "xtermcontrol.h"

struct controlseq ctlseqstab[NSEQ];

static char color_names[256][16];
static char get_color_names[256][16];

static void set(int i, char *option, int ctl1, int ctl2, int type, char *conf_title, char *synopsis, char *description)
{
    ctlseqstab[i].option = option;
    ctlseqstab[i].ctl1 = ctl1;
    ctlseqstab[i].ctl2 = ctl2;
    ctlseqstab[i].text = NULL;
    ctlseqstab[i].type = type;
    ctlseqstab[i].conf_title = conf_title;
    ctlseqstab[i].synopsis = synopsis;
    ctlseqstab[i].description = description;
}

void init_ctlseqstab(void)
{
    int i;

    set(FG, "fg", 10, 0, OSC, "foreground", "--fg=COLOR", "set foreground color");
    set(BG, "bg", 11, 0, OSC, "background", "--bg=COLOR", "set background color");

    for (i = 0; i < 256; i++)
    {
        snprintf(color_names[i], sizeof(color_names[i]), "color%d", i);
        snprintf(get_color_names[i], sizeof(get_color_names[i]), "get-color%d", i);
        set(COLOR_0 + i, color_names[i], 4, i, OSC, color_names[i], NULL, NULL);
        set(GET_COLOR_0 + i, get_color_names[i], 4, i, GET_OSC, color_names[i], NULL, NULL);
    }
    ctlseqstab[COLOR_0].synopsis = "--colorN=COLOR";
    ctlseqstab[COLOR_0].description = "set N'th [0-255] color, e.g. --color88=COLOR";
    ctlseqstab[GET_COLOR_0].synopsis = "--get-colorN";
    ctlseqstab[GET_COLOR_0].description = "report N'th [0-255] color, e.g --get-color88";

    set(COLOR_HL, "highlight", 17, 0, OSC, "highlight", "--highlight=COLOR", "set highlight color");
    set(CURSOR, "cursor", 12, 0, OSC, "cursor", "--cursor=COLOR", "set cursor color");
    set(MOUSE_FG, "mouse-fg", 13, 0, OSC, "mouse-foreground", "--mouse-fg=COLOR", "set mouse pointer foreground color");
    set(MOUSE_BG, "mouse-bg", 14, 0, OSC, "mouse-background", "--mouse-bg=COLOR", "set mouse pointer background color");
    set(FONT, "font", 50, 0, OSC, "font", "--font=FONT", "set font");
    set(TITLE, "title", 0, 0, OSC, "title", "--title=STRING", "set window title");
    set(GEOMETRY, "geometry", 8, 3, CSI, "geometry", "--geometry=WIDTHxHEIGHT+XOFF+YOFF", "set size and/or position");

    set(GET_FG, "get-fg", 10, 0, GET_OSC, "foreground", "--get-fg", "report foreground color");
    set(GET_BG, "get-bg", 11, 0, GET_OSC, "background", "--get-bg", "report background color");
    set(GET_COLOR_HL, "get-highlight", 17, 0, GET_OSC, "highlight", "--get-highlight", "report highlight color");
    set(GET_CURSOR, "get-cursor", 12, 0, GET_OSC, "cursor", "--get-cursor", "report cursor color");
    set(GET_MOUSE_FG, "get-mouse-fg", 13, 0, GET_OSC, "mouse-foreground", "--get-mouse-fg", "report mouse pointer foreground color");
    set(GET_MOUSE_BG, "get-mouse-bg", 14, 0, GET_OSC, "mouse-background", "--get-mouse-bg", "report mouse pointer background color");
    set(GET_FONT, "get-font", 50, 0, GET_OSC, "font", "--get-font", "report font");
    set(GET_TITLE, "get-title", 21, 0, GET_CSI, "title", "--get-title", "report window title");
    set(GET_GEOMETRY, "get-geometry", 18, 13, GET_CSI, "geometry", "--get-geometry", "report size and position");

    set(MAXIMIZE, "maximize", 9, 1, CSI, NULL, "--maximize", "maximize window");
    set(RESTORE, "restore", 9, 0, CSI, NULL, "--restore", "restore maximized window");
    set(ICONIFY, "iconify", 2, 0, CSI, NULL, "--iconify", "iconify window");
    set(DE_ICONIFY, "de-iconify", 1, 0, CSI, NULL, "--de-iconify", "de-iconify window");
    set(RAISE, "raise", 5, 0, CSI, NULL, "--raise", "raise window");
    set(LOWER, "lower", 6, 0, CSI, NULL, "--lower", "lower window");
    set(RESET, "reset", 0, 0, ANY, NULL, "--reset", "full reset");
    set(RAW, "raw", 0, 0, ANY, NULL, "--raw=CTLSEQS", "issue raw control sequence");
    set(FILE_CONF, "file", 0, 0, ANY, NULL, "--file=FILE", "alternative configuration file");
}
