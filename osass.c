#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char bunnyName[32];
    char areaName[32];
    int countOfEntering;
} Applicant;
char *chooseArea()
{
    char *area = malloc(sizeof(char) * 32);
    int ch;
    do
    {
        printf("\nChoose area name of Applicant: ");
        printf("\n1)Barátfa ");
        printf("\n2)Lovas ");
        printf("\n3)Szula");
        printf("\n4)Kígyós-patak");
        printf("\n5)Malom telek");
        printf("\n6)Páskom");
        printf("\n7)Káposztás kert\n");
        scanf("%i", &ch);
        switch (ch)
        {
        case 1:
            strcpy(area, "Barátfa");
            return area;
            break;
        case 2:
            strcpy(area, "Lovas");
            return area;
            break;
        case 3:
            strcpy(area, "Szula");
            return area;
            break;
        case 4:
            strcpy(area, "Kígyós-patak");
            return area;
            break;
        case 5:
            strcpy(area, "Malom telek");
            return area;
            break;
        case 6:
            strcpy(area, "Páskom");
            return area;
            break;
        case 7:
            strcpy(area, "Káposztás kert");
            return area;
            break;
        }
    } while (0 >= ch || ch >= 8);
    return area;
    free(area);
}
void enterList()
{
    Applicant *bunny;
    int n, i;
    FILE *fp;
    printf("Enter how many Applicants you want to store: ");
    scanf("%i", &n);
    fp = fopen("ListOfApplicants.txt", "w");
    bunny = (Applicant *)malloc(n * sizeof(Applicant));
    for (i = 0; i < n; i++)
    {
        printf("\nEnter Name: ");
        scanf("%s", bunny[i].bunnyName);
        char *carea = chooseArea();
        strcpy(bunny[i].areaName, carea);
        printf("\nEnter how many times you are entering the competition: ");
        scanf("%i", &bunny[i].countOfEntering);
        fwrite(&bunny[i], sizeof(Applicant), 1, fp);
    }
    fclose(fp);
    free(bunny);
}
void modifyList()
{
    Applicant bunny;
    FILE *fp, *fp1;
    fp = fopen("ListOfApplicants.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int found = 0;
    int choice;
    char searchName[32];
    printf("\nPlease Enter Name of Applicant you want to Modify: ");
    scanf("%s", searchName);
    while (fread(&bunny, sizeof(Applicant), 1, fp))
    {

        if (strcmp(bunny.bunnyName, searchName) == 0)
        {
            found = 1;
            do
            {
                printf("\nWhat you want to change?");
                printf("\n1)If you want to modify name of Applicant");
                printf("\n2)If you want to modify area of Applicant");
                printf("\n3)If you want to modify count of entering of Applicant\n");
                scanf("%d", &choice);
            } while (choice < 1 || choice > 3);
            switch (choice)
            {
            case 1:
            {
                char newName[32];
                Applicant temp;
                printf("\nEnter new name of Applicant: ");
                scanf("%s", newName);
                strcpy(temp.bunnyName, newName);
                strcpy(temp.areaName, bunny.areaName);
                temp.countOfEntering = bunny.countOfEntering;
                fwrite(&temp, sizeof(Applicant), 1, fp1);
                continue;
            }
            break;
            case 2:
            {
                Applicant temp;
                strcpy(temp.bunnyName, bunny.bunnyName);
                char *newArea = chooseArea();
                strcpy(temp.areaName, newArea);
                temp.countOfEntering = bunny.countOfEntering;
                fwrite(&temp, sizeof(Applicant), 1, fp1);
                continue;
            }
            break;
            case 3:
            {
                int tempCountOfEntering;
                printf("\nEnter new Counter of entering of Applicant: ");
                scanf("%d", &tempCountOfEntering);
                Applicant temp;
                strcpy(temp.bunnyName, bunny.bunnyName);
                strcpy(temp.areaName, bunny.areaName);
                temp.countOfEntering = tempCountOfEntering;
                fwrite(&temp, sizeof(Applicant), 1, fp1);
                continue;
            }
            break;
            }
        }
        fwrite(&bunny, sizeof(Applicant), 1, fp1);
    }
    fclose(fp1);
    fclose(fp);
    if (!found)
    {
        printf("\nThere is no Applicant with the given name!\n");
    }
    else
    {
        fp1 = fopen("ListOfApplicants.txt", "w");
        fp1 = fopen("temp.txt", "r");
        while (fread(&bunny, sizeof(Applicant), 1, fp1))
        {
            fwrite(&bunny, sizeof(Applicant), 1, fp);
        }
        fclose(fp1);
        fclose(fp);
    }
}
void deleteBunny()
{
    Applicant bunny;
    FILE *fp, *fp1;
    fp = fopen("ListOfApplicants.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int found = false;
    char searchName[32];
    printf("Enter Name of Applicant you want to Delete: ");
    scanf("%s", searchName);
    while (fread(&bunny, sizeof(Applicant), 1, fp))
    {
        if (strcmp(bunny.bunnyName, searchName) == 0)
        {
            found = true;
            continue;
        }
        fwrite(&bunny, sizeof(Applicant), 1, fp1);
    }
    fclose(fp1);
    fclose(fp);
    if (!found)
    {
        printf("There is no Applicant with the given name!\n");
    }
    else
    {
        fp1 = fopen("ListOfApplicants.txt", "w");
        fp1 = fopen("temp.txt", "r");
        while (fread(&bunny, sizeof(Applicant), 1, fp1))
        {
            fwrite(&bunny, sizeof(Applicant), 1, fp);
        }
        fclose(fp1);
        fclose(fp);
    }
}
void createList()
{
    Applicant s1;
    FILE *fp;
    fp = fopen("ListOfApplicants.txt", "r");
    while (fread(&s1, sizeof(Applicant), 1, fp))
    {
        printf("\n%s-%s-%i", s1.bunnyName, s1.areaName, s1.countOfEntering);
    }
    printf("\n");
    fclose(fp);
}
void createListByArea()
{
    Applicant bunny;
    FILE *fp, *fp1;
    fp = fopen("ListOfApplicants.txt", "r");
    fp1 = fopen("temporary.txt", "w");
    int found = 0;
    int choice;
    char searchArea[32];
    printf("\nPlease Enter Name Area of Applicants you want to List: ");
    scanf("%s", searchArea);
    while (fread(&bunny, sizeof(Applicant), 1, fp))
    {
        found = 1;
        if (strcmp(bunny.areaName, searchArea) == 0)
        {
            fwrite(&bunny, sizeof(Applicant), 1, fp1);
        }
    }
    fclose(fp1);
    fclose(fp);
    if (!found)
    {
        printf("\nThere is no Applicants with the given Area name!\n");
    }
    else
    {
        fp1 = fopen("ListOfApplicantsByArea.txt", "w");
        fp1 = fopen("temporary.txt", "r");
        while (fread(&bunny, sizeof(Applicant), 1, fp1))
        {
            fwrite(&bunny, sizeof(Applicant), 1, fp);
        }
        fclose(fp1);
        fclose(fp);
    }
    FILE *fp3;
    fp3 = fopen("ListOfApplicantsByArea.txt", "r");
    while (fread(&bunny, sizeof(Applicant), 1, fp3))
    {
        printf("\n%s-%s-%i", bunny.bunnyName, bunny.areaName, bunny.countOfEntering);
    }
    printf("\n");
    fclose(fp3);
}
int main()
{
    system("clear");
    int choice;
    do
    {
        printf("\nEnter Your Choice: ");
        printf("\n1 Enter list of Applicants");
        printf("\n2 Modify list of Applicants");
        printf("\n3 Delete Applicant from list");
        printf("\n4 Create List of Applicant be area");
        printf("\n5 Create List of Applciants");
        printf("\n0 To exit program\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            enterList();
            break;
        case 2:
            modifyList();
            break;
        case 3:
            deleteBunny();
            break;
        case 4:
            createListByArea();
            break;
        case 5:
            createList();
            break;
        }
    } while (choice != 0);
    return 0;
}