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
    if (newTask == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strncpy(newTask->name, name, MAX_NAME_LENGTH);
    newTask->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(newTask->description, description, MAX_DESCRIPTION_LENGTH);
    newTask->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    strncpy(newTask->status, status, MAX_STATUS_LENGTH);
    newTask->status[MAX_STATUS_LENGTH - 1] = '\0';
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
        return;
    }
    
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
    if (root == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strncpy(root->name, "All Tasks", MAX_NAME_LENGTH);
    root->name[MAX_NAME_LENGTH - 1] = '\0';
    root->next = NULL;
    root->subtasks = NULL;
    return root;
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

Task *select_task(Task *task, int searchIndex, int *currentSearchIndex)
{
    if (task == NULL)
    {
        return NULL;
    }

    if (searchIndex == *currentSearchIndex)
    {
        return task;
    }

    (*currentSearchIndex)++;

    Task *found = select_task(task->subtasks, searchIndex, currentSearchIndex);
    if (found != NULL)
    {
        return found;
    }

    return select_task(task->next, searchIndex, currentSearchIndex);
}

int main()
{
    Task *root = init_root();
    if (root == NULL)
    {
        return 1;
    }

    Task *test = create_task("test", "test description", "WIP", 1);
    Task *test2 = create_task("test2", "test description", "WIP", 1);
    Task *test3 = create_task("test3", "test description", "WIP", 1);
    Task *test4 = create_task("test4", "test description", "WIP", 1);
    Task *test5 = create_task("test5", "test description", "WIP", 1);

    if (test && test2 && test3 && test4 && test5)
    {
        add_subtask(root, test);
        add_subtask(test, test2);
        add_subtask(test, test3);
        add_subtask(test2, test4);
        add_subtask(test2, test5);
    }

    bool run = true;
    Task *currentTask = root;
    do {
        int index = 1;
        int searchIndex;
        int choice;
        display_tasks(currentTask, 0, &index);
        printf("1. Quit\n2. Search\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                run = false;
                break;
            case 2:
                printf("Now select a task via its index\n");
                scanf("%d", &searchIndex);
                int currentSearchIndex = 1;
                Task *selectedTask = select_task(root, searchIndex, &currentSearchIndex);
                if (selectedTask != NULL)
                {
                    printf("Selected task: %s - %s\n", selectedTask->name, selectedTask->status);
                    currentTask = selectedTask;
                }
                else
                {
                    printf("Task not found\n");
                }
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (run);

    free_task(root);
    return 0;
}
