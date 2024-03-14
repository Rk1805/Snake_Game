#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#include<termios.h>
#include<fcntl.h>
 
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

int w(char arr[30][60],int *start_x,int *start_y,int *end_x,int *end_y,int *score)
{
    arr[*end_x][*end_y]=' ';
    if(arr[*start_x-1][*start_y]=='x')
    {
        arr[*start_x-1][*start_y]='0';
        *start_x=*start_x-1;
        *score+=5;
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }

    else if(arr[*start_x-1][*start_y]!='|' && arr[*start_x-1][*start_y]!='-' && arr[*start_x-1][*start_y]!='0')
    {
        arr[*start_x-1][*start_y]='0';
        *start_x=*start_x-1;
        if((arr[*end_x][*end_y-1]=='0'&& arr[*end_x+1][*end_y]=='0')||(arr[*end_x][*end_y+1]=='0'&&arr[*end_x+1][*end_y]=='0')) *end_x=*end_x+1;
        else if((arr[*end_x][*end_y-1]=='0'&& arr[*end_x+1][*end_y]=='0' && arr[*end_x][*end_y+1])||(arr[*end_x][*end_y+1]=='0'&&arr[*end_x+1][*end_y]=='0'));
        else if(arr[*end_x][*end_y+1]=='0') *end_y=*end_y+1;
        else if(arr[*end_x][*end_y-1]=='0') *end_y=*end_y-1;
        else if(arr[*end_x+1][*end_y]=='0') *end_x=*end_x+1;
        else *end_x=*end_x-1;
        return 1;
    }
    else            
    {
        return 0;
    }
}

int a(char arr[30][60],int *start_x,int *start_y,int *end_x,int *end_y,int *score)
{
    arr[*end_x][*end_y]=' ';
    if(arr[*start_x][*start_y-1]=='x')
    {
        arr[*start_x][*start_y-1]='0';
        *start_y=*start_y-1;
        *score+=5;
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }
    else if(arr[*start_x][*start_y-1]!='|' && arr[*start_x][*start_y-1]!='-' && arr[*start_x][*start_y-1]!='0')
    {
        arr[*start_x][*start_y-1]='0';
        *start_y=*start_y-1;
        if((arr[*end_x+1][*end_y]=='0'&& arr[*end_x][*end_y+1]=='0')||(arr[*end_x+1][*end_y]=='0'&&arr[*end_x][*end_y+1]=='0')) *end_y=*end_y+1;
        else if(arr[*end_x][*end_y+1]=='0') *end_y=*end_y+1;
        else if(arr[*end_x][*end_y-1]=='0') *end_y=*end_y-1;
        else if(arr[*end_x+1][*end_y]=='0') *end_x=*end_x+1;
        else *end_x=*end_x-1;
        return 1;
    }
    else
    {
        return 0;
    }
}

int s(char arr[30][60],int *start_x,int *start_y,int *end_x,int *end_y,int *score)
{
    arr[*end_x][*end_y]=' ';
    if(arr[*start_x+1][*start_y]=='x')
    {
        arr[*start_x+1][*start_y]='0';
        *start_x=*start_x+1;
        *score+=5;
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }
    else if(arr[*start_x+1][*start_y]!='|' && arr[*start_x+1][*start_y]!='-' && arr[*start_x+1][*start_y]!='0')
    {
        arr[*start_x+1][*start_y]='0';
        *start_x=*start_x+1;
        if((arr[*end_x][*end_y-1]=='0'&& arr[*end_x-1][*end_y]=='0')||(arr[*end_x][*end_y+1]=='0'&&arr[*end_x-1][*end_y]=='0')) *end_x=*end_x-1;
        else if(arr[*end_x][*end_y+1]=='0') *end_y=*end_y+1;
        else if(arr[*end_x][*end_y-1]=='0') *end_y=*end_y-1;
        else if(arr[*end_x+1][*end_y]=='0') *end_x=*end_x+1;
        else *end_x=*end_x-1;
        return 1;
    }
    else
    {
        return 0;
    }
}

int d(char arr[30][60],int *start_x,int *start_y,int *end_x,int *end_y,int *score)
{
    arr[*end_x][*end_y]=' ';
    if(arr[*start_x][*start_y+1]=='x')
    {
        arr[*start_x][*start_y+1]='0';
        *start_y=*start_y+1;
        *score+=5;
        int g1=generate(29);
        int g2=generate(59);
        while(arr[g1][g2]=='0')
        {
            g1=generate(29);
            g2=generate(59);
        }
        arr[g1][g2]='x';
        return 1;
    }
    else if(arr[*start_x][*start_y+1]!='|' && arr[*start_x-1][*start_y+1]!='-' && arr[*start_x][*start_y+1]!='0')
    {
        arr[*start_x][*start_y+1]='0';
        *start_y=*start_y+1;
        if((arr[*end_x][*end_y-1]=='0'&& arr[*end_x+1][*end_y]=='0')||(arr[*end_x][*end_y-1]=='0'&&arr[*end_x-1][*end_y]=='0')) *end_y=*end_y-1;
        else if(arr[*end_x][*end_y+1]=='0') *end_y=*end_y+1;
        else if(arr[*end_x][*end_y-1]=='0') *end_y=*end_y-1;
        else if(arr[*end_x+1][*end_y]=='0') *end_x=*end_x+1;
        else *end_x=*end_x-1;
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
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
    printf("Score : %d\n",*score);
}

void play(char c,int *start_x,int *start_y,int *end_x,int *end_y,int *score,char arr[30][60])
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
                cont=w(arr, start_x,start_y,end_x,end_y,score);
        }
        else if(c=='s' && temp!='w')
        {
                cont=s(arr, start_x,start_y,end_x,end_y,score);
        }
        else if(c=='a' && temp!='d')
        {
                cont=a(arr, start_x,start_y,end_x,end_y,score);
        }
        else if(c=='d' && temp!='a')
        {
                cont=d(arr, start_x,start_y,end_x,end_y,score);
        }

        else
        {
            if(temp=='a')
            {
                cont=a(arr, start_x,start_y,end_x,end_y,score);
            }
            else if(temp=='d')
            {
                cont=d(arr, start_x,start_y,end_x,end_y,score);
            }
            else if(temp=='s')
            {
                cont=s(arr, start_x,start_y,end_x,end_y,score);
            }
            else if(temp=='w')
            {
                cont=w(arr, start_x,start_y,end_x,end_y,score);
            }
            else
            {
                continue;
            }
        }
        if(temp=='w'||temp=='s')
        {
            usleep(300000);
        }
        else if(temp=='a'|| temp=='d')
        {
            usleep(150000);
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
    char arr[]="WELCOME TO THE GAME..";
    for(int i=0;i<strlen(arr);i++)
    {
        printf(YELLOW"%c"RESET,arr[i]);
        fflush(stdout);
        usleep(300000);
    }
}
int main()
{
    char t='y';
    while(t=='y')
    {
        char arr[30][60];
        enter();
        draw(0,0,&arr[0][0],arr);
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
        print(arr,&score);
        int start_x=15;
        int start_y=30;
        int end_x=15;
        int end_y=30;
        char c=' ';
        play(c,&start_x,&start_y,&end_x,&end_y, &score,arr);
        system("clear");
        printf(YELLOW "GAME OVER... \n" RESET);
        printf(YELLOW "Your Score is : %d\n\n" RESET,score); 
        printf(GREEN "To play again press  y\n"RESET);
        printf(RED "To quit press n\n"RESET);
        char te=getchar();
        t=te;
        if(te=='n')
        {
            break;
        }
        system("clear");
    }  
}