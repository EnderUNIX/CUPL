CC = cc -g
AR = ar rc libcupl.a
LDFLAGS = -L/usr/local/lib -L.

CUPL_OBJS = cfg.o cupl.o ds.o string.o

all: clean lib install

lib: $(CUPL_OBJS)
	$(AR) $(CUPL_OBJS)
	ranlib libcupl.a

install:
	cp -f libcupl.a /usr/local/lib
	cp -f ../include/cupl.h /usr/local/include

clean:
	rm -f *~ *core* *pid
	rm -f $(CUPL_OBJS) *.o *.so *~
	rm -f libcupl.a


