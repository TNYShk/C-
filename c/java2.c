#include <stdlib.h>  /* NULL */
#include <stdio.h>
#include <string.h>

typedef struct cat cat_t;
typedef struct dog dog_t;
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

struct dog
{
    animal_t animal;
    int num_legs;
};

struct cat
{
    animal_t animal;
    int num_masters;
    char *color;
};


static int AnimalCounter = 0;
int AnimalStaticFlag_g = 0;
char holder[BUFSIZ] = {0};

static void ObjectHashCode(void *object);
static char *ObjectToString(void *object);
static void ObjectFinalize(void *object);
static char *AnimalToString(void *object);
void AnimalSayHello(void *this);
void AnimalShowCounter(void *this);
void AnimalctorInt(animal_t *this, int num_masters);

vf_t object_vt[] = {(vf_t)&ObjectToString,(vf_t)&ObjectHashCode, (vf_t)&ObjectFinalize };   /* function pointer, &ObjectHashCode and so ...,*/
vf_t animal_vt[] = {&AnimalSayHello, &AnimalShowCounter, (vf_t)&AnimalToString/* (vf_t)&AnimalToString,(vf_t)&AnimalHashCode, (vf_t)&AnimalFinalize */};   /* function pointer, &ObjectHashCode and so ... (Vt_t)&foo  */


class_t object_metadata = {"Object", sizeof(object_t), NULL, &object_vt};
class_t animal_metadata = {"Animal", sizeof(animal_t), &object_metadata, &animal_vt};
class_t dog_metadata =    {"Dog", sizeof(dog_t), &animal_metadata, &animal_vt};
class_t cat_metadata =    {"Cat", sizeof(cat_t), &animal_metadata, &animal_vt};

static void AnimalStaticBlocks()
{
    printf("Static block Animal 1\n");
    printf("Static block Animal 2\n");
}

static void DogStaticBlocks()
{
    printf("Static block Dog\n");
}

static void CatStaticBlock()
{
    printf("Static block Cat\n");
}

void AnimalInstanceBlock(void *object)
{
    char nameInstance[100] = {0};
    memset(nameInstance,0,100);
    strcpy(nameInstance,((char *)object));

    printf("Instance initialization block %s\n",nameInstance );
}

static void ObjectHashCode(void *object)
{
    (void)object;
    printf("ObjectHashCode");
}

static void ObjectFinalize(void *object)
{
    free(object);
}

static char *ObjectToString(void *object)
{
    char adrs[100] = {0};
    char *toString = NULL;

    memset(holder,0,BUFSIZ);
    strcpy(holder,((object_t*)object)->meta->name);
    
    sprintf(adrs, "@%p",(object_t *)object);
    strcat(holder,adrs);
     
    toString = holder;
  
    return toString;
}

static char *AnimalToString(void *object)
{
    char adrs[100] = {0};
    char *toString = NULL;
    memset(holder,0,BUFSIZ);

    strcpy(holder,((object_t*)object)->meta->name);
    
    sprintf(adrs , " with ID: %d",((animal_t *)object)->ID);
    strcat(holder,adrs);
     
    toString = holder;
  
    return toString;
}

static int flag_animal = 1;
void Animalctor(animal_t *this, int num_legs, int num_masters)
{
    if(flag_animal)
    {
        AnimalStaticBlocks();
        flag_animal = 0;
    }
   
    this->ID = ++AnimalCounter;
    this->num_legs = num_legs;
    this->num_masters = num_masters;

    if (strcmp("Cat", this->object.meta->name)!= 0)
    {
         AnimalInstanceBlock(this->object.meta->name);
    }
   
    printf("Animal Ctor\n");
    animal_vt[0](this);
    animal_vt[1](this);

    printf("%s\n", ((vfchar_t (*))animal_vt)[2](this));
    printf("%s\n", ((vfchar_t (*))object_vt)[0](this));
}

void Dogctor(dog_t *this, int num_legs, int num_masters)
{
    DogStaticBlocks();
    AnimalInstanceBlock(this->animal.object.meta->parent->name);
    AnimalctorInt(&this->animal,2);
    
    this->num_legs = num_legs;
    printf("Dog Ctor\n");
}

void Catctor(cat_t *this, int num_masters)
{
    CatStaticBlock();
    AnimalInstanceBlock(this->animal.object.meta->parent->name);
    Animalctor(&this->animal,5,2);

    this->color = "black";
  
     printf("Cat Ctor ");
    printf("with color %s\n",this->color );
     printf("Cat Ctor\n");
   
}


void AnimalctorInt(animal_t *this, int num_masters)
{
    printf("Animal Ctor int\n");
    this->ID = ++AnimalCounter;
   
    this->num_masters = num_masters;
    AnimalInstanceBlock(this->object.meta->name); 
}


void AnimalSayHello(void *this)
{
    char AnyName[10] = {0};
    memset(AnyName,0,10);

    strcpy(AnyName, ((animal_t*)this)->object.meta->parent->name);
    printf("%s ", AnyName);
    printf("Hello!\n");
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



int main(void)
{
    animal_t *any = (animal_t *)ObjectCreate(&animal_metadata);
    dog_t *dogy = NULL;
    cat_t *katy = NULL;
    Animalctor(any,5,1); 
    /*
    printf("%s\n", ((vfchar_t (*))animal_vt)[2](any));
    printf("%s\n", ((vfchar_t (*))object_vt)[0](any));
*/
    ((object_vt)[2](any));
   

    dogy = (dog_t *)ObjectCreate(&dog_metadata);
    
    Dogctor(dogy,4,2);
    ((object_vt)[2](dogy));

     katy = (cat_t *)ObjectCreate(&cat_metadata);
    Catctor(katy,2);

     
     return 0;
}
   