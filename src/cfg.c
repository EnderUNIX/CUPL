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
 *  $Id: cfg.c,v 1.2 2006/08/26 08:44:03 simsek Exp $
 *  
 *  Common Config Parser
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/cupl.h"
#include "../include/cfg.h"

extern int errno;

static int parse_config_file(cfg_data *cfg);
static void add_cfg_array(cfg_data *cfg, char *var, char *val);
static void release_cfg_array(cfg_array *head);

/* To alloc cfg_data object and open config file. */
extern cfg_data *cupl_init_cfg(char *path)
{
	cfg_data *cfg;

	if ((cfg = (cfg_data *) malloc(sizeof(cfg_data))) == NULL) {
		fprintf(stderr, "%s: %d: malloc(): %s.\n", __FILE__, __LINE__,
				strerror(errno));
		return NULL;
	}

	if ((cfg->cfd = fopen(path, "r")) == NULL) {
		fprintf(stderr, "%s: %d: fopen(): %s.\n", __FILE__, __LINE__,
				strerror(errno));
		return NULL;
	}

	cfg->vars = NULL;
	cfg->nov = 0;

	if (parse_config_file(cfg) == -1)
		return NULL;
	
	return cfg;
}

/* To free cfg_data object and close config file. */
extern int cupl_release_cfg(cfg_data *cfg)
{
	if (cfg == NULL) return 0;

	fclose(cfg->cfd);

	if (cfg->vars) release_cfg_array(cfg->vars);

	free(cfg);

	return 1;
}

/* To release cfg_array linked list. */
static void release_cfg_array(cfg_array *head)
{
	cfg_array *prev = head;
	cfg_array *next = head->next;

	while (prev != NULL) {
		/* Save coming chain */
		next = prev->next;

		free(prev);

		/* Move next */
		prev = next;
		if (prev) next = prev->next;
	}
	
	return;
}

/* Parse the config file. */
static int parse_config_file(cfg_data *cfg)
{
	int i, j;
	int lcnt = 0;
	int blen;
	char buf[CFG_VAL_LEN];
	char val[CFG_VAL_LEN];
	char var[CFG_VAR_LEN];
	char ch;

	memset(buf, 0, CFG_VAL_LEN);

	while (fgets(buf, CFG_VAL_LEN, cfg->cfd)) {
		lcnt++;
		ch = buf[0];
		blen = strlen(buf) - 1;

		/* Comments or spaces. Skip. */
		if (USELESS_LINE) {
			goto loop_end;
		}

		/* Invalid chars. Report and skip. */
		if (INVALID) {
			fprintf(stderr, "parse_config_file: Invalid character at line %d.\n", lcnt);
			goto loop_end;
		}

		if (IDENTIFIER) {
			fprintf(stderr, "parse_config_file: Variables must start with a char, line: %d.\n", lcnt);
			goto loop_end;
		}

		/* Valid identifier. */

		/* Get variable */
		memset(var, 0, CFG_VAR_LEN);
		for (i=0;i<blen;i++) {
			ch = buf[i];
			if (END_OF_LINE) {
				fprintf(stderr, "parse_config_file: Syntax error at line %d.\n", lcnt);
				goto loop_end;
			}
			if (INVALID) {
				fprintf(stderr, "parse_config_file: Invalid character at line %d.\n", lcnt);
				goto loop_end;
			}
			if (SEPERATOR) {
				break;
			}
			if (i < CFG_VAR_LEN - 1)
				var[i] = ch;
			else {
				fprintf(stderr, "parse_config_file: Too long variable name at line %d.\n", lcnt);
				goto loop_end;
			}
		}

		i++;

		/* Skip extra seperators. */
		for(j=i;j<blen;j++) {
			ch = buf[j];
			if (SEPERATOR)
				continue;
			else
				break;
		}

		i = j;

		/* Get value */
		memset(val, 0, CFG_VAL_LEN);
		for (j=i;j<blen;j++) {
			ch = buf[j];
			if (END_OF_LINE) {
				break;
			}
			if (INVALID) {
				fprintf(stderr, "parse_config_file: Invalid character at line %d.\n", lcnt);
				goto loop_end;
			}
			if ((j - i) < (CFG_VAL_LEN - 1))
				val[j-i] = ch;
			else {
				fprintf(stderr, "parse_config_file: Too long value at line %d.\n", lcnt);
				goto loop_end;
			}
		}

		add_cfg_array(cfg, var, val);

		cfg->nov = cfg->nov + 1;

loop_end:
		memset(buf, 0, CFG_VAL_LEN);
	}

	return 1;
}

/* Add new item to cfg_array linked list. */
static void add_cfg_array(cfg_data *cfg, char *var, char *val)
{
	cfg_array *tail;
	cfg_array *cfgp;

	tail = cfg->vars;

	if (tail != NULL)
		while (tail->next != NULL)
			tail = tail->next;

	if ((cfgp = (cfg_array *) malloc(sizeof(cfg_array))) == NULL) {
		fprintf(stderr, "%s: %d: malloc(): %s.\n", __FILE__, __LINE__, strerror(errno));
		return;
	}

	strncpy(cfgp->var, var, CFG_VAR_LEN-1);
	strncpy(cfgp->val, val, CFG_VAL_LEN-1);
	cfgp->next = NULL;

	if (cfg->vars == NULL) {
		cfg->vars = cfgp;
	}
	else {
		tail->next = cfgp;
	}


	return;
}

/* To print all the parsed items */
extern void cupl_print_items(cfg_data *cfg)
{
	cfg_array *tmp;

	if (cfg == NULL) return;

	printf("Number of items parsed: %d\n\n", cfg->nov);
	printf("Items:\n");

	tmp = cfg->vars;

	while (tmp != NULL) {
		printf("%s: %s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}

	return;
}

/* To get a variable from cfg_data object */
extern char *cupl_get_var(char *var, cfg_data *cfg)
{
	cfg_array *tmp = cfg->vars;

	if (cfg == NULL) return NULL;

	while (tmp != NULL) {
		if (strncmp(tmp->var, var, sizeof(tmp->var)) == 0) 
			return tmp->val;
		tmp = tmp->next;
	}

	return NULL;
}




