# if !defined(CORE_DECLARATIONS)
#   define    CORE_DECLARATIONS
/*  This file is included to nearly every other header in the Paws codebase; it
 *  provides macros and definitions necessary throughout the codebase.
 *  
 *  You should never have a reason to include or use this file; it’s included
 *  everywhere it is necessary.
 */

# define ALWAYS_EXTERNALIZE(NAME) Paws__ ## NAME

/*  This macro is defined in one of two ways: if one or more Paws headers are
 *  included manually, or if `INTERNALIZE` is defiend (see `Paws.c`), then the
 *  `e()` macro has no effect (the name is not transformed.) However, if one
 *  includes the entire Paws header-set at once (via `#include "Paws.c"`), then
 *  `EXTERNALIZE` will be set, thus causing `e()` to, well, make names safe for
 *  externalization. */
# if defined(EXTERNALIZE)
#   define e(NAME) ALWAYS_EXTERNALIZE(NAME)
#   define E(NAME) e(NAME)
# else
#   define e(NAME) NAME
#   define E(NAME) e(NAME)
# endif //defined(EXTERNALIZE)


/* Yes, I’m a pedant. Get over it. */
typedef void* e(pointer);


# if !defined(__has_attribute)
#   define has_no_has_attribute
#   define __has_attribute(x) 0
# endif //!defined(__has_attribute)

#   if __has_attribute(constructor)
#     define __constructor __attribute__((constructor))
#   else
#     define __constructor
#   endif //__has_attribute(constructor)

#   if __has_attribute(packed)
#     define __packed __attribute__((packed))
#   else
#     define __packed
#   endif //__has_attribute(packed)

# if defined(has_no_has_attribute)
#   undef has_no_has_attribute
#   undef __has_attribute
# endif //!defined(__has_attribute)


# endif //!defined(CORE_DECLARATIONS)
