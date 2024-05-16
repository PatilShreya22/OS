Write a C program to simulate the following non-pre-emptive CPU
scheduling algorithm to find turnaround time and waiting time.
1) FCFS
CODE:
#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESS 30
int p[MAX_PROCESS], arrTime[MAX_PROCESS], burstTime[MAX_PROCESS], compTime[MAX_PROCESS], TAT[MAX_PROCESS], waitTime[MAX_PROCESS];

void sortProcess(int arrTime[], int burstTime[], int n) {
 int temp;
 for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
        if (arrTime[j] > arrTime[j + 1]) {
        // Swap arrival times
        temp = arrTime[j];
        arrTime[j] = arrTime[j + 1];
        arrTime[j + 1] = temp;
        // Swap burst times accordingly
        temp = burstTime[j];
        burstTime[j] = burstTime[j + 1];
        burstTime[j + 1] = temp;
        }
        }
    }
}
int findTurnAroundTime(int ct, int at) {
 return ct - at;
}
int waitingTime(int tat, int bt) {
 return tat - bt;
}
int main() {
 int n;
 printf("Enter total number of processes: ");
 scanf("%d", &n);
 int total_TAT = 0; // Total turnaround time
 int total_WT = 0; // Total waiting time
 for (int i = 0; i < n; i++) {
 printf("Process %d\n", i + 1);
 printf("Arrival time: ");
 scanf("%d", &arrTime[i]);
 printf("Burst time: ");
 scanf("%d", &burstTime[i]);
 p[i] = i + 1; // Assigning process number
 }
 // Sort processes based on arrival time
 sortProcess(arrTime, burstTime, n);
 // Calculate completion time, turnaround time, and waiting time
 for (int i = 0; i < n; i++) {
 if (i == 0 || arrTime[i] > compTime[i - 1]) {
 compTime[i] = arrTime[i] + burstTime[i];
 } else {
 compTime[i] = compTime[i - 1] + burstTime[i];
 }
 TAT[i] = findTurnAroundTime(compTime[i], arrTime[i]);
 waitTime[i] = waitingTime(TAT[i], burstTime[i]);
 // Summing up turnaround time and waiting time
 total_TAT += TAT[i];
 total_WT += waitTime[i];
 }
 // Calculate averages
 float avg_TAT = (float)total_TAT / n;
 float avg_WT = (float)total_WT / n;
 // Displaying results including averages
 printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
 for (int i = 0; i < n; i++) {
 printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], arrTime[i], burstTime[i], compTime[i], TAT[i],
waitTime[i]);
 }
 printf("\nAverage Turnaround Time: %.2f", avg_TAT);
 printf("\nAverage Waiting Time: %.2f\n", avg_WT);
 return 0;
}

OUTPUT:
Enter total number of processes: 4
Process 1
Arrival time: 0
Burst time: 6
Process 2
Arrival time: 1
Burst time: 3
Process 3
Arrival time: 2
Burst time: 6
Process 4
Arrival time: 3
Burst time: 2

Process Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
1       0               6               6               6               0
2       1               3               9               8               5
3       2               6               15              13              7
4       3               2               17              14              12

Average Turnaround Time: 10.25
Average Waiting Time: 6.00

2) SJF (Non-preemptive)
CODE:
#include <stdio.h>
struct P {
 int id;
 int at;
 int bt;
 int ct;
 int tt;
 int wt;
};
void sort(struct P p[], int n);
void sjf(struct P p[], int n);
int main() {
 int n;
 int total_tat = 0;
 int total_wt = 0;
 printf("Enter the number of processes: ");
 scanf("%d", &n);
 struct P p[n];
 printf("Enter the arrival time and burst time for each process:\n");
 for (int i = 0; i < n; i++) {
 printf("Process %d:\n", i + 1);
 p[i].id = i + 1;
 printf("Arrival Time: ");
 scanf("%d", &p[i].at);
 printf("Burst Time: ");
 scanf("%d", &p[i].bt);
 }
 sort(p, n);
 sjf(p, n);
 printf("\nProcess Schedule:\n");
 printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
 for (int i = 0; i < n; i++) {
 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
 total_tat += p[i].tt;
 total_wt += p[i].wt;
 }
 printf("\nAvg TAT: %.2f", (float)total_tat / n);
 printf("\nAvg WT: %.2f", (float)total_wt / n);
 return 0;
}
void sort(struct P p[], int n) {
 for (int i = 0; i < n - 1; i++) {
 for (int j = 0; j < n - i - 1; j++) {
 if (p[j].at > p[j + 1].at || (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt)) {
 struct P temp = p[j];
 p[j] = p[j + 1];
 p[j + 1] = temp;
 }
 }
 }
}
void sjf(struct P p[], int n) {
 int current_time = 0;
 for (int i = 0; i < n; i++) {
 int sj_index = i;
 for (int j = i + 1; j < n && p[j].at <= current_time; j++) {
 if (p[j].bt < p[sj_index].bt) {
 sj_index = j;
 }
 }
 p[sj_index].ct = current_time + p[sj_index].bt;
 p[sj_index].tt = p[sj_index].ct - p[sj_index].at;
 p[sj_index].wt = p[sj_index].tt - p[sj_index].bt;
 current_time = p[sj_index].ct;
 struct P temp = p[i];
 p[i] = p[sj_index];
 p[sj_index] = temp;
 }
}

OUTPUT:
Enter the number of processes: 4
Enter the arrival time and burst time for each process:
Process 1:
Arrival Time: 0
Burst Time: 5
Process 2:
Arrival Time: 2
Burst Time: 6
Process 3:
Arrival Time: 1
Burst Time: 5
Process 4:
Arrival Time: 3
Burst Time: 5

Process Schedule:
Process ID      Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
1               0               5               5               5               0
3               1               5               10              9               4
4               3               5               15              12              7
2               2               6               21              19              13

Avg TAT: 11.25
Avg WT: 6.00
  
