/* See LICENSE for license details */

#ifndef cv_screen_device_h_
#define cv_screen_device_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_file/cv_file_pred.h>

struct cv_screen_device * cv_screen_device_create(
    struct cv_screen_device_desc const * p_device_desc);

void cv_screen_device_destroy(struct cv_screen_device * p_device);

cv_bool cv_screen_device_enter(struct cv_screen_device * p_device);

void cv_screen_device_leave(struct cv_screen_device * p_device);

/* --- key table --- */

void cv_screen_device_set_key(struct cv_screen_device * p_device,
    unsigned short i_index, struct cv_screen_key * p_key);

struct cv_screen_key * cv_screen_device_get_key(
    struct cv_screen_device * p_device, unsigned short i_index);

/* --- attribute table --- */

void cv_screen_device_set_attribute(struct cv_screen_device * p_device,
    unsigned short i_index, struct cv_screen_attribute * p_attribute);

struct cv_screen_attribute * cv_screen_device_get_attribute(
    struct cv_screen_device * p_device, unsigned short i_index);

/* --- glyph table --- */

void cv_screen_device_set_glyph(struct cv_screen_device * p_device,
    unsigned short i_index, struct cv_screen_glyph * p_glyph);

struct cv_screen_glyph * cv_screen_device_get_glyph(
    struct cv_screen_device * p_device, unsigned short i_index);

/* --- window table --- */

void cv_screen_device_set_window(struct cv_screen_device * p_device,
    unsigned short i_index, struct cv_screen_window * p_window);

struct cv_screen_window * cv_screen_device_get_window(
    struct cv_screen_device * p_device, unsigned short i_index);

/* --- input --- */

/* wait for input to be avail using select */
/* provide input via a buffer */
/* read input one char at a time until a key is found */
/* compare key with table */
/* detect modifier keys */
/* escape code parser ESC [ n ; n ST */
cv_bool cv_screen_device_read(struct cv_screen_device * p_device,
    unsigned short * r_key);

/* --- output --- */

/* application creates windows, writes data to windows */
/* use apply to render back buffer and to flip */

/* refresh of root window */
void cv_screen_device_apply(struct cv_screen_device * p_device);

#endif /* #ifndef cv_screen_device_h_ */

/* end-of-file: cv_screen_device.h */
