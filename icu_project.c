#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_TASKS 4

// ================= STRUCTURES =================

typedef struct {
    int id;
    char name[20];
    int deadline_ms;
    int execution_time;
    int priority;
    int deadline_missed;
} Task;

// ================= GLOBAL VARIABLES =================

Task tasks[MAX_TASKS];
int system_overloaded = 0;
int total_deadline_misses = 0;

// ================= UTILITY FUNCTIONS =================

void delay_ms(int ms) {
    Sleep(ms);
}

int random_exec_time() {
    return (rand() % 2500) + 500; // 500–3000 ms
}

// ================= EDF SORT =================

int compare_deadline(const void *a, const void *b) {
    Task *t1 = (Task *)a;
    Task *t2 = (Task *)b;
    return t1->deadline_ms - t2->deadline_ms;
}

// ================= INITIALIZATION =================

void initialize_tasks() {
    tasks[0] = (Task){1, "ECG", 1000, 0, 1, 0};
    tasks[1] = (Task){2, "SpO2", 1500, 0, 2, 0};
    tasks[2] = (Task){3, "BloodPressure", 2000, 0, 3, 0};
    tasks[3] = (Task){4, "Temperature", 2500, 0, 4, 0};
}

// ================= DISPLAY FUNCTIONS =================

void display_tasks() {
    printf("\n-------------------------------------------------\n");
    printf(" ID   SENSOR           DEADLINE(ms)   PRIORITY\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < MAX_TASKS; i++) {
        printf(" %-4d %-15s %-13d %d\n",
               tasks[i].id,
               tasks[i].name,
               tasks[i].deadline_ms,
               tasks[i].priority);
    }
    printf("-------------------------------------------------\n");
}

void display_system_state() {
    printf("\n=============================================\n");
    printf(" SYSTEM STATE: ");
    if (system_overloaded)
        printf("OVERLOADED 🔴\n");
    else
        printf("NORMAL 🟢\n");

    printf(" TOTAL DEADLINE MISSES: %d\n", total_deadline_misses);
    printf("=============================================\n");
}

// ================= EXECUTION =================

void execute_scheduler_cycle() {
    printf("\n🔁 Running Scheduler Cycle...\n");

    qsort(tasks, MAX_TASKS, sizeof(Task), compare_deadline);

    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].execution_time = random_exec_time();

        printf("\n---------------------------------------------\n");
        printf("Executing Task ID      : %d\n", tasks[i].id);
        printf("Sensor                 : %s\n", tasks[i].name);
        printf("Deadline               : %d ms\n", tasks[i].deadline_ms);

        delay_ms(tasks[i].execution_time);

        printf("Execution Time         : %d ms\n", tasks[i].execution_time);

        if (tasks[i].execution_time > tasks[i].deadline_ms) {
            printf("STATUS                 : DEADLINE MISSED ❌\n");
            tasks[i].deadline_missed = 1;
            total_deadline_misses++;
            system_overloaded = 1;
        } else {
            printf("STATUS                 : EXECUTED SUCCESSFULLY ✅\n");
            tasks[i].deadline_missed = 0;
        }
    }
}

// ================= LOGGING =================

void show_trace_log() {
    printf("\n================ TRACE LOG ==================\n");

    for (int i = 0; i < MAX_TASKS; i++) {
        printf("Task %-2d | %-15s | Deadline: %-4d | Exec: %-4d | %s\n",
               tasks[i].id,
               tasks[i].name,
               tasks[i].deadline_ms,
               tasks[i].execution_time,
               tasks[i].deadline_missed ? "FAULT" : "OK");
    }

    printf("=============================================\n");
}

// ================= MENU =================

void show_menu() {
    printf("\n========= ICU SCHEDULING SYSTEM =========\n");
    printf("1. Show Sensor Tasks\n");
    printf("2. Run Scheduler Cycle\n");
    printf("3. Show Trace Log\n");
    printf("4. Show System State\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

// ================= MAIN =================

int main() {
    int choice;
    srand(time(NULL));

    initialize_tasks();

    printf("=============================================\n");
    printf(" ICU DEADLINE-AWARE SCHEDULING SYSTEM\n");
    printf("=============================================\n");

    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_tasks();
                break;

            case 2:
                execute_scheduler_cycle();
                break;

            case 3:
                show_trace_log();
                break;

            case 4:
                display_system_state();
                break;

            case 5:
                printf("\nExiting System...\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }
    }

    return 0;
}
