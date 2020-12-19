Contiguous_Array<My_Entity, entities_per_list> My_Entity::_list;
Contiguous_Array<My_Test, entities_per_list> My_Test::_list;
void initialize_entity_lists() {
	carray_init(&My_Entity::_list);
	carray_init(&My_Test::_list);
}
void free_entity_lists() {
	carray_free(&My_Entity::_list);
	carray_free(&My_Test::_list);
}
void assign_entity_type_tags() {
	My_Entity::_tag = Entity_Type::_My_Entity;
	My_Test::_tag = Entity_Type::_My_Test;
}
Entity_Type My_Entity::_tag;
Entity_Type My_Test::_tag;
