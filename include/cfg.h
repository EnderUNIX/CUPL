/* $Id: cfg.h,v 1.1 2006/08/25 19:42:39 simsek Exp $ */

/* Common Config Parser */

#ifndef CUPL_CFG_H
#define CUPL_CFG_H

#define INVALID (((ch < 32) && (ch != '\t')) || (ch > 126))
#define IDENTIFIER ((ch < 65) || ((ch > 90) && (ch < 97)) || (ch > 122))
#define SEPERATOR ((ch == ' ') || (ch == '=') || (ch == '\t'))
#define END_OF_LINE (ch == '\0')
#define USELESS_LINE ((ch == '#') || (ch == ';') || (ch == ' ') || (ch == '\n'))


#endif

