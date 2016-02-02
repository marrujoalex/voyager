#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<vector>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include <SDL/SDL.h>

using namespace std;


GLint x; GLint y; GLint d; GLint q; GLint a;
GLint red=0.0;
GLint blue=0.0;
GLint green=0.0;
GLint colora=1.0;
GLint colorb=1.0;
GLint colorc=1.0;

class Player 
{
public: 
	//Player
	Player();
	void draw();
	void moveLeft();
	void moveRight();
	void setPlayerPosition();
	//Shot
	void shoot();
	void drawShots( float dt );
	GLfloat getShotOrigin();
	GLint getContainerSize();
	GLfloat getShotLocationX( int i );
	GLfloat getShotLocationY( int i );
private:
	//Player
	GLfloat shiftX;
	GLfloat playervdata[3][2];
	//Shot
	vector <Shot> shotContainer; 
	GLfloat xOrigin;
	GLfloat yOrigin;
};

class Shot
{
public:
	Shot( GLfloat x, GLfloat y ); 
	void draw();
	void update( float dt );
	GLfloat getShotX();
	GLfloat getShotY();
private:
	GLfloat shotX;	
	GLfloat shotY;
	GLfloat shotLength;	
	GLfloat shotSpeed;
};
Shot::Shot( GLfloat x, GLfloat y )
{
	shotX = x;
	shotY = y;
    shotLength = 25;
	shotSpeed = 0.01;	
}

void Shot::draw()
{
	glLineWidth( 2 );
	//glColor3f( 0.0, 0.0, 1.0);
	glBegin( GL_LINES );
		glVertex2f( shotX, shotY );				//beginning
		glVertex2f( shotX, shotY-shotLength );  //end
	glEnd();
}

void Shot::update( float dt )
{
	shotY += shotSpeed * dt; 
}

GLfloat Shot::getShotX()
{
	return( shotX );
}

GLfloat Shot::getShotY()
{
	return( shotY );
}
Player::Player()
{
}

void Player::setPlayerPosition()
{
    shiftX = 0;
	GLfloat playerX[] = {225, 250, 275};
	GLfloat playerY[] = {25, 50, 25};
	for( int i=0; i<3; i++ )
	{
		playervdata[i][0] = playerX[i];
		playervdata[i][1] = playerY[i];
	} 
}

void Player::draw()
{
  glPushMatrix();
  glColor3f( 0.0, 0.0, 0.0 );		
  glTranslatef( shiftX, 0.0, 0.0 );  //translate by shiftX
  glBegin( GL_POLYGON );  
  for ( int i=0; i<3; i++ ) 
  {
    glVertex2f( playervdata[i][0], playervdata[i][1] );   
  }
  glEnd();
  glPopMatrix();
}

void Player::moveLeft()
{
	shiftX-=20;
	glutPostRedisplay();
}

void Player::moveRight()
{
    shiftX+=20;
	glutPostRedisplay();
}

void Player::shoot()
{
	getShotOrigin();
	Shot myShot( xOrigin,yOrigin );
	shotContainer.push_back( myShot );
}

GLfloat Player::getShotOrigin()
{
	xOrigin = ( playervdata[1][0] + shiftX );
	yOrigin = playervdata[1][1];
	return ( xOrigin, yOrigin );
}

void Player::drawShots( float dt )
{
	for( unsigned int i=0; i<shotContainer.size(); i++ )
	{
		shotContainer[i].update( dt );
		shotContainer[i].draw();
	}
}

GLint Player::getContainerSize()
{
	return shotContainer.size();
}

GLfloat Player::getShotLocationX( int i )
{
	return ( shotContainer[i].getShotX() );
}

GLfloat Player::getShotLocationY( int i )
{
	return ( shotContainer[i].getShotY() );
}



void blowup();
void missile();

void ship(void) {
    glColor3f(colora,colorb,colorc);
    glBegin(GL_LINE_LOOP);   
        glVertex2i(x,y);
        glVertex2i(x+0.5*d, y);
        glVertex2i(x+0.5*d, y+0.5*d);
        glVertex2i(x-0.5*d, y+0.5*d);
        glVertex2i(x-0.5*d, y);
    glEnd();
	
    glBegin(GL_POLYGON);
        glVertex2i(x,y);
        glVertex2i(x+0.45*d, y);
        glVertex2i(x+0.45*d, y+0.45*d);
        glVertex2i(x-0.45*d, y+0.45*d);
        glVertex2i(x-0.45*d, y);
    glEnd();

    glBegin(GL_LINES); 
	glVertex2i(x-d, y);
    	glVertex2i(x, y+d);
	glVertex2i(x+d,y);
	glVertex2i(x,y+d);   
    glEnd();

}

void missile(void)
{   
	glPushMatrix();
        glColor3f(1,1,1);
        glBegin(GL_POLYGON);
          glVertex2i(a-2,q);
          glVertex2i(a-2,q+11);
          glVertex2i(a+2,q+11);
          glVertex2i(a+2,q);
        glEnd();
        glBegin(GL_POLYGON);
	glColor3f(red,green,blue);
          glVertex2i(a-3,q+11); 
          glVertex2i(a,  q+15);
          glVertex2i(a+3,q+11);
        glEnd();
        glColor3f(0.7,0.7,0.7);
        glBegin(GL_LINES);
          glVertex2i(a-3,q);
          glVertex2i(a-5,q-2.5);
        glEnd();
        glBegin(GL_LINES);
          glVertex2i(a+3,q);
          glVertex2i(a+5,q-2.5);
        glEnd();
	glPopMatrix();
}

