/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random_crypto.h>

#if defined cv_linux_

#include <cv_file/cv_file_disk_desc.h>
#include <cv_algo/cv_array_tool.h>

/*
 *
 */

static cv_array const * get_dev_urandom_name(void) {
    static unsigned char const s_text[] = {
        '/', 'd', 'e', 'v', '/', 'u', 'r', 'a', 'n', 'd', 'o', 'm' };
    static cv_array const s_array =
        cv_array_text_initializer_(s_text);
    return &s_array;
}

/*
 *
 */

static cv_bool cv_random_crypto_init_linux(struct cv_random_crypto * p_this) {
    cv_bool b_result = cv_false;
    cv_file_disk_desc o_desc;
    cv_file_disk_desc_init(&o_desc);
    o_desc.p_name = get_dev_urandom_name();
    o_desc.e_mode = cv_file_disk_mode_read;
    if (cv_file_disk_init(&p_this->o_file_disk, &o_desc)) {
        b_result = cv_true;
    }
    cv_file_disk_desc_cleanup(&o_desc);
    return b_result;
}

/*
 *
 */

static void cv_random_crypto_cleanup_linux(struct cv_random_crypto * p_this) {
    cv_file_disk_cleanup(&p_this->o_file_disk);
}

/*
 *
 */

static unsigned long cv_random_crypto_pick_linux(
    struct cv_random_crypto * p_this, unsigned long i_modulo) {
    unsigned long i_result = 0;
    unsigned char uc_data[4u];
    cv_array o_data;
    cv_array_init_vector(&o_data, uc_data, sizeof(o_data));
    {
        cv_sptr const i_read_result = cv_file_read(
            &p_this->o_file_disk.o_file, &o_data);
        if (i_read_result > 0) {
            unsigned long const ul_temp = uc_data[0u];
            i_result |= (ul_temp << 24u);
        }
        if (i_read_result > 1) {
            unsigned long const ul_temp = uc_data[1u];
            i_result |= (ul_temp << 16u);
        }
        if (i_read_result > 2) {
            unsigned long const ul_temp = uc_data[2u];
            i_result |= (ul_temp << 8u);
        }
        if (i_read_result > 3) {
            unsigned long const ul_temp = uc_data[3u];
            i_result |= (ul_temp << 0u);
        }
    }
    cv_array_cleanup(&o_data);
    if (i_modulo) {
        i_result = (i_result % i_modulo);
    }
    return i_result;
}

#endif /* #if defined cv_linux_ */

/*
 *
 */

cv_bool cv_random_crypto_init(struct cv_random_crypto * p_this) {
#if defined cv_linux_
    return cv_random_crypto_init_linux(p_this);
#else /* #if defined cv_linux_ */
    (void)p_this;
    return cv_false;
#endif /* #if defined cv_linux_ */
}

/*
 *
 */

void cv_random_crypto_cleanup(struct cv_random_crypto * p_this) {
#if defined cv_linux_
    cv_random_crypto_cleanup_linux(p_this);
#else /* #if defined cv_linux_ */
    (void)p_this;
#endif /* #if defined cv_linux_ */
}

/*
 *
 */

unsigned long cv_random_crypto_pick( struct cv_random_crypto * p_this,
    unsigned long i_modulo) {
#if defined cv_linux_
    return cv_random_crypto_pick_linux(p_this, i_modulo);
#else /* #if defined cv_linux_ */
    (void)p_this;
    (void)i_modulo;
    return 0;
#endif /* #if defined cv_linux_ */
}

/* end-of-file: cv_random_crypto.c */
