void stlinput(char filenamet[20],GLuint file);    
   //���o3d�ɨæs�b�W�r��file��call_list��

GLint sum_of_plan(char fname[20]);                
   //�p�⥭���Ӽ�

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

      struct tre_dim_object                       //�w�q3d����
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
   //���o3d����(3�I+1���k�V�q,�C�I3��double + 1�ճ��k�V�q,�@��12��double)

set_point_and_vector *p_and_v_for_surfaces(tre_dim_object *surfaces, GLuint num);