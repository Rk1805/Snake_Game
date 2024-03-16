#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#include<termios.h>
#include<fcntl.h>
 
struct body{
    int x;
    int y;
    struct body* next;
};
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m" // Reset to default color

void draw(int i, int j, char *ptr,char arr[30][60]) 
{
    if (i <= 29) 
    {
        if ((i == 0 || i == 29) && j != 0 && j != 59) 
        {
            *ptr = '-';
        } 
        else if ((j == 0 || j == 59) && i != 0 && i != 29) 
        {
            *ptr = '|';
        } 
        else 
        {
            *ptr= ' ';
        }
        if (j <59) 
        {
            j+=1;
            ptr++;
            draw(i, j, ptr,arr); 
        } 
        else 
        {
            if(i<29)
            {
                i+=1;
                j=0;
                ptr=&arr[i][j];
                draw(i, j, ptr,arr); 
            }
        }
    }
}
void compartment(char arr[30][60])
{
    draw(0,0,&arr[0][0],arr);
    for(int i=8;i<10;i++)
    {
        for(int j=9;j<50;j++)
        {
            arr[i][j]='*';
        }
    }
    for(int i=21;i<23;i++)
    {
        for(int j=9;j<50;j++)
        {
            arr[i][j]='*';
        }
    }
    for(int i=1;i<7;i++)
    {
        arr[i][1]='*';
        arr[i][58]='*';
    }
    for(int i=24;i<29;i++)
    {
        arr[i][1]='*';
        arr[i][58]='*';
    }
    for(int j=2;j<9;j++)
    {
        arr[1][j]='*';
        arr[28][j]='*';
    }
    for(int j=51;j<58;j++)
    {
        arr[1][j]='*';
        arr[28][j]='*';
    }
}

void apartment(char arr[30][60])
{
    draw(0,0,&arr[0][0],arr);
    for(int i=1;i<29;i++)
    {
        if(i!=10 && i!=11 && i!=12)
        {
            arr[i][20]='*';
        }
    }
    for(int j=1;j<20;j++)
    {
        arr[15][j]='*';
    }
    for(int i=1;i<29;i++)
    {
        if(i!=11 && i!=12)
        {
            arr[i][45]='*';
        }
    }
    for(int j=46;j<59;j++)
    {
        arr[10][j]='*';
    }
}
int generate(int number)
{
    srand(time(NULL));
    return (rand()%(number-1)+1);
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

int w(char arr[30][60],int *score,int *sp,struct body* tail)
{
    struct body *current=tail;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    if(arr[current->x-1][current->y]=='x')
    {
        struct body *t=(struct body*)malloc(sizeof(struct body));
        t->x=current->x-1;
        t->y=current->y;
        t->next=NULL;
        current->next=t;
        arr[t->x][t->y]='0';
        *score+=2*(*sp);
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0' || arr[g1][g2]=='*')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }

    else if(arr[current->x-1][current->y]!='*' && arr[current->x-1][current->y]!='0')
    {
        if(arr[current->x-1][current->y]=='-')
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->x=28;
            arr[tmp->x][tmp->y]='0';
        }
        else
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->x=tmp->x-1;
            arr[tmp->x][tmp->y]='0';
        }
        return 1;
    }
    else            
    {
        return 0;
    }
}

int a(char arr[30][60],int *score,int *sp,struct body* tail)
{
    struct body *current=tail;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    if(arr[current->x][current->y-1]=='x')
    {
        struct body *t=(struct body*)malloc(sizeof(struct body));
        t->x=current->x;
        t->y=current->y-1;
        t->next=NULL;
        current->next=t;
        arr[t->x][t->y]='0';
        *score+=2*(*sp);
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0' || arr[g1][g2]=='*')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }

    else if(arr[current->x][current->y-1]!='*' && arr[current->x][current->y-1]!='0')
    {
        if(arr[current->x][current->y-1]=='|')
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->y=58;
            arr[tmp->x][tmp->y]='0';
        }
        else
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->y=tmp->y-1;
            arr[tmp->x][tmp->y]='0';
        }
        return 1;
    }
    else            
    {
        return 0;
    }
}

