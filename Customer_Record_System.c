#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

COORD C = {0,0};
void gotoxy(int x,int y)
{
    C.X = x;
    C.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),C);
}
int main()
{
    FILE *f1, *f2;
    char another, choice;
    int n;

    struct cus
    {
        int id;
        char name[50];
        int mo;
        float tp;
    };
    struct cus c;
    long int recsize;
    f1= fopen("CUS.bin","rb+");
    if(f1==NULL)
    {
        f1= fopen("CUS.bin","wb+");
        if (f1==NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    recsize = sizeof(c);
    while(1)
    {
        system("cls");
        gotoxy(30,10);
        printf("1. Add Record");
        gotoxy(30,12);
        printf("2. List Records");
        gotoxy(30,14);
        printf("3. Modify Records");
        gotoxy(30,16);
        printf("4. Delete Records");
        gotoxy(30,18);
        printf("5. Exit");
        gotoxy(30,20);
        printf("Your Choice : ");
        fflush(stdin);
        choice =getche();

        switch(choice)
        {
        case '1':
            system("cls");
            fseek(f1,0,SEEK_END);
            another ='y';
            while(another=='y')
            {
                printf("\nEnter ID : ");
                scanf("%d",&c.id);
                printf("\nEnter name : ");
                scanf("%s",&c.name);
                printf("\nEnter mobile : ");
                scanf("%d",&c.mo);
                printf("\nEnter total purchase : ");
                scanf("%f",&c.tp);

                fwrite(&c,recsize,1,f1);
                printf("\nAdd another record (y/n)");
                fflush(stdin);
                another=getche();
            }
            break;
        case '2':
            system("cls");
            rewind(f1);
            while(fread(&c,recsize,1,f1)==1)
            {
                printf("\n%d %s %d %.2f",c.id,c.name,c.mo,c.tp);
            }
            getche();
            break;
        case '3':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter Customer id to modify: ");
                scanf("%d",&n);
                rewind(f1);
                while(fread(&c,recsize,1,f1)==1)
                {
                    if(c.id == n)
                    {
                        printf("\nEnter new id,name,mobile,total purchase: ");
                        scanf("\n%d %s %d %f",&c.id,&c.name,&c.mo,&c.tp);
                        fseek(f1,-recsize,SEEK_CUR);
                        fwrite(&c,recsize,1,f1);
                        break;
                    }
                }
                printf("\nModify another record (y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter customer id to delete: ");
                scanf("%d",&n);
                f2 = fopen("temp.bin","wb");
                rewind(f1);
                while(fread(&c,recsize,1,f1)== 1)
                {
                    if(c.id != n)
                    {
                        fwrite(&c,recsize,1,f2);
                    }
                }
                fclose(f1);
                fclose(f2);
                remove("CUS.bin");
                rename("temp.bin","CUS.bin");
                f1 = fopen("CUS.bin", "rb+");
                printf("Record deleted successfully");
                printf("\nDelete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(f1);
            exit(0);
        }
    }
    return 0;
}
