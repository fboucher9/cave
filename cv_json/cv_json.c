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
#include <cv_runtime.h>

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
        p_storage->o_min.p_void = cv_heap_alloc(i_text_len, 0);
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
 *
 */

struct cv_json {
    cv_list_node o_node;
    /* -- */
    cv_list_root o_root;
    /* -- */
    cv_array o_label;
    /* -- */
    cv_array o_string;
    /* -- */
    double i_number;
    /* -- */
    unsigned e_type;
    int i_padding[3u];
};

/*
 *
 */

static void cv_json_init(cv_json * p_this) {
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

static void cv_json_cleanup(cv_json * p_this) {
    cv_list_node_cleanup(&p_this->o_node);
    {
        cv_list_it o_list_it = {0};
        cv_json_ptr o_ptr = {0};
        cv_list_it_init(&o_list_it, &p_this->o_root);
        while (cv_list_it_first(&o_list_it, &o_ptr.o_list_ptr)) {
            cv_json_destroy(o_ptr.p_value);
        }
        cv_list_it_cleanup(&o_list_it);
    }
    cv_list_root_cleanup(&p_this->o_root);
    free_text(&p_this->o_label);
    cv_array_cleanup(&p_this->o_label);
    free_text(&p_this->o_string);
    cv_array_cleanup(&p_this->o_string);
    p_this->i_number = 0.0;
    p_this->e_type = cv_json_type_null;
}

/*
 *  Function: cv_json_create()
 *
 *  Description: Allocate memory for json value and initialize to null type.
 */

cv_json * cv_json_create(void) {
    cv_json_ptr o_ptr = {0};
    cv_uptr i_placement_len = sizeof(cv_json);
    o_ptr.p_void = cv_heap_alloc(i_placement_len, 0);
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
    cv_heap_free(o_ptr.p_void);
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

void cv_json_get_number( cv_json const * p_this, double * r_number) {
    *r_number = p_this->i_number;
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
