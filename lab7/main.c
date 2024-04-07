#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define size 5

struct Processes {
	char name;
	int arrival_time;
	int service_time;
	int start_time;
	int finish_time;
	int wait_time;
	int turnaround_time;
};

void FCFS(struct Processes* proc, char* gantt) {
	for (int i = 0; i < 5; i++) {
		//
		if (i == 0) {
			proc[0].start_time = proc[0].arrival_time;
			proc[0].finish_time = proc[0].start_time + proc[0].service_time;
			proc[0].wait_time = proc[0].start_time - proc[0].arrival_time;
			proc[0].turnaround_time = proc[0].finish_time - proc[0].arrival_time;
			//temp_time = proc[0].finish_time;
			printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[0].name, proc[0].arrival_time, proc[0].service_time, proc[0].start_time, proc[0].finish_time, proc[0].wait_time, proc[0].turnaround_time);
			for (int j = 0; j < proc[0].finish_time; j++) {
				gantt[j] = proc[0].name;
			}
			continue;
		}
		proc[i].start_time = proc[i-1].finish_time;
		proc[i].finish_time = proc[i].start_time + proc[i].service_time;
		proc[i].wait_time = proc[i].start_time - proc[i].arrival_time;
		proc[i].turnaround_time = proc[i].finish_time - proc[i].arrival_time;

		for (int j = proc[i - 1].finish_time; j < proc[i].finish_time; j++) {
			gantt[j] = proc[i].name;
		}
		//temp_time = proc[i].finish_time;
		printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].name, proc[i].arrival_time, proc[i].service_time, proc[i].start_time, proc[i].finish_time, proc[i].wait_time, proc[i].turnaround_time);
	}
}
void SPN(struct Processes* proc, char* gantt) {
	int temp_time = 0;
	int proc_count = 0;
	int flag[5] = {0,0,0,0,0};
	int temp_shortest = 100;
	int shortest_ind = 0;
	
	proc[0].start_time = proc[0].arrival_time;
	proc[0].finish_time = proc[0].start_time + proc[0].service_time;
	proc[0].wait_time = proc[0].start_time - proc[0].arrival_time;
	proc[0].turnaround_time = proc[0].finish_time - proc[0].arrival_time;
	temp_time = proc[0].finish_time;
	flag[0] = 1;
	proc_count++;
	for (int j = 0; j < proc[0].finish_time; j++) {
		gantt[j] = proc[0].name;
	}
	printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[0].name, proc[0].arrival_time, proc[0].service_time, proc[0].start_time, proc[0].finish_time, proc[0].wait_time, proc[0].turnaround_time);
	while (proc_count != 5) {
		for (int i = 1; i < 5; i++) {
			if (flag[i] == 1)
			{
				continue;
			}
			if (proc[i].arrival_time <= temp_time) {
				if (temp_shortest > proc[i].service_time) {
					temp_shortest = proc[i].service_time;
					shortest_ind = i;
				}
			}
		}
		proc[shortest_ind].start_time = temp_time;
		proc[shortest_ind].finish_time = proc[shortest_ind].start_time + proc[shortest_ind].service_time;
		proc[shortest_ind].wait_time = proc[shortest_ind].start_time - proc[shortest_ind].arrival_time;
		proc[shortest_ind].turnaround_time = proc[shortest_ind].finish_time - proc[shortest_ind].arrival_time;
		for (int j = temp_time; j < proc[shortest_ind].finish_time; j++) {
			gantt[j] = proc[shortest_ind].name;
		}
		printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[shortest_ind].name, proc[shortest_ind].arrival_time, proc[shortest_ind].service_time, proc[shortest_ind].start_time, proc[shortest_ind].finish_time, proc[shortest_ind].wait_time, proc[shortest_ind].turnaround_time);
		temp_time = proc[shortest_ind].finish_time;
		proc_count++;
		flag[shortest_ind] = 1;
		temp_shortest = 100;
	}
}

