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

int main(int argc, char **argv)
{
    int m,
        i,
        st;
    pid_t pid;
    ssize_t n;
    char buf[4096];
    fd_set fds;
    struct timeval tv;

    if (argc < 2)
    {
        fprintf(stderr, "usage: ptytest OPTION [REPLY]\n");
        return 2;
    }

    pid = forkpty(&m, NULL, NULL, NULL);
    if (pid == -1)
    {
        perror("forkpty");
        return 2;
    }
    if (pid == 0)
    {
        const char *xtc = getenv("XTC");
        setenv("TERM", "xterm", 1);
        unsetenv("TMUX");
        unsetenv("HOME");
        execl(xtc ? xtc : "../src/xtermcontrol", "xtermcontrol", argv[1], (char *)NULL);
        _exit(127);
    }

    tv.tv_sec = 2;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(m, &fds);
    if (select(m + 1, &fds, NULL, NULL, &tv) > 0)
    {
        n = read(m, buf, sizeof(buf));
        (void)n;
    }

    if (argc > 2 && argv[2][0])
    {
        n = write(m, argv[2], strlen(argv[2]));
        (void)n;
    }

    for (i = 0; i < 50; i++)
    {
        if (waitpid(pid, &st, WNOHANG) == pid)
        {
            printf("child exited, status=%d\n", WIFEXITED(st) ? WEXITSTATUS(st) : -WTERMSIG(st));
            return 0;
        }
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        FD_ZERO(&fds);
        FD_SET(m, &fds);
        if (select(m + 1, &fds, NULL, NULL, &tv) > 0)
        {
            n = read(m, buf, sizeof(buf));
            (void)n;
        }
    }

    printf("TIMEOUT\n");
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
    return 1;
}
