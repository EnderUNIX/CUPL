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
 *  $Id: ds.c,v 1.5 2006/08/24 22:43:27 simsek Exp $
 *
 *  Library for data structures.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "../include/cupl.h"
#include "../include/ds.h"

static unsigned int cdb_hashadd(unsigned int h, unsigned char c);

/* DJB's hash function, derived from CDB project. */
/* http://cr.yp.to/cdb.html                       */
static unsigned int cdb_hashadd(unsigned int h, unsigned char c)
{
	h += (h << 5);

	return h ^ c;
}

extern unsigned int cupl_hash_get(char *buf, unsigned int len, int tbl_size)
{
	unsigned int h;

	h = CDB_HASHSTART;
	while (len) {
		h = cdb_hashadd(h,*buf++);
		--len;
	}

	return h % tbl_size;
}


