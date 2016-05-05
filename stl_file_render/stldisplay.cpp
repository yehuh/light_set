#include<iostream>
#include<fstream>
#include <string>
#include<windows.h>
#include<gl\glut.h>
#include<gl\gl.h>
#include "stlinput.H"
using namespace std;
 GLfloat ob_angle_x =0.0f;
   GLfloat ob_angle_y =0.0f;
   GLfloat angle=0.0f;
   GLuint demo ;
   GLuint demo2 ;
   GLuint npart;
   char filename[20];


void RenderScene(void)
{
   
   GLfloat gray[] = {0.75f, 0.75f, 0.75f, 1.0f};

   

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);



	glPushMatrix();
	  
      glRotatef(ob_angle_x,1.0,0.0,0.0);     
	  glRotatef(-ob_angle_y,0.0,1.0,0.0);
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,gray);   

         glColor3f(1.0f,0.0f,0.0f);   //標示x軸為紅色
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(200.0f,0.0f,0.0f);
		 glEnd();

		 glColor3f(0.0f,1.0f,0.0f);  //標示y軸為綠色
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(0.0f,200.0f,0.0f);
		 glEnd();

		 glColor3f(0.0f,0.0f,1.0f);  //標示z軸為藍色
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(0.0f,0.0f,200.0f);
		 glEnd();


         glColor3f(1.0f,0.0f,0.0f);
		 
		 glCallList(demo);
		 glColor3f(1.0f,1.0f,0.0f);
		 glCallList(demo2);
		 
         glPopMatrix();

         glutSwapBuffers();

}


void SetupRC(void)
{

	GLfloat ambientLight[]={0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[]={0.7f, 0.7f, 0.7f, 1.0f};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_CCW);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    stlinput(filename,demo);
	//stlinput("democylinder.stl",demo2);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}


void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat lightPos[]={0.0f,0.0f,400.0f,1.0f};
	if(h==0)
		h=1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if(w<=h)
       glOrtho(-200.0f*w/h,200.0f*w/h, -200.0f, 200.f, -200.0f, 200.0f); //顯示範圍
	else
	   glOrtho(-200.0f,200.0f, -200.0f*h/w, 200.f*h/w, -200.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

}


void SpecialKeyHandler(int key, int x, int y)
{  


	if(key == GLUT_KEY_LEFT)
	{
		ob_angle_y = ob_angle_y+10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
	}

	if(key == GLUT_KEY_RIGHT)
	{
		ob_angle_y = ob_angle_y-10.0f;

		if (ob_angle_y>360.0f)
			ob_angle_y = ob_angle_y-360.0f;
	}
	     

	if(key == GLUT_KEY_UP)
	{
		ob_angle_x = ob_angle_x-10.0f;

		if (ob_angle_x>360.0f)
			ob_angle_x = ob_angle_x-360.0f;
	}

	if(key == GLUT_KEY_DOWN)
	{
		ob_angle_x = ob_angle_x+10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
	}
}


void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1, TimerFunc, 1);
}


int main()
{
	cout<<"input the file name of the stl file(XXX.stl asci only)"<<endl;
	cin >> filename ;
    cout<<endl;
	cout<<filename;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("STL_FILE_DISPLAY");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeyHandler);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(500, TimerFunc, 1);
	demo = glGenLists(1);
	//demo2= glGenLists(1);
	SetupRC();
	glutMainLoop();
	glDeleteLists(demo, 1);
	//glDeleteLists(demo2, 1);
    
   return 0;
}