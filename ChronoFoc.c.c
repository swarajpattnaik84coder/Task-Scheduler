#include <stdio.h>
#include <string.h>
#define MAX_TASKS 10
#define MAX_SLOTS 7

typedef enum FOCUS_LEVEL { fixed, high, low } FocusLevel;

typedef struct task{
    char name[10];
    int duration;
    FocusLevel focus_level;
} task;

typedef struct slot{
    char name[20];
    int start_time;
    int end_time;
    int remaining_time;
    FocusLevel focus_level;
} slot;

typedef struct schedule{
    char task_name[50];
    int start_hour;
    int end_hour;
} schedule;

task tasks[MAX_TASKS];
slot slots[MAX_SLOTS];
schedule s_chedule[MAX_TASKS * 2];

FocusLevel focus(char *str) {
    if (strcmp(str, "high") == 0){
        return high;}
    else if (strcmp(str, "low") == 0){
        return low;}
    else{
        return fixed;}
}

void print(int hour) {
    if (hour < 10){
        printf("0%d:00", hour);}
    else{
        printf("%d:00", hour);}
}

void initialize() {
    strcpy(slots[0].name, "Sleep");
    slots[0].start_time = 0;
    slots[0].end_time = 5;
    slots[0].remaining_time = 5;
    slots[0].focus_level = fixed;

    strcpy(slots[1].name, "Refresh");
    slots[1].start_time = 5;
    slots[1].end_time = 6;
    slots[1].remaining_time = 1;
    slots[1].focus_level = fixed;

    strcpy(slots[2].name, "High Focus");
    slots[2].start_time = 6;
    slots[2].end_time = 10;
    slots[2].remaining_time = 4;
    slots[2].focus_level = high;

    strcpy(slots[3].name, "Low Focus");
    slots[3].start_time = 10;
    slots[3].end_time = 14;
    slots[3].remaining_time = 4;
    slots[3].focus_level = low;

    strcpy(slots[4].name, "Refresh");
    slots[4].start_time = 14;
    slots[4].end_time = 17;
    slots[4].remaining_time = 3;
    slots[4].focus_level = fixed;

    strcpy(slots[5].name, "High Focus");
    slots[5].start_time = 17;
    slots[5].end_time = 22;
    slots[5].remaining_time = 5;
    slots[5].focus_level = high;

    strcpy(slots[6].name, "Refresh");
    slots[6].start_time = 22;
    slots[6].end_time = 24;
    slots[6].remaining_time = 2;
    slots[6].focus_level = fixed;
}

int main() {
    printf("\nMaximum available high focus duration = 9 hours");
    printf("\nMaximum available low focus duration = 4 hours\n");
    printf("\ninput your high priority tasks on top otherwise \n if tasks duration exceeds available time them top order will be followed\n");

    int schedule_count = 0;
    int n;
    initialize();

    printf("\nEnter number of tasks: ");
    scanf("%d", &n);

    char focus_input[10];
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of task %d: ", i + 1);
        scanf(" %[^\n]", tasks[i].name);

        printf("Enter task duration (hours): ");
        scanf("%d", &tasks[i].duration);

        printf("Enter task focus level (high/low): ");
        scanf("%s", focus_input);
        tasks[i].focus_level=focus(focus_input);
    }

    int current_time;
printf("\n--------------------------------\n");
printf("FIXED SLOTS");
printf("\n--------------------------------\n");
    
    for (int i = 0; i < 7; i++) {
        slot *ptr = &slots[i];  
        current_time = ptr->start_time;

        if (ptr->focus_level == fixed) {
            printf("%s: ", ptr->name);
            print(ptr->start_time);
            printf(" - ");
            print(ptr->end_time);
            printf("\n");
        } else {
            for (int j = 0; j < n && ptr->remaining_time > 0; j++) {
                if (tasks[j].duration > 0 && tasks[j].focus_level == ptr->focus_level) {
                    int assign_time = (tasks[j].duration <= ptr->remaining_time)
                                          ? tasks[j].duration : ptr->remaining_time;

                    strcpy(s_chedule[schedule_count].task_name, tasks[j].name);
                    s_chedule[schedule_count].start_hour = current_time;
                    s_chedule[schedule_count].end_hour = current_time + assign_time;
                    schedule_count++;

                     tasks[j].duration -= assign_time;
                    ptr->remaining_time -= assign_time;
                    current_time += assign_time;
                }
            }
        }
    }

printf("\n--------------------------------\n");
printf("Final Scheduled Tasks:\n");
printf("--------------------------------\n");
    for (int i = 0; i < schedule_count; i++) {
        printf("%s: ", s_chedule[i].task_name);
        print(s_chedule[i].start_hour);
        printf(" - ");
        print(s_chedule[i].end_hour);
        printf("\n");
    }

    return 0;
}