int s(char arr[30][60],int *score,int *sp,struct body* tail)
{
    struct body *current=tail;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    if(arr[current->x+1][current->y]=='x')
    {
        struct body *t=(struct body*)malloc(sizeof(struct body));
        t->x=current->x+1;
        t->y=current->y;
        t->next=NULL;
        current->next=t;
        arr[t->x][t->y]='0';
        *score+=2*(*sp);
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0' || arr[g1][g2]=='*')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }

    else if(arr[current->x+1][current->y]!='*' && arr[current->x+1][current->y]!='0')
    {
        if(arr[current->x+1][current->y]=='-')
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->x=1;
            arr[tmp->x][tmp->y]='0';
        }
        else
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->x=tmp->x+1;
            arr[tmp->x][tmp->y]='0';
        }
        return 1;
    }
    else            
    {
        return 0;
    }
}

int d(char arr[30][60],int *score,int *sp,struct body* tail)
{
    struct body *current=tail;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    if(arr[current->x][current->y+1]=='x')
    {
        struct body *t=(struct body*)malloc(sizeof(struct body));
        t->x=current->x;
        t->y=current->y+1;
        t->next=NULL;
        current->next=t;
        arr[t->x][t->y]='0';
        *score+=2*(*sp);
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0' || arr[g1][g2]=='*')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }

    else if(arr[current->x][current->y+1]!='*' && arr[current->x][current->y+1]!='0')
    {
        if(arr[current->x][current->y+1]=='|')
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->y=1;
            arr[tmp->x][tmp->y]='0';
        }
        else
        {
            struct body *tmp=tail;
            arr[tail->x][tail->y]=' ';
            while(tmp->next!=NULL)
            {
                tmp->x=tmp->next->x;
                tmp->y=tmp->next->y;
                tmp=tmp->next;
            }
            tmp->y=tmp->y+1;
            arr[tmp->x][tmp->y]='0';
        }

        return 1;
    }
    else            
    {
        return 0;
    }
}

void print(char arr[30][60],int *score)
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            if(arr[i][j]=='*')
            {
                printf(RED"%c"RESET,arr[i][j]);
            }
            else if(arr[i][j]=='0')
            {
                printf(YELLOW"%c"RESET,arr[i][j]);
            }
            else
            {
                printf("%c",arr[i][j]);
            }
        }
        printf("\n");
    }
    printf("Score : %d\n",*score);
}

