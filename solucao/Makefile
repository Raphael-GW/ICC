    CC     = gcc

    CFLAGS = 
    LFLAGS = -lm

      PROG = prog

      OBJS = utils.o lu.o matriz.o

.PHONY: clean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

plain: CFLAGS += -O0
debug: CFLAGS += -g -D__DEBUG__

plain debug: $(PROG)

$(PROG):  $(OBJS) prog.o
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak */*~ */*.bak

purge:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o core a.out
	@rm -f *.png marker.out *.log
