#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

struct Object;
struct LolClass;

struct Module_Descriptor
{
	// pointers to callbacks
	int a;
};

typedef struct Object* (*obj_selector)(struct Object*, va_list);

typedef void (*obj_class_initializer_callback)(struct LolClass*);

void obj_register_class_with_descriptor(struct Module_Descriptor* descriptor);

void obj_load_module_from_file(const char* filename);

void obj_add_selector(struct LolClass* klass, const char* selectorName, obj_selector selector);

void obj_add_class_selector(struct LolClass* klass, const char* selectorName, obj_selector selector);

obj_selector obj_selector_for_name(struct LolClass* klass, const char* selectorName);

struct Object* obj_send_message(struct Object* obj, const char* selectorName, ...);
struct Object* obj_send_message_to_super(struct Object* obj, const char* selectorName, ...);

struct Object* obj_send_message_with_arguments(struct Object* obj, const char* selectorName, va_list arguments);
struct Object* obj_send_message_to_super_with_arguments(struct Object* obj, const char* selectorName, va_list arguments);

void obj_unload_class(struct LolClass* klass);

struct LolClass* Class();

void obj_class_initializer(struct LolClass* klass);

void obj_init_runtime();

void obj_shutdown_runtime();

void obj_initialize_class(struct LolClass* klass, obj_class_initializer_callback initializer);

void obj_print_class_diagram();

void obj_set_class_parent(struct LolClass* klass, struct LolClass* parent);

struct LolClass* obj_class_parent(struct LolClass* klass);

void obj_set_class_name(struct LolClass* klass, const char* name);

const char* obj_class_name(struct LolClass* klass);

struct LolClass* obj_class_for_object(struct Object* object);

size_t obj_number_of_call_arguments_ending_on_null(va_list arguments);

bool obj_object_is_class(struct Object* object);

struct Object* obj_get_object_property(struct Object* object, const char* propertyName);
struct Object* obj_set_object_property(struct Object* object, const char* propertyName, struct Object* value);

void obj_add_property(struct LolClass* klass, const char* propertyName, struct LolClass* type, size_t offset);

void obj_add_selector_from_property(struct LolClass* klass, struct LolClass* memberClass, const char* memberName, const char* selectorName); 

struct LolClass* obj_class_with_name(const char* klassName);

#define RETAIN(OBJ) obj_send_message((OBJ), "retain")
#define RELEASE(OBJ) obj_send_message(obj_class_for_object(OBJ), "release", &OBJ)
