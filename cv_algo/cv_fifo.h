/* See LICENSE for license details */

#ifndef cv_fifo_h_
#define cv_fifo_h_

#include <cv_algo/cv_ptr.h>

#include <cv_misc/cv_bool.h>

typedef union cv_fifo_ptr cv_fifo_ptr;

typedef struct cv_fifo_root cv_fifo_root;

typedef struct cv_fifo_node cv_fifo_node;

typedef struct cv_fifo_it cv_fifo_it;

union cv_fifo_ptr
{
    void const * pc_void;
    void * p_void;
    cv_fifo_node const * pc_node;
    cv_fifo_node * p_node;
    cv_ptr o_ptr;
};

/* Use cv_ptr_null_ to init a cv_fifo_ptr */

struct cv_fifo_root {
    cv_fifo_ptr o_head;
    cv_fifo_ptr o_tail;
};

void cv_fifo_root_init( cv_fifo_root * p_this);
void cv_fifo_root_cleanup( cv_fifo_root * p_this);

struct cv_fifo_node {
    cv_fifo_ptr o_next;
};

void cv_fifo_node_init( cv_fifo_node * p_this);
void cv_fifo_node_cleanup( cv_fifo_node * p_this);
void cv_fifo_push( cv_fifo_root * p_root, cv_fifo_node * p_node);
cv_bool cv_fifo_pop( cv_fifo_root * p_root, cv_fifo_ptr * r_value);

struct cv_fifo_it {
    cv_fifo_ptr o_cur;
};

void cv_fifo_it_init( cv_fifo_it * p_this);
void cv_fifo_it_cleanup( cv_fifo_it * p_this);
cv_bool cv_fifo_it_next( cv_fifo_it * p_this, cv_fifo_ptr * r_value);

