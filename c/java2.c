#include <stdlib.h>  /* NULL */
#include <stdio.h>
#include <string.h>

typedef struct la la_t;
typedef struct cat cat_t;
typedef struct dog dog_t;
typedef struct animal animal_t;
typedef struct object object_t;
typedef struct class class_t;
typedef void (*vf_t)(void *); 

typedef char * (*vfchar_t)(void *);
typedef size_t * (*vfsize_t)(void *);

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

struct la
{
    cat_t cat;
    
};



static int AnimalCounter = 0;
int AnimalStaticFlag_g = 0;
char holder[BUFSIZ] = {0};
animal_t *animal_arr_g[5]; 

static size_t ObjectHashCode(void *object);
static char *ObjectToString(void *object);
static void ObjectFinalize(void *object);
static char *AnimalToString(void *object);
void AnimalSayHello(void *this);
void AnimalShowCounter(void *this);
void AnimalctorInt(animal_t *this, int num_masters);
int GetID(void *object);


vf_t object_vt[] = {(vf_t)&ObjectToString,(vf_t)&ObjectHashCode, &ObjectFinalize };   /* function pointer, &ObjectHashCode and so ...,*/
vf_t animal_vt[] = {&AnimalSayHello, &AnimalShowCounter, (vf_t)&AnimalToString/* (vf_t)&AnimalToString,(vf_t)&AnimalHashCode, (vf_t)&AnimalFinalize */};   /* function pointer, &ObjectHashCode and so ... (Vt_t)&foo  */


class_t object_metadata = {"Object", sizeof(object_t), NULL, &object_vt};
class_t animal_metadata = {"Animal", sizeof(animal_t), &object_metadata, &animal_vt};
class_t dog_metadata =    {"Dog", sizeof(dog_t), &animal_metadata, &animal_vt};
class_t cat_metadata =    {"Cat", sizeof(cat_t), &animal_metadata, &animal_vt};
class_t la_metadata =     {"Legendary", sizeof(la_t), &cat_metadata, &animal_vt};


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

static void LAStaticBlocks()
{
    printf("Static block Legendary Animal\n");
}

void AnimalInstanceBlock(void *object)
{
    char nameInstance[100] = {0};
    memset(nameInstance,0,100);
    strcpy(nameInstance,((char *)object));

    printf("Instance initialization block %s\n",nameInstance );
}

static size_t ObjectHashCode(void *object)
{
    static size_t hash = 31; 
    printf("ObjectHashCode");
    hash <<=  ((animal_t *)object)->ID;
    return hash;
    
}

