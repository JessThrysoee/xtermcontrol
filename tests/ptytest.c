/****************************************************************************
** Copyright (C) 2026 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#include <config.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#ifdef HAVE_UTIL_H
#include <util.h>
#endif
#ifdef HAVE_PTY_H
#include <pty.h>
#endif
#ifdef HAVE_LIBUTIL_H
#include <libutil.h>
#endif

static char capture[65536];
static size_t captured;

static void print_capture(void)
{
    size_t i;
    int c;

    printf("output: ");
    for (i = 0; i < captured; i++)
    {
        c = (unsigned char)capture[i];
        switch (c)
        {
        case '\033':
            printf("\\e");
            break;
        case '\007':
            printf("\\a");
            break;
        case '\r':
            printf("\\r");
            break;
        case '\n':
            printf("\\n");
            break;
        default:
            if (c >= 32 && c < 127)
            {
                putchar(c);
            }
            else
            {
                printf("\\x%02x", c);
            }
            break;
        }
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int m,
        st,
        eof,
        quiet,
        nopts,
        nreplies,
        sent;
    long waited;
    pid_t pid;
    ssize_t n;
    char **child_argv;
    char **replies;
    fd_set fds;
    struct timeval tv;

    for (nopts = 1; nopts < argc; nopts++)
    {
        if (strcmp(argv[nopts], "--") == 0)
        {
            break;
        }
    }
    replies = argv + nopts + (nopts < argc ? 1 : 0);
    nreplies = argc - (int)(replies - argv);

    child_argv = malloc(sizeof(char *) * (nopts + 1));
    if (!child_argv)
    {
        perror("malloc");
        return 2;
    }
    child_argv[0] = "xtermcontrol";
    memcpy(child_argv + 1, argv + 1, sizeof(char *) * (nopts - 1));
    child_argv[nopts] = NULL;

    pid = forkpty(&m, NULL, NULL, NULL);
    if (pid == -1)
    {
        perror("forkpty");
        return 2;
    }
    if (pid == 0)
    {
        const char *xtc = getenv("XTC");
        const char *home = getenv("PTY_HOME");
        setenv("TERM", "xterm", 1);
        if (getenv("PTY_TMUX"))
        {
            setenv("TMUX", "/tmp/tmux-0/default,1,0", 1);
        }
        else
        {
            unsetenv("TMUX");
        }
        if (home)
        {
            setenv("HOME", home, 1);
        }
        else
        {
            unsetenv("HOME");
        }
        execv(xtc ? xtc : "../src/xtermcontrol", child_argv);
        _exit(127);
    }

    eof = 0;
    sent = 0;
    waited = 0;

    while (waited < 5000)
    {
        if (waitpid(pid, &st, WNOHANG) == pid)
        {
            while (!eof)
            {
                tv.tv_sec = 0;
                tv.tv_usec = 0;
                FD_ZERO(&fds);
                FD_SET(m, &fds);
                if (select(m + 1, &fds, NULL, NULL, &tv) <= 0)
                {
                    break;
                }
                n = read(m, capture + captured, sizeof(capture) - captured);
                if (n <= 0)
                {
                    eof = 1;
                }
                else
                {
                    captured += n;
                }
            }
            print_capture();
            printf("child exited, status=%d\n", WIFEXITED(st) ? WEXITSTATUS(st) : -WTERMSIG(st));
            return 0;
        }

        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        FD_ZERO(&fds);
        FD_SET(m, &fds);
        quiet = 1;
        if (eof)
        {
            select(0, NULL, NULL, NULL, &tv);
        }
        else if (select(m + 1, &fds, NULL, NULL, &tv) > 0)
        {
            n = read(m, capture + captured, sizeof(capture) - captured);
            if (n <= 0)
            {
                eof = 1;
            }
            else
            {
                captured += n;
                quiet = 0;
                if (sent < nreplies)
                {
                    n = write(m, replies[sent], strlen(replies[sent]));
                    (void)n;
                    sent++;
                }
            }
        }
        if (quiet)
        {
            waited += 100;
        }
    }

    print_capture();
    printf("TIMEOUT\n");
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
    return 1;
}
