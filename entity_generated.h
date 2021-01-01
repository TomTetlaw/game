#ifndef GENERATED_H
#define GENERATED_H
enum Entity_Type {
	_My_Entity,
	_My_Entity1,
	_My_Entity2,
	_My_Entity3,
	_My_Entity4,
	_My_Entity5,
	_My_Entity6,
	_My_Entity7,
};
extern int num_entity_types;
extern const char *entity_type_names[];
struct Entity;
void ent_remove_base(Entity *entity);
Entity *ent_create_from_name(const char *type_name);
#endif
