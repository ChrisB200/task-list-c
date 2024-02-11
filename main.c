#include <stdio.h>

// Kind if like constants in Python
#define MAX_NAME_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_STATUS_LENGTH 100

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char status[MAX_STATUS_LENGTH];
    int priority;
    struct Task *child;
    struct Task *sibling;
} Task;

// apparantly this is good practice so that there is not a dangling pointer. This means that the pointer will be reset so that it does not point to deallocated memory
void deallocateTask(Task *task)
{
    if (task != NULL)
    {
        free(task);  // deallocate memory
        task = NULL; // set pointer to NULL
    }
}

void createTask(Task **parent, char *name, char *description, char *status, int priority)
{
    Task *newTask = (Task *)malloc(sizeof(Task)); // calculates the size of the task in bytes and allocates the bytes to a block of memory and returns the pointer to the block of memory

    if (newTask != NULL)
    {
        // assigns the name character arrays to the argument character arrays by getting the max length
        strncpy(newTask->name, name, MAX_NAME_LENGTH - 1);
        strncpy(newTask->description, description, MAX_DESCRIPTION_LENGTH - 1);
        strncpy(newTask->status, status, MAX_STATUS_LENGTH - 1);
        newTask->priority = priority;
        newTask->child = NULL;
        newTask->sibling = NULL;

        // now we have to link the new task with its parent
        if (*parent == NULL) // if there is no parent then set the parent to be itself.
        {
            *parent = newTask;
        }
        else
        {
            Task *sibling = (*parent)->child; // creates a pointer to point to the first child of the parent task
            if (sibling == NULL)              // if there are no siblings of the parent then
            {
                (*parent)->child = newTask; // makes the new task be the child of the parent task.
            }
            else // if there are siblings then
            {
                while (sibling->sibling != NULL) // go through all the siblings until there is not another.
                {
                    sibling = sibling->sibling; // set the sibling to the next sibling
                }
                sibling->sibling = newTask; // after there are no more siblings then set the parent sibling to be the new task
            }
        }
    }
    else
    {
        fprintf(stderr, "Memory allocation error\n");
    }
}

int main()
{
    Task *rootTask = NULL;    // initalise a pointer to the root task
    deallocateTask(rootTask); // free the pointer
    return 0;
}