#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<string.h>

GLsizei wh=500,ww=500;
int flag=0;

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
int allowed[25][25];

char quote[8][8];

int ax[25]= {0,8,16,24,32,0,8,16,24,32,0,8,16,24,32,0,8,16,24,32,0,8,16,24,32};
int ay[25]= {0,0,0,0,0,8,8,8,8,8,16,16,16,16,16,24,24,24,24,24,32,32,32,32,32};


void border()
{

    for(int i=0; i<25; i++)
    {
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(ax[i],ay[i]);
        glVertex2i(ax[i]+8,ay[i]);
        glVertex2i(ax[i]+8,ay[i]+8);
        glVertex2i(ax[i],ay[i]+8);
        glEnd();
    }
    glFlush();
}

int findblock(int x, int y)
{
    x=(x/10)-4;
    y=45-(y/10);
    printf(" x= %d , y=%d \n",x,y);
    for(int i=0; i<25; i++)
    {
        if(((x-ax[i]) < 8) && ((y-ay[i])< 8))
            return i;
    }
}

void hideblock(int cur)
{

    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2d(ax[cur],ay[cur]);
    glVertex2d(ax[cur]+8,ay[cur]);
    glVertex2d(ax[cur]+8,ay[cur]+8);
    glVertex2d(ax[cur],ay[cur]+8);
    glEnd();
    border();
}

void displayblock(int i)
{
    border();

    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2d(ax[i],ay[i]);
    glVertex2d(ax[i]+8,ay[i]);
    glVertex2d(ax[i]+8,ay[i]+8);
    glVertex2d(ax[i],ay[i]+8);
    glEnd();
    
    glFlush();
    border();
}

int score=25;
int cur;
int count=0;
void myMouse(int b,int s,int x,int y)
{
    int j;
    if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN)
    {
        if(count==0)
        {
            cur=findblock(x,y);
            displayblock(cur);
            hideblock(cur);
            score-=1;
            printf("%d\n",score);
            count=-1;
            for(int m=0; m<25; m++)
                allowed[m][cur]=-1;
        }
        else
        {
            int	i=findblock(x,y);
            printf("findblock return %d\n",i);
            if (allowed[cur][i]==-1)
                glutIdleFunc(NULL);
            else
            {
                if(allowed[cur][i]==1)
                {
                    score-=1;
                    printf("%d\n",score);
                    printf("allowed[%d][%d]\n",cur,i);
                    printf("findblock return %d\n",i);
                    displayblock(i);
                }
                hideblock(cur);
                allowed[cur][i]=-1;
                cur=i;
                for(int m=0; m<25; m++)
                    allowed[m][cur]=-1;
            }
        }
    }
    glFlush();
}


void resizeHandler( int w, int h )
{

    if( h==0 ) h=1;
    float aspecRatio = (float)w / (float)h;
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(30.0, aspecRatio, 3.0, 8888.0 );
    gluLookAt( 0.0, 0.0, 100.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0 );
    return;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(-20.0,-20.0,10.0);
    for(int i=0; i<25; i++)
    {
        for(int j=0; j<25; j++)
        {
            if(((i+j)%2)==0)
                glColor3f(1.0,1.0,1.0);
            else glColor3f(0.0,0.0,0.0);
            glBegin(GL_POLYGON);
            glVertex2i(ax[i],ay[i]);
            glVertex2i(ax[i]+8,ay[i]);
            glVertex2i(ax[i]+8,ay[i]+8);
            glVertex2i(ax[i],ay[i]+8);
            glEnd();
        }
    }
    border();
    glFlush();
}

void a()
{
    for(int a=0; a<=24; a++)
        for(int b=0; b<=24; b++)
            allowed[a][b]=-1;
    allowed[0][7]=1;
    allowed[0][11]=1;
    allowed[1][8]=1;
    allowed[1][10]=1;
    allowed[1][12]=1;
    allowed[2][5]=1;
    allowed[2][9]=1;
    allowed[2][11]=1;
    allowed[2][13]=1;
    allowed[3][6]=1;
    allowed[3][12]=1;
    allowed[3][14]=1;
    allowed[4][7]=1;
    allowed[4][13]=1;
    allowed[5][2]=1;
    allowed[5][12]=1;
    allowed[5][16]=1;
    allowed[6][3]=1;
    allowed[6][13]=1;
    allowed[6][15]=1;
    allowed[6][17]=1;
    allowed[7][0]=1;
    allowed[7][4]=1;
    allowed[7][10]=1;
    allowed[7][14]=1;
    allowed[7][16]=1;
    allowed[7][18]=1;
    allowed[8][1]=1;
    allowed[8][11]=1;
    allowed[8][17]=1;
    allowed[8][19]=1;
    allowed[9][12]=1;
    allowed[9][18]=1;
    allowed[10][1]=1;
    allowed[10][7]=1;
    allowed[10][17]=1;
    allowed[10][21]=1;
    allowed[11][0]=1;
    allowed[11][2]=1;
    allowed[11][8]=1;
    allowed[11][18]=1;
    allowed[11][20]=1;
    allowed[11][22]=1;
    allowed[12][1]=1;
    allowed[12][3]=1;
    allowed[12][5]=1;
    allowed[12][9]=1;
    allowed[12][15]=1;
    allowed[12][19]=1;
    allowed[12][21]=1;
    allowed[12][23]=1;
    allowed[13][2]=1;
    allowed[13][4]=1;
    allowed[13][6]=1;
    allowed[13][16]=1;
    allowed[13][22]=1;
    allowed[13][24]=1;
    allowed[14][3]=1;
    allowed[14][7]=1;
    allowed[14][17]=1;
    allowed[14][23]=1;
    allowed[15][6]=1;
    allowed[15][12]=1;
    allowed[15][22]=1;
    allowed[16][5]=1;
    allowed[16][7]=1;
    allowed[16][13]=1;
    allowed[16][23]=1;
    allowed[17][6]=1;
    allowed[17][8]=1;
    allowed[17][10]=1;
    allowed[17][14]=1;
    allowed[17][20]=1;
    allowed[17][24]=1;
    allowed[18][7]=1;
    allowed[18][9]=1;
    allowed[18][11]=1;
    allowed[18][21]=1;
    allowed[19][8]=1;
    allowed[19][12]=1;
    allowed[19][22]=1;
    allowed[20][11]=1;
    allowed[20][17]=1;
    allowed[21][10]=1;
    allowed[21][12]=1;
    allowed[21][18]=1;
    allowed[22][11]=1;
    allowed[22][13]=1;
    allowed[22][15]=1;
    allowed[22][19]=1;
    allowed[23][12]=1;
    allowed[23][14]=1;
    allowed[23][16]=1;
    allowed[24][13]=1;
    allowed[24][17]=1;

}

void myinit()
{
    glViewport(0,0,ww,wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 20.0, 0.0, 20.0);
    glClearColor (0.5,0.2,0.3,0.8);
    glColor3f(0.0,0.0,0.0);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Knight Move");
    glutDisplayFunc(display);
    glutReshapeFunc(resizeHandler);
    glutMouseFunc(myMouse);
    myinit();
    a();
    glutMainLoop();
}
