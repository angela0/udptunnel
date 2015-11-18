udptunnel.o : udptunnel.h udptunnel.c
	gcc -c udptunnel.c udptunnel.h

serv : udptunnel.o udptunnel_serv.c
	gcc udptunnel.o udptunnel_serv.c -o serv

cli : udptunnel.o udptunnel_cli.c
	gcc udptunnel.o udptunnel_cli.c -o cli


cus : udptunnel.o udptunnel_cum.c
	gcc udptunnel.o udptunnel_cum.c -o cus

bet : udptunnel.o udptunnel_bet.c
	gcc udptunnel.o udptunnel_bet.c -o bet
