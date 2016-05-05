#include<iostream>
#include<fstream>
#include <string>
#include<windows.h>
#include<gl\glut.h>
#include<gl\gl.h>
#include<cmath>
#include "stlinput.H"
//#include "four_bar.H"
using namespace std;
   const GLfloat pi = 3.141592654;
         GLfloat time =0;
		 GLfloat time2 =0;
		 GLfloat step =0.0f;
         GLfloat ob_angle_x =0;   //the rotating angle of whole in x direction
         GLfloat ob_angle_y =0;   //the rotating angle of whole in y direction
		 GLfloat ob_angle_z =0;   //the rotating angle of whole in z direction

		 GLfloat ob_x =0;         //the moving step of the object in x direction
         GLfloat ob_y =0;         //the moving step of the object in y direction
		 GLfloat ob_z =0;         //the moving step of the object in z direction

         GLfloat light_position_step_x = 0;
		 //the moving step of the light position in x direction
		 GLfloat light_position_step_y = 0;
		 //the moving step of the light position in y direction
		 GLfloat light_position_step_z = 0;
		 //the moving step of the light position in z direction

		 GLfloat temp = 0;
		 GLfloat temp2[3] = {0};
		 GLfloat temp3[3] = {0};
         GLfloat temp4[3] = {0};



		 GLfloat pointzero[4][3] = {
			 {    21.25877f,     15.84321f,     24.74892f},   //reflect point
			 {            0,             0,             0},   //vector (focus to reflect point)
			 {    0.6574436,      0.753275,    0.01856473},   //normal vector
			 {            0,             0,             0}    //reflect vector
		 };

		 GLfloat   point45[4][3] = {
			 {     21.2932f,     19.41709f,     16.51492f},   //reflect point
			 {            0,             0,             0},   //vector (focus to reflect point)
			 {    0.5531000,     0.6357253,     0.5384551},   //normal vector
			 {            0,             0,             0}    //reflect vector
		 };
		 GLfloat   point90[4][3] = {
			 {    29.13765f,      24.6245f,     9.157295f},   //reflect point
			 {            0,             0,             0},   //vector (focus to reflect point)
			 {   0.04641142,     0.5336043,     0.8444598},   //normal vector
			 {            0,             0,             0}    //reflect vector
		 };
		 GLfloat  point135[4][3] = {
			 {     42.84590f,     28.08187f,     12.52092f},  //reflect point
			 {             0,             0,             0},  //vector (focus to reflect point)
			 {    -0.6257902,     0.4878781,     0.6085734},  //normal vector
			 {             0,             0,             0}   //reflect vector
		 };
		 GLfloat  point180[4][3] = {
			 {     49.19841f,     30.48535f,     24.48168f},  //reflect point
			 {             0,             0,             0},  //vector (focus to reflect point)
			 {    -0.8865114,     0.4620668,    0.02432694},  //normal vector
			 {             0,             0,             0}   //reflect vector
		 };

		 GLfloat   focus[3] = {30.0f, 17.0f, 25.0f};  // initial position of light
         GLfloat bulb_position[3] = { 0.0f, 0.0f,  0.0f};

          bool decision = false;		 


		  GLuint demo ;

       GLfloat dot(GLfloat vector1[3], GLfloat vector2[3])   //inner product of vector
	   {
		   GLfloat result = 0;
		   
		   for(int i = 0; i < 3 ;i++)
		   {
			   result = vector1[i] * vector2[i] + result;
		   }

		   return result;
	   }
       

	   void a_minus_b(GLfloat *a, GLfloat *b, GLfloat *ab)    //3d vector minusing
	   {   
		   for(int i = 0; i < 3 ;i++)
		   {
			   ab[i] = a[i] - b[i];
		   }
	   }
	


		 



   void RenderScene(void)
   {
   
    GLfloat gray[] = {0.75f, 0.75f, 0.75f, 1.0f};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);



	glPushMatrix();
	  
      glRotatef(ob_angle_x,1.0,0.0,0.0);     
	  glRotatef(-ob_angle_y,0.0,1.0,0.0);
	  glRotatef(ob_angle_z,0.0,0.0,1.0);
	  
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,gray);   
      
         glColor3f(1.0f,0.0f,0.0f);   //標示x軸為紅色
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(200.0f,0.0f,0.0f);
		 glEnd();

		 glColor3f(0.0f,1.0f,0.0f);  //標示y軸為綠色
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(0.0f,200.0f,0.0f);
		 glEnd();

		 glColor3f(0.0f,0.0f,1.0f);  //標示z軸為藍色
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);
		 glVertex3f(0.0f,0.0f,0.0f);
         glVertex3f(0.0f,0.0f,200.0f);
		 glEnd();
        
		 
		 glPushMatrix();
		 glTranslatef(ob_x,0.0f,0.0f);
	     glTranslatef(0.0f,ob_y,0.0f);
	     glTranslatef(0.0f,0.0f,ob_z);
         
		 //if(decision = true)
		 //{
		 bulb_position[0] = focus[0]+light_position_step_x;
         bulb_position[1] = focus[1]+light_position_step_y;
		 bulb_position[2] = focus[2]+light_position_step_z;
         
		 //decision = false;
		 //}
		 //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		 //glDisable(GL_BLEND);
		 glColor3f(0.5f,0.5f,0.5f) ;
		 glCallList(demo);

		 
		
		 a_minus_b(&pointzero[0][0],&bulb_position[0],&pointzero[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(pointzero[1],pointzero[2]);

	     for(int i = 0 ; i < 3; i++)
		 {
			 temp2[i] = 2*temp*pointzero[2][i];
		     temp4[i] = temp*pointzero[2][i];
		 }

		 a_minus_b(&pointzero[1][0],&temp4[0],&temp3[0]);

         a_minus_b(&pointzero[1][0],&temp2[0],&pointzero[3][0]);//obtain reflect vector
		
		 glEnable(GL_BLEND);
		 glColor4f(1.0f,1.0f,0.0f,0.2f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the line which start from focus to reflectpointzero
		 glVertex3f(bulb_position[0], bulb_position[1], bulb_position[2]);
         glVertex3f(pointzero[0][0], pointzero[0][1], pointzero[0][2]);//21.25877f, 15.84321f, 24.74892f  
		 glEnd();
         
		 glColor3f(1.0f,0.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the reflect vector zero
		 glVertex3f(                pointzero[0][0],                 pointzero[0][1],                 pointzero[0][2]);
		 glVertex3f(pointzero[0][0]+pointzero[3][0], pointzero[0][1]+pointzero[3][1], pointzero[0][2]+pointzero[3][2]);
		 glEnd();


		 /*glColor3f(1.0f,1.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);
		 glVertex3f(pointzero[0][0], pointzero[0][1],                 100);
		 glVertex3f(pointzero[0][0]+10*pointzero[2][0], pointzero[0][1]+10*pointzero[2][1], 100+10*pointzero[2][2]);
		 glEnd();*/
         
		 a_minus_b(&point45[0][0],&bulb_position[0],&point45[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(point45[1],point45[2]);

	     for( i = 0 ; i < 3; i++)
		 {
			 temp2[i] = 2*temp*point45[2][i];
		     temp4[i] = temp*point45[2][i];
		 }

		 a_minus_b(&point45[1][0],&temp4[0],&temp3[0]);
         a_minus_b(&point45[1][0],&temp2[0],&point45[3][0]);//obtain reflect vector

         glColor3f(1.0f,1.0f,0.0f); 
		 glBegin(GL_LINES);        // drew the line which start from focus to reflectpoint45
		 glVertex3f(bulb_position[0], bulb_position[1], bulb_position[2]);
         glVertex3f(point45[0][0], point45[0][1], point45[0][2]);//21.2932f,  19.41709f, 16.51492f
		 glEnd();

		 glColor3f(1.0f,0.5f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);        // drew the reflect vector 45
		 glVertex3f(               point45[0][0],                 point45[0][1],               point45[0][2]);
		 glVertex3f( point45[0][0]+point45[3][0],   point45[0][1]+point45[3][1], point45[0][2]+point45[3][2]);
		 glEnd();



         a_minus_b(&point90[0][0],&bulb_position[0],&point90[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(point90[1],point90[2]);

	     for(i = 0 ; i < 3; i++)
		 {
			 temp2[i] = 2*temp*point90[2][i];
		     temp4[i] = temp*point90[2][i];
		 }

		 a_minus_b(&point90[1][0],&temp4[0],&temp3[0]);
         a_minus_b(&point90[1][0],&temp2[0],&point90[3][0]);//obtain reflect vector

		 glColor3f(1.0f,1.0f,0.0f); 
		 glBegin(GL_LINES);         // drew the line which start from focus to reflectpoint90
		 glVertex3f(bulb_position[0], bulb_position[1], bulb_position[2]);
         glVertex3f(point90[0][0], point90[0][1], point90[0][2]);//29.13765f, 24.6245f, 9.157295f
		 glEnd();

		 glColor3f(1.0f,1.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);        // drew the reflect vector 90
		 glVertex3f(               point90[0][0],                 point90[0][1],               point90[0][2]);
		 glVertex3f( point90[0][0]+point90[3][0],   point90[0][1]+point90[3][1], point90[0][2]+point90[3][2]);
		 glEnd();




         a_minus_b(&point135[0][0],&bulb_position[0],&point135[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(point135[1],point135[2]);

	     for(i = 0 ; i < 3; i++)
		 {
			 temp2[i] = 2*temp*point135[2][i];
		     temp4[i] = temp*point135[2][i];
		 }

		 a_minus_b(&point135[1][0],&temp4[0],&temp3[0]);
         a_minus_b(&point135[1][0],&temp2[0],&point135[3][0]);//obtain reflect vector
         
		 
		 
		 glColor3f(1.0f,1.0f,0.0f); 
		 glBegin(GL_LINES);        // drew the line which start from focus to reflectpoint135
		 glVertex3f(bulb_position[0], bulb_position[1], bulb_position[2]);
         glVertex3f(point135[0][0], point135[0][1], point135[0][2]);//42.84590f, 28.08187f, 12.52092f
		 glEnd();

         
		 glColor3f(0.5f,1.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the reflect vector 135
		 glVertex3f(                point135[0][0],                 point135[0][1],                point135[0][2]);
		 glVertex3f( point135[0][0]+point135[3][0],  point135[0][1]+point135[3][1], point135[0][2]+point135[3][2]);
		 glEnd();


         

		 a_minus_b(&point180[0][0],&bulb_position[0],&point180[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(point180[1],point180[2]);

	     for(i = 0 ; i < 3; i++)
		 {
			 temp2[i] = 2*temp*point180[2][i];
		     temp4[i] = temp*point180[2][i];
		 }

		 a_minus_b(&point180[1][0],&temp4[0],&temp3[0]);
         a_minus_b(&point180[1][0],&temp2[0],&point180[3][0]);//obtain reflect vector

		 //glEnable(GL_BLEND);
         glColor3f(1.0f,1.0f,0.0f); 
		 glBegin(GL_LINES);        // drew the line which start from focus to reflectpoint180
		 glVertex3f(bulb_position[0], bulb_position[1], bulb_position[2]);
         glVertex3f(point180[0][0], point180[0][1], point180[0][2]);//49.19841f, 30.48535f, 24.48168f
		 glEnd();

         

		 //glEnable(GL_BLEND);
		 glColor4f(0.0f,1.0f,0.0f,0.2f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the reflect vector 180
		 glVertex3f(                point180[0][0],                  point180[0][1],                point180[0][2]);
		 glVertex3f( point180[0][0]+point180[3][0],   point180[0][1]+point180[3][1], point180[0][2]+point180[3][2]);
		 glEnd();

         
		
		 glPopMatrix();

		 


		  
	glPopMatrix();

         glutSwapBuffers();
		 glFlush();
   }


   void SetupRC(void)
   {

	GLfloat ambientLight[]={0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat diffuseLight[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specularLight[]={1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specref[]={1.0f, 1.0f, 1.0f, 1.0f};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_CCW);

	glEnable(GL_LIGHTING);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 100);

     stlinput("opengltest.STL",demo);
	
	

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   }

   void ChangeSize(GLsizei w,GLsizei h)
   { 
	GLfloat lightPos[]={0.0f, 70.0f, 100.0f, 1.0f};
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
    
    // evolving of whole start
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



    	if(key == GLUT_KEY_PAGE_UP)
	{
		ob_angle_z = ob_angle_z+10.0f;

		while(ob_angle_z>360.0f)
			ob_angle_z = ob_angle_z - 360.0f;
	}

	if(key == GLUT_KEY_PAGE_DOWN)
	{
		ob_angle_z = ob_angle_z-10.0f;

		while(ob_angle_z < 0.0f)
			ob_angle_z = ob_angle_z + 360.0f;
	}
	// evolving of whole end






    //moving of the objct start
	if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_x = ob_x-10.0f;
		ob_angle_y = ob_angle_y-10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;

	}

	if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_x = ob_x+10.0f;
		ob_angle_y = ob_angle_y+10.0f;

		if (ob_angle_y>360.0f)
			ob_angle_y = ob_angle_y-360.0f;
	}

	     

	if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_y = ob_y+10.0f;
		ob_angle_x = ob_angle_x+10.0f;

		if (ob_angle_x>360.0f)
			ob_angle_x = ob_angle_x-360.0f;
	}

	if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_y = ob_y-10.0f;
		ob_angle_x = ob_angle_x-10.0f;

		if (ob_angle_x<-180.0f)
			ob_angle_x = ob_angle_x+360.0f;
	}



	if(key == GLUT_KEY_PAGE_UP && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_z = ob_z+10.0f;
		ob_angle_z = ob_angle_z-10.0f;

		if (ob_angle_z<-180.0f)
			ob_angle_z = ob_angle_z+360.0f;
	}

	if(key == GLUT_KEY_PAGE_DOWN && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		ob_z = ob_z-10.0f;
		ob_angle_z = ob_angle_z+10.0f;

		if (ob_angle_z<-180.0f)
			ob_angle_z = ob_angle_z+360.0f;
	}
    //moving of the object end

    
	//moving of the light start
	if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_x = light_position_step_x - 5.0f;
		ob_angle_y = ob_angle_y-10.0f;

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
		decision = true;

	}

	if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_x = light_position_step_x + 5.0f;
		ob_angle_y = ob_angle_y+10.0f;

		if (ob_angle_y > 360.0f)
			ob_angle_y = ob_angle_y-360.0f;
		decision = true;

	}



	if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_y = light_position_step_y +5.0f;
		ob_angle_x = ob_angle_x+10.0f;

		if (ob_angle_x>360.0f)
			ob_angle_x = ob_angle_x-360.0f;
		decision = true;
	}

	if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_y = light_position_step_y - 5.0f;
		ob_angle_x = ob_angle_x-10.0f;

		if (ob_angle_x<-180.0f)
			ob_angle_x = ob_angle_x+360.0f;
		decision = true;
	}



	if(key == GLUT_KEY_PAGE_UP && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_z = light_position_step_z + 5.0f;
		ob_angle_z = ob_angle_z-10.0f;

		if (ob_angle_z<-180.0f)
			ob_angle_z = ob_angle_z+360.0f;
		decision = true;
	}

	if(key == GLUT_KEY_PAGE_DOWN && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		light_position_step_z = light_position_step_z - 5.0f;
		ob_angle_z = ob_angle_z+10.0f;

		if (ob_angle_z<-180.0f)
			ob_angle_z = ob_angle_z+360.0f;
		decision = true;
	}
	//moving of the light end
	

   }


   void TimerFunc(int value)
   {
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, 1);
	time = time+step;
         time2 = time2+step;
		 
		 if (time2>pi*2)
			 time2 = time2 -pi*2;

   }



int main()
{
	cout<<" ORIENT      -> evolve the object"<<endl;
	cout<<" CTRL+ORIENT -> move   the object"<<endl;
	cout<<" ALT +ORIENT -> move   the light position"<<endl;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("lighting_thread_test");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeyHandler);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(500, TimerFunc, 1);
	demo = glGenLists(1);
	SetupRC();
	glutMainLoop();
	glDeleteLists(demo, 1);

   return 0;
}