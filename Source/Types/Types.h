# if !defined(TYPE_DECLARATIONS)
#   define    TYPE_DECLARATIONS

# include "Core.h"


/*  This file exists simply to forward-declare some structs and types used throughout the rest of the Paws.c
 *  codebase (including the `thing` union-struct).
 *  
 *  You should never have a reason to include or use this file; it’s already included everywhere it is necessary.
 */

        struct e(list);
typedef struct e(list)* e(list);

        struct e(routine);
typedef struct e(routine)* e(routine);

        struct e(execution);
typedef struct e(execution)* e(execution);

        struct e(numeric);
typedef struct e(numeric)* e(numeric);

        struct e(string);
typedef struct e(string)* e(string);


        struct e(thing); // A union representing a pointer to *any* core Paws datatype
typedef struct e(thing) e(thing); /*
typedef   enum e(kind) e(kind); // ISO C forbids forward references to 'enum' types. YAY. >,< */

struct e(thing) {
  union /* e(thing_pointers) */ {
    void         *unknown;
    
    e(list)       list;
    e(routine)    routine;
    e(execution)  execution;
    e(numeric)    numeric;
    e(string)     string;
  } const pointer;
  
  enum e(kind) {
    E(UNKNOWN) = 0,
    
    E(LIST),
    E(ROUTINE),
    E(EXECUTION),
    E(NUMERIC),
    E(STRING)
  } const isa;
};

typedef   enum e(kind) e(kind); // See above

# endif
