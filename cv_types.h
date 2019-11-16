/* See LICENSE for license details */

#ifndef cv_types_h_
#define cv_types_h_

#if 1 /* cv_have_stdint_h_ */

#include <stdint.h>

typedef uint64_t cv_ull;
typedef int64_t cv_sll;

#else /* cv_have_stdint_h_ */

#endif /* cv_have_stdint_h_ */

#endif /* #ifndef cv_types_h_ */
