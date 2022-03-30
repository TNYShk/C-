#include <stdlib.h>  /* size_t */
#include <stdio.h> /* printf*/
#include <string.h> /* memset*/

#define FALSE (0)
#define TRUE (1)
typedef struct object object_t;
typedef struct class class_t;
typedef struct animal animal_t;
typedef struct dog dog_t;
typedef struct cat cat_t;
typedef struct legendary_animal la_t;

typedef void (*vf_t)(void *);
typedef char * (*vfchar_t)(void *);  


enum func_names
{
    ToString = 0,
    HashCode = 1,
    FINALIZE = 2,
    SAYHello = 3,
    ShowCounter = 4,
    GetNumMaster = 5
};

struct class
{
    char *name;
    size_t class_size;
    class_t *parent;
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
    int id;    
};

struct dog
{
    animal_t animal;
    int num_legs;
};

struct cat
{
    animal_t animal;
    char *color;
    int num_masters;
};

struct legendary_animal
{
    cat_t cat;
};

char *ObjectToString(void *);
size_t ObjectHashCode(void *);
void ObjectFinalize(void *);
static object_t *ObjectCreate(class_t *);

void AnimalLoad(void);
void AnimalStaticBlock(void);
void DogStaticBlock(void);
void CatStaticBlock(void);
void LAStaticBlock(void);

void AnimalInstanceBlock(void);
void DogInstanceBlock(void);

void AnimalCtor(animal_t *);
void AnimalCtorInt(animal_t *, int);

void AnimalHello(void *);
void AnimalShowCounter(void *);
int AnimalGetNumMaster(void *);
char *AnimalToString(void *);
void AnimalFinalize(void *);

void DogCtor(dog_t *);

void DogHello(void *);
char *DogToString(void *);
void DogFinalize(void *);

void CatCtor(cat_t *);

void CatCtorColor(cat_t *, char *);
void CatFinalize(void *);
char *CatToString(void *);

void LACtor(la_t *);

void LAHello(void *);
void LAFinalize(void *);
char *LAToString(void *);

void foo(animal_t *);
static void Test();
 
static int AnimalCounter = 0;
static int static_flag_animal = TRUE;
static int static_flag_dog = TRUE;
static int static_flag_cat = TRUE;
static int static_flag_la = TRUE;


char buffer[BUFSIZ] = {0};
animal_t *animal_arr[5] = {0}; 


vf_t object_vt[] = {(vf_t)&ObjectToString, (vf_t)&ObjectHashCode, &ObjectFinalize};

vf_t animal_vt[] = {(vf_t)&AnimalToString, (vf_t)&ObjectHashCode, &AnimalFinalize, 
                    &AnimalHello, &AnimalShowCounter, (vf_t)&AnimalGetNumMaster};
vf_t dog_vt[] = {(vf_t)&DogToString, (vf_t)&ObjectHashCode, &DogFinalize, 
                 &DogHello, &AnimalShowCounter, (vf_t)&AnimalGetNumMaster};
vf_t cat_vt[] = {(vf_t)&CatToString, (vf_t)&ObjectHashCode, &CatFinalize, 
                &AnimalHello, &AnimalShowCounter, (vf_t)&AnimalGetNumMaster};
vf_t la_vt[] = {(vf_t)&LAToString, (vf_t)&ObjectHashCode, &LAFinalize, 
                &LAHello, &AnimalShowCounter, (vf_t)&AnimalGetNumMaster};

class_t Object_metadata = {"Object", sizeof(object_t), NULL, &object_vt};
class_t animal_metadata = {"Animal", sizeof(animal_t), &Object_metadata, &animal_vt};
class_t dog_metadata = {"Dog", sizeof(dog_t), &animal_metadata, &dog_vt};
class_t cat_metadata = {"Cat", sizeof(cat_t), &animal_metadata, &cat_vt};
class_t la_metadata = {"LegendaryAnimal", sizeof(la_t), &cat_metadata, &la_vt};



int main(void)
{
   Test();

    return 0;
}