void SRT(struct Processes* proc, char* gantt) {
	int total_rtime = 0;
	int temp_stime[5] = { 0, 0, 0, 0, 0 };
	int flag[5] = { 0, 0, 0, 0, 0 };
	int shortest_ind = 0;
	int temp_shortest = 100;
	int gantt_ind = 0;
	int curr_time = 0;

	//find total run time
	for (int i = 0; i < 5; i++) {
		total_rtime += proc[i].service_time;
		temp_stime[i] = proc[i].service_time;
		proc[i].start_time = -1;
	}
	
	while (curr_time < total_rtime) {
		for (int i = 0; i < 5; i++) {
			if (flag[i] == 1) {
				continue;
			}
			if (proc[i].arrival_time <= curr_time) {
				if (temp_shortest > temp_stime[i]) {
					temp_shortest = temp_stime[i];
					shortest_ind = i;
				}
			}
		}
		temp_stime[shortest_ind] = temp_stime[shortest_ind] - 1;

		if (proc[shortest_ind].start_time == -1) {
			proc[shortest_ind].start_time == curr_time;
		}
		gantt[gantt_ind] = proc[shortest_ind].name;
		gantt_ind++;
		curr_time++;

		if (temp_stime[shortest_ind] == 0) {
			proc[shortest_ind].finish_time = curr_time;
			flag[shortest_ind] == 1;
			proc[shortest_ind].wait_time = proc[shortest_ind].start_time - proc[shortest_ind].arrival_time;
			proc[shortest_ind].turnaround_time = proc[shortest_ind].finish_time - proc[shortest_ind].arrival_time;
			printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[shortest_ind].name, proc[shortest_ind].arrival_time, proc[shortest_ind].service_time, proc[shortest_ind].start_time, proc[shortest_ind].finish_time, proc[shortest_ind].wait_time, proc[shortest_ind].turnaround_time);
		}
		temp_shortest = 100;
	}
}

void gantt_chart(char* gantt) {
	printf("Gantt Chart: \n");
	// Goes through gantt array and prints the visual presentation
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 30; j++) {
			switch (i) {
			case 0:
				if (gantt[j] == 'A') {
					printf("A");
				}
				else {
					printf(" ");
				}
				break;
			case 1:
				if (gantt[j] == 'B') {
					printf("B");
				}
				else {
					printf(" ");
				}
				break;
			case 2:
				if (gantt[j] == 'C') {
					printf("C");
				}
				else {
					printf(" ");
				}
				break;
			case 3:
				if (gantt[j] == 'D') {
					printf("D");
				}
				else {
					printf(" ");
				}
				break;
			case 4:
				if (gantt[j] == 'E') {
					printf("E");
				}
				else {
					printf(" ");
				}
				break;
			}
		}
		printf("\n");
	}

}

int main() {
	struct Processes proc[5];
	int user_inp;
	//store name, arrival time and service time from text file
	FILE* file = fopen("part1.txt", "r");

	for (int i = 0; i < 5; i++) {
		fscanf(file, " %c %d %d", &proc[i].name, &proc[i].arrival_time, &proc[i].service_time);
	}

	fclose(file);

	
	while (1) {
		printf("Input 1 for FCFS, 2 for SPN or 3 for SRT (0 to quit): ");
		scanf("%d", &user_inp);
		if (user_inp == 1) {
			printf("----------------FCFS Scheduling----------------\n");
			printf("Process \tArrival Time\tService Time\tStart Time\tFinish Time\tWait Time\tTurnaround Time\n");
			char gantt_fcfs[30];
			FCFS(proc, gantt_fcfs);
			gantt_chart(gantt_fcfs);
		}
		else if (user_inp == 2) {
			printf("----------------SPN Scheduling----------------\n");
			printf("Process \tArrival Time\tService Time\tStart Time\tFinish Time\tWait Time\tTurnaround Time\n");
			char gantt_spn[30];
			SPN(proc, gantt_spn);
			gantt_chart(gantt_spn);
		}
		else if (user_inp == 3) {
			printf("----------------SRT Scheduling----------------\n");
			printf("Process \tArrival Time\tService Time\tStart Time\tFinish Time\tWait Time\tTurnaround Time\n");
			char gantt_spn[30];
			SPN(proc, gantt_spn);
			gantt_chart(gantt_spn);
		}
		else break;
	}

	return 0;
}