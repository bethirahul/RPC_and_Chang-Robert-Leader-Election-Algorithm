//********************************************************************
//
// Rahul Bethi
// Advanced Operating Systems
// Project #4: RPC and Chang and Robert's Leader Election Algorithm
// December 01, 2016
// Instructor: Dr. Ajay K. Katangur
//
// Part 2: Chang and Robert's Leader Election Algorithm using MPI
//
//********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h> // to set srand
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rank, size, root = 0;
	MPI_Status status;
	
	MPI_Init(&argc, &argv); // Initializing MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // to know the rank of each process
	MPI_Comm_size(MPI_COMM_WORLD, &size); // to know the total number of processes
	
	if(size < 3) // condition to check minimum 3 processes to run the program
	{
		if(rank == root)
			printf("Error: Minimum 3 processes are needed to run the simulation\n");
		MPI_Finalize();
		return;
	}
	
	int initProcess;
	sscanf(argv[1], "%d", &initProcess);
	if(initProcess >= size || initProcess < 0) // initial process must be less than the size and grater than zero
	{
		if(rank == root)
			printf("Error: Rank of the inital process must be from 0 to %d\n", size-1);
		MPI_Finalize();
		return;
	}
	
	int i, ID, recvID, sender, phase = 0, coordinator = -1, message[3];
	enum states_enum { passive = 0, active = 1 } state;
	enum boolean { false = 0, true = 1 } running, leader;
	state = passive;
	leader = false;
	running = true;
	
	srand(time(NULL) + rank); // seeding random function
	
	if(rank == root)
	{
		printf("\n***************************************************\nChang and Roberts Election Algorithm Implementation\n***************************************************\n\n");
	}
	
	usleep(1000); // wait for it the heading to be printed
	
	for(i=0;i<size;i++)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		if(rank == i)
		{
			ID = rand() % 10000000000; //from 0 to 9,999,999,999 (10 digits)
			printf("Initially Rank:  %d, Identifier: %d\n", rank, ID);
		}
		usleep(1000); // wait for the above printf to be printed
	}
	
	MPI_Barrier(MPI_COMM_WORLD); // Barrier to align all process to start simulation
	
	if(rank == initProcess)
	{
		sender = rank+1;
		if(sender >= size) // if last process, then the next process is zero
			sender = 0;
		printf("\nProcessor %d is initiating the election and sending the number %d to processor %d\n\n", rank, ID, sender);
		state = active;
		message[0] = 0;
		message[1] = -1; // slot invalid as this is election message
		message[2] = ID; // sending ID
		MPI_Send(message, 3, MPI_INT, sender, 0, MPI_COMM_WORLD); // initial process starting election
	}
	
	usleep(2500); // wait for initial process to print that its starting
	
	while(running) // simulation loop
	{
		MPI_Recv(message, 3, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		
		if(message[0] == 1) // elected message
		{
			coordinator = message[1]; // storing soordinator
			recvID = message[2]; // storing coordinator ID
			state = passive; // making itself passive
			running = false; // end simulation
		}
		
		else // election message
		{
			if(message[2] < ID)
			{
				state = active; // if received id is less the its own id, make it active and send its own id
				message[2] = ID;
			}
			else if(message[2] > ID)
				state = passive; // else make itself passive
			else
			{
				leader = true; // if the ID comes back, it is the coordinator
				message[0] = 1; // start sending elected message with result
				message[1] = rank;
			}
			phase++;
			printf("Phase: %d, Rank:  %d, Identifier: %d, Status: ", phase, rank, ID);
			if(state)
				printf("Active\n");
			else
				printf("Passive\n");
		}
		sender = rank+1;
		if(sender >= size)
			sender = 0;
		MPI_Send(message, 3, MPI_INT, sender, 0, MPI_COMM_WORLD); // sending message to next process
	}
	
	usleep(2500);
	
	if(leader)
		printf("\nI am the Leader and my Rank is:  %d and my Identifier is: %d\n\n", rank, ID); // finally leader will print and exit
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	MPI_Finalize();
	return;
}