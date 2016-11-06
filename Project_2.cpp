// Project_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Initial code by Naser Al Madi (Zero-Cool)
//Operating Systems - Scheduling project
//21-OCT-2016
//student name:
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>



//data process ID, Burst time, and priority
//size is the size of the arrays or data records
std::string pID[10];
int burst[10];
int priority[10];
int size;


struct process
{
	std::string pid;
	int cpu_burst;
	int priority;
	int read = 0;
	void print_struct()
	{
		std::cout << "pid: " << pid << std::endl
			<< "cpu_burst " << cpu_burst << std::endl
			<< "Priority: " << priority << std::endl
			<< "read: " << read << std::endl;
	}
};

process processes[6];
//the function initializes the data arrays with records from the file stream
void initFrom(std::ifstream& in) {

	std::string id, temp;
	int b_time;
	int proi;
	int i = 0;
	//process * pointer = new process[10];//array of process structures
	
	//prints out the header of the file
	if (!in.eof()) {
		in >> id;
		std::cout << "\n" << id << "\t";
		in >> temp;
		std::cout << temp << "\t";
		in >> temp;
		std::cout << temp << "\n";
	}
	
	//reading in data from the file and storing it in the right array
	while (!in.eof() && in >> id && in >> b_time && in >> proi && i < 10) {

		pID[i] = id;
		std::cout << pID[i] << "\t";
		
		processes[i].pid = pID[i];//adding to struct

		burst[i] = b_time;
		std::cout << burst[i] << "\t";
		processes[i].cpu_burst = burst[i];//adding cpu burst time to struct

		priority[i] = proi;
		std::cout << priority[i] << "\n";
		processes[i].priority = priority[i];//adding priority time to struct

		
		i++;
	}
	//the size of the arrays is the same
	size = i;
	std::cout << "size: " << size;
	std::cout << "\nDone reading data from file\n";

	for (int x = 0; x < size; x++)
	{
		processes[x].print_struct();
	}
	
}





//First Come First Serve implementation, this is a working example to show you how the output could look like
void myFCFS() {
	int wait_t[10];
	int turn_t[10];
	double avg_wait = 0;
	double avg_turn = 0;
	int i = 0;
	int t = 0;

	std::cout << "\nPID\twait\tturnaround\n";

	//calculating wait-time and turnarround-time for each process
	while (i<size) {
		//compute wait time
		wait_t[i] = t;
		t = t + burst[i];
		//compute turnaround time
		turn_t[i] = wait_t[i] + burst[i];

		std::cout << "P" << i + 1 << "\t" << wait_t[i] << "\t" << turn_t[i] << "\n";
		i++;
	}

	//calculating the averages of wait time and turnaround time
	i = 0;
	while (i<size) {
		avg_wait = avg_wait + wait_t[i];
		avg_turn = avg_turn + turn_t[i];
		i++;
	}

	avg_wait = avg_wait / size;
	avg_turn = avg_turn / size;

	//printing the averages
	std::cout << "AVG wait is: " << avg_wait << "\n";
	std::cout << "AVG turnaround is: " << avg_turn << "\n";

}




void mySJF() {
	int wait_t[10];
	int turn_t[10];
	double avg_wait = 0;
	double avg_turn = 0;
	int i = 0;
	int t = 0;
	int smallest_cpu;
	std::string pid_arr[10];//array to store pid in
	int priority_arr[10];//array to store priorityies in
	int burstArr[10];
	for (int z = 0; z < size; z++)
	{
		burstArr[z] = burst[z];
		//std::cout << burst[z] << std::endl;
	}
	


	std::sort(burstArr, burstArr + size);//sorts cpu_burst times
	

	//matching sorted cpu burst time to pid and priority 
	for (int x = 0; x < 6; x++)//iterate through sorted burst array
	{
		for (int y = 6; y >= 0; y--)//iterate through processes array
		{
			if (burstArr[x] == processes[y].cpu_burst)
			{
				//std::cout << burst[x] << "=" << processes[y].cpu_burst << std::endl;
				pid_arr[x] = processes[y].pid;//matching pid from struct to its proper place in array
				priority_arr[x] = processes[y].priority;// matching priority from struct to its proper place in array

			}
		}
		
	}

	std::cout << "\nPID\twait\tturnaround\n";

	//calculating wait-time and turnarround-time for each process
	while (i<size) {
		//compute wait time
		wait_t[i] = t;
		t = t + burstArr[i];
		//compute turnaround time
		turn_t[i] = wait_t[i] + burstArr[i];

		std::cout << "P" << pid_arr[i] << "\t" << wait_t[i] << "\t" << turn_t[i] << "\n";
		i++;
	}

	//calculating the averages of wait time and turnaround time
	i = 0;
	while (i<size) {
		avg_wait = avg_wait + wait_t[i];
		avg_turn = avg_turn + turn_t[i];
		i++;
	}

	avg_wait = avg_wait / size;
	avg_turn = avg_turn / size;

	//printing the averages
	std::cout << "AVG wait is: " << avg_wait << "\n";
	std::cout << "AVG turnaround is: " << avg_turn << "\n";

	

}

