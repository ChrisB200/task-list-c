#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_STATUS_LENGTH 100

typedef struct Task
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char status[MAX_STATUS_LENGTH];
    int priority;
    struct Task *p_next;
    struct Task *p_child;
} Task;

void create_task(Task *p_task, char *p_name, char *p_description, char *p_status, int priority)
{
    if (p_task != NULL)
    {
        Task *newTask = (Task *)malloc(sizeof(Task));
        if (newTask != NULL)
        {
            strncpy(newTask->name, p_name, MAX_NAME_LENGTH - 1);
            strncpy(newTask->description, p_description, MAX_DESCRIPTION_LENGTH - 1);
            strncpy(newTask->status, p_status, MAX_STATUS_LENGTH - 1);
            newTask->priority = priority;
            newTask->p_next = NULL;
            newTask->p_child = NULL;

            Task *p_current = p_task->p_child;
            while (p_current->p_next != NULL)
            {
                p_current = p_current->p_next;
            }
            p_current->p_next = newTask;
        }
        else
        {
            printf("Memory allocation failed\n");
        }
    }
}

void navigate_list(Task *p_taskList, int index)
{
    Task *p_current = p_taskList->p_child;
    index = 0;
    while (p_current != NULL)
    {
        index++;
        printf("%d: %s\n", index, p_current->name);
        navigate_list(p_taskList, index);
        p_current = p_current->p_next;
    }
}

void sort_tasks(Task *p_taskList)
{
    int swapped;
    Task *p_current;
    Task *p_last = NULL;

    if (p_taskList == NULL || p_taskList->p_next == NULL)
        return;

    do
    {
        swapped = 0;
        p_current = p_taskList->p_next;

        while (p_current->p_next != p_last)
        {
            if (p_current->priority > p_current->p_next->priority)
            {
                // swap positions by adjusting pointers
                Task *temp = p_current->p_next;
                p_current->p_next = temp->p_next;
                temp->p_next = p_current;

                if (p_current == p_taskList->p_next) // if p_current is the head
                    p_taskList->p_next = temp;
                else
                {
                    Task *prev = p_taskList;
                    while (prev->p_next != p_current)
                        prev = prev->p_next;
                    prev->p_next = temp;
                }
                swapped = 1;
            }
            p_current = p_current->p_next;
        }
        p_last = p_current;
    } while (swapped);
}

Task *init_task_list()
{
    Task *p_taskList = (Task *)malloc(sizeof(Task));
    if (p_taskList != NULL)
    {
        p_taskList->p_next = NULL;
        p_taskList->p_child = NULL;
    }
    else
    {
        printf("Memory allocation failed\n");
    }
    return p_taskList;
}

int main()
{
    Task *p_taskList = init_task_list();
    if (p_taskList != NULL)
    {
        create_task(p_taskList, "Task 1", "Description 1", "pending", 1);
        create_task(p_taskList, "Task 2", "Description 1", "pending", 3);
        create_task(p_taskList, "Task 3", "Description 1", "pending", 2);
        create_task(p_taskList, "Task 4", "Description 1", "pending", 6);

        // sort_tasks(p_taskList);
        navigate_list(p_taskList, 0);

        free(p_taskList);
    }
    return 0;
}
