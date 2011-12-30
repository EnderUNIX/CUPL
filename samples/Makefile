CC = cc -g
LIBS = -lcupl
LDFLAGS = -L/usr/local/lib -I/usr/local/include

SAMPLE_OBJS = cfg-sample.o hash-sample.o regex-sample.o

all: clean samples

samples: $(SAMPLE_OBJS)
	$(CC) -o cfg cfg-sample.o $(LIBS) $(LDFLAGS)
	$(CC) -o hash hash-sample.o $(LIBS) $(LDFLAGS)
	$(CC) -o regex regex-sample.o $(LIBS) $(LDFLAGS)

clean:
	rm -f $(OBJS) *.o *.so *~
	rm -f cfg
	rm -f hash
	rm -f regex


