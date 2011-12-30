# $Id: Makefile,v 1.3 2006/08/26 09:46:15 simsek Exp $
#

DIRS = src

all:
	for DIR in $(DIRS); do \
		echo; \
		echo "Entering $$DIR..."; \
		(cd $$DIR; ${MAKE} all); \
	done

clean:
	for DIR in $(DIRS); do \
		echo; \
		echo "Entering $$DIR..."; \
		(cd $$DIR; ${MAKE} clean); \
	done


