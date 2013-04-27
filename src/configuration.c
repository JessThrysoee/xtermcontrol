/****************************************************************************
** $Id: configuration.c,v 1.17 2002/10/26 17:20:36 jet Exp $
**
** Copyright (C) 2002-2013 Jess Thrysoee <jess@thrysoee.dk>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
***************************************************************************  */

#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "configuration.h"

static void configuration_add(configuration * list, const char *keyword, const char *value);
static void do_regerror(int errcode, const regex_t * preg);


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void configuration_init(configuration * list)
{
   list->n_elements = 0;
   list->first = NULL;
}


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
int configuration_read(configuration * list, const char *filepath)
{
   int            errcode;
   char           temp[BUFSIZ];
   size_t         matchlen;

   FILE          *stream;
   char          *value,
                 *p;
   char          *keyword;

   regex_t        preg;
   regmatch_t    *pmatch;
   const char    *regex;

   stream = fopen(filepath, "r");
   if (stream == NULL)
   {
      return -1;
   }

   /* 
    * match: 'keyword=value'
    * and  : 'keyword = value'
    * and  : '"key word" = value'
    * and  : 'keyword = value # comment'
    * and  : 'keyword = value1 value2 # comment'
    * and  : 'keyword = #ffffff'
    * not  : '#keyword = value'
    */
   regex = "^[ \t\"']*([^#]*[^ \t\"'#])[ \t\"']*=[ \t\"']*(#?[^\"'#]*)";
   errcode = regcomp(&preg, regex, REG_EXTENDED | REG_NEWLINE);
   if (errcode)
   {
      do_regerror(errcode, &preg);
      return -1;
   }
   pmatch = (regmatch_t *) malloc(sizeof(regmatch_t) * (preg.re_nsub + 1));
   if (!pmatch)
   {
      fprintf(stderr, "out of memory\n");
      exit(8);
   }

   while (fgets(temp, sizeof(temp), stream) != NULL)
   {
      /* fgets keeps the newline - delete it */
      if ((p = strchr(temp, '\n')) != NULL)
      {
         *p = '\0';
      }
      errcode = regexec(&preg, temp, (preg.re_nsub + 1), pmatch, 0);
      if (errcode)
      {
         /* line did not match */
         continue;
      }
      /* ignore pmatch[0] which is the entire match */

      /* keyword */
      if (pmatch[1].rm_so != -1)
      {
         matchlen = pmatch[1].rm_eo - pmatch[1].rm_so;
         keyword = (char *) malloc(matchlen + 1);
         if (!keyword)
         {
            fprintf(stderr, "out of memory\n");
            exit(8);
         }
         strncpy(keyword, temp + pmatch[1].rm_so, matchlen);
         keyword[matchlen] = '\0';
      }
      else
      {
         fprintf(stderr, "missing keyword: %s\n", temp);
         continue;
      }
      /* value */
      if (pmatch[2].rm_so != -1)
      {
         matchlen = pmatch[2].rm_eo - pmatch[2].rm_so;
         value = (char *) malloc(matchlen + 1);
         if (!value)
         {
            fprintf(stderr, "out of memory\n");
            exit(8);
         }
         strncpy(value, temp + pmatch[2].rm_so, matchlen);
         value[matchlen] = '\0';
      }
      else
      {
         fprintf(stderr, "missing value: %s\n", temp);
         free(keyword);
         keyword = NULL;
         continue;
      }
      configuration_add(list, keyword, value);

      free(keyword);
      keyword = NULL;
      free(value);
      value = NULL;
   }

   free(pmatch);
   regfree(&preg);
   fclose(stream);

   return 0;
}


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
static void configuration_add(configuration * list, const char *keyword, const char *value)
{
   configuration_element *new_element;

   /* check if keyword already exists */
   new_element = (configuration_element *) configuration_find(list, keyword);
   if (new_element)
   {
      if (new_element->value)
      {
         free(new_element->value);
         new_element->value = NULL;
      }
   }
   else
   {
      /* allocate mem for the struct */
      new_element = (configuration_element *) malloc(sizeof(configuration_element));
      if (!new_element)
      {
         fprintf(stderr, "out of memory\n");
         exit(8);
      }

      /* allocate mem for the keyword */
      new_element->keyword = (char *) malloc(strlen(keyword) + 1);
      if (new_element->keyword)
      {
         strcpy(new_element->keyword, keyword);
      }
      else
      {
         fprintf(stderr, "out of memory\n");
         exit(8);
      }

      /* link */
      new_element->next = list->first;
      list->first = new_element;
      list->n_elements++;
   }

   /* allocate mem for the value */
   new_element->value = (char *) malloc(strlen(value) + 1);
   if (new_element->value)
   {
      strcpy(new_element->value, value);
   }
   else
   {
      fprintf(stderr, "out of memory\n");
      exit(8);
   }
}


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
void configuration_free(configuration * list)
{
   configuration_element *lp,
                 *lp_next;

   for (lp_next = list->first; lp_next != NULL;)
   {
      lp = lp_next;
      lp_next = lp_next->next;
      if (lp->keyword)
      {
         free(lp->keyword);
         lp->keyword = NULL;
      }
      if (lp->value)
      {
         free(lp->value);
         lp->value = NULL;
      }
      free(lp);
   }
   list->first = NULL;
   list->n_elements = 0;
}


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
const configuration_element *configuration_find(configuration * list, const char *keyword)
{
   configuration_element *lp = NULL;

   if (!keyword)
   {
      return NULL;
   }

   for (lp = list->first; lp != NULL; lp = lp->next)
   {
      if (strcmp(lp->keyword, keyword) == 0)
      {
         break;
      }
   }

   return lp;
}


/*=****************************************************************************
**
** DESCRIPTION :
**
** RETURN VALUE:
**                                                                           */
/*=***************************************************************************/
static void do_regerror(int errcode, const regex_t * preg)
{
   char          *errbuf;
   size_t         errbuf_size;

   errbuf_size = regerror(errcode, preg, NULL, 0);
   errbuf = (char *) malloc(errbuf_size);
   if (!errbuf)
   {
      fprintf(stderr, "out of memory\n");
      exit(8);
   }
   regerror(errcode, preg, errbuf, errbuf_size);
   fprintf(stderr, "%s\n", errbuf);

   free(errbuf);
}
