#include "includes.h"

internal Contiguous_Array<Entity, entities_per_list> entities;

internal int next_parity = 0;

#include "entity_generated.cpp"

void ent_init() {
    carray_init(&entities);
    initialize_entity_lists();
    assign_entity_type_tags();
}

void ent_shutdown() {
    carray_free(&entities);
    free_entity_lists();
}

template<typename T>
T *_ent_create() {
    Entity ent;
    
    int index = -1;
    Entity *entity = carray_alloc(&entities, &index);
    entity->index = index;
    entity->parity = next_parity++;
    entity->tag = T::_tag;
    
    int derived_index = -1;
    T *derived = carray_alloc(&T::_list, &derived_index);
    derived->base = entity;
    entity->derived_index = derived_index;
    
    return derived;
}

Entity *ent_get_from_handle(ehandle handle) {
    if(handle.index < 0 || handle.index >= entities.size)
        return null;
    Entity *entity = &entities[handle.index];
    if(entity->parity != handle.parity)
        return null;
    return entity;
}

template<typename T>
void ent_remove(T *entity) {
    assert(entity->index > 0, "trying to remove an entity that hasn't been added yet");
    carray_remove(&T::_list, entity->base->derived_index);
    carray_remove(&entities, entity->base->index);
}

template<typename T>
inline T *_ent_downcast(Entity *base) {
    if(base->tag != T::_tag) {
        assert(false, "Trying to downcast an entity to a type that it isn't.");
        return null;
    }
    return &T::_list[base->derived_index];
}