/****************************************************************************
** Copyright (C) 2002-2025 Jess Thrysoee <jess@thrysoee.dk>
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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "configuration.h"
#include "getopt.h"
#include "xtermcontrol.h"

/* The name the program was run with, stripped of any leading path. */
static char *program_name;

/* controlling terminal fps and descriptor */
static FILE *ctty;
static FILE *tty_in;
static FILE *tty_out;
static int TTY_FILENO;

/* termios settings */
static struct termios tty_ts;
static struct termios tty_ts_orig;
static struct termios *tty_ts_orig_pt = NULL;

static int a = -1;
static struct option longopts[NSEQ + 5];

static int process_ctlseq(unsigned int i, char *text, int verbose);
static void on_signal(int sig);
static void init_longopts(void);

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
        type;
    int cli_order[NSEQ];
    unsigned n_cli = 0;
    int has_options = 0;
    int force = 0;
    int verbose = 0;
    int failed = 0;
    int configuration_missing = 0;
    char *home;
    char configuration_file[BUFSIZ];

    configuration list;              /* configuration linked list                 */
    const configuration_element *lp; /* configuration linked list element     */

    program_name = argv[0];
    if (program_name && strrchr(program_name, '/'))
    {
        program_name = strrchr(program_name, '/') + 1;
    }

    configuration_file[0] = '\0';

    init_ctlseqstab();
    init_longopts();

    while (1)
    {
        int longindex = 0;

        c = getopt_long(argc, argv, "+fvh", longopts, &longindex);
        if (c == -1)
        {
            break;
        }

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
            if (a != FILE_CONF)
            {
                has_options = 1;
                if (ctlseqstab[a].text == NULL)
                {
                    cli_order[n_cli++] = a;
                }
            }
            if ((a >= FG && a <= GEOMETRY) || a == RAW)
            {
                ctlseqstab[a].text = optarg;
            }
            else if (a >= GET_FG && a <= LOWER)
            {
                ctlseqstab[a].text = "";
            }
            else if (a == RESET)
            {
                ctlseqstab[a].text = "\\ec";
            }
            else if (a == FILE_CONF)
            {
                if (optarg[0] == '~' && (optarg[1] == '/' || optarg[1] == '\0'))
                {
                    home = getenv("HOME");
                    if (!home)
                    {
                        fprintf(stderr, "%s: HOME environment variable not set\n", program_name);
                        exit(EXIT_FAILURE);
                    }
                    snprintf(configuration_file, sizeof(configuration_file), "%s%s", home, optarg + 1);
                }
                else
                {
                    snprintf(configuration_file, sizeof(configuration_file), "%s", optarg);
                }
            }
            else
            {
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
            home = getenv("HOME");
            if (home)
            {
                /* default ~/.program_name configuration file */
                snprintf(configuration_file, sizeof(configuration_file), "%s/.%s", home, program_name);
                if (configuration_read(&list, configuration_file) == -1)
                {
                    configuration_missing = 1;
                }
            }
        }
        else
        {
            /* user specified configuration file */
            if (configuration_read(&list, configuration_file) == -1)
            {
                fprintf(stderr, "%s: %s: %s\n", program_name, configuration_file, strerror(errno));
                do_exit(EXIT_FAILURE);
            }
        }
    }

    tty_control();

    for (i = 0; i < NSEQ; i++)
    {
        type = ctlseqstab[i].type;

        if (!ctlseqstab[i].text && (type == OSC || type == CSI))
        {
            lp = configuration_find(&list, ctlseqstab[i].conf_title);
            if (lp && process_ctlseq(i, lp->value, verbose) < 0)
            {
                failed = 1;
            }
        }
    }

    for (i = 0; i < n_cli; i++)
    {
        if (process_ctlseq(cli_order[i], ctlseqstab[cli_order[i]].text, verbose) < 0)
        {
            failed = 1;
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

    do_exit(failed ? EXIT_FAILURE : EXIT_SUCCESS);

    /* NOTREACHED */
    assert(0);

    return 0; /* shut up the compiler */
}

static int process_ctlseq(unsigned int i, char *text, int verbose)
{
    int type,
        ctl1,
        ctl2;
    char temp[BUFSIZ];

    type = ctlseqstab[i].type;
    ctl1 = ctlseqstab[i].ctl1;
    ctl2 = ctlseqstab[i].ctl2;

    temp[0] = '\0';

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
                return -1;
            }
            if (*temp)
            {
                fprintf(stdout, "%s\n", temp);
            }
            break;
        case GET_TITLE:
            if (get_title(temp, sizeof(temp), verbose, ctl1) < 0)
            {
                report_error(ctlseqstab[i].synopsis);
                return -1;
            }
            if (*temp)
            {
                fprintf(stdout, "%s\n", temp);
            }
            break;
        default:
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
            return -1;
        }
        if (*temp)
        {
            fprintf(stdout, "%s\n", temp);
        }
        break;

    case ANY:
        raw_print(text);
        break;

    default:
        fprintf(stderr, "unknown type: %d\n", type);
        do_exit(EXIT_FAILURE);
    }

    return 0;
}

