import glob, os

os.chdir("W:\\")

files = []
for file in os.listdir("./"):
	if file.endswith(".h") or file.endswith(".cpp"):
		files.append(file)

def get_entity_type_names(file):
	type_names = []
	with open(file) as f:
		while True:
			read_data = f.readline()
			if read_data == "":
				break
			if "@entity_type" in read_data:
				words = read_data.split(' ')
				type_names.append(words[1])
	return type_names

def process_entity_types():
	type_names = []
	for file in files:
		type_names = type_names + get_entity_type_names(file)

	with open("entity_generated.cpp", 'w') as f:
		print("generating code for " + str(len(type_names)) + " entity types.")

		# generate a carray for every entity type
		for name in type_names:
			f.write("Contiguous_Array<" + name + ", entities_per_list> " + name + "::_list;\n")

		# generate a function to initialize all the lists
		f.write("void initialize_entity_lists() {\n")
		for name in type_names:
			f.write("\tcarray_init(&" + name + "::_list);\n")
		f.write("}\n")
	
		# generate a function to free all the lists
		f.write("void free_entity_lists() {\n")
		for name in type_names:
			f.write("\tcarray_free(&" + name + "::_list);\n")
		f.write("}\n")

		# generate a function to assign the correct Entity_Type value to each entity type
		f.write("void assign_entity_type_tags() {\n")
		for name in type_names:
			f.write("\t" + name + "::_tag " + "= Entity_Type::_" + name + ";\n")
		f.write("}\n")

		# generate the declarations for entity tags
		for name in type_names:
			f.write("Entity_Type " + name + "::_tag;\n")

		f.write("void ent_remove_base(Entity *entity) {\n")
		f.write("\tswitch(entity->tag) {\n");
		for name in type_names:
			f.write("\tcase Entity_Type::_" + name + ": {\n")
			f.write("\t\t\t" + name + " *derived = (" + name + " *)entity->derived;\n")
			f.write("\t\t\tent_remove(derived);\n")
			f.write("\t\t} break;\n")
		f.write("\t}\n")
		f.write("}\n")

		f.write("Entity *ent_create_from_name(const char *type_name) {\n")
		for name in type_names:
			f.write("\tif(!strcmp(type_name, \"" + name + "\")) {\n")
			f.write("\t\treturn ent_create(" + name + ")->base;\n")
			f.write("\t}\n")
		f.write("\n\treturn null;\n")
		f.write("}\n")

		f.write("const char *entity_type_names[] = {\n")
		for name in type_names:
			f.write("\t\"" + name + "\",\n")
		f.write("};\n")

		f.write("int num_entity_types = " + str(len(type_names)) + ";\n")

#Entity ent_create_from_name(const char *type_name) {
#	if(!strcmp(type_name, "My_Entity)) {
#		return ent_create(My_Entity)->base;
#	}
#	
#	return null;
#}

	with open("entity_generated.h", 'w') as f:
		f.write("#ifndef GENERATED_H\n")
		f.write("#define GENERATED_H\n")

		# generate an enum entry for each entity type
		f.write("enum Entity_Type {\n")
		for name in type_names:
			f.write("\t_" + name + ",\n")
		f.write("};\n")

		f.write("extern int num_entity_types;\n")

		f.write("extern const char *entity_type_names[];\n")

		f.write("struct Entity;\n")
		f.write("void ent_remove_base(Entity *entity);\n")
		f.write("Entity *ent_create_from_name(const char *type_name);\n")

		f.write("#endif\n")

process_entity_types()