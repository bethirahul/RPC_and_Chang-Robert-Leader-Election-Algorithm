//********************************************************************
//
// Rahul Bethi
// Advanced Operating Systems
// Project #4: RPC and Chang and Robert's Leader Election Algorithm
// December 01, 2016
// Instructor: Dr. Ajay K. Katangur
//
// Part 1: RPC - Client
//
//********************************************************************

#include "primefib.h"
#include "time.h" // to calculate time elapsed

int main(int argc, char *argv[])
{
	char *host;
	int num;

	if(argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	num = atoi(argv[2]);
	if(num > 0) // condition to check if the input is more than zero
		primefib_prog_1(host, num); // call the client program
	else
		printf("Error: Input must be more than 0\n"); // error when input is less than or equal to zero
	exit(0);
}

// client program which calls two function calls to server
void primefib_prog_1(char *host, int num)
{
	CLIENT *clnt;
	int  *result_1;
	int  prime_1_arg = num; // prime number function argument
	int  *result_2;
	int  fib_1_arg = num; // fibonacci number function argument
	unsigned long timeTaken = 0; // to calculate time in micro seconds
	struct timeval startTime, endTime; // defined in time.h

	#ifndef	DEBUG
		clnt = clnt_create(host, PRIMEFIB_PROG, PRIMEFIB_VERSION, "udp");
		if(clnt == NULL)
		{
			clnt_pcreateerror(host);
			exit(1);
		}
		
	#endif	/* DEBUG */
		// prime number
		gettimeofday(&startTime, NULL); // start time
		result_1 = prime_1(&prime_1_arg, clnt); // calling prime number function in server
		if( result_1 == (int *)NULL )
		{
			clnt_perror(clnt, "call failed");
		}
		gettimeofday(&endTime, NULL); // end time
		timeTaken = ( ((endTime.tv_sec - startTime.tv_sec)*1000000L) + endTime.tv_usec ) - startTime.tv_usec; // calculate time difference (difference of seconds and also microseconds and converting to microseconds)
		printf("Prime number %d is %d and the time taken is %lu micro seconds.\n", num, *result_1, timeTaken);
		
		// fibonacci number
		gettimeofday(&startTime, NULL);
		result_2 = fib_1(&fib_1_arg, clnt); // calling fibonacci number function in server
		if( result_2 == (int *)NULL )
		{
			clnt_perror(clnt, "call failed");
		}
		gettimeofday(&endTime, NULL);
		timeTaken = ( ((endTime.tv_sec - startTime.tv_sec)*1000000L) + endTime.tv_usec ) - startTime.tv_usec;
		printf("Fibonacci number %d is %d and the time taken is %lu micro seconds.\n", num, *result_2, timeTaken);
		
	#ifndef	DEBUG
		clnt_destroy(clnt);
	
	#endif	 /* DEBUG */
}

