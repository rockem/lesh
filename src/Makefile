CC=	 gcc	         
STD=	 _GNU_SOURCE
OBJS=	 main.o general.o getline.o hash.o parser.o executer.o lesh_perl.o cmd/cd_cmd.o
EXE= 	 lesh
PERL_CC= `perl -MExtUtils::Embed -e ccopts`
PERL_LD= `perl -MExtUtils::Embed -e ldopts` 
# CHK_SOURCES= Point.cpp Rect.cpp Game.cpp

.c.o:
	$(CC) -c -Wall -g -O0 -D$(STD) -D_LINUX $(PERL_CC) $<

main: $(OBJS) commands
	$(CC) $(OBJS) -o $(EXE) $(PERL_LD)

.PHONY: check-syntax
check-syntax:
	$(CC) -Wall -Wextra -pedantic -fsyntax-only -D$(STD) -D_LINUX $(PERL_CC) $(CHK_SOURCES)

commands: 
	make -C ./cmd

clean:
	rm -f *.o
#	rm -f ../*.o
	make -C ./cmd clean

clobber: clean
	rm -f $(EXE)

