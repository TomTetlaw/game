#include "includes.h"

internal Contiguous_Array<Entity, entities_per_list> entities;
Contiguous_Array<My_Entity, entities_per_list> My_Entity::_list;

internal int next_parity = 0;

void ent_init() {
    carray_init(&entities);
    carray_init(&My_Entity::_list);
}

void ent_shutdown() {
    carray_free(&entities);
    carray_free(&My_Entity::_list);
}

template<typename T>
T *_ent_create() {
    Entity ent;
    
    int index = -1;
    Entity *entity = carray_alloc(&entities, &index);
    entity->index = index;
    entity->parity = next_parity++;
    
    int derived_index = -1;
    T *derived = carray_alloc(&T::_list, &derived_index);
    derived->base = entity;
    entity->derived_index = derived_index;
    
    return derived;
}