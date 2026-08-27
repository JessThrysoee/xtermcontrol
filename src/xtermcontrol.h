/****************************************************************************
** Copyright (C) 2002-2025 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#ifndef XTERMCONTROL_H
#define XTERMCONTROL_H

#include <sys/types.h>

enum CTLSEQS_TYPE
{
    CSI,
    GET_CSI,
    OSC,
    GET_OSC,
    ANY
};

/* xterm control sequences are described in ctlseq.ms, which is
   distributed with the xterm source package, obtainable from
   http://dickey.his.com/xterm.
   To read the troff file as plain text, issue
   "nroff -ms -t -c ctlseqs.ms | col -b > ctlseqs.txt"              */

struct controlseq
{
    char *option;
    int ctl1;          /* Ps                                        */
    int ctl2;          /* Ps                                        */
    char *text;        /* Pt                                        */
    int type;          /* CTLSEQS_TYPE                              */
    char *conf_title;  /* used in reports and configuration file    */
    char *synopsis;    /* used in usage                             */
    char *description; /* used in usage and configuration file      */
};

extern struct controlseq ctlseqstab[];

void init_ctlseqstab(void);
void check_term_variable(void);
void csi_print1(int ctl1);
void csi_print2(int ctl1, int ctl2);
void csi_print3(int ctl1, int ctl2, int ctl3);

void osc_print(int ps1, int ps2, char *pt);

void tty_control(void);
void raw_print(char *ctlseq);
ssize_t tty_read(char *output, size_t size);

void set_tty_raw(void);
void set_tty_restore(void);

int get_title(char *title, size_t size, int verbose, int ctl1);
int get_osc(char *osc, size_t size, int verbose, unsigned int option, int ctl1, int ctl2);

void set_geometry(int ctl1, int ctl2, char *geometry);
int get_geometry(char *geometry, size_t size, int verbose, int ctl1, int ctl2);

int configuration_write(const char *filepath);

void usage(int status);
void version(void);

void report_error(const char *synopsis);
void do_exit(int status);

enum OPTION
{
    FG,
    BG,
    COLOR_0,
    COLOR_255 = COLOR_0 + 255,
    COLOR_HL,
    CURSOR,
    MOUSE_FG,
    MOUSE_BG,
    FONT,
    TITLE,
    GEOMETRY,
    GET_FG,
    GET_BG,
    GET_COLOR_0,
    GET_COLOR_255 = GET_COLOR_0 + 255,
    GET_COLOR_HL,
    GET_CURSOR,
    GET_MOUSE_FG,
    GET_MOUSE_BG,
    GET_FONT,
    GET_TITLE,
    GET_GEOMETRY,
    MAXIMIZE,
    RESTORE,
    ICONIFY,
    DE_ICONIFY,
    RAISE,
    LOWER,
    RESET,
    RAW,
    FILE_CONF,
    NSEQ
};

#endif
