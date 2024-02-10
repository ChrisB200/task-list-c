#include <stdio.h>

typedef struct
{
    char name[25];
    char description[100];
    char status[25];
    int priority;
    int id;
    Task *child;
    Task *sibling;
} Task;

Task createTask()
{
}

int main()
{
    Task *rootTask = NULL; // initalise a pointer to the root task
    return 0;
}