void stars(void) {
    int random_number = rand()%630+1, random_number2 = rand()%470+1;
    int random_number3 = rand()%830+1, random_number4 = rand()%570+1;  
	int random_number5 = rand()%130+1, random_number6 = rand()%270+1;
	int random_number7 = rand()%330+1, random_number8 = rand()%970+1;
   
    glColor3f(0.8,0.8,0.8);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
          glVertex2i(random_number, random_number2);
          srand(time(NULL));
          random_number = rand()%630+1, random_number2 = rand()%470+1;
          glVertex2i(random_number, random_number2);
    }
    glEnd();
	glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
          glVertex2i(random_number3, random_number4);
          srand(time(NULL));
        random_number3 = rand()%830+1, random_number4 = rand()%570+1;  
          glVertex2i(random_number3, random_number4);
    }
    glEnd();
	glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
          glVertex2i(random_number5, random_number6);
          srand(time(NULL));
        random_number5 = rand()%130+1, random_number6 = rand()%270+1;  
          glVertex2i(random_number5, random_number6);
    }
    glEnd();

	glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
          glVertex2i(random_number7, random_number8);
          srand(time(NULL));
        random_number7 = rand()%330+1, random_number8 = rand()%970+1;  
          glVertex2i(random_number7, random_number8);
    }
    glEnd();
}

/*void enemies(void) {

    glColor3f(1,0,1);
    vector<Enemy> enemy[10];
    for (int i=0; i<11; i++) {
        enemy[i] = new Enemy enemy();
    }

void Enemy::enemy() {
    for (int i(0); i<11; i++) {
        glBegin(GL_POLYGON);
            glVertex2f(x+20, 400);
            glVertex2f(x+30, 400);
            glVertex2f(x+25, 420);
        glEnd();
    }
}
*/

void menu(void) {
    cout << endl << "Welcome to our attempt at a reincarnation of a space shooter!" << endl;
    cout << "=============================================================" << endl;
    cout << "Controls are as follows: " << endl;
    cout << "  A and D for Left/Right movementof the ship" << endl;
    cout << "  Left Arrow/Right Arrow also for Left/Right" << endl;
    cout << "  Space Bar to shoot a missile" << endl;
    cout << "  s to turn on shield, shift+S to turn off shield" << endl;
    cout << "  shift+E or ESC to quit " << endl;
    cout << "=============================================================" << endl;
    cout << "  Avoid the rolling spheres at all costs! " << endl;
    cout << "      They will come in randomly!" << endl;
    cout << "  Please enjoy our very small iteration of the space shooter!" << endl;
}

void display(void) { 
  glClear(GL_COLOR_BUFFER_BIT);
  ship();
  stars();
  missile();	
  //enemies();
 // enemy();
  glFlush();
}

void init(void) 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void incoming(void) {
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(20, 600, 0);    //Supposed to roll towards the ship
    glutSolidSphere(6, 10, 10);  //Might need help on this idea, just placing it here
    glRotatef(0.0,-30.0,0.0,1);  //Can possibly set an HP value to the ship, then if 
    glPopMatrix();               //say any spot on the sphere touches any spot on the ship (x,y,d)etc.,
                                 //then HP = 0 and ship disappears? Just a quick thought.
}

void processNormalKeys (unsigned char key, int mx, int my) {
 switch (key) {
        case 32:
		missile();
		red=1.0;
		a=x;
		for(int i=0;i<10;i++)
		{
			q=q+i;
			if(q>500)
			{
				q=30;
			}
			if(q<31)
			{
				red=0.0;
	 		}
		}
		glutPostRedisplay();
	        break;
        case 's':
		colora=0.0;
		colorb=0.0;
		glutPostRedisplay();
		break;
        case 'S':
            	colora=1.0;
	    	colorb=1.0;
            	glutPostRedisplay();
            	break;
        case 'a':
        case 'A':
            x = (x-10);
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            x = (x+10);
            glutPostRedisplay();
            break;
        case 27:
        case 'E':
            exit(-1);
            break;
        case 'm':
        case 'M':
            missile();
            glutPostRedisplay();
            break;
        case 'f':
        case 'F':
            glutPostRedisplay();
            break;
        case 'y':
        case 'Y':
            blowup();
            glutPostRedisplay();
            break;
    default: 
        break;  
	}
}

void processSpecialKeys (int key, int mx, int my) {
    switch(key) {
    case GLUT_KEY_LEFT:
        x = (x-10);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        x = (x+10);
        glutPostRedisplay();
        break;
    default: 
        break;
    }
}

void processMouseKeys(int button, int state, int x, int y) {
   switch(button) {
      case GLUT_LEFT_BUTTON:
         missile();
         glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         glutPostRedisplay();
         break;
      case GLUT_MIDDLE_BUTTON:
         blowup();
         glutPostRedisplay();
         break;
      default:
         break;
      }
}

void blowup(void) {  // idea
    glColor3f(0,0,0);
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    menu();
    srand(time(NULL));
    stars();
    a = x;
    x = 350;
    y = 10;
    d = 35;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (640, 480); 
   glutInitWindowPosition (200, 100);
   glutCreateWindow ("Voyager");
   glutDisplayFunc(display); 
   glutKeyboardFunc(processNormalKeys);
   glutSpecialFunc(processSpecialKeys);
   glutMouseFunc(processMouseKeys);
   glutPostRedisplay();
   init();
   glutMainLoop();
   return 0;
}
