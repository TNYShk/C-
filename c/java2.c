#include <stdlib.h>  /* NULL */
#include <stdio.h>
#include <string.h>

typedef struct animal animal_t;
typedef struct object object_t;
typedef struct class class_t;
typedef void (*vf_t)(void *); 

typedef char * (*vfchar_t)(void *);

struct class 
{
    char *name;
    size_t class_size;
    class_t* parent;
    vf_t (*vtable)[];
};

struct object
{
    class_t *meta;
};

struct animal
{
    object_t object;   
    int num_legs;
    int num_masters;
    int ID;

};
static int AnimalCounter = 0;
int AnimalStaticFlag_g = 0;

static void ObjectHashCode(void *object);
static char *ObjectToString(void *object);
static void ObjectFinalize(void *object);

void AnimalSayHello(void *this);
void AnimalShowCounter(void *this);
/*
struct B
{
    animal_t object;
    int b;
};*/

vf_t object_vt[] = {(vf_t)&ObjectToString,(vf_t)&ObjectHashCode, (vf_t)&ObjectFinalize };   /* function pointer, &ObjectHashCode and so ...,*/
vf_t animal_vt[] = {&AnimalSayHello, &AnimalShowCounter/* (vf_t)&AnimalToString,(vf_t)&AnimalHashCode, (vf_t)&AnimalFinalize */};   /* function pointer, &ObjectHashCode and so ... (Vt_t)&foo  */


class_t object_metadata = {"Object", sizeof(object_t), NULL, &object_vt};
class_t animal_metadata = {"Animal", sizeof(animal_t), &object_metadata, &animal_vt};



static void AnimalStaticBlocks()
{
    printf("Static block Animal 1\n");
    printf("Static block Animal 2\n");
   
}

void AnimalInstanceBlock()
{
    printf("Instance initialization block Animal\n");
}

static void ObjectHashCode(void *object)
{
    (void)object;
    printf("ObjectHashCode");
}

static void ObjectFinalize(void *object)
{
    class_t *freer = ((object_t*)object)->meta;
    free(freer);


}

static char *ObjectToString(void *object)
{
    char holder[BUFSIZ] = {0};
    char *toString;
    size_t stringname = strlen(((object_t*)object)->meta->name);
    memcpy(holder,((object_t*)object)->meta->name,stringname +1);
    
    sprintf(holder +stringname, "@%p",(object_t *)object);

     
    toString = holder;
  
    return toString;
}

void Animalctor(animal_t *this, int num_legs, int num_masters)
{
    AnimalStaticBlocks();
    this->ID = ++AnimalCounter;
    this->num_legs = num_legs;
    this->num_masters = num_masters;
    AnimalInstanceBlock();
    printf("Animal Ctor\n");
    animal_vt[0](this);
    animal_vt[1](this);



}

void AnimalSayHello(void *this)
{
    printf("Animal Hello!\n");
     printf("I Have %d legs\n",((animal_t*)this)->num_legs);
}

void AnimalShowCounter(void *this)
{
    printf("counter %d\n", AnimalCounter);
}


object_t *ObjectCreate(class_t *meta)
{
    object_t *obj = (object_t *)calloc(meta->class_size, sizeof(size_t));
    if (NULL == obj)
    {
        return NULL;
    }

    obj->meta = meta;
    return obj;
}



int main()
{
    animal_t* any = (animal_t *)ObjectCreate(&animal_metadata);
    Animalctor(any,5,1); 
   
    printf("to string %s\n", ((vfchar_t (*))object_vt)[0](any));

     
     return 0;
}
   