Contiguous_Array<My_Entity, entities_per_list> My_Entity::_list;
Contiguous_Array<My_Entity1, entities_per_list> My_Entity1::_list;
Contiguous_Array<My_Entity2, entities_per_list> My_Entity2::_list;
Contiguous_Array<My_Entity3, entities_per_list> My_Entity3::_list;
Contiguous_Array<My_Entity4, entities_per_list> My_Entity4::_list;
Contiguous_Array<My_Entity5, entities_per_list> My_Entity5::_list;
Contiguous_Array<My_Entity6, entities_per_list> My_Entity6::_list;
Contiguous_Array<My_Entity7, entities_per_list> My_Entity7::_list;
Contiguous_Array<My_Entity8, entities_per_list> My_Entity8::_list;
Contiguous_Array<My_Entity9, entities_per_list> My_Entity9::_list;
void initialize_entity_lists() {
	carray_init(&My_Entity::_list);
	carray_init(&My_Entity1::_list);
	carray_init(&My_Entity2::_list);
	carray_init(&My_Entity3::_list);
	carray_init(&My_Entity4::_list);
	carray_init(&My_Entity5::_list);
	carray_init(&My_Entity6::_list);
	carray_init(&My_Entity7::_list);
	carray_init(&My_Entity8::_list);
	carray_init(&My_Entity9::_list);
}
void free_entity_lists() {
	carray_free(&My_Entity::_list);
	carray_free(&My_Entity1::_list);
	carray_free(&My_Entity2::_list);
	carray_free(&My_Entity3::_list);
	carray_free(&My_Entity4::_list);
	carray_free(&My_Entity5::_list);
	carray_free(&My_Entity6::_list);
	carray_free(&My_Entity7::_list);
	carray_free(&My_Entity8::_list);
	carray_free(&My_Entity9::_list);
}
void assign_entity_type_tags() {
	My_Entity::_tag = Entity_Type::_My_Entity;
	My_Entity1::_tag = Entity_Type::_My_Entity1;
	My_Entity2::_tag = Entity_Type::_My_Entity2;
	My_Entity3::_tag = Entity_Type::_My_Entity3;
	My_Entity4::_tag = Entity_Type::_My_Entity4;
	My_Entity5::_tag = Entity_Type::_My_Entity5;
	My_Entity6::_tag = Entity_Type::_My_Entity6;
	My_Entity7::_tag = Entity_Type::_My_Entity7;
	My_Entity8::_tag = Entity_Type::_My_Entity8;
	My_Entity9::_tag = Entity_Type::_My_Entity9;
}
Entity_Type My_Entity::_tag;
Entity_Type My_Entity1::_tag;
Entity_Type My_Entity2::_tag;
Entity_Type My_Entity3::_tag;
Entity_Type My_Entity4::_tag;
Entity_Type My_Entity5::_tag;
Entity_Type My_Entity6::_tag;
Entity_Type My_Entity7::_tag;
Entity_Type My_Entity8::_tag;
Entity_Type My_Entity9::_tag;
void ent_remove_base(Entity *entity) {
	switch(entity->tag) {
	case Entity_Type::_My_Entity: {
			My_Entity *derived = (My_Entity *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity1: {
			My_Entity1 *derived = (My_Entity1 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity2: {
			My_Entity2 *derived = (My_Entity2 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity3: {
			My_Entity3 *derived = (My_Entity3 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity4: {
			My_Entity4 *derived = (My_Entity4 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity5: {
			My_Entity5 *derived = (My_Entity5 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity6: {
			My_Entity6 *derived = (My_Entity6 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity7: {
			My_Entity7 *derived = (My_Entity7 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity8: {
			My_Entity8 *derived = (My_Entity8 *)entity->derived;
			ent_remove(derived);
		} break;
	case Entity_Type::_My_Entity9: {
			My_Entity9 *derived = (My_Entity9 *)entity->derived;
			ent_remove(derived);
		} break;
	}
}
Entity *ent_create_from_name(const char *type_name) {
	if(!strcmp(type_name, "My_Entity")) {
		return ent_create(My_Entity)->base;
	}
	if(!strcmp(type_name, "My_Entity1")) {
		return ent_create(My_Entity1)->base;
	}
	if(!strcmp(type_name, "My_Entity2")) {
		return ent_create(My_Entity2)->base;
	}
	if(!strcmp(type_name, "My_Entity3")) {
		return ent_create(My_Entity3)->base;
	}
	if(!strcmp(type_name, "My_Entity4")) {
		return ent_create(My_Entity4)->base;
	}
	if(!strcmp(type_name, "My_Entity5")) {
		return ent_create(My_Entity5)->base;
	}
	if(!strcmp(type_name, "My_Entity6")) {
		return ent_create(My_Entity6)->base;
	}
	if(!strcmp(type_name, "My_Entity7")) {
		return ent_create(My_Entity7)->base;
	}
	if(!strcmp(type_name, "My_Entity8")) {
		return ent_create(My_Entity8)->base;
	}
	if(!strcmp(type_name, "My_Entity9")) {
		return ent_create(My_Entity9)->base;
	}

	return null;
}
const char *entity_type_names[] = {
	"My_Entity",
	"My_Entity1",
	"My_Entity2",
	"My_Entity3",
	"My_Entity4",
	"My_Entity5",
	"My_Entity6",
	"My_Entity7",
	"My_Entity8",
	"My_Entity9",
};
int num_entity_types = 10;