static void init_longopts(void)
{
    unsigned int i;

    for (i = 0; i < NSEQ; i++)
    {
        longopts[i].name = ctlseqstab[i].option;
        longopts[i].has_arg = (i <= GEOMETRY || i == RAW || i == FILE_CONF) ? 1 : 0;
        longopts[i].flag = &a;
        longopts[i].val = i;
    }
    longopts[NSEQ].name = "force";
    longopts[NSEQ].val = 'f';
    longopts[NSEQ + 1].name = "verbose";
    longopts[NSEQ + 1].val = 'v';
    longopts[NSEQ + 2].name = "version";
    longopts[NSEQ + 2].val = 'u';
    longopts[NSEQ + 3].name = "help";
    longopts[NSEQ + 3].val = 'h';
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

    if (getenv("TMUX"))
    {
        return;
    }

    if ((term = getenv("TERM")) == NULL)
    {
        fprintf(stderr, "%s: failed to read TERM environment variable\n", program_name);
        do_exit(EXIT_FAILURE);
    }

    if (strstr(term, "xterm") == NULL && strstr(term, "tmux") == NULL)
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
        if ((ctty = fopen("/dev/tty", "r+")) == NULL)
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

    signal(SIGHUP, on_signal);
    signal(SIGINT, on_signal);
    signal(SIGQUIT, on_signal);
    signal(SIGTERM, on_signal);

    set_tty_raw();
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
    if (tcgetattr(TTY_FILENO, &tty_ts) == -1)
    {
        perror("tcgetattr");
        do_exit(EXIT_FAILURE);
    }
    tty_ts_orig = tty_ts;
    tty_ts_orig_pt = &tty_ts_orig;

    /* set tty raw */
    tty_ts.c_iflag = 0;
    tty_ts.c_lflag = 0;

    tty_ts.c_cc[VMIN] = 0;
    tty_ts.c_cc[VTIME] = 1;
    tty_ts.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(TTY_FILENO, TCSANOW, &tty_ts) == -1)
    {
        perror("tcsetattr");
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
void set_tty_restore(void)
{
    /* restore tty mode */
    if (tty_ts_orig_pt)
    {
        tcsetattr(TTY_FILENO, TCSAFLUSH, tty_ts_orig_pt);
    }
}

static void on_signal(int sig)
{
    set_tty_restore();
    signal(sig, SIG_DFL);
    raise(sig);
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
    size_t n,
        i;
    static char buf[BUFSIZ];

    n = 0;

    while ((c = *ctlseq++) && n < sizeof(buf) - 1)
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
                buf[n++] = '\\';
                break;
            }
        }
        buf[n++] = c;
    }

    if (getenv("TMUX"))
    {
        fputs("\033Ptmux;", tty_out);
        for (i = 0; i < n; i++)
        {
            if (buf[i] == '\033')
            {
                fputc('\033', tty_out);
            }
            fputc(buf[i], tty_out);
        }
        fputs("\033\\", tty_out);
    }
    else
    {
        fwrite(buf, 1, n, tty_out);
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
    char buf[BUFSIZ];

    snprintf(buf, sizeof(buf), "\033[%dt", ctl1);
    raw_print(buf);
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
    char buf[BUFSIZ];

    snprintf(buf, sizeof(buf), "\033[%d;%dt", ctl1, ctl2);
    raw_print(buf);
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
    char buf[BUFSIZ];

    snprintf(buf, sizeof(buf), "\033[%d;%d;%dt", ctl1, ctl2, ctl3);
    raw_print(buf);
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
    ssize_t n,
        r;
    static char s[BUFSIZ];

    csi_print1(ctl1);

    n = tty_read(s, sizeof(s));

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    while ((s[n - 1] != '\007') && (n < 2 || !(s[n - 2] == '\033' && s[n - 1] == '\\')))
    {
        r = tty_read(s + n, sizeof(s) - n);
        if (r == 0)
        {
            return -1;
        }
        n += r;
    }

    if (s[n - 1] == '\007')
    {
        s[n - 1] = '\0';
    }
    else
    {
        s[n - 2] = '\0';
    }

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
    char buf[BUFSIZ];

    if (pt && *pt)
    {
        if (ps1 == 4)
        {
            /* colorN */
            snprintf(buf, sizeof(buf), "\033]%d;%d;%s\033\\", ps1, ps2, pt);
        }
        else
        {
            snprintf(buf, sizeof(buf), "\033]%d;%s\033\\", ps1, pt);
        }
    }
    else if (ps1 == 4)
    {
        /* colorN */
        snprintf(buf, sizeof(buf), "\033]%d;%d;?\033\\", ps1, ps2);
    }
    else
    {
        snprintf(buf, sizeof(buf), "\033]%d;?\033\\", ps1);
    }

    raw_print(buf);
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
    ssize_t n,
        r;
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

    while ((s[n - 1] != '\007') && !(n - 2 >= 0 && s[n - 2] == '\033' && s[n - 1] == '\\'))
    {
        r = tty_read(s + n, sizeof(s) - n);
        if (r == 0)
        {
            return -1;
        }
        n += r;
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
    if (p && ctl1 == 4)
    {
        p = strchr(p + 1, ';');
    }

    if (!p)
    {
        return -1;
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
    else
    {
        fprintf(stderr, "%s: invalid geometry: %s\n", program_name, geometry);
        do_exit(EXIT_FAILURE);
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
    ssize_t n,
        r;
    int w,
        h,
        x,
        y;
    char local_temp[BUFSIZ];

    /* get height, width - CSI 8 ; height ; width t */
    csi_print1(ctl1);
    n = tty_read(local_temp, sizeof(local_temp));

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    while (local_temp[n - 1] != 't')
    {
        r = tty_read(local_temp + n, sizeof(local_temp) - n);
        if (r == 0)
        {
            return -1;
        }
        n += r;
    }

    if (n < 5)
    {
        return -1;
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

    if (n == 0)
    {
        /* unsupported or disallowed */
        return -1;
    }

    while (local_temp[n - 1] != 't')
    {
        r = tty_read(local_temp + n, sizeof(local_temp) - n);
        if (r == 0)
        {
            return -1;
        }
        n += r;
    }

    if (n < 5)
    {
        return -1;
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
        printf("See xtermcontrol(1) manpage for more information.\n");
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
    printf("Copyright (C) 2002-2026 Jess Thrysoee.\n");
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
