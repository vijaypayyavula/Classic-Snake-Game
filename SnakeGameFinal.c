#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length = 0 ;
int bend_no ;
int len ;
char key ;
int life ;
int ch ;
int speed = 10000000 ;

char name[50] ;

void Move() ; 
void Food() ; 
int Score() ;
void Rules() ;
void GotoXY(int x , int y) ;
void Bend() ; 
void Border() ; 
void Down() ; 
void Left() ;
void Up() ;
void Right() ;
void ExitGame() ; 
void load() ; 
void print() ; 
void high_score() ;
void game() ;
void settings() ; 
void mspeed(); 
void colour();

FILE *highscore , *highscore_1;

typedef struct coord1
{
    int x ;
    int y ;
    int direction ;
}coord1 ;

coord1 head , bend[500] , food , body[1000] ;

void main()
{
    print() ;
    while(TRUE)
    {
        switch(ch)
        {
            case 1 : game() ; 
            case 2 : high_score() ;
            case 3 : settings() ;
            case 4 : exit(0) ;
            default : printf("Invalid choice ! Please try again .....") ;                
        } 
    }   
}

void game()
{
    system("cls");
    printf("Hello ! Welcome to the Snake Game \n Please enter your name : ") ;
    scanf("%s",name);
    if(name[0]>=(char)97&&name[0]<=(char)122)
        name[0]-=(char)32;

    printf("\nPress enter to read rules") ;
    getch() ;

    Rules() ;
    load() ;

    length = 5;
    head.x = 25 ;
    head.y = 20 ;
    head.direction = RIGHT ;

    Border() ;
    Food() ;
    life = 0 ;
    bend[0] = head ;
    Move() ;
}

void print()
{
        system("cls") ;
        GotoXY(24,8) ;
        printf(" _______________________________________________________________") ;
        GotoXY(24,9) ;
        printf("|\t\t\t\t\t\t\t\t|") ;
        GotoXY(24,10) ;
        printf("|\t\t\t\t\t\t\t\t|") ;
        GotoXY(24,11);
        printf("|\t\t\t    SNAKE GAME    \t\t\t|") ;
        GotoXY(24,11) ;
        printf("|\t\t\t\t\t\t\t\t|") ;
        GotoXY(24,12) ;
        printf("|\t\t\t\t\t~Sachin,Vijay,Vineet\t|") ;
        GotoXY(24,13) ;
        printf("|_______________________________________________________________|") ;
        GotoXY(30,16) ;
        printf("1. Play Game") ;
        GotoXY(30,18) ;
        printf("2. Highscore") ;
        GotoXY(30,20) ;
        printf("3. Settings") ;
        GotoXY(30,22) ;
        printf("4. Exit") ;
        GotoXY(24,24) ;
        printf(" ______________________________________________________________") ;
        GotoXY(25,26) ;
        printf("Enter your choice : ") ;
        scanf("%d",&ch) ;        
}

void Border()
{
    system("cls") ;
    int i ;
    GotoXY(food.x,food.y) ;  
    printf("O") ;
    for(i=10; i<71; i++)
    {
        GotoXY(i,10) ;
        printf("-") ;
        GotoXY(i,30) ;
        printf("-") ;
    }
    for(i=11; i<30; i++)
    {
        GotoXY(10,i) ;
        printf("|") ;
        GotoXY(70,i) ;
        printf("|") ;
    }
}

void Delay(long double k)
{
    Score() ;    
    long double i ;
    for(i=0; i<=speed; i++) ; //1000000
}

void Food()
{
    if(head.x==food.x&&head.y==food.y)  // snakes eats the food
    {
        length++ ;
        food.x=rand()%70 ;
        if(food.x<=10)
            food.x+=11 ;
        food.y=rand()%30 ;
        if(food.y<=10)
            food.y+=11 ;
    }
    else if(food.x==0) 
    {
        food.x=rand()%70 ;
        if(food.x<=10)
            food.x+=11 ;
        food.y=rand()%30 ;
        if(food.y<=10)
            food.y+=11 ;
    }
}

