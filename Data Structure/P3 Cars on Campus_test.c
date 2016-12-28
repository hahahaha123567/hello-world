/*
Zhejiang University has 8 campuses and a lot of gates. 
From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate. 
Now with all the information available, you are supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.

Input Specification:
Each input file contains one test case. Each case starts with two positive integers N (≤10^​4​), the number of records, and K (≤8×10^​4) the number of queries. 
Then NN lines follow, each gives a record in the format:
plate_number hh:mm:ss status
where plate_number is a string of 7 English capital letters or 1-digit numbers; 
hh:mm:ss represents the time point in a day by hour:minute:second, with the earliest time being 00:00:00 and the latest 23:59:59; 
and status is either in or out.
Note that all times will be within a single day. 
Each in record is paired with the chronologically next record for the same car provided it is an out record. 
Any in records that are not paired with an out record are ignored, as are out records not paired with an in record. 
It is guaranteed that at least one car is well paired in the input, and no car is both in and out at the same moment. 
Times are recorded using a 24-hour clock.
Then KK lines of queries follow, each gives a time point in the format hh:mm:ss. 
Note: the queries are given in accending order of the times.

Output Specification:
For each query, output in a line the total number of cars parking on campus. 
The last line of output is supposed to give the plate number of the car that has parked for the longest time period, and the corresponding time length. 
If such a car is not unique, then output all of their plate numbers in a line in alphabetical order, separated by a space.

Sample Input:
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
Sample Output:
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
*/
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

char* rand_car();			//generate the Names
int Compare(const void *a,const void *b);	//an auxiliary function used in qsort

int main(void)
{
	int N, K;				//total number of records and queries
	int CarNum;				//the total number of cars
	char** Name;			//an array of pointer that stores the Names
	int isUsed[24*60*60];	//an auxiliary array that store every second in the day, to avoid one moment to be printed twice
	char *Status[2];		//store the two status
	int RecordTime;
	int* QueryTime;

	//some initials
	FILE* fp;
	fp = fopen("niconiconi.txt", "w");
	Status[0] = "in";		
	Status[1] = "out";		
	srand((unsigned int)time(NULL));

	//total numbers
	N = rand() % 9999 + 2;						//2 <= N <= 10000							
	CarNum = N / 2;								//guarantee that at least one car is well paired in the input
	K = (int)((float)rand() / 32768 * 80000);	//0 <= K <= 80000
	fprintf(fp, "%d %d\n", N, K);	

	//record: generate names
	Name = malloc(sizeof(char *) * CarNum);
	for(int i = 0; i < CarNum; i++)
		Name[i] = rand_car();

	//record: generate time and status
	for(int i = 0; i < 24*60*60; i++)
		isUsed[i] = 0;
	for(int i = 0; i < N; i++){
		do{	
			QueryTime[i] = rand() + rand() + rand() % 14467;
		}while(isUsed[RecordTime]);				//make sure that no car is both in and out at the same moment
		isUsed[RecordTime] = 1;
		fprintf(fp, "%s %02d:%02d:%02d %s\n", 
			Name[rand() % CarNum], RecordTime / (60*60), RecordTime / (60*60) % (60*60), RecordTime % 60, Status[rand() % 2]);
	}

	//query: generate time
	QueryTime = malloc(sizeof(int) * K);
	for(int i = 0; i < 24*60*60; i++)
		isUsed[i] = 0;
	for(int i = 0; i < K; i++){
		do{
			//QueryTime[i] = (int)((float)rand() / 32768 * 24 * 60 *60);
			//this random is wrong, because function rand() can only produce 32768 different numbers
			QueryTime[i] = rand() + rand() + rand() % 14467;
			//by this way, the numbers are not generated with the same possiblity, but it doesn't matter
		}while(isUsed[QueryTime[i]]);
		isUsed[QueryTime[i]] = 1;
	}
	qsort(QueryTime, K, sizeof(int), Compare);	//sort the K time 
	for(int i = 0; i < K; i++){
		fprintf(fp, "%02d:%02d:%02d\n", 
			QueryTime[i] / (60*60), QueryTime[i] % (60*60) / 60, QueryTime[i] % 60);
	}

	fclose(fp);
	return 0;
}

char* rand_car()
{
	char* car = malloc(sizeof(int) * 8);

	/*	char  ASCII
		0-9:  48-57
		A-Z:  65-90	*/
	for(int i = 0; i < 7; i++){
		do{
			car[i] = rand() % 43 + '0';
		}while('9' < car[i] && car[i] < 'A');
	}
	car[7] = '\0';

	return car;
}

int Compare(const void *a,const void *b)
{
	if(*(int*)a < *(int*)b)
		return -1;
	else if(*(int*)a > *(int*)b)
		return 1;
	else
		return 0;
}
