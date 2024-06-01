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

Task *create_task(char *name, char *description, char *status, int priority)
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
            Task *current = task->subtasks;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = subtask;
        }
    }
}

void free_task(Task *task)
{
    if (task == NULL)
    {
        return;
    }

    free_task(task->subtasks);
    free_task(task->next);

    free(task);
}

Task *init_root()
{
    Task *root = (Task *)malloc(sizeof(Task));
    if (root != NULL)
    {
        strncpy(root->name, "All Tasks", MAX_NAME_LENGTH);
        root->next = NULL;
        root->subtasks = NULL;
        return root;
    }
    else
    {
        printf("Memory allocation failed\n");
        return root;
    }
}

void display_tasks(Task *task, int depth, int *index)
{
    if (task == NULL)
    {
        return;
    }

    printf("%d. %*s- %s - %s\n", *index, depth * 4, "", task->name, task->status);
    (*index)++;

    display_tasks(task->subtasks, depth + 1, index);
    display_tasks(task->next, depth, index);
}

int main()
{
    Task *root = init_root();
    Task *test = create_task("test", "test description", "WIP", 1);
    Task *test2 = create_task("test2", "test description", "WIP", 1);
    Task *test3 = create_task("test3", "test description", "WIP", 1);
    Task *test4 = create_task("test4", "test description", "WIP", 1);
    Task *test5 = create_task("test5", "test description", "WIP", 1);

    add_subtask(root, test);
    add_subtask(test, test2);
    add_subtask(test, test3);
    add_subtask(test2, test4);
    add_subtask(test2, test5);
    
    int index = 0;
    display_tasks(root, 0, &index);

    free_task(root);
    return 0;
}
