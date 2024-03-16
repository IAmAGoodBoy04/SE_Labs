#include<stdio.h>
#include<stdlib.h>

typedef struct pizza_tuple{
    int transit;
    int arrival;
    int number;
    int waiting_time;
    int turn_around_time;
    int priority;
}pizza_tuple;

int compare_arrival_time(const void* a, const void* b){
    return (((pizza_tuple*)a)->arrival - ((pizza_tuple*)b)->arrival);
}

int compare_transit_time(const void* a, const void* b){
    return (((pizza_tuple*)a)->transit - ((pizza_tuple*)b)->transit);
}

int compare_priority(const void* a, const void* b){
    if(((pizza_tuple*)a)->priority != ((pizza_tuple*)b)->priority)
    return (((pizza_tuple*)a)->priority - ((pizza_tuple*)b)->priority);
    else
    return (((pizza_tuple*)a)->transit - ((pizza_tuple*)b)->transit);
}

int main(){
    int n;
    printf("Enter the number of pizzas: ");
    scanf("%d", &n);
    int transit_time[n];
    pizza_tuple parr[n];
    for(int i=0; i<n; i++){
        printf("Enter the transit time for pizza %d: ", i+1);
        scanf("%d", &transit_time[i]);
        parr[i].transit = transit_time[i];
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
                printf("Enter the arrival time for pizza %d: ", i+1);
                scanf("%d", &arrival_time[i]);
                parr[i].arrival = arrival_time[i];
            }
            qsort(parr, n, sizeof(pizza_tuple), compare_arrival_time);
            parr[0].waiting_time=waiting_time[0] = 0;
            parr[0].turn_around_time=parr[0].transit;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].transit;
                parr[i].waiting_time = waiting_time[i]-parr[i].arrival;
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + parr[i].transit;
                parr[i].turn_around_time = turn_around_time[i]-parr[i].arrival;
            }
            printf("pizza\tArrival time\ttransit Time\tWaiting Time\tdelivery Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", parr[i].number,parr[i].arrival,parr[i].transit, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average delivery time: %.2lf\n", avg_turn_around_time/n);

            break;
        }
        case 2: {
            qsort(parr, n, sizeof(pizza_tuple), compare_transit_time);
            parr[0].waiting_time=waiting_time[0] = 0;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].transit;
                parr[i].waiting_time = waiting_time[i];
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + parr[i].transit;
                parr[i].turn_around_time = turn_around_time[i];
            }
            printf("pizza\ttransit Time\tWaiting Time\tdelivery Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\n", parr[i].number, parr[i].transit, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average delivery time: %.2lf\n", avg_turn_around_time/n);
            break;
        }
        case 3: {
            int priority[n];
            printf("Enter priority as 1 for emergency delivery, 2 for VIP delivery, 3 for normal delivery.\n");
            for(int i=0; i<n; i++){
                printf("Enter the priority for pizza %d: ", i+1);
                scanf("%d", &priority[i]);
                parr[i].priority = priority[i];
            }
            qsort(parr, n, sizeof(pizza_tuple), compare_priority);
            parr[0].waiting_time=waiting_time[0] = 0;
            for(int i=1; i<n; i++){
                waiting_time[i] = waiting_time[i-1] + parr[i-1].transit;
                parr[i].waiting_time = waiting_time[i];
            }
            for(int i=0; i<n; i++){
                turn_around_time[i] = waiting_time[i] + parr[i].transit;
                parr[i].turn_around_time = turn_around_time[i];
            }
            printf("pizza\tpriority\ttransit Time\tWaiting Time\tdelivery Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", parr[i].number,parr[i].priority,parr[i].transit, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average delivery time: %.2lf\n", avg_turn_around_time/n);
            break;
        }
        case 4:{
            int quantum;
            printf("Enter the quantum: ");
            scanf("%d", &quantum);
            int time=0,completed=0;
            while(completed<n){
                for(int i=0;i<n;i++){
                    if(transit_time[i]<=0){
                        continue;
                    }
                    if(transit_time[i]>quantum){
                        time+=quantum;
                        transit_time[i]-=quantum;
                    }
                    else{
                        time+=transit_time[i];
                        parr[i].turn_around_time=time;
                        parr[i].waiting_time=parr[i].turn_around_time-parr[i].transit;
                        transit_time[i]=0;
                        completed++;
                    }
                }
            }
            printf("pizza\ttransit Time\tWaiting Time\tdelivery Time\n");
            for(int i=0; i<n; i++){
                printf("%d\t%d\t\t%d\t\t%d\n", parr[i].number, parr[i].transit, parr[i].waiting_time, parr[i].turn_around_time);
            }
            double avg_waiting_time=0, avg_turn_around_time=0;
            for(int i=0; i<n; i++){
                avg_waiting_time+=parr[i].waiting_time;
                avg_turn_around_time+=parr[i].turn_around_time;
            }
            printf("Average waiting time: %.2lf\n", avg_waiting_time/n);
            printf("Average delivery time: %.2lf\n", avg_turn_around_time/n);

            break;
        }
    }
return 0;
}