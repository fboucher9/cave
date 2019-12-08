/* See LICENSE for license details */

#include <cv_test.h>

#include <cv_misc/cv_null.h>

#if defined cv_have_libc_

int main(
    int argc,
    char const * const * argv)
{
    return cv_test_main(argc, argv);
}

#else /* #if defined cv_have_libc_ */

#if defined __cplusplus
extern "C"
#endif /* #if defined __cplusplus */
void _start(void);

void _start(void)
{
    cv_test_main(0, cv_null_);
    __asm("movl $1,%eax;"
        "xorl %ebx,%ebx;"
        "int $0x80"
       );
}

#endif /* #if defined cv_have_libc_ */
