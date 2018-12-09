/****************************************************************************
** $Id: xtermcontrol.c,v 1.33 2002/10/26 17:20:36 jet Exp $
**
** Copyright (C) 2002-2013 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#include <config.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "configuration.h"
#include "controlseq.h"
#include "getopt.h"
#include "xtermcontrol.h"

/* The name the program was run with, stripped of any leading path. */
static char *program_name;

static char temp[BUFSIZ];

/* controlling terminal fps and descriptor */
static FILE *ctty;
static FILE *tty_in;
static FILE *tty_out;
static int TTY_FILENO;

/* termios settings */
static struct termios tty_ts;
static struct termios tty_ts_orig;
static struct termios *tty_ts_orig_pt = NULL;

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int main(int argc, char **argv)
{
    unsigned i;
    int c,
        ctl1,
        ctl2,
        type;
    int has_options = 0;
    int force = 0;
    int verbose = 0;
    int configuration_missing = 0;
    char *text = NULL;
    char configuration_file[BUFSIZ];

    configuration list;              /* configuration linked list                 */
    const configuration_element *lp; /* configuration linked list element     */

    program_name = argv[0];
    if (program_name && strrchr(program_name, '/'))
    {
        program_name = strrchr(program_name, '/') + 1;
    }

    configuration_file[0] = '\0';

    while (1)
    {
        static int a = -1;
        int longindex = 0;

        static struct option longopts[] =
            {
                {"fg", 1, &a, FG},
                {"bg", 1, &a, BG},
                {"color0", 1, &a, COLOR_0},
                {"color1", 1, &a, COLOR_1},
                {"color2", 1, &a, COLOR_2},
                {"color3", 1, &a, COLOR_3},
                {"color4", 1, &a, COLOR_4},
                {"color5", 1, &a, COLOR_5},
                {"color6", 1, &a, COLOR_6},
                {"color7", 1, &a, COLOR_7},
                {"color8", 1, &a, COLOR_8},
                {"color9", 1, &a, COLOR_9},
                {"color10", 1, &a, COLOR_10},
                {"color11", 1, &a, COLOR_11},
                {"color12", 1, &a, COLOR_12},
                {"color13", 1, &a, COLOR_13},
                {"color14", 1, &a, COLOR_14},
                {"color15", 1, &a, COLOR_15},
                {"color16", 1, &a, COLOR_16},
                {"color17", 1, &a, COLOR_17},
                {"color18", 1, &a, COLOR_18},
                {"color19", 1, &a, COLOR_19},
                {"color20", 1, &a, COLOR_20},
                {"color21", 1, &a, COLOR_21},
                {"color22", 1, &a, COLOR_22},
                {"color23", 1, &a, COLOR_23},
                {"color24", 1, &a, COLOR_24},
                {"color25", 1, &a, COLOR_25},
                {"color26", 1, &a, COLOR_26},
                {"color27", 1, &a, COLOR_27},
                {"color28", 1, &a, COLOR_28},
                {"color29", 1, &a, COLOR_29},
                {"color30", 1, &a, COLOR_30},
                {"color31", 1, &a, COLOR_31},
                {"color32", 1, &a, COLOR_32},
                {"color33", 1, &a, COLOR_33},
                {"color34", 1, &a, COLOR_34},
                {"color35", 1, &a, COLOR_35},
                {"color36", 1, &a, COLOR_36},
                {"color37", 1, &a, COLOR_37},
                {"color38", 1, &a, COLOR_38},
                {"color39", 1, &a, COLOR_39},
                {"color40", 1, &a, COLOR_40},
                {"color41", 1, &a, COLOR_41},
                {"color42", 1, &a, COLOR_42},
                {"color43", 1, &a, COLOR_43},
                {"color44", 1, &a, COLOR_44},
                {"color45", 1, &a, COLOR_45},
                {"color46", 1, &a, COLOR_46},
                {"color47", 1, &a, COLOR_47},
                {"color48", 1, &a, COLOR_48},
                {"color49", 1, &a, COLOR_49},
                {"color50", 1, &a, COLOR_50},
                {"color51", 1, &a, COLOR_51},
                {"color52", 1, &a, COLOR_52},
                {"color53", 1, &a, COLOR_53},
                {"color54", 1, &a, COLOR_54},
                {"color55", 1, &a, COLOR_55},
                {"color56", 1, &a, COLOR_56},
                {"color57", 1, &a, COLOR_57},
                {"color58", 1, &a, COLOR_58},
                {"color59", 1, &a, COLOR_59},
                {"color60", 1, &a, COLOR_60},
                {"color61", 1, &a, COLOR_61},
                {"color62", 1, &a, COLOR_62},
                {"color63", 1, &a, COLOR_63},
                {"color64", 1, &a, COLOR_64},
                {"color65", 1, &a, COLOR_65},
                {"color66", 1, &a, COLOR_66},
                {"color67", 1, &a, COLOR_67},
                {"color68", 1, &a, COLOR_68},
                {"color69", 1, &a, COLOR_69},
                {"color70", 1, &a, COLOR_70},
                {"color71", 1, &a, COLOR_71},
                {"color72", 1, &a, COLOR_72},
                {"color73", 1, &a, COLOR_73},
                {"color74", 1, &a, COLOR_74},
                {"color75", 1, &a, COLOR_75},
                {"color76", 1, &a, COLOR_76},
                {"color77", 1, &a, COLOR_77},
                {"color78", 1, &a, COLOR_78},
                {"color79", 1, &a, COLOR_79},
                {"color80", 1, &a, COLOR_80},
                {"color81", 1, &a, COLOR_81},
                {"color82", 1, &a, COLOR_82},
                {"color83", 1, &a, COLOR_83},
                {"color84", 1, &a, COLOR_84},
                {"color85", 1, &a, COLOR_85},
                {"color86", 1, &a, COLOR_86},
                {"color87", 1, &a, COLOR_87},
                {"color88", 1, &a, COLOR_88},
                {"color89", 1, &a, COLOR_89},
                {"color90", 1, &a, COLOR_90},
                {"color91", 1, &a, COLOR_91},
                {"color92", 1, &a, COLOR_92},
                {"color93", 1, &a, COLOR_93},
                {"color94", 1, &a, COLOR_94},
                {"color95", 1, &a, COLOR_95},
                {"color96", 1, &a, COLOR_96},
                {"color97", 1, &a, COLOR_97},
                {"color98", 1, &a, COLOR_98},
                {"color99", 1, &a, COLOR_99},
                {"color100", 1, &a, COLOR_100},
                {"color101", 1, &a, COLOR_101},
                {"color102", 1, &a, COLOR_102},
                {"color103", 1, &a, COLOR_103},
                {"color104", 1, &a, COLOR_104},
                {"color105", 1, &a, COLOR_105},
                {"color106", 1, &a, COLOR_106},
                {"color107", 1, &a, COLOR_107},
                {"color108", 1, &a, COLOR_108},
                {"color109", 1, &a, COLOR_109},
                {"color110", 1, &a, COLOR_110},
                {"color111", 1, &a, COLOR_111},
                {"color112", 1, &a, COLOR_112},
                {"color113", 1, &a, COLOR_113},
                {"color114", 1, &a, COLOR_114},
                {"color115", 1, &a, COLOR_115},
                {"color116", 1, &a, COLOR_116},
                {"color117", 1, &a, COLOR_117},
                {"color118", 1, &a, COLOR_118},
                {"color119", 1, &a, COLOR_119},
                {"color120", 1, &a, COLOR_120},
                {"color121", 1, &a, COLOR_121},
                {"color122", 1, &a, COLOR_122},
                {"color123", 1, &a, COLOR_123},
                {"color124", 1, &a, COLOR_124},
                {"color125", 1, &a, COLOR_125},
                {"color126", 1, &a, COLOR_126},
                {"color127", 1, &a, COLOR_127},
                {"color128", 1, &a, COLOR_128},
                {"color129", 1, &a, COLOR_129},
                {"color130", 1, &a, COLOR_130},
                {"color131", 1, &a, COLOR_131},
                {"color132", 1, &a, COLOR_132},
                {"color133", 1, &a, COLOR_133},
                {"color134", 1, &a, COLOR_134},
                {"color135", 1, &a, COLOR_135},
                {"color136", 1, &a, COLOR_136},
                {"color137", 1, &a, COLOR_137},
                {"color138", 1, &a, COLOR_138},
                {"color139", 1, &a, COLOR_139},
                {"color140", 1, &a, COLOR_140},
                {"color141", 1, &a, COLOR_141},
                {"color142", 1, &a, COLOR_142},
                {"color143", 1, &a, COLOR_143},
                {"color144", 1, &a, COLOR_144},
                {"color145", 1, &a, COLOR_145},
                {"color146", 1, &a, COLOR_146},
                {"color147", 1, &a, COLOR_147},
                {"color148", 1, &a, COLOR_148},
                {"color149", 1, &a, COLOR_149},
                {"color150", 1, &a, COLOR_150},
                {"color151", 1, &a, COLOR_151},
                {"color152", 1, &a, COLOR_152},
                {"color153", 1, &a, COLOR_153},
                {"color154", 1, &a, COLOR_154},
                {"color155", 1, &a, COLOR_155},
                {"color156", 1, &a, COLOR_156},
                {"color157", 1, &a, COLOR_157},
                {"color158", 1, &a, COLOR_158},
                {"color159", 1, &a, COLOR_159},
                {"color160", 1, &a, COLOR_160},
                {"color161", 1, &a, COLOR_161},
                {"color162", 1, &a, COLOR_162},
                {"color163", 1, &a, COLOR_163},
                {"color164", 1, &a, COLOR_164},
                {"color165", 1, &a, COLOR_165},
                {"color166", 1, &a, COLOR_166},
                {"color167", 1, &a, COLOR_167},
                {"color168", 1, &a, COLOR_168},
                {"color169", 1, &a, COLOR_169},
                {"color170", 1, &a, COLOR_170},
                {"color171", 1, &a, COLOR_171},
                {"color172", 1, &a, COLOR_172},
                {"color173", 1, &a, COLOR_173},
                {"color174", 1, &a, COLOR_174},
                {"color175", 1, &a, COLOR_175},
                {"color176", 1, &a, COLOR_176},
                {"color177", 1, &a, COLOR_177},
                {"color178", 1, &a, COLOR_178},
                {"color179", 1, &a, COLOR_179},
                {"color180", 1, &a, COLOR_180},
                {"color181", 1, &a, COLOR_181},
                {"color182", 1, &a, COLOR_182},
                {"color183", 1, &a, COLOR_183},
                {"color184", 1, &a, COLOR_184},
                {"color185", 1, &a, COLOR_185},
                {"color186", 1, &a, COLOR_186},
                {"color187", 1, &a, COLOR_187},
                {"color188", 1, &a, COLOR_188},
                {"color189", 1, &a, COLOR_189},
                {"color190", 1, &a, COLOR_190},
                {"color191", 1, &a, COLOR_191},
                {"color192", 1, &a, COLOR_192},
                {"color193", 1, &a, COLOR_193},
                {"color194", 1, &a, COLOR_194},
                {"color195", 1, &a, COLOR_195},
                {"color196", 1, &a, COLOR_196},
                {"color197", 1, &a, COLOR_197},
                {"color198", 1, &a, COLOR_198},
                {"color199", 1, &a, COLOR_199},
                {"color200", 1, &a, COLOR_200},
                {"color201", 1, &a, COLOR_201},
                {"color202", 1, &a, COLOR_202},
                {"color203", 1, &a, COLOR_203},
                {"color204", 1, &a, COLOR_204},
                {"color205", 1, &a, COLOR_205},
                {"color206", 1, &a, COLOR_206},
                {"color207", 1, &a, COLOR_207},
                {"color208", 1, &a, COLOR_208},
                {"color209", 1, &a, COLOR_209},
                {"color210", 1, &a, COLOR_210},
                {"color211", 1, &a, COLOR_211},
                {"color212", 1, &a, COLOR_212},
                {"color213", 1, &a, COLOR_213},
                {"color214", 1, &a, COLOR_214},
                {"color215", 1, &a, COLOR_215},
                {"color216", 1, &a, COLOR_216},
                {"color217", 1, &a, COLOR_217},
                {"color218", 1, &a, COLOR_218},
                {"color219", 1, &a, COLOR_219},
                {"color220", 1, &a, COLOR_220},
                {"color221", 1, &a, COLOR_221},
                {"color222", 1, &a, COLOR_222},
                {"color223", 1, &a, COLOR_223},
                {"color224", 1, &a, COLOR_224},
                {"color225", 1, &a, COLOR_225},
                {"color226", 1, &a, COLOR_226},
                {"color227", 1, &a, COLOR_227},
                {"color228", 1, &a, COLOR_228},
                {"color229", 1, &a, COLOR_229},
                {"color230", 1, &a, COLOR_230},
                {"color231", 1, &a, COLOR_231},
                {"color232", 1, &a, COLOR_232},
                {"color233", 1, &a, COLOR_233},
                {"color234", 1, &a, COLOR_234},
                {"color235", 1, &a, COLOR_235},
                {"color236", 1, &a, COLOR_236},
                {"color237", 1, &a, COLOR_237},
                {"color238", 1, &a, COLOR_238},
                {"color239", 1, &a, COLOR_239},
                {"color240", 1, &a, COLOR_240},
                {"color241", 1, &a, COLOR_241},
                {"color242", 1, &a, COLOR_242},
                {"color243", 1, &a, COLOR_243},
                {"color244", 1, &a, COLOR_244},
                {"color245", 1, &a, COLOR_245},
                {"color246", 1, &a, COLOR_246},
                {"color247", 1, &a, COLOR_247},
                {"color248", 1, &a, COLOR_248},
                {"color249", 1, &a, COLOR_249},
                {"color250", 1, &a, COLOR_250},
                {"color251", 1, &a, COLOR_251},
                {"color252", 1, &a, COLOR_252},
                {"color253", 1, &a, COLOR_253},
                {"color254", 1, &a, COLOR_254},
                {"color255", 1, &a, COLOR_255},
                {"highlight", 1, &a, COLOR_HL},
                {"cursor", 1, &a, CURSOR},
                {"mouse-fg", 1, &a, MOUSE_FG},
                {"mouse-bg", 1, &a, MOUSE_BG},
                {"font", 1, &a, FONT},
                {"title", 1, &a, TITLE},
                {"geometry", 1, &a, GEOMETRY},
                {"get-fg", 0, &a, GET_FG},
                {"get-bg", 0, &a, GET_BG},
                {"get-color0", 0, &a, GET_COLOR_0},
                {"get-color1", 0, &a, GET_COLOR_1},
                {"get-color2", 0, &a, GET_COLOR_2},
                {"get-color3", 0, &a, GET_COLOR_3},
                {"get-color4", 0, &a, GET_COLOR_4},
                {"get-color5", 0, &a, GET_COLOR_5},
                {"get-color6", 0, &a, GET_COLOR_6},
                {"get-color7", 0, &a, GET_COLOR_7},
                {"get-color8", 0, &a, GET_COLOR_8},
                {"get-color9", 0, &a, GET_COLOR_9},
                {"get-color10", 0, &a, GET_COLOR_10},
                {"get-color11", 0, &a, GET_COLOR_11},
                {"get-color12", 0, &a, GET_COLOR_12},
                {"get-color13", 0, &a, GET_COLOR_13},
                {"get-color14", 0, &a, GET_COLOR_14},
                {"get-color15", 0, &a, GET_COLOR_15},
                {"get-color16", 0, &a, GET_COLOR_16},
                {"get-color17", 0, &a, GET_COLOR_17},
                {"get-color18", 0, &a, GET_COLOR_18},
                {"get-color19", 0, &a, GET_COLOR_19},
                {"get-color20", 0, &a, GET_COLOR_20},
                {"get-color21", 0, &a, GET_COLOR_21},
                {"get-color22", 0, &a, GET_COLOR_22},
                {"get-color23", 0, &a, GET_COLOR_23},
                {"get-color24", 0, &a, GET_COLOR_24},
                {"get-color25", 0, &a, GET_COLOR_25},
                {"get-color26", 0, &a, GET_COLOR_26},
                {"get-color27", 0, &a, GET_COLOR_27},
                {"get-color28", 0, &a, GET_COLOR_28},
                {"get-color29", 0, &a, GET_COLOR_29},
                {"get-color30", 0, &a, GET_COLOR_30},
                {"get-color31", 0, &a, GET_COLOR_31},
                {"get-color32", 0, &a, GET_COLOR_32},
                {"get-color33", 0, &a, GET_COLOR_33},
                {"get-color34", 0, &a, GET_COLOR_34},
                {"get-color35", 0, &a, GET_COLOR_35},
                {"get-color36", 0, &a, GET_COLOR_36},
                {"get-color37", 0, &a, GET_COLOR_37},
                {"get-color38", 0, &a, GET_COLOR_38},
                {"get-color39", 0, &a, GET_COLOR_39},
                {"get-color40", 0, &a, GET_COLOR_40},
                {"get-color41", 0, &a, GET_COLOR_41},
                {"get-color42", 0, &a, GET_COLOR_42},
                {"get-color43", 0, &a, GET_COLOR_43},
                {"get-color44", 0, &a, GET_COLOR_44},
                {"get-color45", 0, &a, GET_COLOR_45},
                {"get-color46", 0, &a, GET_COLOR_46},
                {"get-color47", 0, &a, GET_COLOR_47},
                {"get-color48", 0, &a, GET_COLOR_48},
                {"get-color49", 0, &a, GET_COLOR_49},
                {"get-color50", 0, &a, GET_COLOR_50},
                {"get-color51", 0, &a, GET_COLOR_51},
                {"get-color52", 0, &a, GET_COLOR_52},
                {"get-color53", 0, &a, GET_COLOR_53},
                {"get-color54", 0, &a, GET_COLOR_54},
                {"get-color55", 0, &a, GET_COLOR_55},
                {"get-color56", 0, &a, GET_COLOR_56},
                {"get-color57", 0, &a, GET_COLOR_57},
                {"get-color58", 0, &a, GET_COLOR_58},
                {"get-color59", 0, &a, GET_COLOR_59},
                {"get-color60", 0, &a, GET_COLOR_60},
                {"get-color61", 0, &a, GET_COLOR_61},
                {"get-color62", 0, &a, GET_COLOR_62},
                {"get-color63", 0, &a, GET_COLOR_63},
                {"get-color64", 0, &a, GET_COLOR_64},
                {"get-color65", 0, &a, GET_COLOR_65},
                {"get-color66", 0, &a, GET_COLOR_66},
                {"get-color67", 0, &a, GET_COLOR_67},
                {"get-color68", 0, &a, GET_COLOR_68},
                {"get-color69", 0, &a, GET_COLOR_69},
                {"get-color70", 0, &a, GET_COLOR_70},
                {"get-color71", 0, &a, GET_COLOR_71},
                {"get-color72", 0, &a, GET_COLOR_72},
                {"get-color73", 0, &a, GET_COLOR_73},
                {"get-color74", 0, &a, GET_COLOR_74},
                {"get-color75", 0, &a, GET_COLOR_75},
                {"get-color76", 0, &a, GET_COLOR_76},
                {"get-color77", 0, &a, GET_COLOR_77},
                {"get-color78", 0, &a, GET_COLOR_78},
                {"get-color79", 0, &a, GET_COLOR_79},
                {"get-color80", 0, &a, GET_COLOR_80},
                {"get-color81", 0, &a, GET_COLOR_81},
                {"get-color82", 0, &a, GET_COLOR_82},
                {"get-color83", 0, &a, GET_COLOR_83},
                {"get-color84", 0, &a, GET_COLOR_84},
                {"get-color85", 0, &a, GET_COLOR_85},
                {"get-color86", 0, &a, GET_COLOR_86},
                {"get-color87", 0, &a, GET_COLOR_87},
                {"get-color88", 0, &a, GET_COLOR_88},
                {"get-color89", 0, &a, GET_COLOR_89},
                {"get-color90", 0, &a, GET_COLOR_90},
                {"get-color91", 0, &a, GET_COLOR_91},
                {"get-color92", 0, &a, GET_COLOR_92},
                {"get-color93", 0, &a, GET_COLOR_93},
                {"get-color94", 0, &a, GET_COLOR_94},
                {"get-color95", 0, &a, GET_COLOR_95},
                {"get-color96", 0, &a, GET_COLOR_96},
                {"get-color97", 0, &a, GET_COLOR_97},
                {"get-color98", 0, &a, GET_COLOR_98},
                {"get-color99", 0, &a, GET_COLOR_99},
                {"get-color100", 0, &a, GET_COLOR_100},
                {"get-color101", 0, &a, GET_COLOR_101},
                {"get-color102", 0, &a, GET_COLOR_102},
                {"get-color103", 0, &a, GET_COLOR_103},
                {"get-color104", 0, &a, GET_COLOR_104},
                {"get-color105", 0, &a, GET_COLOR_105},
                {"get-color106", 0, &a, GET_COLOR_106},
                {"get-color107", 0, &a, GET_COLOR_107},
                {"get-color108", 0, &a, GET_COLOR_108},
                {"get-color109", 0, &a, GET_COLOR_109},
                {"get-color110", 0, &a, GET_COLOR_110},
                {"get-color111", 0, &a, GET_COLOR_111},
                {"get-color112", 0, &a, GET_COLOR_112},
                {"get-color113", 0, &a, GET_COLOR_113},
                {"get-color114", 0, &a, GET_COLOR_114},
                {"get-color115", 0, &a, GET_COLOR_115},
                {"get-color116", 0, &a, GET_COLOR_116},
                {"get-color117", 0, &a, GET_COLOR_117},
                {"get-color118", 0, &a, GET_COLOR_118},
                {"get-color119", 0, &a, GET_COLOR_119},
                {"get-color120", 0, &a, GET_COLOR_120},
                {"get-color121", 0, &a, GET_COLOR_121},
                {"get-color122", 0, &a, GET_COLOR_122},
                {"get-color123", 0, &a, GET_COLOR_123},
                {"get-color124", 0, &a, GET_COLOR_124},
                {"get-color125", 0, &a, GET_COLOR_125},
                {"get-color126", 0, &a, GET_COLOR_126},
                {"get-color127", 0, &a, GET_COLOR_127},
                {"get-color128", 0, &a, GET_COLOR_128},
                {"get-color129", 0, &a, GET_COLOR_129},
                {"get-color130", 0, &a, GET_COLOR_130},
                {"get-color131", 0, &a, GET_COLOR_131},
                {"get-color132", 0, &a, GET_COLOR_132},
                {"get-color133", 0, &a, GET_COLOR_133},
                {"get-color134", 0, &a, GET_COLOR_134},
                {"get-color135", 0, &a, GET_COLOR_135},
                {"get-color136", 0, &a, GET_COLOR_136},
                {"get-color137", 0, &a, GET_COLOR_137},
                {"get-color138", 0, &a, GET_COLOR_138},
                {"get-color139", 0, &a, GET_COLOR_139},
                {"get-color140", 0, &a, GET_COLOR_140},
                {"get-color141", 0, &a, GET_COLOR_141},
                {"get-color142", 0, &a, GET_COLOR_142},
                {"get-color143", 0, &a, GET_COLOR_143},
                {"get-color144", 0, &a, GET_COLOR_144},
                {"get-color145", 0, &a, GET_COLOR_145},
                {"get-color146", 0, &a, GET_COLOR_146},
                {"get-color147", 0, &a, GET_COLOR_147},
                {"get-color148", 0, &a, GET_COLOR_148},
                {"get-color149", 0, &a, GET_COLOR_149},
                {"get-color150", 0, &a, GET_COLOR_150},
                {"get-color151", 0, &a, GET_COLOR_151},
                {"get-color152", 0, &a, GET_COLOR_152},
                {"get-color153", 0, &a, GET_COLOR_153},
                {"get-color154", 0, &a, GET_COLOR_154},
                {"get-color155", 0, &a, GET_COLOR_155},
                {"get-color156", 0, &a, GET_COLOR_156},
                {"get-color157", 0, &a, GET_COLOR_157},
                {"get-color158", 0, &a, GET_COLOR_158},
                {"get-color159", 0, &a, GET_COLOR_159},
                {"get-color160", 0, &a, GET_COLOR_160},
                {"get-color161", 0, &a, GET_COLOR_161},
                {"get-color162", 0, &a, GET_COLOR_162},
                {"get-color163", 0, &a, GET_COLOR_163},
                {"get-color164", 0, &a, GET_COLOR_164},
                {"get-color165", 0, &a, GET_COLOR_165},
                {"get-color166", 0, &a, GET_COLOR_166},
                {"get-color167", 0, &a, GET_COLOR_167},
                {"get-color168", 0, &a, GET_COLOR_168},
                {"get-color169", 0, &a, GET_COLOR_169},
                {"get-color170", 0, &a, GET_COLOR_170},
                {"get-color171", 0, &a, GET_COLOR_171},
                {"get-color172", 0, &a, GET_COLOR_172},
                {"get-color173", 0, &a, GET_COLOR_173},
                {"get-color174", 0, &a, GET_COLOR_174},
                {"get-color175", 0, &a, GET_COLOR_175},
                {"get-color176", 0, &a, GET_COLOR_176},
                {"get-color177", 0, &a, GET_COLOR_177},
                {"get-color178", 0, &a, GET_COLOR_178},
                {"get-color179", 0, &a, GET_COLOR_179},
                {"get-color180", 0, &a, GET_COLOR_180},
                {"get-color181", 0, &a, GET_COLOR_181},
                {"get-color182", 0, &a, GET_COLOR_182},
                {"get-color183", 0, &a, GET_COLOR_183},
                {"get-color184", 0, &a, GET_COLOR_184},
                {"get-color185", 0, &a, GET_COLOR_185},
                {"get-color186", 0, &a, GET_COLOR_186},
                {"get-color187", 0, &a, GET_COLOR_187},
                {"get-color188", 0, &a, GET_COLOR_188},
                {"get-color189", 0, &a, GET_COLOR_189},
                {"get-color190", 0, &a, GET_COLOR_190},
                {"get-color191", 0, &a, GET_COLOR_191},
                {"get-color192", 0, &a, GET_COLOR_192},
                {"get-color193", 0, &a, GET_COLOR_193},
                {"get-color194", 0, &a, GET_COLOR_194},
                {"get-color195", 0, &a, GET_COLOR_195},
                {"get-color196", 0, &a, GET_COLOR_196},
                {"get-color197", 0, &a, GET_COLOR_197},
                {"get-color198", 0, &a, GET_COLOR_198},
                {"get-color199", 0, &a, GET_COLOR_199},
                {"get-color200", 0, &a, GET_COLOR_200},
                {"get-color201", 0, &a, GET_COLOR_201},
                {"get-color202", 0, &a, GET_COLOR_202},
                {"get-color203", 0, &a, GET_COLOR_203},
                {"get-color204", 0, &a, GET_COLOR_204},
                {"get-color205", 0, &a, GET_COLOR_205},
                {"get-color206", 0, &a, GET_COLOR_206},
                {"get-color207", 0, &a, GET_COLOR_207},
                {"get-color208", 0, &a, GET_COLOR_208},
                {"get-color209", 0, &a, GET_COLOR_209},
                {"get-color210", 0, &a, GET_COLOR_210},
                {"get-color211", 0, &a, GET_COLOR_211},
                {"get-color212", 0, &a, GET_COLOR_212},
                {"get-color213", 0, &a, GET_COLOR_213},
                {"get-color214", 0, &a, GET_COLOR_214},
                {"get-color215", 0, &a, GET_COLOR_215},
                {"get-color216", 0, &a, GET_COLOR_216},
                {"get-color217", 0, &a, GET_COLOR_217},
                {"get-color218", 0, &a, GET_COLOR_218},
                {"get-color219", 0, &a, GET_COLOR_219},
                {"get-color220", 0, &a, GET_COLOR_220},
                {"get-color221", 0, &a, GET_COLOR_221},
                {"get-color222", 0, &a, GET_COLOR_222},
                {"get-color223", 0, &a, GET_COLOR_223},
                {"get-color224", 0, &a, GET_COLOR_224},
                {"get-color225", 0, &a, GET_COLOR_225},
                {"get-color226", 0, &a, GET_COLOR_226},
                {"get-color227", 0, &a, GET_COLOR_227},
                {"get-color228", 0, &a, GET_COLOR_228},
                {"get-color229", 0, &a, GET_COLOR_229},
                {"get-color230", 0, &a, GET_COLOR_230},
                {"get-color231", 0, &a, GET_COLOR_231},
                {"get-color232", 0, &a, GET_COLOR_232},
                {"get-color233", 0, &a, GET_COLOR_233},
                {"get-color234", 0, &a, GET_COLOR_234},
                {"get-color235", 0, &a, GET_COLOR_235},
                {"get-color236", 0, &a, GET_COLOR_236},
                {"get-color237", 0, &a, GET_COLOR_237},
                {"get-color238", 0, &a, GET_COLOR_238},
                {"get-color239", 0, &a, GET_COLOR_239},
                {"get-color240", 0, &a, GET_COLOR_240},
                {"get-color241", 0, &a, GET_COLOR_241},
                {"get-color242", 0, &a, GET_COLOR_242},
                {"get-color243", 0, &a, GET_COLOR_243},
                {"get-color244", 0, &a, GET_COLOR_244},
                {"get-color245", 0, &a, GET_COLOR_245},
                {"get-color246", 0, &a, GET_COLOR_246},
                {"get-color247", 0, &a, GET_COLOR_247},
                {"get-color248", 0, &a, GET_COLOR_248},
                {"get-color249", 0, &a, GET_COLOR_249},
                {"get-color250", 0, &a, GET_COLOR_250},
                {"get-color251", 0, &a, GET_COLOR_251},
                {"get-color252", 0, &a, GET_COLOR_252},
                {"get-color253", 0, &a, GET_COLOR_253},
                {"get-color254", 0, &a, GET_COLOR_254},
                {"get-color255", 0, &a, GET_COLOR_255},
                {"get-highlight", 0, &a, GET_COLOR_HL},
                {"get-cursor", 0, &a, GET_CURSOR},
                {"get-mouse-fg", 0, &a, GET_MOUSE_FG},
                {"get-mouse-bg", 0, &a, GET_MOUSE_BG},
                {"get-font", 0, &a, GET_FONT},
                {"get-title", 0, &a, GET_TITLE},
                {"get-geometry", 0, &a, GET_GEOMETRY},
                {"maximize", 0, &a, MAXIMIZE},
                {"restore", 0, &a, RESTORE},
                {"iconify", 0, &a, ICONIFY},
                {"de-iconify", 0, &a, DE_ICONIFY},
                {"raise", 0, &a, RAISE},
                {"lower", 0, &a, LOWER},
                {"reset", 0, &a, RESET},
                {"raw", 1, &a, RAW},
                {"file", 1, &a, FILE_CONF},
                {"force", 0, 0, 'f'},
                {"verbose", 0, 0, 'v'},
                {"version", 0, 0, 'u'},
                {"help", 0, 0, 'h'},
                {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "+fvh", longopts, &longindex);
        if (c == -1)
        {
            break;
        }

        has_options = 1;

        switch (c)
        {
        case 'u':
            version();

        case 'h':
            usage(EXIT_SUCCESS);

        case 'v':
            verbose = 1;
            break;

        case 'f':
            force = 1;
            break;

        case 0:
            switch (a)
            {
            case FG:
            case BG:
            case COLOR_0:
            case COLOR_1:
            case COLOR_2:
            case COLOR_3:
            case COLOR_4:
            case COLOR_5:
            case COLOR_6:
            case COLOR_7:
            case COLOR_8:
            case COLOR_9:
            case COLOR_10:
            case COLOR_11:
            case COLOR_12:
            case COLOR_13:
            case COLOR_14:
            case COLOR_15:
            case COLOR_16:
            case COLOR_17:
            case COLOR_18:
            case COLOR_19:
            case COLOR_20:
            case COLOR_21:
            case COLOR_22:
            case COLOR_23:
            case COLOR_24:
            case COLOR_25:
            case COLOR_26:
            case COLOR_27:
            case COLOR_28:
            case COLOR_29:
            case COLOR_30:
            case COLOR_31:
            case COLOR_32:
            case COLOR_33:
            case COLOR_34:
            case COLOR_35:
            case COLOR_36:
            case COLOR_37:
            case COLOR_38:
            case COLOR_39:
            case COLOR_40:
            case COLOR_41:
            case COLOR_42:
            case COLOR_43:
            case COLOR_44:
            case COLOR_45:
            case COLOR_46:
            case COLOR_47:
            case COLOR_48:
            case COLOR_49:
            case COLOR_50:
            case COLOR_51:
            case COLOR_52:
            case COLOR_53:
            case COLOR_54:
            case COLOR_55:
            case COLOR_56:
            case COLOR_57:
            case COLOR_58:
            case COLOR_59:
            case COLOR_60:
            case COLOR_61:
            case COLOR_62:
            case COLOR_63:
            case COLOR_64:
            case COLOR_65:
            case COLOR_66:
            case COLOR_67:
            case COLOR_68:
            case COLOR_69:
            case COLOR_70:
            case COLOR_71:
            case COLOR_72:
            case COLOR_73:
            case COLOR_74:
            case COLOR_75:
            case COLOR_76:
            case COLOR_77:
            case COLOR_78:
            case COLOR_79:
            case COLOR_80:
            case COLOR_81:
            case COLOR_82:
            case COLOR_83:
            case COLOR_84:
            case COLOR_85:
            case COLOR_86:
            case COLOR_87:
            case COLOR_88:
            case COLOR_89:
            case COLOR_90:
            case COLOR_91:
            case COLOR_92:
            case COLOR_93:
            case COLOR_94:
            case COLOR_95:
            case COLOR_96:
            case COLOR_97:
            case COLOR_98:
            case COLOR_99:
            case COLOR_100:
            case COLOR_101:
            case COLOR_102:
            case COLOR_103:
            case COLOR_104:
            case COLOR_105:
            case COLOR_106:
            case COLOR_107:
            case COLOR_108:
            case COLOR_109:
            case COLOR_110:
            case COLOR_111:
            case COLOR_112:
            case COLOR_113:
            case COLOR_114:
            case COLOR_115:
            case COLOR_116:
            case COLOR_117:
            case COLOR_118:
            case COLOR_119:
            case COLOR_120:
            case COLOR_121:
            case COLOR_122:
            case COLOR_123:
            case COLOR_124:
            case COLOR_125:
            case COLOR_126:
            case COLOR_127:
            case COLOR_128:
            case COLOR_129:
            case COLOR_130:
            case COLOR_131:
            case COLOR_132:
            case COLOR_133:
            case COLOR_134:
            case COLOR_135:
            case COLOR_136:
            case COLOR_137:
            case COLOR_138:
            case COLOR_139:
            case COLOR_140:
            case COLOR_141:
            case COLOR_142:
            case COLOR_143:
            case COLOR_144:
            case COLOR_145:
            case COLOR_146:
            case COLOR_147:
            case COLOR_148:
            case COLOR_149:
            case COLOR_150:
            case COLOR_151:
            case COLOR_152:
            case COLOR_153:
            case COLOR_154:
            case COLOR_155:
            case COLOR_156:
            case COLOR_157:
            case COLOR_158:
            case COLOR_159:
            case COLOR_160:
            case COLOR_161:
            case COLOR_162:
            case COLOR_163:
            case COLOR_164:
            case COLOR_165:
            case COLOR_166:
            case COLOR_167:
            case COLOR_168:
            case COLOR_169:
            case COLOR_170:
            case COLOR_171:
            case COLOR_172:
            case COLOR_173:
            case COLOR_174:
            case COLOR_175:
            case COLOR_176:
            case COLOR_177:
            case COLOR_178:
            case COLOR_179:
            case COLOR_180:
            case COLOR_181:
            case COLOR_182:
            case COLOR_183:
            case COLOR_184:
            case COLOR_185:
            case COLOR_186:
            case COLOR_187:
            case COLOR_188:
            case COLOR_189:
            case COLOR_190:
            case COLOR_191:
            case COLOR_192:
            case COLOR_193:
            case COLOR_194:
            case COLOR_195:
            case COLOR_196:
            case COLOR_197:
            case COLOR_198:
            case COLOR_199:
            case COLOR_200:
            case COLOR_201:
            case COLOR_202:
            case COLOR_203:
            case COLOR_204:
            case COLOR_205:
            case COLOR_206:
            case COLOR_207:
            case COLOR_208:
            case COLOR_209:
            case COLOR_210:
            case COLOR_211:
            case COLOR_212:
            case COLOR_213:
            case COLOR_214:
            case COLOR_215:
            case COLOR_216:
            case COLOR_217:
            case COLOR_218:
            case COLOR_219:
            case COLOR_220:
            case COLOR_221:
            case COLOR_222:
            case COLOR_223:
            case COLOR_224:
            case COLOR_225:
            case COLOR_226:
            case COLOR_227:
            case COLOR_228:
            case COLOR_229:
            case COLOR_230:
            case COLOR_231:
            case COLOR_232:
            case COLOR_233:
            case COLOR_234:
            case COLOR_235:
            case COLOR_236:
            case COLOR_237:
            case COLOR_238:
            case COLOR_239:
            case COLOR_240:
            case COLOR_241:
            case COLOR_242:
            case COLOR_243:
            case COLOR_244:
            case COLOR_245:
            case COLOR_246:
            case COLOR_247:
            case COLOR_248:
            case COLOR_249:
            case COLOR_250:
            case COLOR_251:
            case COLOR_252:
            case COLOR_253:
            case COLOR_254:
            case COLOR_255:
            case COLOR_HL:
            case CURSOR:
            case MOUSE_FG:
            case MOUSE_BG:
            case FONT:
            case TITLE:
            case RAW:
                ctlseqstab[a].text = optarg;
                break;
            case GET_FG:
            case GET_BG:
            case GET_COLOR_0:
            case GET_COLOR_1:
            case GET_COLOR_2:
            case GET_COLOR_3:
            case GET_COLOR_4:
            case GET_COLOR_5:
            case GET_COLOR_6:
            case GET_COLOR_7:
            case GET_COLOR_8:
            case GET_COLOR_9:
            case GET_COLOR_10:
            case GET_COLOR_11:
            case GET_COLOR_12:
            case GET_COLOR_13:
            case GET_COLOR_14:
            case GET_COLOR_15:
            case GET_COLOR_16:
            case GET_COLOR_17:
            case GET_COLOR_18:
            case GET_COLOR_19:
            case GET_COLOR_20:
            case GET_COLOR_21:
            case GET_COLOR_22:
            case GET_COLOR_23:
            case GET_COLOR_24:
            case GET_COLOR_25:
            case GET_COLOR_26:
            case GET_COLOR_27:
            case GET_COLOR_28:
            case GET_COLOR_29:
            case GET_COLOR_30:
            case GET_COLOR_31:
            case GET_COLOR_32:
            case GET_COLOR_33:
            case GET_COLOR_34:
            case GET_COLOR_35:
            case GET_COLOR_36:
            case GET_COLOR_37:
            case GET_COLOR_38:
            case GET_COLOR_39:
            case GET_COLOR_40:
            case GET_COLOR_41:
            case GET_COLOR_42:
            case GET_COLOR_43:
            case GET_COLOR_44:
            case GET_COLOR_45:
            case GET_COLOR_46:
            case GET_COLOR_47:
            case GET_COLOR_48:
            case GET_COLOR_49:
            case GET_COLOR_50:
            case GET_COLOR_51:
            case GET_COLOR_52:
            case GET_COLOR_53:
            case GET_COLOR_54:
            case GET_COLOR_55:
            case GET_COLOR_56:
            case GET_COLOR_57:
            case GET_COLOR_58:
            case GET_COLOR_59:
            case GET_COLOR_60:
            case GET_COLOR_61:
            case GET_COLOR_62:
            case GET_COLOR_63:
            case GET_COLOR_64:
            case GET_COLOR_65:
            case GET_COLOR_66:
            case GET_COLOR_67:
            case GET_COLOR_68:
            case GET_COLOR_69:
            case GET_COLOR_70:
            case GET_COLOR_71:
            case GET_COLOR_72:
            case GET_COLOR_73:
            case GET_COLOR_74:
            case GET_COLOR_75:
            case GET_COLOR_76:
            case GET_COLOR_77:
            case GET_COLOR_78:
            case GET_COLOR_79:
            case GET_COLOR_80:
            case GET_COLOR_81:
            case GET_COLOR_82:
            case GET_COLOR_83:
            case GET_COLOR_84:
            case GET_COLOR_85:
            case GET_COLOR_86:
            case GET_COLOR_87:
            case GET_COLOR_88:
            case GET_COLOR_89:
            case GET_COLOR_90:
            case GET_COLOR_91:
            case GET_COLOR_92:
            case GET_COLOR_93:
            case GET_COLOR_94:
            case GET_COLOR_95:
            case GET_COLOR_96:
            case GET_COLOR_97:
            case GET_COLOR_98:
            case GET_COLOR_99:
            case GET_COLOR_100:
            case GET_COLOR_101:
            case GET_COLOR_102:
            case GET_COLOR_103:
            case GET_COLOR_104:
            case GET_COLOR_105:
            case GET_COLOR_106:
            case GET_COLOR_107:
            case GET_COLOR_108:
            case GET_COLOR_109:
            case GET_COLOR_110:
            case GET_COLOR_111:
            case GET_COLOR_112:
            case GET_COLOR_113:
            case GET_COLOR_114:
            case GET_COLOR_115:
            case GET_COLOR_116:
            case GET_COLOR_117:
            case GET_COLOR_118:
            case GET_COLOR_119:
            case GET_COLOR_120:
            case GET_COLOR_121:
            case GET_COLOR_122:
            case GET_COLOR_123:
            case GET_COLOR_124:
            case GET_COLOR_125:
            case GET_COLOR_126:
            case GET_COLOR_127:
            case GET_COLOR_128:
            case GET_COLOR_129:
            case GET_COLOR_130:
            case GET_COLOR_131:
            case GET_COLOR_132:
            case GET_COLOR_133:
            case GET_COLOR_134:
            case GET_COLOR_135:
            case GET_COLOR_136:
            case GET_COLOR_137:
            case GET_COLOR_138:
            case GET_COLOR_139:
            case GET_COLOR_140:
            case GET_COLOR_141:
            case GET_COLOR_142:
            case GET_COLOR_143:
            case GET_COLOR_144:
            case GET_COLOR_145:
            case GET_COLOR_146:
            case GET_COLOR_147:
            case GET_COLOR_148:
            case GET_COLOR_149:
            case GET_COLOR_150:
            case GET_COLOR_151:
            case GET_COLOR_152:
            case GET_COLOR_153:
            case GET_COLOR_154:
            case GET_COLOR_155:
            case GET_COLOR_156:
            case GET_COLOR_157:
            case GET_COLOR_158:
            case GET_COLOR_159:
            case GET_COLOR_160:
            case GET_COLOR_161:
            case GET_COLOR_162:
            case GET_COLOR_163:
            case GET_COLOR_164:
            case GET_COLOR_165:
            case GET_COLOR_166:
            case GET_COLOR_167:
            case GET_COLOR_168:
            case GET_COLOR_169:
            case GET_COLOR_170:
            case GET_COLOR_171:
            case GET_COLOR_172:
            case GET_COLOR_173:
            case GET_COLOR_174:
            case GET_COLOR_175:
            case GET_COLOR_176:
            case GET_COLOR_177:
            case GET_COLOR_178:
            case GET_COLOR_179:
            case GET_COLOR_180:
            case GET_COLOR_181:
            case GET_COLOR_182:
            case GET_COLOR_183:
            case GET_COLOR_184:
            case GET_COLOR_185:
            case GET_COLOR_186:
            case GET_COLOR_187:
            case GET_COLOR_188:
            case GET_COLOR_189:
            case GET_COLOR_190:
            case GET_COLOR_191:
            case GET_COLOR_192:
            case GET_COLOR_193:
            case GET_COLOR_194:
            case GET_COLOR_195:
            case GET_COLOR_196:
            case GET_COLOR_197:
            case GET_COLOR_198:
            case GET_COLOR_199:
            case GET_COLOR_200:
            case GET_COLOR_201:
            case GET_COLOR_202:
            case GET_COLOR_203:
            case GET_COLOR_204:
            case GET_COLOR_205:
            case GET_COLOR_206:
            case GET_COLOR_207:
            case GET_COLOR_208:
            case GET_COLOR_209:
            case GET_COLOR_210:
            case GET_COLOR_211:
            case GET_COLOR_212:
            case GET_COLOR_213:
            case GET_COLOR_214:
            case GET_COLOR_215:
            case GET_COLOR_216:
            case GET_COLOR_217:
            case GET_COLOR_218:
            case GET_COLOR_219:
            case GET_COLOR_220:
            case GET_COLOR_221:
            case GET_COLOR_222:
            case GET_COLOR_223:
            case GET_COLOR_224:
            case GET_COLOR_225:
            case GET_COLOR_226:
            case GET_COLOR_227:
            case GET_COLOR_228:
            case GET_COLOR_229:
            case GET_COLOR_230:
            case GET_COLOR_231:
            case GET_COLOR_232:
            case GET_COLOR_233:
            case GET_COLOR_234:
            case GET_COLOR_235:
            case GET_COLOR_236:
            case GET_COLOR_237:
            case GET_COLOR_238:
            case GET_COLOR_239:
            case GET_COLOR_240:
            case GET_COLOR_241:
            case GET_COLOR_242:
            case GET_COLOR_243:
            case GET_COLOR_244:
            case GET_COLOR_245:
            case GET_COLOR_246:
            case GET_COLOR_247:
            case GET_COLOR_248:
            case GET_COLOR_249:
            case GET_COLOR_250:
            case GET_COLOR_251:
            case GET_COLOR_252:
            case GET_COLOR_253:
            case GET_COLOR_254:
            case GET_COLOR_255:
            case GET_COLOR_HL:
            case GET_CURSOR:
            case GET_MOUSE_FG:
            case GET_MOUSE_BG:
            case GET_FONT:
            case GET_TITLE:
            case GET_GEOMETRY:
            case MAXIMIZE:
            case RESTORE:
            case ICONIFY:
            case DE_ICONIFY:
            case RAISE:
            case LOWER:
                ctlseqstab[a].text = "";
                break;
            case RESET:
                ctlseqstab[a].text = "\\ec";
                break;
            case GEOMETRY:
                ctlseqstab[GEOMETRY].text = optarg;
                break;
            case FILE_CONF:
                if (*optarg == '~')
                {
                    snprintf(configuration_file, sizeof(configuration_file), "%s%s", getenv("HOME"), optarg + 1);
                }
                else
                {
                    snprintf(configuration_file, sizeof(configuration_file), "%s", optarg);
                }
                break;
            default:
                usage(EXIT_FAILURE);
            }
            break;

        case '?':
        case ':':
        default:
            usage(EXIT_FAILURE);
        }
    }

    /* check if environment variable TERM is XFree86 variant */
    if (!force)
    {
        check_term_variable();
    }

    configuration_init(&list);

    /* only apply configurations if no options are specified or if a
      configuration is specifically specified by the --file option */
    if (!has_options || configuration_file[0])
    {

        /* read configuration file */
        if (!configuration_file[0])
        {
            /* default ~/.program_name configuration file */
            snprintf(configuration_file, sizeof(configuration_file), "%s/.%s", getenv("HOME"), program_name);
            if (configuration_read(&list, configuration_file) == -1)
            {
                configuration_missing = 1;
            }
        }
        else
        {
            /* user specified configuration file */
            if (configuration_read(&list, configuration_file) == -1)
            {
                fprintf(stderr, "%s: %s: No such file or directory\n", program_name, configuration_file);
                do_exit(EXIT_FAILURE);
            }
        }
    }

    tty_control();

    for (i = 0; i < NSEQ; i++)
    {
        type = ctlseqstab[i].type;
        text = ctlseqstab[i].text;

        temp[0] = '\0';

        /* check if configuration exists */
        if (!text && (type == OSC || type == CSI))
        {
            lp = configuration_find(&list, ctlseqstab[i].conf_title);
            if (lp)
            {
                text = lp->value;
            }
        }

        if (text)
        {
            ctl1 = ctlseqstab[i].ctl1;
            ctl2 = ctlseqstab[i].ctl2;

            switch (type)
            {
            case CSI:
                switch (i)
                {
                case RESTORE:
                case MAXIMIZE:
                    csi_print2(ctl1, ctl2);
                    break;
                case GEOMETRY:
                    set_geometry(ctl1, ctl2, text);
                    break;
                default:
                    csi_print1(ctl1);
                    break;
                }
                break;

            case GET_CSI:
                switch (i)
                {
                case GET_GEOMETRY:
                    if (get_geometry(temp, sizeof(temp), verbose, ctl1, ctl2) < 0)
                    {
                        report_error(ctlseqstab[i].synopsis);
                    }
                    else if (*temp)
                    {
                        fprintf(stdout, "%s\n", temp);
                    }
                    break;
                case GET_TITLE:
                    if (get_title(temp, sizeof(temp), verbose, ctl1) < 0)
                    {
                        report_error(ctlseqstab[i].synopsis);
                    }
                    else if (*temp)
                    {
                        fprintf(stdout, "%s\n", temp);
                    }
                    break;
                default:
                    /* NOTREACHED */
                    assert(0);
                    break;
                }
                break;

            case OSC:
                osc_print(ctl1, ctl2, text);
                break;

            case GET_OSC:
                if (get_osc(temp, sizeof(temp), verbose, i, ctl1, ctl2) < 0)
                {
                    report_error(ctlseqstab[i].synopsis);
                }
                else if (*temp)
                {
                    fprintf(stdout, "%s\n", temp);
                }
                break;

            case ANY:
                raw_print(text);
                break;

            default:
                fprintf(stderr, "unknown type: %d\n", type);
                exit(EXIT_FAILURE);
            }
        }
    }
    configuration_free(&list);

    if (configuration_missing)
    {
        if (configuration_write(configuration_file) < 0)
        {
            do_exit(EXIT_FAILURE);
        }
    }

    do_exit(EXIT_SUCCESS);

    /* NOTREACHED */
    assert(0);

    return 0; /* shut up the compiler */
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void check_term_variable(void)
{
    char *term;

    if ((term = getenv("TERM")) == NULL)
    {
        fprintf(stderr, "%s: failed to read TERM environment variable\n", program_name);
        do_exit(EXIT_FAILURE);
    }

    if (strstr(term, "xterm") == NULL)
    {
        fprintf(stderr, "%s: TERM=%s: probably not xterm variant\n", program_name, term);
        do_exit(EXIT_FAILURE);
    }
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void tty_control()
{
    ctty = NULL;

    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
    {
        /* get controlling terminal */
        if ((ctty = fopen(ctty_path(), "r+")) == NULL)
        {
            fprintf(stderr, "%s: failed to get controlling terminal\n", program_name);
            exit(EXIT_FAILURE);
        }
    }

    if (!isatty(STDIN_FILENO) && ctty)
    {
        tty_in = ctty;
        TTY_FILENO = fileno(tty_in);
    }
    else
    {
        tty_in = stdin;
        TTY_FILENO = STDIN_FILENO;
    }

    if (!isatty(STDOUT_FILENO) && ctty)
    {
        tty_out = ctty;
    }
    else
    {
        tty_out = stdout;
    }

    set_tty_raw();
}

/*=****************************************************************************
**
** DESCRIPTION : find path to controlling terminal
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
char *ctty_path(void)
{
    int i;
    char *tty_path = NULL;

    for (i = 0; i <= 2; i++)
    {
        if ((tty_path = ttyname(i)))
        {
            break;
        }
    }

    return tty_path;
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void set_tty_raw()
{
    /* get and backup tty_in termios */
    tcgetattr(TTY_FILENO, &tty_ts);
    tty_ts_orig = tty_ts;
    tty_ts_orig_pt = &tty_ts_orig;

    /* set tty raw */
    tty_ts.c_iflag = 0;
    tty_ts.c_lflag = 0;

    tty_ts.c_cc[VMIN] = 0;
    tty_ts.c_cc[VTIME] = 1;
    tty_ts.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(TTY_FILENO, TCSANOW, &tty_ts);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void set_tty_restore(void)
{
    /* restore tty mode */
    if (tty_ts_orig_pt)
    {
        tcsetattr(TTY_FILENO, TCSAFLUSH, tty_ts_orig_pt);
    }
}

/*=****************************************************************************
**
** DESCRIPTION : In tmux, use DCS with a "tmux;" prefix to pass escape
** sequences through to the underlying terminal.
**
** Escape characters in the sequences must be doubled.
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
char *tmux_dcs_passthrough(char *ctlseq)
{
    static char s[BUFSIZ];

    if (getenv("TMUX"))
    {
        snprintf(s, sizeof(s), "\033Ptmux;\033%s\033\\", ctlseq);
        return s;
    }

    return ctlseq;
}

/*=****************************************************************************
**
** DESCRIPTION : issue raw escape sequence.
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void raw_print(char *ctlseq)
{
    int c;

    ctlseq = tmux_dcs_passthrough(ctlseq);

    while ((c = *ctlseq++))
    {
        if (c == '\\' && *ctlseq)
        {
            switch (c = *ctlseq++)
            {
            case 'e':
                c = '\033';
                break;
            case 'a':
                c = '\007';
                break;
            case 'b':
                c = '\b';
                break;
            case 'f':
                c = '\f';
                break;
            case 'n':
                c = '\n';
                break;
            case 'r':
                c = '\r';
                break;
            case 't':
                c = '\t';
                break;
            case 'v':
                c = (int)0x0B;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                c -= '0';

                if (*ctlseq >= '0' && *ctlseq <= '7')
                {
                    c = (c * 8) + (*ctlseq++ - '0');
                }

                if (*ctlseq >= '0' && *ctlseq <= '7')
                {
                    c = (c * 8) + (*ctlseq++ - '0');
                }
                break;
            case '\\':
                break;
            default:
                fputc('\\', tty_out);
                break;
            }
        }
        fputc(c, tty_out);
    }

    fflush(tty_out);
}

/*=****************************************************************************
**
** DESCRIPTION : read raw terminal output, not '\0' terminated!
**
** RETURN VALUE: number of bytes read, or 0 on VTIME timeout
**                                                                           */
/*=***************************************************************************/
ssize_t tty_read(char *output, size_t size)
{
    ssize_t res,
        n;
    char *p;

    res = 0;
    p = output;

    while (p < output + size)
    {
        n = read(TTY_FILENO, p, 1);

        if (n > 0)
        {
            p += n;
            res += n;
        }
        else if (n == 0 || (n == -1 && EAGAIN == errno))
        {
            /* VTIME timeout. Nothing more to read, or nothing read. */

            /* tcsetattr(3). If no data is available, POSIX permits a read(2)
             * in noncanonical mode to return either 0, or -1 with errno set
             * to EAGAIN. */
            break;
        }
        else if (n < 0)
        {
            perror("read");
            do_exit(EXIT_FAILURE);
        }
    }

    return res;
}

/*=****************************************************************************
**
** DESCRIPTION : issue CSI (Control Sequence Introducer) escape sequence
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void csi_print1(int ctl1)
{
    snprintf(temp, sizeof(temp), "\033[%dt", ctl1);
    raw_print(temp);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void csi_print2(int ctl1, int ctl2)
{
    snprintf(temp, sizeof(temp), "\033[%d;%dt", ctl1, ctl2);
    raw_print(temp);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void csi_print3(int ctl1, int ctl2, int ctl3)
{
    snprintf(temp, sizeof(temp), "\033[%d;%d;%dt", ctl1, ctl2, ctl3);
    raw_print(temp);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int get_title(char *title, size_t size, int verbose, int ctl1)
{
    /* OSC  l title ST */
    ssize_t n;
    static char s[BUFSIZ];

    csi_print1(ctl1);

    n = tty_read(s, sizeof(s));

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    /* get at least the OSC */
    if (n == 1)
    {
        n += tty_read(s + 1, sizeof(s) - 1);
    }

    while (!(s[n - 2] == '\033' && s[n - 1] == '\\'))
    {
        n += tty_read(s + n, sizeof(s) - n);
    }

    /* n-2: discard ST */
    s[n - 2] = '\0';

    /* s+3: discard OSC l */
    if (!verbose)
    {
        snprintf(title, size, "%s", s + 3);
    }
    else
    {
        snprintf(title, size, "%s=\"%s\"", ctlseqstab[GET_TITLE].conf_title, s + 3);
    }

    return 0;
}

/*=****************************************************************************
**
** DESCRIPTION : issue OSC (Operating System Controls) escape sequence
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void osc_print(int ps1, int ps2, char *pt)
{

    if (pt && *pt)
    {
        if (ps1 == 4)
        {
            /* colorN */
            snprintf(temp, sizeof(temp), "\033]%d;%d;%s\033\\", ps1, ps2, pt);
        }
        else
        {
            snprintf(temp, sizeof(temp), "\033]%d;%s\033\\", ps1, pt);
        }
    }
    else if (ps1 == 4)
    {
        /* colorN */
        snprintf(temp, sizeof(temp), "\033]%d;%d;?\033\\", ps1, ps2);
    }
    else
    {
        snprintf(temp, sizeof(temp), "\033]%d;?\033\\", ps1);
    }

    raw_print(temp);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int get_osc(char *osc, size_t size, int verbose, unsigned int option, int ctl1, int ctl2)
{
    ssize_t n;
    char *p;
    static char s[BUFSIZ];

    char *conf_title = ctlseqstab[option].conf_title;

    if (ctl1 == 4)
    {
        osc_print(ctl1, ctl2, NULL);
    }
    else
    {
        osc_print(ctl1, 0, NULL);
    }

    n = tty_read(s, sizeof(s));

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    /* get at least the OSC */
    if (n == 1)
    {
        n += tty_read(s + 1, sizeof(s) - 1);
    }

    while ((s[n - 1] != '\007') && !(n - 2 >= 0 && s[n - 2] == '\033' && s[n - 1] == '\\'))
    {
        n += tty_read(s + n, sizeof(s) - n);
    }

    if (s[n - 1] == '\007')
    {
        /* n-1: discard BEL */
        s[n - 1] = '\0';
    }
    else if (n - 2 >= 0 && s[n - 2] == '\033' && s[n - 1] == '\\')
    {
        /* n-2: discard ST */
        s[n - 2] = '\0';
    }
    else
    {
        return -1;
    }

    /* discard OSC Ps ; */
    p = strchr(s, ';');
    if (ctl1 == 4)
    {
        p = strchr(p + 1, ';');
    }

    ++p;

    if (!verbose)
    {
        snprintf(osc, size, "%s", p);
    }
    else
    {
        snprintf(osc, size, "%s=\"%s\"", conf_title, p);
    }

    return 0;
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void set_geometry(int ctl1, int ctl2, char *geometry)
{
    int w,
        h,
        x,
        y;
    int set_pos,
        set_size;

    set_pos = set_size = 0;
    if (sscanf(geometry, "%d%*[xX]%d%d%d", &w, &h, &x, &y) == 4)
    {
        set_pos = set_size = 1;
    }
    else if (sscanf(geometry, "%d%d", &x, &y) == 2)
    {
        set_pos = 1;
    }
    else if (sscanf(geometry, "%d%*[xX]%d", &w, &h) == 2)
    {
        set_size = 1;
    }

    if (set_size)
    {
        csi_print3(ctl1, h, w);
    }

    /* negative positions are truncated to origo */
    if (set_pos)
    {
        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;
        csi_print3(ctl2, x, y);
    }
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int get_geometry(char *geometry, size_t size, int verbose, int ctl1, int ctl2)
{
    ssize_t n;
    int w,
        h,
        x,
        y;
    char local_temp[20];

    /* get height, width - CSI 8 ; height ; width t */
    csi_print1(ctl1);
    n = tty_read(local_temp, sizeof(local_temp));

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    /* get at least the CSI */
    if (n == 1)
    {
        n += tty_read(local_temp + 1, sizeof(local_temp) - 1);
    }

    while (local_temp[n - 1] != 't')
    {
        n += tty_read(local_temp + n, sizeof(local_temp) - n);
    }

    /* n-1: discard t */
    local_temp[n - 1] = '\0';

    /* local_temp+4: discard CSI 8 ; */
    if (sscanf(local_temp + 4, "%d;%d", &h, &w) != 2)
    {
        fprintf(stderr, "%s: failed to read xterm size\n", program_name);
        do_exit(EXIT_FAILURE);
    }

    /* get x,y  - CSI 3 ; x; yt */
    csi_print1(ctl2);
    n = tty_read(local_temp, sizeof(local_temp));

    /* get at least the CSI */
    if (n == 1)
    {
        n += tty_read(local_temp + 1, sizeof(local_temp) - 1);
    }

    while (local_temp[n - 1] != 't')
    {
        n += tty_read(local_temp + n, sizeof(local_temp) - n);
    }

    /* n-1: discard t */
    local_temp[n - 1] = '\0';

    /* local_temp+4: discard CSI 3 ; */
    if (sscanf(local_temp + 4, "%d;%dt", &x, &y) != 2)
    {
        fprintf(stderr, "%s: failed to read xterm position\n", program_name);
        do_exit(EXIT_FAILURE);
    }

    if (!verbose)
    {
        snprintf(geometry, size, "%dx%d%+d%+d", w, h, x, y);
    }
    else
    {
        snprintf(geometry, size, "%s=\"%dx%d%+d%+d\"", ctlseqstab[GET_GEOMETRY].conf_title, w, h, x, y);
    }

    return 0;
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void usage(int status)
{
    unsigned int i;

    if (status)
    {
        fprintf(stderr, "Usage: %s [OPTIONS]...\n", program_name);
        fprintf(stderr, "Try `%s --help' for more information.\n", program_name);
    }
    else
    {
        printf("Usage: %s [OPTIONS]...\n", program_name);
        printf("\n");
        printf("Purpose:\n");
        printf("  This program enables dynamic control of XFree86 xterm properties.\n");
        printf("\n");
        printf("Options:\n");

        for (i = 0; i < NSEQ; i++)
        {
            if (ctlseqstab[i].synopsis)
            {
                printf("  %-35s %s\n", ctlseqstab[i].synopsis, ctlseqstab[i].description);
            }
        }
        printf("  %-35s %s\n", "--force, -f", "skip TERM check");
        printf("  %-35s %s\n", "--verbose, -v", "print verbose reports");
        printf("  %-35s %s\n", "--help, -h", "print this help and exit");
        printf("  %-35s %s\n", "--version", "print the version number and exit");
        printf("\n");
        printf("Report bugs to <jess@thrysoee.dk>\n");
    }

    do_exit(status);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void version(void)
{
    printf("%s %s\n", program_name, VERSION);
    printf("\n");
    printf("Copyright (C) 2002-2013 Jess Thrysoee.\n");
    printf("This is free software; see the source for copying conditions. There is NO\n");
    printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");

    do_exit(EXIT_SUCCESS);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int configuration_write(const char *filepath)
{
    FILE *fp;

    fp = fopen(filepath, "w");
    if (fp == NULL)
    {
        perror("configuration_write");
        return -1;
    }

    fprintf(fp, "#\n");
    fprintf(fp, "# This is the configuration file for xtermcontrol.\n");
    fprintf(fp, "#\n");
    fprintf(fp, "# Each line in the file is either a comment or contains an attribute.\n");
    fprintf(fp, "# Attributes consist of a keyword and an associated value:\n");
    fprintf(fp, "#\n");
    fprintf(fp, "# keyword = value # comment\n");
    fprintf(fp, "#\n");
    fprintf(fp, "# Whitespace is ignored in attributes unless within a quoted value. The\n");
    fprintf(fp, "# character '#' is taken to begin a comment. Each '#' and all remaining\n");
    fprintf(fp, "# characters on that line is ignored.\n");
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
    fprintf(fp, "# foreground color\n");
    fprintf(fp, "#foreground=\"black\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# background color\n");
    fprintf(fp, "#background=\"white\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# highlight color\n");
    fprintf(fp, "#highlight=\"yellow\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# cursor color\n");
    fprintf(fp, "#cursor=\"black\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# mouse pointer foreground color\n");
    fprintf(fp, "#mouse-foreground=\"black\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# mouse pointer background color\n");
    fprintf(fp, "#mouse-background=\"white\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# size and/or position\n");
    fprintf(fp, "#geometry=\"80x24\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# font\n");
    fprintf(fp, "#font=\"fixed\"\n");
    fprintf(fp, "\n");
    fprintf(fp, "# color definitions\n");
    fprintf(fp, "#color0=\"#000000\"\n");
    fprintf(fp, "#color1=\"#c00000\"\n");
    fprintf(fp, "#color2=\"#008000\"\n");
    fprintf(fp, "#color3=\"#808000\"\n");
    fprintf(fp, "#color4=\"#0000c0\"\n");
    fprintf(fp, "#color5=\"#c000c0\"\n");
    fprintf(fp, "#color6=\"#008080\"\n");
    fprintf(fp, "#color7=\"#c0c0c0\"\n");
    fprintf(fp, "#color8=\"#808080\"\n");
    fprintf(fp, "#color9=\"#ff6060\"\n");
    fprintf(fp, "#color10=\"#00ff00\"\n");
    fprintf(fp, "#color11=\"#ffff00\"\n");
    fprintf(fp, "#color12=\"#8080ff\"\n");
    fprintf(fp, "#color13=\"#ff40ff\"\n");
    fprintf(fp, "#color14=\"#00ffff\"\n");
    fprintf(fp, "#color15=\"#ffffff\"\n");
    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void report_error(const char *synopsis)
{
    fprintf(stderr, "%s: %s is unsupported or disallowed by this terminal. "
                    "See also, TROUBLESHOOTING section of xtermcontrol(1) manpage.\n",
            program_name, synopsis);
}

/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void do_exit(int status)
{
    set_tty_restore();
    if (ctty)
    {
        fclose(ctty);
    }
    exit(status);
}
