#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_STATUS_LENGTH 100

// Task tree structure
typedef struct Task
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char status[MAX_STATUS_LENGTH];
    int priority;
    struct Task *next;
    struct Task *subtasks;
} Task;

Task create_task(char *name, char *description, char *status, int priority)
{
    Task *newTask = (Task *)malloc(sizeof(Task));
    strncpy(newTask->name, name, MAX_NAME_LENGTH);
    strncpy(newTask->description, description, MAX_DESCRIPTION_LENGTH);
    strncpy(newTask->status, status, MAX_STATUS_LENGTH);
    newTask->priority = priority;
    newTask->next = NULL;
    newTask->subtasks = NULL;

    return newTask;
}

void add_subtask(Task *task, Task *subtask)
{
    if (task == NULL || subtask == NULL)
    {
        printf("\n Failed to allocate subtask");
    }
    else
    {
        if (task->subtasks == NULL)
        {
            task->subtasks = subtask;
        }
        else
        {
            Task current = task->subtasks;
            while (current->next != NULL)
            {
                current = current->next
            }
            current->next = subtask
        }
    }
}

Task *init_root()
{
    Task *root = (Task *)malloc(sizeof(Task));
    if (root != NULL)
    {
        strncpy(root->name, "All Tasks", MAX_NAME_LENGTH, -1);
        root->next = NULL;
        root->subtasks = NULL;
        return root;
    }
    else
    {
        printf("Memory allocation failed\n");
    }
}

int main(int argc, char *argv[])
{
    
    return EXIT_SUCCESS;
}
