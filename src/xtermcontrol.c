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

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <config.h>

#include "getopt.h"
#include "xtermcontrol.h"
#include "configuration.h"

/* The name the program was run with, stripped of any leading path. */
char *program_name;

static char temp[BUFSIZ];

/* controlling terminal fps and descriptor */
FILE *ctty;
FILE *tty_in;
FILE *tty_out;
int TTY_FILENO;

/* termios settings */
struct termios tty_ts,
 tty_ts_orig;
struct termios *tty_ts_orig_pt = NULL;

struct controlseqs ctlseqstab[] =
{
   {10, 0, NULL, OSC,           /* FG                                        */
      "foreground",
      "--fg=COLOR",
   "set foreground color"},

   {11, 0, NULL, OSC,           /* BG                                        */
      "background",
      "--bg=COLOR",
   "set background color"},

   {4, 0, NULL, OSC,            /* COLOR_0                                   */
      "color0",
      "--colorN=COLOR",
   "set N'th [0-15] color"},

   {4, 1, NULL, OSC,            /* COLOR_1                                   */
      "color1",
   NULL, NULL},

   {4, 2, NULL, OSC,            /* COLOR_2                                   */
      "color2",
   NULL, NULL},

   {4, 3, NULL, OSC,            /* COLOR_3                                   */
      "color3",
   NULL, NULL},

   {4, 4, NULL, OSC,            /* COLOR_4                                   */
      "color4",
   NULL, NULL},

   {4, 5, NULL, OSC,            /* COLOR_5                                   */
      "color5",
   NULL, NULL},

   {4, 6, NULL, OSC,            /* COLOR_6                                   */
      "color6",
   NULL, NULL},

   {4, 7, NULL, OSC,            /* COLOR_7                                   */
      "color7",
   NULL, NULL},

   {4, 8, NULL, OSC,            /* COLOR_8                                   */
      "color8",
   NULL, NULL},

   {4, 9, NULL, OSC,            /* COLOR_9                                   */
      "color9",
   NULL, NULL},

   {4, 10, NULL, OSC,           /* COLOR_10                                  */
      "color10",
   NULL, NULL},

   {4, 11, NULL, OSC,           /* COLOR_11                                  */
      "color11",
   NULL, NULL},

   {4, 12, NULL, OSC,           /* COLOR_12                                  */
      "color12",
   NULL, NULL},

   {4, 13, NULL, OSC,           /* COLOR_13                                  */
      "color13",
   NULL, NULL},

   {4, 14, NULL, OSC,           /* COLOR_14                                  */
      "color14",
   NULL, NULL},

   {4, 15, NULL, OSC,           /* COLOR_15                                  */
      "color15",
   NULL, NULL},

   {17, 0, NULL, OSC,           /* COLOR_HL                                  */
      "highlight",
      "--highlight=COLOR",
   "set highlight color"},

   {12, 0, NULL, OSC,           /* CURSOR                                    */
      "cursor",
      "--cursor=COLOR",
   "set cursor color"},

   {13, 0, NULL, OSC,           /* MOUSE_FG                                  */
      "mouse-foreground",
      "--mouse-fg=COLOR",
   "set mouse pointer foreground color"},

   {14, 0, NULL, OSC,           /* MOUSE_BG                                  */
      "mouse-background",
      "--mouse-bg=COLOR",
   "set mouse pointer background color"},

   {50, 0, NULL, OSC,           /* FONT                                      */
      "font",
      "--font=FONT",
   "set font"},

   {0, 0, NULL, OSC,            /* TITLE                                     */
      "title",
      "--title=STRING",
   "set window title"},

   {8, 3, NULL, CSI,            /* GEOMETRY                                  */
      "geometry",
      "--geometry=WIDTHxHEIGHT+XOFF+YOFF",
   "set size and/or position"},

   {10, 0, NULL, GET_OSC,       /* GET_FG                                    */
      "foreground",
      "--get-fg",
   "report foreground color"},

   {11, 0, NULL, GET_OSC,       /* GET_BG                                    */
      "background",
      "--get-bg",
   "report background color"},

