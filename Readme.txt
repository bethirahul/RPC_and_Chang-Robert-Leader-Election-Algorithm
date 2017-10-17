//********************************************************************
//
//  Rahul Bethi
//  Advanced Operating Systems
//  Programming Project #4: RPC and Chang and Robert's
//			    Leader Election Algorithm
//  October 27, 2016
//  Instructor: Dr. Ajay K. Katangur
//
//  Read me file
//
//********************************************************************
----------------------------------------------------
Part 1: RPC
----------------------------------------------------
This program simulates Remote Procedure Calls (RPC). First the primefib.x program is executed with rpcgen command as shown in the input/output section. This generates client and server .c files. These two files are edited. The client program takes the input number and then calls the server for prime number function first with the input number. After obtaining the result, it then calls the fibonacci number function. It displays the result as soon as it gets it along with the time elapsed calculated by checking times before and after calling the server and getting the result. Server program takes the input call and number and calls the appropriate function with the input number. It then calculates the prime number or the fibonacci number and send back the result back to the client.

Note:- One make file for both the parts. Type 'make' to run the make file, just like the previous projects.

----------------------------------------------------
Part 2: Chang and Robert's Leader Election Algorithm
----------------------------------------------------
This program is to implement Chang and Robert's Leader Election Algorithm using MPI. Each process has its own ID, which is generated randomly at first. Every process will be in passive state at first. Initial process which has to start the election is given in the input. This process starts the election by making its status to Active and sends its ID to its neighbor. The next process which receives the ID takes compares its own ID and if its own ID is larger, it makes its ID was the message and makes its status to active. If not, it will make its state to passive if it’s not and just forward the ID number it received to its next neighbor. If the message comes to the process which has the same ID., then it is the leader. Now this leader sends elected message to its next neighbor. This elected message is sent to the next neighbor again by the received process and also it will exit. Finally, the message comes back to the leader. Leader then prints that it is the leader and then exits.

Note:- usleep function is only used to wait for the processes to print and not during the simulation.
Note:- One make file for both the parts. Type 'make' to run the make file, just like the previous projects.

//********************************************************************
//  FILE NAMES
//********************************************************************
Readme.txt
Makefile
election.c
election.pdf
primefib.x
primefib.h
primefib_client.c
primefib_server.c
primefib_clnt.c
primefib_svc.c

//********************************************************************
//  EXAMPLE INPUT/OUTPUT
//********************************************************************
----------------------------------------------------
Part 1: RPC
----------------------------------------------------
$ rpcgen -C -a primefib.x

<<< edited primefib_client.c, primefib_server.c files >>>

$ make
gcc -c -o primefib_clnt.o primefib_clnt.c
gcc -c -o primefib_client.o primefib_client.c
primefib_client.c:36: warning: conflicting types for ‘primefib_prog_1’
primefib_client.c:29: note: previous implicit declaration of ‘primefib_prog_1’ was here
gcc -o primefib_client primefib_clnt.o primefib_client.o
gcc -c -o primefib_svc.o primefib_svc.c
gcc -c -o primefib_server.o primefib_server.c
gcc -o primefib_server primefib_svc.o primefib_server.o
mpecc -mpilog election.c -o election

<<< note that last line of make file also compiles Part 2 (Chang and Robert's Leader Election Algorithm) >>>

Server side
$ ./primefib_server

Client side
$ ./primefib_client joker.tamucc.edu 9
Prime number 9 is 23 and the time taken is 75 micro seconds.
Fibonacci number 9 is 21 and the time taken is 30 micro seconds.

----------------------------------------------------
Part 2: Chang and Robert's Leader Election Algorithm
----------------------------------------------------

$ mpirun -np 5 election 3
--------------------------------------------------------------------------
A request was made to bind to that would result in binding more
processes than cpus on a resource:

   Bind to:     CORE
   Node:        clst
   #processes:  2
   #cpus:       1

You can override this protection by adding the "overload-allowed"
option to your binding directive.
--------------------------------------------------------------------------

***************************************************
Chang and Roberts Election Algorithm Implementation
***************************************************

Initially Rank:  0, Identifier: 1189915677
Initially Rank:  1, Identifier: 1964636767
Initially Rank:  2, Identifier: 1652995801
Initially Rank:  3, Identifier: 275818721
Initially Rank:  4, Identifier: 1052072885

Processor 3 is initiating the election and sending the number 275818721 to processor 4

Phase: 1, Rank:  0, Identifier: 1189915677, Status: Active
Phase: 1, Rank:  1, Identifier: 1964636767, Status: Active
Phase: 1, Rank:  2, Identifier: 1652995801, Status: Passive
Phase: 1, Rank:  4, Identifier: 1052072885, Status: Active
Phase: 1, Rank:  3, Identifier: 275818721, Status: Passive
Phase: 2, Rank:  1, Identifier: 1964636767, Status: Active
Phase: 2, Rank:  4, Identifier: 1052072885, Status: Passive
Phase: 2, Rank:  0, Identifier: 1189915677, Status: Passive

I am the Leader and my Rank is:  1 and my Identifier is: 1964636767
