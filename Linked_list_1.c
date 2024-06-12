#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DPRINTF(...) {fflush(stdout); fflush(stdin); printf(__VA_ARGS__); fflush(stdout); fflush(stdin);}

struct Sdata
{
    int id;
    char name[40];
    float Height;
};

struct sstudent
{
    struct Sdata Student;
    struct sstudent* P_NEXT_STUDENT;
};

struct sstudent* g_p_First_Student = NULL;

void Add_Student()
{
    struct sstudent* P_NEW_STUDENT = (struct sstudent*)malloc(sizeof(struct sstudent));
    struct sstudent* P_Last_STUDENT;

    if (P_NEW_STUDENT == NULL) {
        DPRINTF("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    char temp_text[40];

    DPRINTF("\n Enter the student ID: ");
    fgets(temp_text, sizeof(temp_text), stdin);
    P_NEW_STUDENT->Student.id = atoi(temp_text);

    DPRINTF("\n Enter the student Full Name: ");
    fgets(P_NEW_STUDENT->Student.name, sizeof(P_NEW_STUDENT->Student.name), stdin);
    P_NEW_STUDENT->Student.name[strcspn(P_NEW_STUDENT->Student.name, "\n")] = '\0'; // remove newline character

    DPRINTF("\n Enter the student Height: ");
    fgets(temp_text, sizeof(temp_text), stdin);
    P_NEW_STUDENT->Student.Height = atof(temp_text);

    P_NEW_STUDENT->P_NEXT_STUDENT = NULL;

    if (g_p_First_Student == NULL)
    {
        g_p_First_Student = P_NEW_STUDENT;
    }
    else
    {
        P_Last_STUDENT = g_p_First_Student;
        while (P_Last_STUDENT->P_NEXT_STUDENT != NULL)
        {
            P_Last_STUDENT = P_Last_STUDENT->P_NEXT_STUDENT;
        }
        P_Last_STUDENT->P_NEXT_STUDENT = P_NEW_STUDENT;
    }
}

void Delete_Student()
{
    char temp_text[40];
    unsigned int Selected_Id;
    struct sstudent* P_Selected_STUDENT;
    struct sstudent* P_previos_STUDENT = NULL;

    DPRINTF("\nEnter the student ID to be Deleted: ");
    fgets(temp_text, sizeof(temp_text), stdin);
    Selected_Id = atoi(temp_text);

    P_Selected_STUDENT = g_p_First_Student;
    while (P_Selected_STUDENT)
    {
        if (P_Selected_STUDENT->Student.id == Selected_Id)
        {
            if (P_previos_STUDENT)
            {
                P_previos_STUDENT->P_NEXT_STUDENT = P_Selected_STUDENT->P_NEXT_STUDENT;
            }
            else
            {
                g_p_First_Student = P_Selected_STUDENT->P_NEXT_STUDENT;
            }
            free(P_Selected_STUDENT);
            DPRINTF("Student with ID %d has been deleted.\n", Selected_Id);
            return;
        }
        P_previos_STUDENT = P_Selected_STUDENT;
        P_Selected_STUDENT = P_Selected_STUDENT->P_NEXT_STUDENT;
    }
    DPRINTF("Student with ID %d not found.\n", Selected_Id);
}

void View_Students()
{
    struct sstudent* P_CURRENT_STUDENT = g_p_First_Student;
    int count = 0;

    if (g_p_First_Student == NULL)
    {
        DPRINTF("\n Empty List\n");
    }
    else
    {
        while (P_CURRENT_STUDENT)
        {
            DPRINTF("\n Record number %d", count + 1);
            DPRINTF("\n\t Student ID: %d", P_CURRENT_STUDENT->Student.id);
            DPRINTF("\n\t Student Name: %s", P_CURRENT_STUDENT->Student.name);
            DPRINTF("\n\t Student Height: %f\n", P_CURRENT_STUDENT->Student.Height);
            P_CURRENT_STUDENT = P_CURRENT_STUDENT->P_NEXT_STUDENT;
            count++;
        }
    }
}

void Delete_All()
{
    struct sstudent* P_CURRENT_STUDENT = g_p_First_Student;
    struct sstudent* P_TEMP_STUDENT;

    while (P_CURRENT_STUDENT)
    {
        P_TEMP_STUDENT = P_CURRENT_STUDENT;
        P_CURRENT_STUDENT = P_CURRENT_STUDENT->P_NEXT_STUDENT;
        free(P_TEMP_STUDENT);
    }
    g_p_First_Student = NULL;
    DPRINTF("\nAll students have been deleted.\n");
}

int main()
{
    char temp_text[40];
    int option;

    while (1)
    {
        DPRINTF("\n====================");
        DPRINTF("\n\t choose the following options \n");
        DPRINTF("\n 1: Add Student ");
        DPRINTF("\n 2: Delete Student ");
        DPRINTF("\n 3: View Students ");
        DPRINTF("\n 4: Delete All ");
        DPRINTF("\n 5: Exit ");
        DPRINTF("\n Enter option number: ");

        fgets(temp_text, sizeof(temp_text), stdin);
        option = atoi(temp_text);

        DPRINTF("=====================");

        switch (option)
        {
        case 1:
            Add_Student();
            break;
        case 2:
            Delete_Student();
            break;
        case 3:
            View_Students();
            break;
        case 4:
            Delete_All();
            break;
        case 5:
            return 0;
        default:
            DPRINTF("\n wrong option\n");
            break;
        }
    }
    return 0;
}
