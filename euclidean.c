/**
	@file
	simplemax - a max object shell
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include <stdio.h>
#include <stdlib.h>

////////////////////////// object struct
typedef struct _euclidean_
{
	t_object					ob;			// the object itself (must be first)
    long s_numerator;
    long s_denominator;
    void *m_outlet1;

} t_euclidean_;

///////////////////////// function prototypes
//// standard set
void *euclidean_new(t_symbol *s, long argc, t_atom *argv);
void euclidean_free(t_euclidean_ *x);
void euclidean_assist(t_euclidean_ *x, void *b, long m, long a, char *s);

//void euclidean_float(t_euclidean_ *x, double f);
//////////////////////// global class pointer variable
void *euclidean_class;
void euclidean_int(t_euclidean_ *x, long n);
void euclidean_in1(t_euclidean_ *x, long n);

void ext_main(void *r)
{
	t_class *c;

	c = class_new("euclidean_", (method)euclidean_new, (method)euclidean_free, (long)sizeof(t_euclidean_),
				  0L /* leave NULL!! */, A_GIMME, 0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)euclidean_assist,			"assist",		A_CANT, 0);

    class_addmethod(c, (method)euclidean_int, "int", A_LONG, 0);
    
    class_addmethod(c, (method)euclidean_in1, "in1", A_LONG, 0 );

    
    class_register(CLASS_BOX, c); /* CLASS_NOBOX */
    
    
    euclidean_class = c;
    
	post("I am the simplemax object with a new name ;) ;)  ");
}

void euclidean_assist(t_euclidean_ *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}

void euclidean_free(t_euclidean_ *x)
{
	;
}


void *euclidean_new(t_symbol *s, long argc, t_atom *argv)
{
	t_euclidean_ *x = NULL;
	long i;
    
    
    //WHAT IS THIS IDIOM?
	if ( (x = (t_euclidean_ *)object_alloc(euclidean_class)) ) {
		object_post((t_object *)x, "a new %s object was instantiated: %p", s->s_name, x);
		object_post((t_object *)x, "it has %ld arguments", argc);

		for (i = 0; i < argc; i++) {
			if ((argv + i)->a_type == A_LONG) {
				object_post((t_object *)x, "arg %ld: long (%ld)", i, atom_getlong(argv+i));
			} else if ((argv + i)->a_type == A_FLOAT) {
				object_post((t_object *)x, "arg %ld: float (%f)", i, atom_getfloat(argv+i));
			} else if ((argv + i)->a_type == A_SYM) {
				object_post((t_object *)x, "arg %ld: symbol (%s)", i, atom_getsym(argv+i)->s_name);
			} else {
				object_error((t_object *)x, "forbidden argument");
			}
		}
           
	}
    //intin(x,2);
    intin(x,1);
   
    x->m_outlet1= intout ((t_object *) x);
   return (x);
}
// Function to return gcd of a and b
int gcd(t_euclidean_ *x, int a, int b)
{
    if (a == 0)
        return b;
    return gcd(x, b%a, a);
}
void euclidean_int(t_euclidean_ *x, long n){
    
    //set numerator to n
    x->s_numerator= n;
    
    post("just received an int in the_first inlet");
    post("the result of gcd is  %ld" , gcd(x, x->s_numerator, x->s_denominator));
    
    
    
}
void euclidean_in1(t_euclidean_ *x, long n){
    x->s_denominator= n;
    post("just received an int in the second inlet");
}



