#ifndef ENTITY_H
#define ENTITY_H

struct ehandle {
    int index = -1;
    int parity = -1;
};

struct Entity {
    int index = -1;
    int parity = -1;
    int derived_index = -1;
    
    Vec3 position;
    Texture *texture = null;
};

const int entities_per_list = 1024;

#define entity_stuff(T) static Contiguous_Array<T, entities_per_list> _list; Entity *base = null;

struct My_Entity {
    entity_stuff(My_Entity);
    int my_value = 1;
};

void ent_init();
void ent_shutdown();

#define ent_create(T) _ent_create<T>()
template<typename T>
T *_ent_create();

#define ent_downcast(e, T) _ent_downcast<T>(e)
template<typename T>
inline T *_ent_downcast(Entity *base) {
    return &T::_list[base->derived_index];
}

#endif
