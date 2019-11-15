/* See LICENSE for license details */

#ifndef cv_types_h_
#define cv_types_h_

#if 1 /* cv_have_stdint_h_ */

#include <stdint.h>

typedef uint64_t cv_ull_t;
typedef int64_t cv_sll_t;

#else /* cv_have_stdint_h_ */

#endif /* cv_have_stdint_h_ */

#endif /* #ifndef cv_types_h_ */
