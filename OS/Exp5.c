#include<stdio.h>
#include<stdlib.h>

typedef struct process_tuple{
    int burst;
    int arrival;
    int number;
    int waiting_time;
    int turn_around_time;
    int priority;
}process_tuple;

int compare_arrival_time(const void* a, const void* b){
    return (((process_tuple*)a)->arrival - ((process_tuple*)b)->arrival);
}

int compare_burst_time(const void* a, const void* b){
    return (((process_tuple*)a)->burst - ((process_tuple*)b)->burst);
}

int compare_priority(const void* a, const void* b){
    return (((process_tuple*)a)->priority - ((process_tuple*)b)->priority);
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n];
    process_tuple parr[n];
    for(int i=0; i<n; i++){
        printf("Enter the burst time for process %d: ", i+1);
        scanf("%d", &burst_time[i]);
        parr[i].burst = burst_time[i];
        parr[i].number=i+1;
    }
    int waiting_time[n], turn_around_time[n];
    printf("Enter 1 for FCFS, 2 for SJF, 3 for Priority, 4 for Round Robin: ");
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1: {
            int arrival_time[n];
            for(int i=0; i<n; i++){
                printf("Enter the arrival time for process %d: ", i+1);
                scanf("%d", &arrival_time[i]);
                parr[i].arrival = arrival_time[i];
            }
            qsort(parr, n, sizeof(process_tuple), compare_arrival_time);
            parr[0].waiting_time=waiting_time[0] = 0;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].burst;
                parr[i].waiting_time = waiting_time[i]-parr[i].arrival;
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + burst_time[i];
                parr[i].turn_around_time = turn_around_time[i]-parr[i].arrival;
            }
            printf("Process\tArrival time\tBurst Time\tWaiting Time\tTurn Around Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", parr[i].number,parr[i].arrival,parr[i].burst, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average turn around time: %.2lf\n", avg_turn_around_time/n);

            break;
        }
        case 2: {
            qsort(parr, n, sizeof(process_tuple), compare_burst_time);
            parr[0].waiting_time=waiting_time[0] = 0;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].burst;
                parr[i].waiting_time = waiting_time[i];
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + parr[i].burst;
                parr[i].turn_around_time = turn_around_time[i];
            }
            printf("Process\tBurst Time\tWaiting Time\tTurn Around Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\n", parr[i].number, parr[i].burst, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average turn around time: %.2lf\n", avg_turn_around_time/n);
            break;
        }
        case 3: {
            int priority[n];
            for(int i=0; i<n; i++){
                printf("Enter the priority for process %d: ", i+1);
                scanf("%d", &priority[i]);
                parr[i].priority = priority[i];
            }
            qsort(parr, n, sizeof(process_tuple), compare_priority);
            parr[0].waiting_time=waiting_time[0] = 0;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].burst;
                parr[i].waiting_time = waiting_time[i];
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + parr[i].burst;
                parr[i].turn_around_time = turn_around_time[i];
            }
            printf("Process\tpriority\tBurst Time\tWaiting Time\tTurn Around Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", parr[i].number,parr[i].priority,parr[i].burst, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average turn around time: %.2lf\n", avg_turn_around_time/n);
            break;
        }
        case 4:{
            int quantum;
            printf("Enter the quantum: ");
            scanf("%d", &quantum);
            int time=0,completed=0;
            while(completed<n){
                for(int i=0;i<n;i++){
                    if(burst_time[i]<=0){
                        continue;
                    }
                    if(burst_time[i]>quantum){
                        time+=quantum;
                        burst_time[i]-=quantum;
                    }
                    else{
                        time+=burst_time[i];
                        parr[i].turn_around_time=time;
                        parr[i].waiting_time=parr[i].turn_around_time-parr[i].burst;
                        burst_time[i]=0;
                        completed++;
                    }
                }
            }
            printf("Process\tBurst Time\tWaiting Time\tTurn Around Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\n", parr[i].number, parr[i].burst, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average turn around time: %.2lf\n", avg_turn_around_time/n);

            break;
        }
    }
return 0;
}