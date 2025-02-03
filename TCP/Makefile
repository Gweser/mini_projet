COMPILER=gcc
EXE_DIR=/tmp/
FICHIERS=erreur tcp nombre
OBJS:=$(FICHIERS:%=%.o)

all: serveur_tcp testsuite analyse
	-rm $(OBJS)

serveur_tcp: serveur_tcp.c $(EXE_DIR) $(OBJS)
	mkdir -p $(EXE_DIR)/$@
	$(COMPILER) erreur.o tcp.o nombre.o serveur_tcp.c -o $(EXE_DIR)/$@/serveur_tcp
	chmod -R u+x $(EXE_DIR)/$@

testsuite: testsuite.c tcp.o erreur.o nombre.o
	$(COMPILER) -o testsuite testsuite.c tcp.o erreur.o nombre.o -lcunit

tcp.o: tcp.c tcp.h
	$(COMPILER) -c tcp.c -o tcp.o

erreur.o: erreur.c erreur.h
	$(COMPILER) -c erreur.c -o erreur.o

nombre.o: nombre.c nombre.h
	$(COMPILER) -c nombre.c -o nombre.o

analyse:
	cppcheck --enable=all --inconclusive --std=c99 --language=c --suppress=missingIncludeSystem .

$(EXE_DIR):
	mkdir -p $(EXE_DIR)

clean:
	rm -f *.o testsuite
	rm -rf $(EXE_DIR)/serveur_tcp
