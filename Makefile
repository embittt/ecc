CFLAGS=-std=c11 -g -static
SRCS=main.c parse.c codegen.c container.c
OBJS=$(SRCS:.c=.o)

ecc: $(OBJS)
	$(CC) -o ecc $(OBJS) $(LDFLAGS)

$(OBJS): ecc.h

test: ecc
	./test.sh

testfncall: ecc
	./testfncall.sh

clean:
	rm -f ecc *.o *~ tmp*

.PHONY: test clean
