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
 *  $Id: cupl.h,v 1.7 2006/08/25 19:42:39 simsek Exp $
 *
 *  CUPL library header file.
 *
 */

#ifndef CUPL_CUPL_H
#define CUPL_CUPL_H

#define CUPL_VERSION "0.8"
#define CFG_VAR_LEN 32
#define CFG_VAL_LEN 512

typedef struct cfg_array {
    char var[CFG_VAR_LEN]; /* Variable */
    char val[CFG_VAL_LEN]; /* Value */
    struct cfg_array *next; /* Next variable */
} cfg_array;

typedef struct cfg_data {
    int nov;  /* Number of variable parsed */
    FILE *cfd;  /* Config file descriptor */
    cfg_array *vars;  /* Parsed variables */
} cfg_data;

/* Library functions */
extern void cupl_print_info();

/* Common Config Parser */
extern cfg_data *cupl_init_cfg(char *path);
extern char *cupl_get_var(char *var, cfg_data *cfg);
extern int cupl_release_cfg(cfg_data *cfg);
extern void cupl_print_items(cfg_data *cfg);

/* Data structures */
extern unsigned int cupl_hash_get(char *buf, unsigned int len, int tbl_size);

/* String processing */
extern int cupl_match_regex(char *buffer, char *pattern);

#endif