   {4, 0, NULL, GET_OSC,        /* GET_COLOR_0                               */
      "color0",
      "--get-colorN",
   "report N'th [0-15] color"},

   {4, 1, NULL, GET_OSC,        /* GET_COLOR_1                               */
      "color1",
   NULL, NULL},

   {4, 2, NULL, GET_OSC,        /* GET_COLOR_2                               */
      "color2",
   NULL, NULL},

   {4, 3, NULL, GET_OSC,        /* GET_COLOR_3                               */
      "color3",
   NULL, NULL},

   {4, 4, NULL, GET_OSC,        /* GET_COLOR_4                               */
      "color4",
   NULL, NULL},

   {4, 5, NULL, GET_OSC,        /* GET_COLOR_5                               */
      "color5",
   NULL, NULL},

   {4, 6, NULL, GET_OSC,        /* GET_COLOR_6                               */
      "color6",
   NULL, NULL},

   {4, 7, NULL, GET_OSC,        /* GET_COLOR_7                               */
      "color7",
   NULL, NULL},

   {4, 8, NULL, GET_OSC,        /* GET_COLOR_8                               */
      "color8",
   NULL, NULL},

   {4, 9, NULL, GET_OSC,        /* GET_COLOR_9                               */
      "color9",
   NULL, NULL},

   {4, 10, NULL, GET_OSC,       /* GET_COLOR_10                              */
      "color10",
   NULL, NULL},

   {4, 11, NULL, GET_OSC,       /* GET_COLOR_11                              */
      "color11",
   NULL, NULL},

   {4, 12, NULL, GET_OSC,       /* GET_COLOR_12                              */
      "color12",
   NULL, NULL},

   {4, 13, NULL, GET_OSC,       /* GET_COLOR_13                              */
      "color13",
   NULL, NULL},

   {4, 14, NULL, GET_OSC,       /* GET_COLOR_14                              */
      "color14",
   NULL, NULL},

   {4, 15, NULL, GET_OSC,       /* GET_COLOR_15                              */
      "color15",
   NULL, NULL},

   {17, 0, NULL, GET_OSC,       /* GET_COLOR_HL                              */
      "highlight",
      "--get-highlight",
   "report highlight color"},

   {12, 0, NULL, GET_OSC,       /* GET_CURSOR                                */
      "cursor",
      "--get-cursor",
   "report cursor color"},

   {13, 0, NULL, GET_OSC,       /* GET_MOUSE_FG                              */
      "mouse-foreground",
      "--get-mouse-fg",
   "report mouse pointer foreground color"},

   {14, 0, NULL, GET_OSC,       /* GET_MOUSE_BG                              */
      "mouse-background",
      "--get-mouse-bg",
   "report mouse pointer background color"},

   {50, 0, NULL, GET_OSC,       /* GET_FONT                                  */
      "font",
      "--get-font",
   "report font"},

   {21, 0, NULL, GET_CSI,       /* GET_TITLE                                 */
      "title",
      "--get-title",
   "report window title"},

   {18, 13, NULL, GET_CSI,      /* GET_GEOMETRY                              */
      "geometry",
      "--get-geometry",
   "report size and position"},

   {9, 1, NULL, CSI, NULL,      /* MAXIMIZE                                  */
      "--maximize",
   "maximize window"},

   {9, 0, NULL, CSI, NULL,      /* RESTORE                                   */
      "--restore",
   "restore maximized window"},

   {2, 0, NULL, CSI, NULL,      /* ICONIFY                                   */
      "--iconify",
   "iconify window"},

   {1, 0, NULL, CSI, NULL,      /* DE_ICONIFY                                */
      "--de-iconify",
   "de-iconify window"},

   {5, 0, NULL, CSI, NULL,      /* RAISE                                     */
      "--raise",
   "raise window"},

   {6, 0, NULL, CSI, NULL,      /* LOWER                                     */
      "--lower",
   "lower window"},

   {0, 0, NULL, ANY, NULL,      /* RESET                                     */
      "--reset",
   "full reset"},

   {0, 0, NULL, ANY, NULL,      /* RAW                                       */
      "--raw=CTLSEQS",
   "issue raw control sequence"},

