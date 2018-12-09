/****************************************************************************
** $Id: xtermcontrol.h,v 1.13 2002/08/01 21:54:17 jet Exp $
**
** Copyright (C) 2002-2013 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#ifndef XTERMCONTROL_H
#define XTERMCONTROL_H

#define NSEQ (sizeof ctlseqstab / sizeof ctlseqstab[0])

enum CTLSEQS_TYPE
{
    CSI,
    GET_CSI,
    OSC,
    GET_OSC,
    ANY
};

enum OPTIONS
{
    FG,
    BG,
    COLOR_0,
    COLOR_1,
    COLOR_2,
    COLOR_3,
    COLOR_4,
    COLOR_5,
    COLOR_6,
    COLOR_7,
    COLOR_8,
    COLOR_9,
    COLOR_10,
    COLOR_11,
    COLOR_12,
    COLOR_13,
    COLOR_14,
    COLOR_15,
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
    GET_COLOR_1,
    GET_COLOR_2,
    GET_COLOR_3,
    GET_COLOR_4,
    GET_COLOR_5,
    GET_COLOR_6,
    GET_COLOR_7,
    GET_COLOR_8,
    GET_COLOR_9,
    GET_COLOR_10,
    GET_COLOR_11,
    GET_COLOR_12,
    GET_COLOR_13,
    GET_COLOR_14,
    GET_COLOR_15,
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
    FILE_CONF
};

/* xterm control sequences are described in ctlseq.ms, which is
   distributed with the xterm source package, obtainable from
   http://dickey.his.com/xterm.
   To read the troff file as plain text, issue
   "nroff -ms -t -c ctlseqs.ms | col -b > ctlseqs.txt"              */

struct controlseqs
{
    int ctl1;          /* Ps                                        */
    int ctl2;          /* Ps                                        */
    char *text;        /* Pt                                        */
    int type;          /* CTLSEQS_TYPE                              */
    char *conf_title;  /* used in reports and configuration file    */
    char *synopsis;    /* used in usage                             */
    char *description; /* used in usage and configuration file      */
};

void check_term_variable(void);
void csi_print1(int ctl1);
void csi_print2(int ctl1, int ctl2);
void csi_print3(int ctl1, int ctl2, int ctl3);

void osc_print(int ps1, int ps2, char *pt);

void tty_control(void);
char *ctty_path(void);
void raw_print(char *ctlseq);
ssize_t tty_read(char *output, size_t size);

char *tmux_dcs_passthrough(char *ctlseq);
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

#endif
