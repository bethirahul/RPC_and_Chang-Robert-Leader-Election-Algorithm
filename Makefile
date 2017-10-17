make:
	gcc -c -o primefib_clnt.o primefib_clnt.c
	gcc -c -o primefib_client.o primefib_client.c
	gcc -o primefib_client primefib_clnt.o primefib_client.o
	gcc -c -o primefib_svc.o primefib_svc.c
	gcc -c -o primefib_server.o primefib_server.c
	gcc -o primefib_server primefib_svc.o primefib_server.o

	mpecc -mpilog election.c -o election