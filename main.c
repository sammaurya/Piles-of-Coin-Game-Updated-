#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

struct piles
{
    int coins;
    int index;
    struct piles *next;
};
struct piles *first=NULL;

void GetNames();
void Print_Name(char []);
void Print_Pills(struct piles *[],int,int);
void Play(struct piles *[],int);
int Check(struct piles *);
char player1[80],player2[80];

int main()
{
    int cases,i,j,n,data;
    printf("\n\n\t\t  PILES OF COINS");
    printf("\n\t   =========================");
    printf("\n\t===============================");
    GetNames();
    printf("\nEnter Rounds : ");
    scanf("%d",&cases);
    struct piles *Round[cases];
    for(i=0;i<cases;i++)
    {
        printf("\nEnter no. of piles : ");
        scanf("%d",&n);
        struct piles *ptr;
        ptr=(struct piles *)malloc(sizeof(struct piles));
        first=ptr;
        printf("\nEnter no. of coins : ");
        for(j=1;j<=n;j++)
        {
            do
            {
                scanf("%d",&data);
                if(data<=0||data>15)
                {
                    printf("\nCoins must be b/w (0 & 16) : ");
                    fflush(stdin);          //Clear b uffer
                }
            }while(data<=0||data>15);
            if(j==1)
            {
                ptr->coins=data;
                ptr->index=j;
            }
            else
            {
                struct piles *cpt;
                cpt=(struct piles *)malloc(sizeof(struct piles));
                cpt->coins=data;
                cpt->index=j;
                ptr->next=cpt;
                ptr=cpt;
            }
        }
        ptr->next=NULL;
        Round[i]=first;
    }
    Play(Round,cases);
    getch();
    return 0;
}

void Print_Piles(struct piles *Round[],int x,int cases)
{
    int max,temp,num,i;
    for(i=x;i<cases;i++)
    {
        printf("\n\n\tPiles : \n\n\t\t");
        struct piles *cpt,*ptr,*tpt;
        ptr=tpt=Round[i];
        max=tpt->coins;
        num=0;
        while(tpt!=NULL)
        {
            if(tpt->coins>=max)
            {
                max=tpt->coins;
            }
            printf("  %d  ",tpt->coins);
            num++;
            tpt=tpt->next;
        }
        temp=max;
        while(ptr->coins!=max)
        {
            ptr=ptr->next;
        }
        while(ptr->coins!=0)
        {
            printf("\n\n\t\t");
            cpt=Round[i];
            while(cpt->coins<ptr->coins)
            {
                printf("     ");
                cpt=cpt->next;
            }
            while(cpt!=NULL)
            {
                if(ptr->coins<=cpt->coins)
                {
                    printf("  *  ");
                }
                else
                {
                    printf("     ");
                }
                cpt=cpt->next;
            }
            temp--;
            ptr->coins=temp;
        }
        ptr->coins=max;
        printf("\n\t\t");
        cpt=Round[i];
        while(cpt!=NULL)
        {
            printf(" --- ");
            cpt=cpt->next;
        }
        printf("\n\t\t");
        cpt=Round[i];
        while(cpt!=NULL)
        {
            printf(" (%d) ",cpt->index);
            cpt=cpt->next;
        }
        printf("\n");
    }
}

void GetNames()
{
    int i;
    //flag=true;
    printf("\nEnter Player Names : ");
   // do
    //{
        i=0;
        printf("\n\tPlayer 1 : ");
        do
        {
            scanf("%c",&player1[i]);
            i++;
        }while(player1[i-1]!='\n');
        i=0;
        printf("\n\tPlayer 2 : ");
        do
        {
            scanf("%c",&player2[i]);
            i++;
        }while(player2[i-1]!='\n');
    /*    for(j=0;j<10;j++)
        {
            if(player1[0]==j||player2[0]==j)
            {
                printf("\nError : Names Can not start with numbers");
                printf("\nEnter again : ");
                flag=false;
                i=0;
            }
        } */

     //   while(getchar()!='\n');
 //   }while(flag==true);
}
void Print_Name(char name[])
{
    int a=0;
    while(name[a]!='\n')
    {
        printf("%c",name[a]);
        a++;
    }
}
void Play(struct piles *Round[],int cases)
{
    int k=cases,i,j;
    char ch;
    for(i=0;i<cases;i++)
    {
        int flag=true;
        j=1;
        printf("\nPress (Y/N) to Play Round %d or exit : ",i+1);
        scanf(" %c",&ch);
        if(ch=='n'||ch=='N')
        {
            cases=0;
            flag=false;
        }
        else
        {
            printf("\nRound %d ",i+1);
        }

        struct piles *ptr;
        ptr=Round[i];
        while(flag==true)
        {
            if(j%2!=0)
            {
                Print_Piles(Round,i,(cases-(k-i-1)));
                printf("\n\n");
                Print_Name(player1);
                printf("'s Turn : ");
                if(Check(ptr)==0)
                {
                    printf("\n\tYou have No Moves ");
                    printf("\n\n\t");
                    Print_Name(player2);
                    printf(" WON\n");
                    flag=false;
                }

            }
            else
            {
                Print_Piles(Round,i,(cases-(k-i-1)));
                printf("\n\n");
                Print_Name(player2);
                printf("'s Turn : ");
                if(Check(ptr)==0)
                {
                    printf("\nYou have No Moves ");
                    printf("\n\n\t");
                    Print_Name(player1);
                    printf(" WON\n");
                    flag=false;
                }
            }
            j++;
        }

    }
}
int Check(struct piles *ptr)
{
    int p,flag1=false,flag2=false;
    struct piles *cpt,*tpt;
    printf("\n\tSelect a Pile : ");
    do
    {
        tpt=cpt=ptr;
        scanf("%d",&p);
        while(tpt->index!=p)
        {
            tpt=tpt->next;
        }
        if(tpt->coins==0)
        {
            while(cpt!=NULL&&flag2==false)
            {
                if(cpt->coins!=0)
                {
                    printf("\n\tPile %d contains zero coin\n\tSelect another Pile : ",p);
                    flag2=true;
                }
                cpt=cpt->next;
            }
        }
        else
        {
            if((tpt->coins)%2==0)
            {
                tpt->coins=(tpt->coins)/2;
            }
            else
            {
                tpt->coins=(tpt->coins-1)/2;
            }
            flag1=true;
        }
    }while(flag1!=true&&flag2==true);
    if(flag1==true)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
