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

         GLfloat ob_angle_x =0;
         GLfloat ob_angle_y =0;
		 GLfloat ob_angle_z =0;

		 GLfloat ob_x =0;
         GLfloat ob_y =0;
		 GLfloat ob_z =0;

		 GLdouble temp = 0;  
		 GLfloat temp2[3] = {0};
		 GLfloat temp3[3] = {0};
         GLfloat temp4[3] = {0};

		 GLint n_of_tri = sum_of_plan("opengltest.STL") ;                   //number of plans
		 GLint n_of_non_reflect_point = sum_of_plan("semi_sphere.stl");
		 GLint n_of_mirrow_plan=0;
		 
		 GLuint *arrangement_of_mirrow_points;
		 tre_dim_object *miror_left_surface={0};  
		 tre_dim_object *miror_right_surface={0};
		 tre_dim_object *total_surface=read("opengltest.STL",n_of_tri);
		 tre_dim_object *half_sphere=read("semi_sphere.stl",n_of_non_reflect_point);

		 set_point_and_vector *total_surface_points={0}; //points_for_surfaces(total_surface,n_of_tri);
         set_point_and_vector *total_halfsphere_point = {0};
         
		 
		 //total_surface_points = new set_point_and_vector[n_of_tri];
		 //set_point *mirrow_surface_points;
		 set_point *focus_to_refl={0};
		 set_point *reflect_vectors={0};
		 set_point *mirrow_normal={0};
		 set_point_and_vector *mirrow_points={0};
		 set_point *direct_light = {0};

		 bool d_light_functional = false;
		 
		 


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
		 GLdouble     focus[3] = {    30.0f,     17.0f,     25.0f};

		 


		  GLuint demo ;

       GLfloat dot(GLfloat vector1[3], GLfloat vector2[3])
	   {
		   GLfloat result = 0;
		   
		   for(int i = 0; i < 3 ;i++)
		   {
			   result = vector1[i] * vector2[i] + result;
		   }

		   return result;
	   }

	   GLfloat dotv(set_point vector3, set_point vector4)
	   {
		   GLfloat result = 0;
           result = vector3.X * vector4.X + vector3.Y * vector4.Y + vector3.Z * vector4.Z;
		   return result;
	   }
       

	   void a_minus_b(GLfloat *a, GLfloat *b, GLfloat *ab)
	   {   
		   for(int i = 0; i < 3 ;i++)
		   {
			   ab[i] = a[i] - b[i];
		   }
	   }

	   void c_minus_d(set_point c, GLdouble d[3], set_point cd)
	   {   
		   cd.X = c.X - d[0];
		   cd.Y = c.Y - d[1];
		   cd.Z = c.Z - d[2];
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
        



		 /*glBegin(GL_POINTS);
		  for(int i =0;i<n_of_tri;i++)
		  {
			  glVertex3d(mirrow_surface_points[i].X,mirrow_surface_points[i].Y,mirrow_surface_points[i].Z+30);
		  }
		 glEnd(); */
	     


		 glPushMatrix();
		 glTranslatef(ob_x,0.0f,0.0f);
	     glTranslatef(0.0f,ob_y,0.0f);
	     glTranslatef(0.0f,0.0f,ob_z);

		 


		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		 glDisable(GL_BLEND);
		 glColor3f(0.5f,0.5f,0.5f) ;
		 glCallList(demo);


		 //glColor3f(1.0f,1.0f,0.0f); 
		 for(int i = 0; i < n_of_mirrow_plan ; i++)
		 {
           //c_minus_d(mirrow_points[i].r,&focus[0],focus_to_refl[i]);// obtain vector (focus to reflect point)
			 focus_to_refl[i].X=mirrow_points[i].r.X - focus[0];
			 focus_to_refl[i].Y=mirrow_points[i].r.Y - focus[1];
			 focus_to_refl[i].Z=mirrow_points[i].r.Z - focus[2];
           temp = dotv(focus_to_refl[i],mirrow_points[i].nvector);//focus_to_refl[i].X*
           reflect_vectors[i].X = focus_to_refl[i].X - 2*temp*mirrow_points[i].nvector.X;
		   reflect_vectors[i].Y = focus_to_refl[i].Y - 2*temp*mirrow_points[i].nvector.Y;
		   reflect_vectors[i].Z = focus_to_refl[i].Z - 2*temp*mirrow_points[i].nvector.Z;

           glEnable(GL_BLEND);
		   glColor4f(1.0f,1.0f,0.0f,0.5f);
		   glLineWidth(10.0);  
		   glBegin(GL_LINES);         // drew the line which start from focus to reflectpoint
		   glVertex3d(focus[0], focus[1], focus[2]);
           glVertex3d(focus[0]+focus_to_refl[i].X, focus[1]+focus_to_refl[i].Y, focus[2]+focus_to_refl[i].Z);
		   glEnd();
           
		   glEnable(GL_BLEND);
		   glColor4f(1.0f,1.0f,0.0f,0.2f);
		   glLineWidth(6.0);  
		   glBegin(GL_LINES);
		   glVertex3d(mirrow_points[i].r.X, mirrow_points[i].r.Y, mirrow_points[i].r.Z);
           glVertex3d(mirrow_points[i].r.X+reflect_vectors[i].X, mirrow_points[i].r.Y+reflect_vectors[i].Y, mirrow_points[i].r.Z+reflect_vectors[i].Z);
           glEnd();
		 }
         if(d_light_functional == true)
		 {
		   for(i = 0; i < n_of_non_reflect_point ; i++)
		   {
			 direct_light[i].X = total_halfsphere_point[i].r.X - focus[0];
			 direct_light[i].Y = total_halfsphere_point[i].r.Y - focus[1];
			 direct_light[i].Z = total_halfsphere_point[i].r.Z - focus[2];

		     glEnable(GL_BLEND);
		     glColor4f(1.0f,1.0f,0.0f,0.1f);
		     glLineWidth(10.0);  
		     glBegin(GL_LINES);         // drew the line which start from focus to reflectpoint
		     glVertex3d(focus[0], focus[1], focus[2]);
             glVertex3d(focus[0]+1.2*direct_light[i].X, focus[1]+1.2*direct_light[i].Y, focus[2]+1.2*direct_light[i].Z);
		     glEnd();
		   }
		 }
		 /*glLineWidth(3.0f);
		 glBegin(GL_LINES);        // drew the reflect vector 90
		 glVertex3f(               point90[0][0],                 point90[0][1],               point90[0][2]);
		 glVertex3f( point90[0][0]+point90[3][0],   point90[0][1]+point90[3][1], point90[0][2]+point90[3][2]);
		 glEnd();*/

		 
		
		 /*a_minus_b(&pointzero[0][0],&focus[0],&pointzero[1][0]);  // obtain vector (focus to reflect point)
		 temp = dot(pointzero[1],pointzero[2]);

	     for(i = 0 ; i < 3; i++)
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
		 glVertex3f(focus[0], focus[1], focus[2]);
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
		 glEnd();
         
		 a_minus_b(&point45[0][0],&focus[0],&point45[1][0]);  // obtain vector (focus to reflect point)
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
		 glVertex3f(focus[0], focus[1], focus[2]);
         glVertex3f(point45[0][0], point45[0][1], point45[0][2]);//21.2932f,  19.41709f, 16.51492f
		 glEnd();

		 glColor3f(1.0f,0.5f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);        // drew the reflect vector 45
		 glVertex3f(               point45[0][0],                 point45[0][1],               point45[0][2]);
		 glVertex3f( point45[0][0]+point45[3][0],   point45[0][1]+point45[3][1], point45[0][2]+point45[3][2]);
		 glEnd();



         a_minus_b(&point90[0][0],&focus[0],&point90[1][0]);  // obtain vector (focus to reflect point)
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
		 glVertex3f(focus[0], focus[1], focus[2]);
         glVertex3f(point90[0][0], point90[0][1], point90[0][2]);//29.13765f, 24.6245f, 9.157295f
		 glEnd();

		 glColor3f(1.0f,1.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);        // drew the reflect vector 90
		 glVertex3f(               point90[0][0],                 point90[0][1],               point90[0][2]);
		 glVertex3f( point90[0][0]+point90[3][0],   point90[0][1]+point90[3][1], point90[0][2]+point90[3][2]);
		 glEnd();




         a_minus_b(&point135[0][0],&focus[0],&point135[1][0]);  // obtain vector (focus to reflect point)
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
		 glVertex3f(focus[0], focus[1], focus[2]);
         glVertex3f(point135[0][0], point135[0][1], point135[0][2]);//42.84590f, 28.08187f, 12.52092f
		 glEnd();

         
		 glColor3f(0.5f,1.0f,0.0f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the reflect vector 135
		 glVertex3f(                point135[0][0],                 point135[0][1],                point135[0][2]);
		 glVertex3f( point135[0][0]+point135[3][0],  point135[0][1]+point135[3][1], point135[0][2]+point135[3][2]);
		 glEnd();


         

		 a_minus_b(&point180[0][0],&focus[0],&point180[1][0]);  // obtain vector (focus to reflect point)
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
		 glVertex3f(focus[0], focus[1], focus[2]);
         glVertex3f(point180[0][0], point180[0][1], point180[0][2]);//49.19841f, 30.48535f, 24.48168f
		 glEnd();

         

		 glEnable(GL_BLEND);
		 glColor4f(0.0f,1.0f,0.0f,0.2f);  
		 glLineWidth(3.0f);
		 glBegin(GL_LINES);         // drew the reflect vector 180
		 glVertex3f(                point180[0][0],                  point180[0][1],                point180[0][2]);
		 glVertex3f( point180[0][0]+point180[3][0],   point180[0][1]+point180[3][1], point180[0][2]+point180[3][2]);
		 glEnd();*/

         
		
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

		if (ob_angle_y<-180.0f)
			ob_angle_y = ob_angle_y+360.0f;
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

   }

 	void asci_handler(unsigned char ascima, int l, int k)
	{		

		if(ascima == 'e')
			d_light_functional = true;

		if(ascima =='d')
			d_light_functional = false;

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
	cout<<" CTRL+ORIENT -> move   the object"<<endl;
	cout<<" ORIENT      -> evolve the object"<<endl;
	cout<<" D           -> disable direct light"<<endl;
	cout<<" E           -> enable  direct light"<<endl;
	 int j = 0;

	 total_surface_points = new set_point_and_vector[n_of_tri];
	 total_surface_points = p_and_v_for_surfaces(total_surface,n_of_tri);

	 total_halfsphere_point = new set_point_and_vector[n_of_non_reflect_point];
     total_halfsphere_point = p_and_v_for_surfaces(half_sphere, n_of_non_reflect_point);
	 direct_light = new set_point[n_of_non_reflect_point];
	 

		 for(int i =0;i<n_of_tri;i++)
		 {
			 if (total_surface_points[i].r.X>10 && total_surface_points[i].r.X<50)
			 {
				 if (total_surface_points[i].r.Y>12 && total_surface_points[i].r.Y<32)
				 {
					 if (total_surface_points[i].r.Z>5 && total_surface_points[i].r.Z<25)
					 {
						 j++;
					 }
				 }
			 }
		 }

		 n_of_mirrow_plan = j;
		 
		 arrangement_of_mirrow_points = new GLuint[n_of_mirrow_plan];
//		 mirrow_surface_points = new set_point[n_of_mirrow_plan];

		 reflect_vectors = new set_point[n_of_mirrow_plan];
		 mirrow_normal   = new set_point[n_of_mirrow_plan];
		 focus_to_refl   = new set_point[n_of_mirrow_plan];
		 mirrow_points  = new set_point_and_vector[n_of_mirrow_plan];

		 j=0;

		 for(i =0;i<n_of_tri;i++)
		 {
			 if (total_surface_points[i].r.X>10 && total_surface_points[i].r.X<50)
			 {
				 if (total_surface_points[i].r.Y>12 && total_surface_points[i].r.Y<32)
				 {
					 if (total_surface_points[i].r.Z>5 && total_surface_points[i].r.Z<25)
					 {
						 mirrow_points[j] = total_surface_points[i];
                         arrangement_of_mirrow_points[j] = i;
						 j++;
					 }
				 }
			 }
		 }

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("light simulation");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeyHandler);
	glutKeyboardFunc(asci_handler);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(500, TimerFunc, 1);
	demo = glGenLists(1);
	SetupRC();
	glutMainLoop();
	glDeleteLists(demo, 1);

   return 0;
}