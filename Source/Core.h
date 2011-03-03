# if !defined(CORE_DECLARATIONS)
#   define    CORE_DECLARATIONS
/*  This file is included to nearly every other header in the Paws codebase; it provides macros and definitions
 *  necessary throughout the codebase.
 *  
 *  You should never have a reason to include or use this file; it’s included everywhere it is necessary.
 */


/*  This macro is defined in one of two ways: if one or more Paws headers are included manually, or if
 *  `INTERNALIZE` is defiend (see `Paws.c`), then the `e()` macro has no effect (the name is not transformed.)
 *  However, if one includes the entire Paws header-set at once (via `#include "Paws.c"`), then `EXTERNALIZE`
 *  will be set, thus causing `e()` to, well, make names safe for externalization.
 *  
 *  By contrast, `MAKE_EXTERNAL()` will *always* `EXTERNALIZE` a snippet of code as if `EXTERNALIZE` were set,
 *  whereas `INTERNIFY` will never externalize code (it’s a noop, provided for balance.)
 *  
 *  Generally speaking: `e()` gets used all over the `DECLARATIONS` section of a portion of code; it ensures that
 *  a given identifier isn’t going to trample all over somebody’s parade when they compile against Paws. However,
 *  if you need to universally consider something externalized, then you use `MAKE_EXTERNAL()` in *both* the
 *  `DECLARATIONS` and `IMPLEMENTATION` sections, consistently.
 *  
 *  Finally, `IF_EXTERNAL(some code)` will only be included if `EXTERNAL` is set, while `IF_INTERNAL(some code)`
 *  will only be compiled if it’s *not*.
 */
# define MAKE_EXTERNAL(NAME) Paws__ ## NAME
# define MAKE_INTERNAL(NAME) NAME

# if defined(EXTERNALIZE)
#   define e(NAME) MAKE_EXTERNAL(NAME)
#   define E(NAME) MAKE_EXTERNAL(NAME)

#   define IF_EXTERNAL(CODE) // fizzle
#   define IF_INTERNAL(CODE) CODE
# else
#   define e(NAME) INTERNIFY(NAME)
#   define E(NAME) INTERNIFY(NAME)

#   define IF_EXTERNAL(CODE) CODE
#   define IF_INTERNAL(CODE) // fizzle
# endif //defined(EXTERNALIZE)


/* Yes, I’m a pedant. Get over it. */
typedef void*   e(pointer);


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