static void Test()
{
    size_t idx = 0;
    animal_t *animal = NULL;
    dog_t *dog = NULL;
    cat_t *cat = NULL;
    la_t *la = NULL;
    
    animal = (animal_t *)ObjectCreate(&animal_metadata);
    AnimalCtor(animal);

    dog = (dog_t *)ObjectCreate(&dog_metadata);
    DogCtor(dog);

    cat = (cat_t *)ObjectCreate(&cat_metadata);
    CatCtor(cat);

    la = (la_t *)ObjectCreate(&la_metadata);
    LACtor(la);

    (*animal->object.meta->vtable)[ShowCounter]((void *)animal); 

    printf("%d\n", animal->id);
    printf("%d\n", ((animal_t *)dog)->id);
    printf("%d\n", ((animal_t *)cat)->id);
    printf("%d\n", ((animal_t *)la)->id);

    animal_arr[0] = (animal_t *)ObjectCreate(&dog_metadata);
    DogCtor((dog_t *)animal_arr[0]);
    animal_arr[1] = (animal_t *)ObjectCreate(&cat_metadata);
    CatCtor((cat_t *)animal_arr[1]);
    animal_arr[2] = (animal_t *)ObjectCreate(&cat_metadata);
    CatCtorColor((cat_t *)animal_arr[2], "white");
    animal_arr[3] = (animal_t *)ObjectCreate(&la_metadata);
    LACtor((la_t *)animal_arr[3]);
    animal_arr[4] = (animal_t *)ObjectCreate(&animal_metadata);
    AnimalCtor((animal_t *)animal_arr[4]);

    for (idx = 0; idx < 5; ++idx)
    {
        (*animal_arr[idx]->object.meta->vtable)[SAYHello]((void *)animal_arr[idx]);
        printf("%d\n", ((vfchar_t (*))(*animal_arr[idx]->object.meta->vtable))[GetNumMaster]((void *)animal_arr[idx]));
    }

    for (idx = 0; idx < 5; ++idx)
    {
        foo(animal_arr[idx]);
    }

    for (idx = 0; idx < 5; ++idx)
    {
        (*animal_arr[idx]->object.meta->vtable)[FINALIZE]((void *)animal_arr[idx]);
    }

            (*animal->object.meta->parent->vtable)[FINALIZE](animal);
        (*dog->animal.object.meta->parent->parent->vtable)[FINALIZE](dog);
        (*cat->animal.object.meta->parent->parent->vtable)[FINALIZE](cat);
     (*la->cat.animal.object.meta->parent->parent->parent->vtable)[FINALIZE](la);
}

void foo(animal_t *obj)
{
    printf("%s\n", ((vfchar_t (*))(*obj->object.meta->vtable))[ToString]((void *)obj));
}

char *ObjectToString(void *obj)
{
    char *name = NULL;
    char text[100] = {0};
    char *toString = NULL;

    memset(buffer, 0 ,BUFSIZ);
   
    name = ((object_t *)obj)->meta->name;
    sprintf(text, "il.co.ilrd.java2c.%s", name);
    strcpy(buffer, text);
    memset(text,0, 100);
    sprintf(text, "@%p", obj);
   
    strcat(buffer, text);
    toString = buffer;

    return toString;      
}

size_t ObjectHashCode(void *obj)
{
    static size_t hash = 31; 
    printf("ObjectHashCode ");
    hash <<=  ((animal_t *)obj)->id;
    return hash;
}

void ObjectFinalize(void *obj)
{
    if (NULL != obj)
    {
        free(obj); 
        obj = NULL;
    }
}

static object_t *ObjectCreate(class_t *meta)
{
    object_t *obj = (object_t *)calloc(meta->class_size, sizeof(size_t));
    if (NULL == obj)
    {
        return NULL;
    }

    obj->meta = meta;
    return obj;
}

void AnimalStaticBlock(void)
{
    if(static_flag_animal)
    {
        printf("Static block Animal 1\n");
        printf("Static block Animal 2\n");
        static_flag_animal = FALSE;
    }
}
void DogStaticBlock(void)
{
    if(static_flag_dog)
    {
        printf("Static block Dog\n");
        static_flag_dog = FALSE;
    }
}
void CatStaticBlock(void)
{
    if (static_flag_cat)
    {
        printf("Static block Cat\n");
        static_flag_cat = FALSE;
    }
}

void LAStaticBlock(void)
{
    if (static_flag_la)
    {
        printf("Static block Legendary Animal\n");
        static_flag_la = FALSE;
    }
}

void DogInstanceBlock(void)
{
    printf("Instance initialization block Dog\n");
}

void AnimalInstanceBlock(void)
{
    printf("Instance initialization block Animal\n");
}