static void ObjectFinalize(void *object)
{
    printf("finalize Animal with ID: %d\n" , ((animal_t *)object)->ID);
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

int GetID(void *object)
{
   return ((animal_t *)object)->ID;
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

    if ((strcmp("Cat", this->object.meta->name)!= 0) && 
            (strcmp("Legendary", this->object.meta->name)!= 0))
    {
        AnimalInstanceBlock(this->object.meta->name);
    }
   
    printf("Animal Ctor\n");
    animal_vt[0](this);
    animal_vt[1](this);

    printf("%s\n", ((vfchar_t (*))animal_vt)[2](this));
    printf("%s\n", ((vfchar_t (*))object_vt)[0](this));
}
static int flag_dog = 1;
void Dogctor(dog_t *this, int num_legs, int num_masters)
{
    if(flag_dog)
    {
        DogStaticBlocks();
        flag_dog = 0;
    }
   
    AnimalInstanceBlock(this->animal.object.meta->parent->name);
    AnimalctorInt(&this->animal,2);
    
    this->num_legs = num_legs;
    printf("Dog Ctor\n");
}
static int flag_cat = 1;
void Catctor(cat_t *this, int num_masters, char *color)
{
    if(strcmp("Cat", this->animal.object.meta->name) == 0)
    {
        if(flag_cat)
        {
            CatStaticBlock();
            flag_cat = 0;
        }
        AnimalInstanceBlock(this->animal.object.meta->parent->name);
        Animalctor(&this->animal,5,2);
    }
    
    this->color = color;
  
     printf("Cat Ctor with color %s\n",this->color );
     printf("Cat Ctor\n");
   
}
int flag_la = 1;
void LActor(la_t *this)
{
    if(flag_la)
    {
        LAStaticBlocks();
        flag_la = 0;
    }
    
    AnimalInstanceBlock(this->cat.animal.object.meta->parent->parent->name);
    
    Animalctor(&this->cat.animal,5,0); 
    Catctor(&this->cat,0,"black");
    printf("Legendary Ctor\n");

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
    char AnyName[20] = {0};
   
    char parName[20] = {0};
    memset(AnyName,0,20);
    memset(parName,0,20);

    strcpy(AnyName, ((animal_t*)this)->object.meta->name);
    strcpy(parName, ((animal_t*)this)->object.meta->parent->name);
    
    if(strcmp("Legendary",AnyName) == 0)
    {
        printf("%s ", AnyName);
        printf("Hello!\n");
        memset(AnyName,0,20);

    }
    else if(strcmp("Cat",AnyName) == 0)
    {
        printf("%s ", parName);
        printf("Hello!\n");
        printf("I Have %d legs\n",((animal_t*)this)->num_legs);
        memset(parName,0,20);
        
    }

    else if (strcmp("Object",parName) == 0)
    {
        printf("%s ", AnyName);
        printf("Hello!\n");
        printf("I Have %d legs\n",((animal_t*)this)->num_legs);
    }
}


void AnimalShowCounter(void *this)
{
    (void)this;
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
    animal_t *any = NULL;
    dog_t *dogy = NULL;
    cat_t *katy = NULL;
    la_t *not = NULL;
    int idx = 0;
   
    /*
    printf("%s\n", ((vfchar_t (*))animal_vt)[2](any));
    printf("%s\n", ((vfchar_t (*))object_vt)[0](any));
*/  any = (animal_t *)ObjectCreate(&animal_metadata);
    Animalctor(any,5,1); 
    printf(" %ld\n", ((vfchar_t (*))object_vt)[1](any));
    
   
    dogy = (dog_t *)ObjectCreate(&dog_metadata);
    Dogctor(dogy,4,2);
    printf(" %ld\n", ((vfchar_t (*))object_vt)[1](dogy));

   
    katy = (cat_t *)ObjectCreate(&cat_metadata);
    Catctor(katy,2, "black");
    printf(" %ld\n", ((vfchar_t (*))object_vt)[1](katy));
   
     
    not = (la_t *)ObjectCreate(&la_metadata);
    LActor(not);
    printf(" %ld\n", ((vfsize_t (*))object_vt)[1](not));
   
    AnimalShowCounter(any);
    printf("%d\n", GetID(any));
    printf("%d\n", GetID(dogy));
    printf("%d\n", GetID(katy));
    printf("%d\n", GetID(not));


    animal_arr_g[0] = (animal_t *)ObjectCreate(&dog_metadata);
    Dogctor((dog_t *)animal_arr_g[0],4,2);
    animal_arr_g[1] = (animal_t *)ObjectCreate(&cat_metadata);
    Catctor((cat_t *)animal_arr_g[1], 0,"black");
    animal_arr_g[2] = (animal_t *)ObjectCreate(&cat_metadata);
   Catctor((cat_t *)animal_arr_g[2],0, "white");
    animal_arr_g[3] = (animal_t *)ObjectCreate(&la_metadata);
    LActor((la_t *)animal_arr_g[3]);
   animal_arr_g[4] = (animal_t *)ObjectCreate(&animal_metadata);
    Animalctor((animal_t *)animal_arr_g[4],4,1);

    for (idx = 0; idx < 5; ++idx)
    {
        (*animal_arr_g[idx]->object.meta->vtable)[0]((void *)animal_arr_g[idx]);
        ((object_vt)[2](animal_arr_g[idx]));
       
    }





    ((object_vt)[2](any));
     ((object_vt)[2](dogy));
      ((object_vt)[2](katy));
       ((object_vt)[2](not));

     return 0;
}
   