# if !defined(TYPE_DECLARATIONS)
#   define    TYPE_DECLARATIONS

# include "Core.h"


/*  This file forward-declares the two fundamental nuketypes absolutely essential to the operation of Paws’
 *  Nucleus: `struct fork` and `struct execution`. Other nuketypes are encapsulated in nuclear extensions (see
 *  the contents of the `Source/Nuclear Extensions/` directory), some of which are shipped with the `Paws.c`
 *  distribution, and some of which Paws.c will not even (sanely) compile without.
 *  
 *  Equally importantly, this file defines the `thing` struct utilized throughout the `Paws.c` codebase to
 *  represent objects of any Paws nuketype. This struct encapsulates an arbitrary pointer (pointing to the heap-
 *  space allocated for the storage of an instance of some Paws nuketype) as well as a pointer to a
 *  `struct typeRepresentation` instance.
 *  
 *  `struct typeRepresentation` instances are registered by n’exts when the interpreter initially bootstraps
 *  itself. They are subsequentially a static pointer, and direct pointer comparison is used to determine if a
 *  given `thing` is of the type required for a given purpose or function. The information they contain is only
 *  useful for debugging purposes, and they are generally never dereferenced; the pointer to their instance only
 *  acts as a dynamically-generated unique identifier at runtime.
 *  
 *  This file is already included everywhere it is relevant. It is very unlikely that you, as an API consumer,
 *  will have a reason to electively include this file yourself.
 */

        struct e(list);
typedef struct e(list)* e(list);

        struct e(execution);
typedef struct e(execution)* e(execution);


        struct e(thing);
typedef struct e(thing) e(thing);

        struct e(typeRepresentation);
typedef struct e(typeRepresentation) e(typeRepresentation);


struct e(typeRepresentation) {
  e(pointer)                    family;
  char                          name[64];
};

struct e(thing) {
  e(pointer) const              pointer;
  e(typeRepresentation) const   isa;
};

# endif
