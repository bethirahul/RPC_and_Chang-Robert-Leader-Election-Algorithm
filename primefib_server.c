//********************************************************************
//
// Rahul Bethi
// Advanced Operating Systems
// Project #4: RPC and Chang and Robert's Leader Election Algorithm
// December 01, 2016
// Instructor: Dr. Ajay K. Katangur
//
// Part 1: RPC - Server
//
//********************************************************************

#include "primefib.h"

// prime number function
int *prime_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result = 0;
	int i, count = 0, num = 2, flag = 0;
	
	//printf("Prime number %d is ", *argp);
	while(count < *argp) // check prime number till the desired number's prime number is obtained
	{
		flag = 0;
		for(i=2; i<=(num/2); i++) // start with 2 and make flag 1 if the number is a composite number
		{
			if(num%i == 0)
			{
				flag = 1;
				break; // if the number is composute number, come out of for loop
			}
		}
		result = num; // store the last found prome number into result
		num++;
		if(flag == 0) // count number of prime numbers
			count++;
	}
	//printf("%d\n", result);

	return &result; // send result
}

// fibonacci number function
int *fib_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result = 0;
	int i, a[3]; // 3 variables to find out fibonacci numbers
	
	//printf("Finonacci number %d is ", *argp);
	a[0] = 0; // first number
	a[1] = 1; // second number
	if(*argp < 3)
		result = a[*argp-1]; // simply display the fibonacci numbers for first two fibonacci numbers
	else
	{
		for(i=0; i<*argp-2; i++)
		{
			a[2] = a[0] + a[1]; // final number = first + second numbers
			a[0] = a[1];
			a[1] = a[2];
			//printf("%d ", a[2]);
		}
		result = a[2]; // store the last known fibonacci number into result
	}
	//printf("; %d\n", result);

	return &result;
}