void stlinput(char filenamet[20],GLuint file);    
   //取得3d檔並存在名字為file的call_list裡

GLint sum_of_plan(char fname[20]);                
   //計算平面個數

struct set_point
	  {
	    GLdouble X;
	    GLdouble Y;
	    GLdouble Z;  
	  };

      struct set_tri_surface
	  {
	    set_point plan[3];
	  };

      struct tre_dim_object                       //定義3d物件
	  {  
	   set_tri_surface obj_plan;
	   set_point nomalvector;
	  };

	  struct set_point_and_vector
	  {
		  set_point r;
		  set_point nvector;
	  };

tre_dim_object *read(char filename[20],GLint n);  
   //取得3d平面(3點+1單位法向量,每點3個double + 1組單位法向量,共有12個double)

set_point_and_vector *p_and_v_for_surfaces(tre_dim_object *surfaces, GLuint num);
