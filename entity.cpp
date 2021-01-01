#include "includes.h"

Contiguous_Array<Entity, entities_per_list> entities;

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
    entity->derived = derived;
    
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
    assert(entity->base->index >= 0, "trying to remove an entity that hasn't been added yet");
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

void ent_update() {
    for(int i = 0; i < entities.size; i++) {
        if(!entities.filled[i]) continue;
        if(entities[i].remove_me) continue;
        Entity *entity = &entities[i];
        
// @todo        if(entity->remove_me) ent_remove(
    }
}

void ent_render() {
    for(int i = 0; i < entities.size; i++) {
        if(!entities.filled[i]) continue;
        if(entities[i].remove_me) continue;
        Entity *entity = &entities[i];
        
        r_render_texture(entity->texture, entity->position);
    }
}