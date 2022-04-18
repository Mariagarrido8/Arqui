#include <stdio.h>
#define SIZE 20


	enum level_jedi {
	T_APPRENTICE=0, T_MASTER=1
	} ;

	
	struct points{
		  
		int hit_points;
		int attack_array[2];
		int defense_array[2];
		float speed_array[2];
		enum level_jedi level;

	};


	struct jedi{
		int id;
		char *s_full_name;
		int size_name;
		struct points *ptr_points;
		
	};

	struct lista_jedis{
        struct jedi *j;
        struct lista_jedis* next;
	}; 

	

