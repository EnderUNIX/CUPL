/*
 *  Copyright (C) 2006  Baris Simsek, http://www.enderunix.org/simsek
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  $Id: string.c,v 1.3 2006/08/26 09:35:04 simsek Exp $
 *
 *  Library for data structures.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

#include "../include/cupl.h"
#include "../include/string.h"

static int regex_match_pattern(regex_t *regexp, char *buffer);

/* Regular expression support. */
static int regex_match_pattern(regex_t *regexp, char *buffer)
{
	int start = 0;						/* The offset from the beginning of the buffer */
	size_t no_sub = regexp->re_nsub + 1;			/* How many matches are there in a buffer? */
	regmatch_t *result;

	if ((result = (regmatch_t *) malloc(sizeof(regmatch_t) * no_sub)) == 0)
	{
		fprintf(stderr, "%s: %d: malloc(): %s.\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}
  
	while (regexec(regexp, buffer+start, no_sub, result, 0) == 0)
	{
		free(result);
		return 1;					/* Found a match. */
	}

	free(result);

	return 0;
}

/* \todo Should be regex library independent.
   Should be written a small regex library. */
extern int cupl_match_regex(char *buffer, char *pattern)
{
	int ret = 0;
	regex_t *regexp; /* Regular expression pointer for the filter. */

	/* Allocate space for the regular expressions. */
	if ((regexp = (regex_t *) malloc(sizeof(regex_t))) == NULL) {
		fprintf(stderr, "%s: %d: malloc(): %s.\n", __FILE__, __LINE__, strerror(errno));
		return -1;
	}

	memset(regexp, 0, sizeof(regex_t));

	if ((ret = regcomp(regexp, pattern, 0)) != 0) /* Compile the regular expression. */
	{
		regfree(regexp);
		free(regexp);
		return -1;
	}

	ret = regex_match_pattern(regexp, buffer);

	regfree(regexp);
	free(regexp);

	return ret;
}



