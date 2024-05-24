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
    struct Task *p_next;
    struct Task *p_subtasks;
} Task;


// Creates a task
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

// Adds tasks into the main tree.
void add_subtask(Task *p_task, Task *p_subtask)
{
    if (p_task == NULL || p_subtask == NULL)
    {
        printf("\n Task allocation failed");
    }
    else
    {
        // Adds subtask as a parent
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

// Displays the tree from the task
void display_tree(Task *p_task, int *depth, int *index)
{
    if (p_task == NULL)
        return;

    // Display current task
    printf("%d. %*s- %s\n", *index, (*depth) * 4, "", p_task->name);
    (*index)++;

    // Display subtasks
    (*depth)++;
    display_tree(p_task->p_subtasks, depth, index);

    // Display siblings
    (*depth)--;
    if ((*depth) > 0)
    {
        display_tree(p_task->p_next, depth, index);
    }
}

// Finds a task based on its index
Task *find_task(Task *p_task, int searchIndex, int *p_index)
{
    if (p_task == NULL)
        return NULL;
    if ((*p_index) == searchIndex)
    {
        return p_task;
    }
    else
    {
        (*p_index)++;
        Task *subtasks = find_task(p_task->p_subtasks, searchIndex, p_index);

        if (subtasks == NULL)
        {
            Task *siblings = find_task(p_task->p_next, searchIndex, p_index);
            return siblings;
        }
        else
        {
            return subtasks;
        }
        return NULL;
    }
}

// Initialise the root directory
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

// Allows for users to add a task
void add_task(Task *task)
{
}

void free_task(Task *task)
{
    if (task == NULL)
        return;

    free_task(task->p_subtasks);
    free_task(task->p_next);

    free(task);
}

// Check input to test whether its a character, string, int
int check_type(char input[20])
{
    // Calculate the length of the input string
    int length = strlen(input);
    int intCounter = 0;
    int charCounter = 0;
    for (int i = 0; i < length; i++)
    {
        if (isdigit(input[i]))
        {
            intCounter++;
        }
        else if (isalpha(input[i]))
        {
            charCounter++;
        }
    }

    if (intCounter == length) // If all characters are digits
    {
        return 0;
    }
    else if (charCounter == length) // If none of the characters are digits
    {
        return 1;
    }
    else // If characters are invalid
    {
        return 2;
    }
}

// Allows for user to choose an option
char *get_option(Task *currentTask, int *p_maxOptions, int *p_depth, int *p_index)
{
    char choice[20];

    // Display and get input
    printf("\n\n\n ----------------------------------------------------------\n\n\n");
    display_tree(currentTask, p_depth, p_maxOptions);
    printf("Press a number to access the tasks\nq - Quit\nr - Reset\nc - Create a task\n");
    scanf(" %s", &choice);

    return choice;
}

// Character option
bool task_option(char *choice)
{
    option = atoi((*choice)); // Convert to integer
    if (option < maxOptions)
    {
        Task *foundTask = find_task(currentTask, option, p_index);
        if (foundTask != NULL)
        {
            currentTask = foundTask;
            return true;
        }
        else
        {
            printf("Task not found\n");
            return false;
        }
    }
}

// Task option
bool character_option(char *choice)
{
    char fChar = (*choice)[0];
    bool error = true;

    switch (tolower(fChar))
    {
        case 'q':
            run = false;
            break;
        case 'r':
            depth = 0;
            currentTask = root;
            break;
        default:
            printf("That character is not valid\n");
            error = false;
            break;
    }

    return error;
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

    bool run = true;
    Task *currentTask = root;
    
    // Display variable pointers
    int maxOptions = 1;
    int *p_maxOptions = &maxOptions;

    int depth = 0;
    int *p_depth = &depth;

    // Search variables
    int index = 1;
    int *p_index = &index;

    do
    {
        char *p_choice = get_option(currentTask, p_maxOptions, p_depth, p_index);

        // Check if input is a digit or a character
        switch (check_type((* p_choice)))
        {
            case 0:
                character_option(p_choice);
                break;
            case 1:
                task_option(p_choice);
                break;
            case 2:
                printf("Not a valid input try again");
                break;
        }
     
    } while (run != false);

    free_task(root);

    return 0;
}
