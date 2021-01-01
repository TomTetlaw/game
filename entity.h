#ifndef ENTITY_H
#define ENTITY_H

#include "entity_generated.h"

struct ehandle {
    int index = -1;
    int parity = -1;
};

struct Entity {
    int index = -1;
    int parity = -1;
    int derived_index = -1;
    
    Entity_Type tag;
    void *derived = null;
    
    Vec2 position;
    Texture *texture = null;
    
    bool remove_me = false;
};

const int entities_per_list = 1024;
extern Contiguous_Array<Entity, entities_per_list> entities;

#define entity_stuff(T) static Entity_Type _tag; static Contiguous_Array<T, entities_per_list> _list; Entity *base = null;

void ent_init();
void ent_shutdown();
void ent_update();
void ent_render();

#define ent_create(T) _ent_create<T>()
template<typename T>
T *_ent_create();

#define ent_downcast(e, T) _ent_downcast<T>(e)
template<typename T>
T *_ent_downcast(Entity *base);

Entity *ent_get_from_handle(ehandle handle);

template<typename T>
void ent_remove(T *entity);

#endif
