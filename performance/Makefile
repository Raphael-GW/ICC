       PROG   = matmult

           CC = gcc 
         OBJS = matriz.o utils.o

       LIKWID = -DLIKWID_PERFMON -I/home/soft/likwid/include -L/home/soft/likwid/lib -llikwid
       CFLAGS = -Wall -O3 
       LFLAGS = -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h *.txt Makefile resultados perfctr 
DISTDIR = ${USER}

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

debug:         CFLAGS += -g -DDEBUG
debug:         $(PROG)

$(PROG):  $(PROG).o

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) $(LIKWID)

clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp

purge:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -chvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