void play(char c,int *score,char arr[30][60],int *sp,struct body* h)
{
    
    char temp=c;
    int cont=1;
    while(cont)
    {
        if(kbhit())
        {
            c=getchar();
        }
        if(c=='w' && temp!='s' )
        {
                cont=w(arr,score,sp,h);
        }
        else if(c=='s' && temp!='w')
        {
                cont=s(arr,score,sp,h);
        }
        else if(c=='a' && temp!='d')
        {
                cont=a(arr,score,sp,h);
        }
        else if(c=='d' && temp!='a')
        {
                cont=d(arr,score,sp,h);
        }

        else
        {
            if(temp=='a')
            {
                cont=a(arr,score,sp,h);
            }
            else if(temp=='d')
            {
                cont=d(arr,score,sp,h);
            }
            else if(temp=='s')
            {
                cont=s(arr,score,sp,h);
            }
            else if(temp=='w')
            {
                cont=w(arr,score,sp,h);
            }
            else
            {
                continue;
            }
        }
        if(temp=='w'||temp=='s')
        {
            usleep(600000/(*sp));
        }
        else if(temp=='a'|| temp=='d')
        {
            usleep(300000/(*sp));
        }
        system("clear");
        print(arr,score);
        if((c=='w'&&temp!='s')||(c=='a'&&temp!='d')||(c=='s'&&temp!='w')||(c=='d'&&temp!='a'))
        {
            temp=c;
        }
    }
}
void enter()
{
    system("clear");
    char arr[]="WELCOME TO THE GAME..";
    printf("\t\t\t\t");
    for(int i=0;i<strlen(arr);i++)
    {
        printf(YELLOW"%c"RESET,arr[i]);
        fflush(stdout);
        usleep(150000);
    }
    printf("\n");
    system("clear");
}
void start()
{
    printf("1. NEW GAME\n2. MAPS\n3. SPEED\n4. HIGH SCORES\n5. HELP\n6. QUIT\n");
}
void map(char arr[30][60],int *m)
{
    char ch;
    while(1)
    {
        system("clear");
        if(*m==1)
        {
            printf("1. Classic Box\n2. Compartment\n3. Apartment\n4. Back\n\ncurrent map: Classic Box\n");
        }
        else if(*m==2)
        {
            printf("1. Classic Box\n2. Compartment\n3. Apartment\n4. Back\n\ncurrent map: Compartment\n");
        }
        else if(*m==3)
        {
            printf("1. Classic Box\n2. Compartment\n3. Apartment\n4. Back\n\ncurrent map: Apartment\n");
        }
        ch=getchar();
        if(ch=='1')
        {
            draw(0,0,&arr[0][0],arr);
            *m=1;
        }
        else if(ch=='2')
        {
            compartment(arr);
            *m=2;
        }
        else if(ch=='3')
        {
            apartment(arr);
            *m=3;
        }
        else if(ch=='4')
        {
            break;
        }
    }
}
void speedchange(int *speed)
{
    char c;
    while(1)
    {
        printf("Speed: %d\nincrease: i \t decrease: d \t back : b\n",*speed);
        c=getchar();
        if(c=='i')
        {
            *speed+=1;
        }
        else if(c=='d')
        {
            *speed-=1;
        }
        else if(c=='b')
        {
            system("clear");
            break;
        }
        system("clear");
    }
    system("clear");
}
int highscore()
{
    return 0;
}
void help()
{
    printf("This game contains several maps.\n Your aim should be to collect as many fruits as possible until the game is over.\n");
    printf("1. The movements of the snake is caused by pressing  the keys w,s,a,d\n");
    printf("2. Pressing any other key will not cause any change in motion\n");
    printf("3. When the snake is  moving, you cannot change the motion of the snake directly in the opposite direction.\n  You need to moving in either of the remianing direction and then move backwards\n");
    printf("4. The snake should be moved with the  boundaries drawn.\n");
    printf("5. The game gets over when the snake either hits its own body or it hits the boundary\n");
    printf("6. To eat the fruit, move over the fruit . The length of the snake gets increased by 1 unit.\n\n");
    printf("7. To change the map, go to the maps option. There are 3 maps available");
    printf("8. To increase the speed go to speed option and increase it or decrease it ");
    printf("   ...press any key and enter to go back\n");
    char c=getchar();
}
int main()
{
    
    int m=1, speed=2, i=0;
    char t='y';
    while(t=='y')
    {
        struct body* tail=(struct body*)malloc(sizeof(struct body));
        tail->x=15;
        tail->y=30;
        tail->next=NULL;
        char arr[30][60];
        if(i==0)
        {
            enter();
        }
        start();
        char ch=getchar();
        fflush(stdin);
        if(m==1)
        {
            draw(0,0,&arr[0][0],arr);
        }
        else if(m==2)
        {
            compartment(arr);
        }
        else if(m==3)
        {
            apartment(arr);
        }
        int g1=generate(29);
        int g2=generate(59);
        arr[g1][g2]='x';
        if(g1==15 && g2==30)
        {
            arr[g1][g2]=' ';
            int g1=generate(29);
            int g2=generate(59);
            arr[g1][g2]='x';
        }
        arr[15][30]='0';
        int score=0;
        char c=' ';
        system("clear");
        if(ch=='1')
        {
            print(arr,&score);
            play(c,&score,arr,&speed,tail);
            system("clear");
            printf(YELLOW "GAME OVER... \n" RESET);
            printf(YELLOW "Your Score is : %d\n" RESET,score); 
            usleep(3000000);
            system("clear");
        }
        else if(ch=='2')
        {
            map(arr,&m);
        }
        else if(ch=='3')
        {
            speedchange(&speed);
        }
        else if(ch=='4')
        {
            highscore();
        }
        else if(ch=='5')
        {
            help();
        }
        else if(ch=='6')
        {
            break;
        }
        i++;
        system("clear");
        struct body* temp=tail;
        while(temp->next!=NULL)
        {
            struct body* t=temp;
            t=temp;
            temp=temp->next;
            free(t);
        }
        free(temp);
    }  
}