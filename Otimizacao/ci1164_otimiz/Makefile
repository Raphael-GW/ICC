# PROGRAMA
        PROG = matmult
        OBJS = matriz.o utils.o

# Compilador
           CC = gcc

       CFLAGS = -O3 -mavx2 -march=native -DLIKWID_PERFMON -I /home/soft/likwid/include
       LFLAGS = -L /home/soft/likwid/lib -llikwid -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h *.txt Makefile resultados perfctr
DISTDIR = ${USER}

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

avx: $(PROG)

debug:         CFLAGS += -g -D_DEBUG_
debug:         $(PROG)

$(PROG): $(PROG).o

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp

purge:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -chvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

