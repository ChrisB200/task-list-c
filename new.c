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
    struct Task *p_subtasks;
} Task;

Task *create_task(char *p_name, char *p_description, char *p_status, int priority)
{

    Task *newTask = (Task *)malloc(sizeof(Task));
    strncpy(newTask->name, p_name, MAX_NAME_LENGTH);
    strncpy(newTask->description, p_description, MAX_DESCRIPTION_LENGTH);
    strncpy(newTask->status, p_status, MAX_STATUS_LENGTH);
    newTask->priority = priority;
    newTask->p_next = NULL;
    newTask->p_subtasks = NULL;

    return newTask;
}

void add_subtask(Task *p_task, Task *p_subtask)
{
    if (p_task == NULL || p_subtask == NULL)
    {
        printf("\n Task allocation failed");
    }
    else
    {
        if (p_task->p_subtasks == NULL)
        {
            p_task->p_subtasks = p_subtask;
        }
        else
        {
            Task *p_current = p_task->p_subtasks;
            while (p_current->p_next != NULL)
            {
                p_current = p_current->p_next;
            }
            p_current->p_next = p_subtask;
        }
    }
}

void display_tree(Task *p_task, int depth, int index)
{
    if (p_task == NULL)
        return;

    // Display current task
    printf("%d. %*s- %s\n", index, depth * 4, "", p_task->name);
    index++;

    // Display subtasks
    display_tree(p_task->p_subtasks, depth + 1, index);

    // Display siblings
    display_tree(p_task->p_next, depth, index);
}

display_area(Task *p_task, int depth, int index)
{
    if (p_task == NULL)
        return;

    // Display current task
    printf("%d. %*s- %s\n", index, depth * 4, "", p_task->name);
    index++;

    // Display subtasks
    display_tree(p_task->p_subtasks, depth + 1, index);
}

Task *init_root()
{
    Task *root = (Task *)malloc(sizeof(Task));
    if (root != NULL)
    {
        strncpy(root->name, "All Tasks", MAX_NAME_LENGTH - 1);
        root->p_next = NULL;
        root->p_subtasks = NULL;
        return root;
    }
    else
    {
        printf("Memory allocation failed\n");
    }
}

Task *find_task(Task *startingPoint)
{
}

void add_task(Task *task)
{
}

int main()
{
    Task *root = init_root();

    Task *p_task1 = create_task("Project Management", "Manage project tasks and timeline", "Pending", 2);
    Task *p_task2 = create_task("Development", "Develop application features", "In Progress", 3);
    Task *p_task3 = create_task("Testing", "Test application functionality", "Pending", 1);
    Task *p_task4 = create_task("Documentation", "Document project requirements and progress", "In Progress", 2);

    // Subtasks of Project Management
    Task *p_subtask1 = create_task("Create project plan", "Define project scope, objectives, and deliverables", "Pending", 2);
    Task *p_subtask2 = create_task("Schedule team meetings", "Coordinate regular meetings with project team", "In Progress", 3);
    add_subtask(p_task1, p_subtask1);
    add_subtask(p_task1, p_subtask2);

    // Subtasks of Development
    Task *p_subtask3 = create_task("Implement user authentication", "Implement user login and registration functionality", "In Progress", 3);
    Task *p_subtask4 = create_task("Design database schema", "Design database tables and relationships", "Pending", 2);
    add_subtask(p_task2, p_subtask3);
    add_subtask(p_task2, p_subtask4);

    // Subtasks of Testing
    Task *p_subtask5 = create_task("Unit testing", "Test individual components/modules", "Pending", 1);
    Task *p_subtask6 = create_task("Integration testing", "Test integration of different components/modules", "Pending", 2);
    add_subtask(p_task3, p_subtask5);
    add_subtask(p_task3, p_subtask6);

    // Subtasks of Documentation
    Task *p_subtask7 = create_task("Write user manual", "Create user manual for end users", "Pending", 2);
    Task *p_subtask8 = create_task("Prepare technical documentation", "Document technical details and architecture", "In Progress", 3);
    add_subtask(p_task4, p_subtask7);
    add_subtask(p_task4, p_subtask8);

    add_subtask(root, p_task1);
    add_subtask(root, p_task2);
    add_subtask(root, p_task3);
    add_subtask(root, p_task4);

    display_area(p_task1, 0, 1);

    free(root);

    return 0;
}