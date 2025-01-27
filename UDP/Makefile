COMPILER=gcc
EXE_DIR=/tmp/ping_pong/UDP
FICHIERS=erreur udp nombre
OBJS=$(FICHIERS:%=%.o)

all: client_udp_ping_pong serveur_udp_ping_pong

client_udp_ping_pong: client_udp_ping_pong.c $(OBJS)
	mkdir -p $(EXE_DIR)
	$(COMPILER) $(OBJS) client_udp_ping_pong.c -o $(EXE_DIR)/client_udp_ping_pong
	chmod -R u+x $(EXE_DIR)/client_udp_ping_pong

serveur_udp_ping_pong: serveur_udp_ping_pong.c $(OBJS)
	mkdir -p $(EXE_DIR)
	$(COMPILER) $(OBJS) serveur_udp_ping_pong.c -o $(EXE_DIR)/serveur_udp_ping_pong
	chmod -R u+x $(EXE_DIR)/serveur_udp_ping_pong

udp.o: udp.c udp.h
	$(COMPILER) -c udp.c -o udp.o

erreur.o: erreur.c erreur.h
	$(COMPILER) -c erreur.c -o erreur.o

nombre.o: nombre.c nombre.h
	$(COMPILER) -c nombre.c -o nombre.o

clean:
	rm -f $(OBJS) $(EXE_DIR)/* testsuite