void Move()
{
    int a,i;
    do
    {
        Food();
        fflush(stdin);
        len=0;
        for(i=0; i<1000; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        Delay(length);
            Border();

        if(head.direction==RIGHT)
            Right();

        else if(head.direction==LEFT)
            Left();

        else if(head.direction==DOWN)
            Down();

        else if(head.direction==UP)
            Up();

        ExitGame();
    }
    while(!kbhit());
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||
        (key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;        
        bend[bend_no]=head;
        head.direction=key;

        if(key==UP)
            head.y--;

        if(key==DOWN)
            head.y++;

        if(key==RIGHT)
            head.x++;

        if(key==LEFT)
            head.x--;

        Move();
    }
    else if(key==27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        Move();
    }
}

void GotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void load()
{
    system("cls");
    int r,q;
    GotoXY(36,14);
    printf("Game starts in ");
    GotoXY(45,15);
    for(r=3; r>=0; r--)
        for(q=0; q<=300000000; q++);
            printf("\t%d...",r);
            
    printf("\tLETS GOOO...");
    for(q=0; q<=300000000; q++);
}

void ExitGame()
{
    int i,check=0,ch;
    for(i=4; i<length; i++) //check snake touches itself
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\n\nPress enter to return to menu\n\nYour score is : %d",length-5); 
            getch();  
            main();  
        }
    }
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("o");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("o");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("o");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("o");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}

void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("o");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}

void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("o");
        }
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}

void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("o");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}

void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("o");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(46,8);
    printf("LIFES LEFT : %d",life);
    return score;
}

void Rules()
{
    system("cls");
    printf("Here are the rules of the game\n\n-> Use arrow keys to move\n-> Press escape to quit game");
    printf("\n-> If you touch the walls your life redcues\n-> Game ends when life is zero\n\nHave fun and Good luck");
    getch();
}

void high_score()
{    
    int oldscore=0;
    int newscore=length-5;
    
    char str[100],c;  
    
    highscore_1 = fopen("highscore.txt","r");
    fgets(str,100,highscore_1);
    fclose(highscore_1);  
   
    for(int i=0;i<sizeof(str)-2;i++)       
        if(str[i]>=48&&str[i]<=57&&str[i]!='\0')
                oldscore=oldscore*10+(str[i]-48);               
    
    oldscore/=1000;

    if(newscore>oldscore)
    {   
        highscore=fopen("highscore.txt","w");       
        //highscore = freopen("score.txt","w",stdout);
        fprintf(highscore,"Name : %s\t\tScore : %d",name,newscore); 
        fclose(highscore);       
        high_score();
    }
    else
    {
        system("cls");
        printf("Highscore \n\t ");
        printf("\t%s",str);
        printf("\n\n\nPress enter to go to back to main menu....");
        getch();
        main();
    }
}

void mspeed()
{
    system("cls");
    printf("\n\n\n\tChoose speed : \n\n\t\t1. Slow \n\n\t\t2. Normal \n\n\t\t3. Fast\n\t_____________________\n\n\tEnter your choice : ");
    scanf("%d",&ch);

    if(ch==1)
        speed = 50000000;
    else if(ch==2)
        speed = 10000000;
    else if(ch==3)
        speed = 1000000;

    printf("\nSpeed changed , Press enter to get back to settings");
    getch();
    settings();
}

void settings()
{
    while(1)
    {
        system("cls");
        printf("\n\n\n\tSettings : \n\n\t\t1. Speed\n\n\t\t2. Color\n\n\t\t3. Main Menu\n\n\t_____________________\n\n\tEnter your choice : ");
        scanf("%d",&ch);
                
            switch(ch)
            {
                case 1 : mspeed();
                case 2 : colour();
                case 3 : main();
                default: printf("\n\t\tWrong choice entered....press enter to try again");
                         getch();
            }
        }

}

void colour()
{
    char color;

    while(1)
    {
        system("cls");

        printf("COLOR CHANGE CODES: ");
        printf("\n A - GREEN\n B - AQUA\n C - RED\n D - PURPLE\n E - YELLOW\n F - WHITE");
        scanf("%c",&color);
        printf("\n\nEnter A-F to change to that colour : ");
        scanf("%c",&color);

        if(color>=(char)97&&color<=(char)122)
            color-=(char)32;        

        switch(color)
        {
            case 'A' : system("Color 0A");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            case 'B' : system("Color 0B");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            case 'C' : system("Color 0C");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            case 'D' : system("Color 0D");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            case 'E' : system("Color 0E");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            case 'F' : system("Color 0F");
                       printf("Color changed...Press enter to continue...");
                       getch();
                       settings();
            default : printf("Wrong choice try again.....");  
        }        
        getch();                                                      
    }
}