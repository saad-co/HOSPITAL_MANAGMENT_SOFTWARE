#include <stdio.h>
#define size 20
#include <stdbool.h>
struct PATIENT
{
    char name[size];
    int id;
    int cnic;
    int ph_no;
    char disease[size];
    int is_addmitted;
};
typedef struct PATIENT pat;

void add_patient(pat *p)
{
    FILE *ptr;
    ptr = fopen("patient_record.txt", "a");
    if (ptr == NULL)
    {
        ptr = fopen("patient_record.txt", "w");
    }
    if (ptr == NULL)
    {
        printf("\nencountered error while opening the file");
    }
    else
    {
        printf("\nENTER THE NAME OF THE PATIENT:");
        fflush(stdin);
        gets(p->name);
        fflush(stdin);
        printf("\nenter the id:");
        scanf("%d", &p->id);
        fflush(stdin);
        printf("\nEnter the disease of the patient: ");
        gets(p->disease);
        fflush(stdin);
        printf("\nEnter the cnic of the user:");
        scanf("%d", &p->cnic);
        fflush(stdin);
        printf("\nEnter the phone number:");
        scanf("%d", &p->ph_no);
        fflush(stdin);
        printf("\nenter the status of the patient (1 OR 0?):");
        scanf("%d", &p->is_addmitted);
        fflush(stdin);
        fwrite(p, sizeof(pat), 1, ptr);
        fclose(ptr);
        printf("Record has been wriiten\n");
        printf("\n\n----------------------------------------------------\n\n");
    }
}

void display(pat *p)
{

    FILE *ptr;
    ptr = fopen("patient_record.txt", "r");
    if (ptr == NULL)
    {
        printf("error while opening the file");
    }
    else
    {
        while (fread(p, sizeof(pat), 1, ptr))
        {
            printf("Name : %s\n", p->name);
            printf("ID: %d\n", p->id);
            printf("DISEASE: %s\n", p->disease);
            printf("CNIC: %d\n", p->cnic);
            printf("PHONE NUMBER: %d\n", p->ph_no);
            // printf("ADDMIT STATUS: %d",p->is_addmitted);
            if (p->is_addmitted)
            {
                printf("PATIENT IS ADMITTED\n");
            }
            else
            {
                printf("PATIENT IS NOT ADMITTED\n");
            }
            printf("\n\n----------------------------------------------------\n\n");
        }
        fclose(ptr);
    }
}
void search_patient(pat *p)
{
    FILE *ptr;
    int id = 0;
    bool exist = false;
    printf("\n ENTER THE ID OF THE PATIENT: ");
    scanf("%d", &id);
    ptr = fopen("patient_record.txt", "r");
    if (ptr == NULL)
    {
        printf("errror while opening the file");
    }
    else
    {
        while (fread(p, sizeof(pat), 1, ptr))
        {
            if (id == p->id)
            {
                printf("Name : %s\n", p->name);
                printf("ID: %d\n", p->id);
                printf("DISEASE: %s\n", p->disease);
                printf("CNIC: %d\n", p->cnic);
                printf("PHONE NUMBER: %d\n", p->ph_no);
                if (p->is_addmitted)
                {
                    printf("PATIENT IS ADMITTED\n");
                }
                else
                {
                    printf("PATIENT IS NOT ADMITTED\n");
                }
                printf("\n\n----------------------------------------------------\n\n");
                exist = true;
            }
        }
        if (exist == false)
        {
            printf("\nRECORD NOT FOUND\n");
        }
    }
}

void delete_patient(pat *p)
{
    struct PATIENT temp_pat_struct;
    FILE *ptr;
    ptr = fopen("patient_record.txt", "r");
    printf("\nENTER THE ID YOU THE PATIENT: ");
    int id = 0;
    scanf("%d", &id);
    FILE *temp_ptr;
    temp_ptr = fopen("tem_patient.txt", "a");
    int found = 0;
    if (ptr == NULL)
    {
        printf("\nerror");
    }
    else
    {
        while (fread(&temp_pat_struct, sizeof(struct PATIENT), 1, ptr))
        {
            if (temp_pat_struct.id == id)
            {
                found = 1;
            }
            else
            {
                fwrite(&temp_pat_struct, sizeof(pat), 1, temp_ptr);
            }
        }
    }
    if (found == 1)
    {
        printf("\n\nPATIENT RECORD DELETED SUCCESFULLY\n");
    }
    else
    {
        printf("\nNO RECORD FOUND FOR THE GIVEN ID");
    }
    fclose(temp_ptr);
    fclose(ptr);
    remove("patient_record.txt");
    rename("tem_patient.txt", "patient_record.txt");
    printf("\n\n----------------------------------------------------\n\n");
}

void update_patient(pat *p)
{
    FILE *ptr;
    ptr = fopen("patient_record.txt", "r");
    FILE *temp_ptr;
    temp_ptr = fopen("temp_file.txt", "w");
    int id = 0;
    int flag = 0;
    printf("\nENTER THE ID OF THE PATIENT TO UPDATE: ");
    scanf("%d", &id);
    bool fnd = false;
    if (ptr == NULL)
    {
        printf("\nERROR ");
    }
    else
    {
        while (fread(p, sizeof(pat), 1, ptr))
        {
            flag = 1;
            if (p->id == id)
            {
                fflush(stdin);
                printf("\nENTER THE NAME OF THE PATIENT:");
                fflush(stdin);
                gets(p->name);
                fflush(stdin);
                printf("\nenter the id:");
                scanf("%d", &p->id);
                fflush(stdin);
                printf("\nEnter the disease of the patient: ");
                gets(p->disease);
                fflush(stdin);
                printf("\nEnter the cnic of the user:");
                scanf("%d", &p->cnic);
                fflush(stdin);
                printf("\nEnter the phone number:");
                scanf("%d", &p->ph_no);
                fflush(stdin);
                printf("\nenter the status of the patient (1 OR 0?):");
                scanf("%d", &p->is_addmitted);
                fflush(stdin);
                fwrite(p, sizeof(pat), 1, temp_ptr);
                printf("Record has been wriiten\n");
                printf("\n\n----------------------------------------------------\n\n");
                fnd = true; 
                flag = 0;
            }
            if (flag == 1)
            {
                fwrite(p, sizeof(pat), 1, temp_ptr);
            }
        }
        if(fnd == false)
        {
            printf("\nrecord not found");
        }
        else
        {
            printf("\nupdated sucessfully");
        }
        fclose(ptr);
        fclose(temp_ptr);
        remove("patient_record.txt");
        rename("temp_file.txt", "patient_record.txt");
    }
}

int main()
{
    pat p;

    bool keep_reading = true;
    int choice = 0;
    while (keep_reading)
    {
        printf("\n\n----------------------------------------------------\n\n");
        printf("1: ADD PATIENT\t\t\t\t");
        printf("2: DELETE PATIENT\n\n");
        printf("3: UPDATE PATIENT\t\t\t");
        printf("4: SEARCH PATIENT\n\n");
        printf("5: DISPLAY ALL PATIENTS\t\t\t");
        printf("6: EXIT\n\n");
        printf("\n----------------------------------------------------\n\n");

        printf("\n Enter the choise:\t");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_patient(&p);
            break;
        case 2:
           delete_patient(&p);
            break;
        case 4:
            search_patient(&p);
            break;
        case 3:
            update_patient(&p);
            break;
        case 5:
            display(&p);
            break;
        case 6:
            keep_reading = false;
            break;
        default:
            printf("\nINVALID INPUT");
            break;
        }
    }
}