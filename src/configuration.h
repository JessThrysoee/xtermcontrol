/****************************************************************************
** $Id: configuration.h,v 1.5 2002/08/01 21:54:17 jet Exp $
**
** Copyright (C) 2002-2013 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

/* Configuration files must be plain ascii test file. Each line in the file is
 * either a comment or contains an attribute. Attributes consist of a keyword
 * and an associated value:
 *
 * keyword = value # comment
 *
 * Whitespace is ignored in attributes unless within a quoted value. The
 * character '#' is taken to begin a comment. Each '#' and all remaining
 * characters on that line is ignored.
 *
 *
 * EXAMPLE:
 *
 *    char path[BUFSIZ];
 *    configuration list;
 *    const configuration_element *lp;
 *
 *    configuration_init(&list)
 *    configuration_read(&list, "/etc/application.conf");
 *    snprintf(path, sizeof(path), "%s/.%s", getenv("HOME"), "application");
 *    configuration_read(&list, path);
 *
 *    for (lp = list.first; lp != NULL; lp = lp->next) {
 *       printf("key:%s value:%s\n", lp->keyword, lp->value);
 *    }
 *
 *    if (lp = configuration_find(&list, "example_keyword"))
 *       printf("found %s with value %s\n", lp->keyword, lp->value);
 *
 *    configuration_free(&list);
                                                                             */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef struct configuration_element
{
    struct configuration_element *next;
    char *keyword;
    char *value;

} configuration_element;

typedef struct configuration
{
    struct configuration_element *first;
    int n_elements;

} configuration;

/* configuration.c */
void configuration_init(configuration *list);
int configuration_read(configuration *list, const char *filepath);
void configuration_free(configuration *list);
const configuration_element *configuration_find(configuration *list, const char *keyword);

/*
  Something like the following function should be created to write the
  configuration to a file, but it will always be very implementation specific,
  so it is left to be done per project and not in this library.

      int configuration_write(const char* filepath);
*/

#endif