void myPriority() {
	// for you to implement
	int wait_t[10];
	int turn_t[10];
	double avg_wait = 0;
	double avg_turn = 0;
	int i = 0;
	int t = 0;
	int smallest_cpu;
	std::string pid_arr[10];//array to store pid in
	int burst_arr[10];//array to store cpu_bursts in
	int priorityArr[10];
	for (int z = 0; z < size; z++)
	{
		priorityArr[z] = priority[z];
		//std::cout << burst[z] << std::endl;
	}


	std::sort(priorityArr, priorityArr + size);//sorts priority
										 /*for (int z = 0; z < size; z++)
										 {
										 std::cout << priority[z] << std::endl;
										 }*/

										 //matching sorted cpu burst time to pid and priority 
	for (int x = 0; x < 6; x++)//iterate through sorted burst array
	{
		for (int y = 6; y >= 0; y--)//iterate through processes array
		{
			if (priorityArr[y] == processes[x].priority)
			{
				//std::cout << burst[x] << "=" << processes[y].cpu_burst << std::endl;
				pid_arr[y] = processes[x].pid;//matching pid from struct to its proper place in array
				burst_arr[y] = processes[x].cpu_burst;// matching cpu_burst from struct to its proper place in array

			}
		}

	}

	std::cout << "\nPID\twait\tturnaround\n";

	//calculating wait-time and turnarround-time for each process
	while (i<size) {
		//compute wait time
		wait_t[i] = t;
		t = t + burst_arr[i];
		//compute turnaround time
		turn_t[i] = wait_t[i] + burst_arr[i];

		std::cout << "P" << pid_arr[i] << "\t" << wait_t[i] << "\t" << turn_t[i] << "\n";
		i++;
	}

	//calculating the averages of wait time and turnaround time
	i = 0;
	while (i<size) {
		avg_wait = avg_wait + wait_t[i];
		avg_turn = avg_turn + turn_t[i];
		i++;
	}

	avg_wait = avg_wait / size;
	avg_turn = avg_turn / size;

	//printing the averages
	std::cout << "AVG wait is: " << avg_wait << "\n";
	std::cout << "AVG turnaround is: " << avg_turn << "\n";



}

void myLJF() {
	//Extra credit question


}

void myRR() {
	//Extra credit question


}

int main() {
	//open a file stream
	std::ifstream file("proc.txt");

	if (!file) {
		std::cerr << "\ncould not open file!\n";
		return 1;
	}
	initFrom(file);

	int alg;
	//this outputs the usage message
	while (true) {

		std::cout << "\nwhich scheduling algorithm do you want to run:\n 1- First Come First Serve (FCFS)\n 2- Shortest Job First (SJF)\n 3- Priority (p)\n 4- Longest Job First (LJF) (bonus)\n 5- Round-Robin (RR)(bonus)\nchoice: ";
		std::cin >> alg;

		switch (alg) {
		case 1: myFCFS();
			break;
		case 2: mySJF();
			break;
		case 3: myPriority();
			break;
		case 4: myLJF();
			break;
		case 5: myRR();
			break;
		default: std::cout << "\npick 1 or 2 or 3.\n";
		}
	}

	return 0;
}