void AnimalCtor(animal_t *this)
{
    AnimalLoad();
    printf("Animal Ctor\n");

    this->id = ++AnimalCounter;
    this->num_legs = 5;
    this->num_masters = 1;

    (*this->object.meta->vtable)[SAYHello](this);
    (*this->object.meta->vtable)[ShowCounter](this);

    printf("%s\n", ((vfchar_t (*))(*this->object.meta->vtable))[ToString](this));
    printf("%s\n", ((vfchar_t (*))object_vt)[ToString](this));
}

void AnimalCtorInt(animal_t *this, int num_masters)
{
    AnimalLoad();
    printf("Animal Ctor int\n");
    this->id = ++AnimalCounter;
    this->num_masters = num_masters;
    this->num_legs = 5;
}

void AnimalLoad(void)
{
    AnimalStaticBlock();
    AnimalInstanceBlock();
}

void AnimalHello(void *obj)
{
    printf("Animal Hello!\n");
    printf("I have %d legs\n", ((animal_t *)obj)->num_legs);
}

void AnimalShowCounter(void *obj)
{
    (void)obj;
    printf("counter %d\n", AnimalCounter);
}

int AnimalGetNumMaster(void *obj)
{
    return ((animal_t *)obj)->num_masters;
}

char *AnimalToString(void *obj)
{
    char text[100] = {'\0'};
    char *toString = NULL;
    
    memset(buffer, 0, BUFSIZ);
    memset(text, 0, 100);
    
    strcpy(buffer, "Animal with ID: ");
    sprintf(text, "%d", ((animal_t *)obj)->id);
    strcat(buffer, text);
    
    toString = buffer;
    return toString;  
}

void AnimalFinalize(void *obj)
{
    ((*((animal_t *)obj)->object.meta->parent->vtable)[FINALIZE](obj));
}



void DogHello(void *obj)
{
    printf("%s Hello!\n",((dog_t *)obj)->animal.object.meta->name);
    printf("I have %d legs\n", ((dog_t *)obj)->animal.num_legs);
}

char *DogToString(void *obj)
{
    char text[50] = {'\0'};
    char *toString = NULL;
   
    memset(buffer, 0, BUFSIZ);
    memset(text, 0, 50);
    
    strcpy(buffer, "Dog with ID: ");
    sprintf(text, "%d", ((dog_t *)obj)->animal.id);
    strcat(buffer, text);
    
    toString = buffer;
    return toString;  
}

void DogFinalize(void *obj)
{
    ((*((dog_t *)obj)->animal.object.meta->parent->parent->vtable)[FINALIZE](obj));
}

void DogCtor(dog_t *this)
{
    DogStaticBlock();
    AnimalCtorInt(&this->animal, 2);

    this->animal.num_legs = 4;
    DogInstanceBlock();

    printf("Dog Ctor\n");
}

void CatCtor(cat_t *this)
{
    CatStaticBlock();
    CatCtorColor(this, "black");
    printf("Cat Ctor\n");
    this->num_masters = 2;
}

void CatCtorColor(cat_t *this, char *color)
{
    AnimalCtor(&this->animal);
    this->color = color;
    printf("Cat Ctor with color: %s\n", this->color);
}



char *CatToString(void *obj)
{
    char text[50] = {'\0'};
    char *toString = NULL;
   
    memset(buffer, 0, BUFSIZ);
    memset(text, 0, 50);
    
    strcpy(buffer, "Cat with ID: ");
    sprintf(text, "%d", ((cat_t *)obj)->animal.id);
    strcat(buffer, text);
    
    toString = buffer;
    return toString;  
}

void CatFinalize(void *obj)
{
    ((*((cat_t *)obj)->animal.object.meta->parent->parent->vtable)[FINALIZE](obj));
}

void LACtor(la_t *this)
{
    LAStaticBlock();
    CatCtor(&this->cat);
    printf("Legendary Ctor\n");
}


void LAHello(void *obj)
{
    printf("%s Hello!\n",((la_t *)obj)->cat.animal.object.meta->name);
}

void LAFinalize(void *obj)
{
    ((*((la_t *)obj)->cat.animal.object.meta->parent->parent->parent->vtable)[FINALIZE](obj));
}

char *LAToString(void *obj)
{
    char text[100] = {0};
    char *toString = NULL;
   
    memset(buffer, 0, BUFSIZ);
    memset(text, 0, 100);
    
    strcpy(buffer, "Legendary Animal with ID: ");
    sprintf(text, "%d", ((la_t *)obj)->cat.animal.id);
    strcat(buffer, text);
    
    toString = buffer;
    return toString;  
}
