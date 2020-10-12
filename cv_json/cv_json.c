/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json.h>
#include <cv_heap/cv_heap.h>
#include <cv_json/cv_json_ptr.h>
#include <cv_json/cv_json_type.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_list_it.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_heap.h>
#include <cv_runtime.h>
#include <cv_json/cv_json_node.h>
#include <cv_object/cv_object.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_json", sizeof(cv_json));

/*
 *
 */

static void free_text( cv_array * p_storage) {
    if (p_storage->o_min.p_void) {
        cv_heap_free(p_storage->o_min.p_void);
        p_storage->o_min.p_void = 0;
        p_storage->o_max.p_void = 0;
    }
}

/*
 *
 */

static cv_bool dup_text( cv_array * p_storage, cv_array const * p_text) {
    cv_bool b_result = cv_false;
    cv_uptr const i_text_len = cv_array_len(p_text);
    free_text(p_storage);
    if (i_text_len) {
        p_storage->o_min.p_void = cv_heap_alloc(i_text_len, "json_text", 0);
        if (p_storage->o_min.p_void) {
            cv_runtime_memcpy( p_storage->o_min.p_void,
                p_text->o_min.pc_void, i_text_len);
            p_storage->o_max.pc_uchar =
                p_storage->o_min.pc_uchar + i_text_len;
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static void cv_json_init(cv_json * p_this) {
    cv_debug_construct_(g_class, p_this);
    cv_list_node_init(&p_this->o_node);
    cv_list_root_init(&p_this->o_root);
    cv_array_init(&p_this->o_label);
    cv_array_init(&p_this->o_string);
    p_this->i_number = 0.0;
    p_this->e_type = cv_json_type_null;
}

/*
 *
 */

static void cv_json_empty(cv_json * p_this) {
    /* Detach ourselves from any parent */
    /* cv_list_join(&p_this->o_node, &p_this->o_node); */
    /* Destroy all children */
    {
        cv_list_it o_list_it = {0};
        cv_json_ptr o_ptr = {0};
        cv_list_it_init(&o_list_it, &p_this->o_root);
        while (cv_list_it_first(&o_list_it, &o_ptr.o_list_ptr)) {
            cv_json_destroy(o_ptr.p_value);
        }
        cv_list_it_cleanup(&o_list_it);
    }
    free_text(&p_this->o_label);
    free_text(&p_this->o_string);
    p_this->i_number = 0.0;
    p_this->e_type = cv_json_type_null;
}

/*
 *
 */

static void cv_json_cleanup(cv_json * p_this) {
    cv_json_empty(p_this);
    cv_list_node_cleanup(&p_this->o_node);
    cv_list_root_cleanup(&p_this->o_root);
    cv_array_cleanup(&p_this->o_label);
    cv_array_cleanup(&p_this->o_string);
    cv_debug_destruct_(g_class, p_this);
}

static cv_object g_json_node_object;

/*
 *
 */

void cv_json_load(void) {
    cv_uptr const i_placement_len = sizeof(cv_json);
    cv_object_init(&g_json_node_object, "json_node", i_placement_len);
}

/*
 *
 */

void cv_json_unload(void) {
    cv_object_cleanup(&g_json_node_object);
}

/*
 *  Function: cv_json_create()
 *
 *  Description: Allocate memory for json value and initialize to null type.
 */

cv_json * cv_json_create(void) {
    cv_json_ptr o_ptr = {0};
    o_ptr.p_void = cv_object_alloc(&g_json_node_object, 0);
    if (o_ptr.p_void) {
        cv_json_init(o_ptr.p_value);
    }
    return o_ptr.p_value;
}

/*
 *  Function: cv_json_destroy()
 *
 *  Description: Detect json value from lists and destroy data.
 */

void cv_json_destroy( cv_json * p_this) {
    cv_json_ptr o_ptr = {0};
    o_ptr.p_value = p_this;
    cv_json_cleanup(o_ptr.p_value);
    cv_object_free(&g_json_node_object, o_ptr.p_void);
}

/*
 *
 */

void cv_json_move( cv_json * p_this, cv_json * p_other) {
    /* first, release everything */
    cv_json_empty(p_this);
    /* Move type */
    p_this->e_type = p_other->e_type;
    p_other->e_type = cv_json_type_null;
    /* Move number */
    p_this->i_number = p_other->i_number;
    p_other->i_number = 0.0;
    /* Move label */
    cv_array_move(&p_this->o_label, &p_other->o_label);
    /* Move string */
    cv_array_move(&p_this->o_string, &p_other->o_string);
    /* Move children */
    {
        cv_list_it o_list_it = {0};
        cv_json_ptr o_ptr = {0};
        cv_list_it_init(&o_list_it, &p_other->o_root);
        while (cv_list_it_first(&o_list_it, &o_ptr.o_list_ptr)) {
            /* Detach child from other list */
            cv_list_join(&o_ptr.p_value->o_node, &o_ptr.p_value->o_node);
            /* Attach child to this list */
            cv_json_join(o_ptr.p_value, p_this);
        }
        cv_list_it_cleanup(&o_list_it);
    }
    /* Keep same parents? */
}

/*
 *
 */

void cv_json_set_type( cv_json * p_this, unsigned e_type) {
    p_this->e_type = e_type;
}

/*
 *
 */

void cv_json_set_number( cv_json * p_this, double i_number) {
    p_this->i_number = i_number;
}

/*
 *
 */

cv_bool cv_json_set_label( cv_json * p_this, cv_array const * p_text) {
    return dup_text(&p_this->o_label, p_text);
}

/*
 *
 */

cv_bool cv_json_set_string( cv_json * p_this, cv_array const * p_text) {
    return dup_text(&p_this->o_string, p_text);
}

/*
 *
 */

void cv_json_move_label( cv_json * p_this, cv_array_heap * r_string) {
    /* Free the previous instance */
    free_text(&p_this->o_label);
    /* Acquire new instance */
    cv_array_move(&p_this->o_label, &r_string->o_array);
}

/*
 *
 */

void cv_json_move_string( cv_json * p_this, cv_array_heap * r_string) {
    /* Free the previous instance */
    free_text(&p_this->o_string);
    /* Acquire new instance */
    cv_array_move(&p_this->o_string, &r_string->o_array);
}

/*
 *
 */

void cv_json_join( cv_json * p_node, cv_json * p_root) {
    cv_list_join(&p_node->o_node, &p_root->o_root.o_node);
}

/*
 *
 */

unsigned cv_json_get_type( cv_json const * p_this) {
    return p_this->e_type;
}

/*
 *
 */

double cv_json_get_number( cv_json const * p_this) {
    return p_this->i_number;
}

/*
 *
 */

void cv_json_get_label( cv_json const * p_this, cv_array * r_text) {
    *r_text = p_this->o_label;
}

/*
 *
 */

void cv_json_get_string( cv_json const * p_this, cv_array * r_text) {
    *r_text = p_this->o_string;
}

/* end-of-file: cv_json.c */