   {0, 0, NULL, ANY, NULL,      /* FILE_CONF                                 */
      "--file=FILE",
   "alternative configuration file"}
};


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int main(int argc, char **argv)
{
   unsigned       i;
   int            c,
                  ctl1,
                  ctl2,
                  type;
   int            has_options = 0;
   int            force = 0;
   int            verbose = 0;
   int            configuration_missing = 0;
   char          *text = NULL;
   char           configuration_file[BUFSIZ];

   configuration  list;         /* configuration linked list                 */
   const configuration_element *lp; /* configuration linked list element     */

   program_name = argv[0];
   if (program_name && strrchr(program_name, '/'))
   {
      program_name = strrchr(program_name, '/') + 1;
   }

   configuration_file[0] = '\0';

   while (1)
   {
      static int     a = -1;
      int            longindex = 0;

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
         {0, 0, 0, 0}
      };

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
      configuration is specifically specified by the --file option           */
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

   return 0;                    /* shut up the compiler                      */
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
   char          *term;

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
   int            i;
   char          *tty_path = NULL;

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
   static char    s[BUFSIZ];

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
   int            c;

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
            c = (int) 0x0B;
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
int tty_read(char *output, size_t size)
{
   int            res,
                  n;
   char          *p;

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
      else if (n == 0)
      {
         /* VTIME timeout. Nothing more to read, or nothing read */
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
   int            n;
   static char    s[BUFSIZ];

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
         snprintf(temp, sizeof(temp), "\033]%d;%d;%s\007", ps1, ps2, pt);
      }
      else
      {
         snprintf(temp, sizeof(temp), "\033]%d;%s\007", ps1, pt);
      }
   }
   else if (ps1 == 4)
   {
      /* colorN */
      snprintf(temp, sizeof(temp), "\033]%d;%d;?\007", ps1, ps2);
   }
   else
   {
      snprintf(temp, sizeof(temp), "\033]%d;?\007", ps1);
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
int get_osc(char *osc, size_t size, int verbose, int option, int ctl1, int ctl2)
{
   int            n;
   char          *p;
   static char    s[BUFSIZ];

   char          *conf_title = ctlseqstab[option].conf_title;

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

   while (s[n - 1] != '\007')
   {
      n += tty_read(s + n, sizeof(s) - n);
   }

   /* n-2: discard BEL */
   s[n - 1] = '\0';

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
   int            w,
                  h,
                  x,
                  y;
   int            set_pos,
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
   int            n,
                  w,
                  h,
                  x,
                  y;
   char           temp[20];

   /* get height, width - CSI 8 ; height ; width t */
   csi_print1(ctl1);
   n = tty_read(temp, sizeof(temp));

   if (n == 0)
   {
      /* unsupported or disallowed */
      return -1;
   }

   /* get at least the CSI */
   if (n == 1)
   {
      n += tty_read(temp + 1, sizeof(temp) - 1);
   }

   while (temp[n - 1] != 't')
   {
      n += tty_read(temp + n, sizeof(temp) - n);
   }

   /* n-1: discard t */
   temp[n - 1] = '\0';

   /* temp+4: discard CSI 8 ; */
   if (sscanf(temp + 4, "%d;%d", &h, &w) != 2)
   {
      fprintf(stderr, "%s: failed to read xterm size\n", program_name);
      do_exit(EXIT_FAILURE);
   }

   /* get x,y  - CSI 3 ; x; yt */
   csi_print1(ctl2);
   n = tty_read(temp, sizeof(temp));

   /* get at least the CSI */
   if (n == 1)
   {
      n += tty_read(temp + 1, sizeof(temp) - 1);
   }

   while (temp[n - 1] != 't')
   {
      n += tty_read(temp + n, sizeof(temp) - n);
   }

   /* n-1: discard t */
   temp[n - 1] = '\0';

   /* temp+4: discard CSI 3 ; */
   if (sscanf(temp + 4, "%d;%dt", &x, &y) != 2)
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
   unsigned int   i;

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
   FILE          *fp;

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
           "See also, TROUBLESHOOTING section of xtermcontrol(1) manpage.\n", program_name, synopsis);
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
