# if !defined(PAWS_DECLARATIONS)
#   define    PAWS_DECLARATIONS
/*  Welcome to the `Paws.c` API. This is the first file you have to `#include` to interface with the Paws API.
 *  For example:
 *      
 *      # define DECLARATIONS
 *      #   include "Paws.c"
 *      # undef  DECLARATIONS
 *      
 *  (In this project, we eschew “header files” in most circumstances, for conditional preprocessor directives.
 *   Defining `DECLARATIONS` before including a file is equivalent to including that file’s header. In this case,
 *   it will ensure inclusion of all of the project’s definitions, just like including all of the header files.)
 *  
 *  ### Types and Families
 *  The `Paws.c` API consists of a few core datatypes (called ‘nuclear types’, to differentiate them from the
 *  library ‘types’ belonging to libspace object systems) and ‘families’, which exist to collect functions and
 *  data relevant to those ‘types.’
 *  
 *  Basics
 *  ------
 *  The core element of the `Paws.c` API is the `Paws` family. It is statically defined by this file, and filled
 *  with static references to other families. Some of the elements remain `NULL`ed, and are filled by the
 *  included n’exts provided by this distribution. (The presence of nuclear extensions shipped with this
 *  distribution can be tested for by comparing the family pointer with `NULL`.)
 *  
 *  For every nuclear type, we provide three identifiers:
 *  
 *  1.  The nuketype data structure itself, as a struct tag: `struct fork`. This is always camelCase, with the
 *      initial character lowercased. This tag can be used to directly allocate or manipulate memory of that
 *      form on the stack or through `malloc()` (though that’s discouraged; see №. 2):
 *          
 *          struct fork   my_fork;
 *          my_fork.content = // ...
 *          
 *  2.  Pointers to memory containing instances of that nuketype’s data structure, as a typedef: `fork`. The name
 *      is identical to the struct tag. Many API functions that operate on one specific type return one of these
 *      typedef’d pointer-types:
 *          
 *          fork    my_fork;
 *          my_fork = malloc(sizeof(struct fork));
 *          
 *  3.  A static “family” data structure, containing function pointers to native functions that operate on
 *      instances of nuketype (“type functions”), as well as other functions somehow relevant (“family
 *      functions”.) This is always CamelCase, with the initial character uppercased:
 *          
 *          fork    my_fork;
 *          my_fork = Fork->allocate();
 *          
 *  We also provide a cruicial `thing` pointer type, which can refer to *any* Paws nuketype (even those defined
 *  in nuclear extensions.) More information about that is available in `Types/Types.h`.
 *  
 *  Memory Mapping
 *  ==============
 *  The casting of pointers is generally considered a dangerous practice by the majority of the C community;
 *  however, the `Paws.c` API makes abundant use of this technique. Specifically, two of our most important data-
 *  types are *built* to be typecast in many situations: the `thing` and our `fork`s.
 *  
 *  1.  `thing`s can be safely cast-masked to appear to be a specific nuketype’s pointer-type. For instance,
 *      without dereferencing it to check the type, we can assume that a `thing` we recieve from a function is
 *      a `fork` (just as an example) and pass it to a function requiring a `fork` to operate on:
 *          
 *          thing   result = some_function();
 *          Fork->execute( (execution)thing, something, 42 )
 *          
 *      Obviously, this is only a good idea if you know for a fact that the `thing` is of the type you care
 *      about, or for some reason, you don’t care about the type of the `thing` at all (see №. 2.)
 *      
 *  2.  Every object in Paws’ libside object-space exposes the same ordered-list-esque libside interface as
 *      `fork`. This means that every nuketype is backed by a linked-list for storage; in addition, we organize
 *      our nuclear data structures such that any nuketype is cast-maskable to a `fork`. This means you can apply
 *      native `fork` operations to *any* nuketype:
 *          
 *          execution   my_exe;
 *          my_exe = Execution->create(NULL);
 *          Fork->insert( (fork)my_exe, something_else, 1 )
 *          
 *  What’s Next?
 *  ------------
 *  From here, you can start learning more about the various nuketypes that ship with `Paws.c` and the associated
 *  families of functions. Just start looking through the files in `Types/`. In addition, there are several APIs
 *  and datatypes utilized throughout the codebase that aren’t themselves nuketypes; these can be found in
 *  `Ancillary/`.
 */


# if defined(DECLARATIONS) && !defined(INTERNALIZE)
#   define PAWS_C__BEHEST__EXTERNALIZE
#   define EXTERNALIZE
# endif //defined(DECLARATIONS) && !defined(INTERNALIZE)
#   if !defined(DECLARATIONS)
#     define PAWS_C__BEHEST
#     define DECLARATIONS
#   endif //!defined(DECLARATIONS)
#       include <stdbool.h>

/*#     include "Ancillary/Threading/Threading.c" */
/*#     include "Ancillary/Unit/Unit.c" */

/*#     include "Types/list/list.c" */
/*#     include "Types/execution/execution.c" */

#       include "Core.h"
#       include "Types/Types.h"
#   if defined(PAWS_C__BEHEST)
#     undef DECLARATIONS
#   endif //defined(PAWS_C__BEHEST)
# if defined(PAWS_C__BEHEST__EXTERNALIZE)
#   undef EXTERNALIZE
# endif //defined(PAWS_C__BEHEST__EXTERNALIZE)


struct Paws {
  // Families ==== === ====
  /// Ancillary families
  struct E(Threading)    *Threading;
  struct E(Unit)         *Unit;
  
  /// Fundamental nuketypes’ families
  struct E(Fork)         *Fork;
  struct E(Execution)    *Execution;
  
  /// Core nuclear extensions’ families
  struct E(Number)       *Number;
  struct E(Label)        *Label;
} // »
extern *Paws;


void    extern e(construct)   (void);

bool    extern EXTERNIFY(constructed); // (see `void construct(void)` below.)



# endif //!defined(PAWS_DECLARATIONS)
# if !defined(PAWS_IMPLEMENTATION) && !defined(DECLARATIONS) /* ========================================= BODY */
#   define    PAWS_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


struct Paws *   Paws = NULL;
void static Paws__register_Paws(void) { Paws = malloc(sizeof(struct Paws));
  
  struct Paws // »
  data = {
    .Threading    = NULL,
    .Unit         = NULL,
    
    .Fork         = NULL,
    .Execution    = NULL,
    
    .Number       = NULL,
    .Label        = NULL
  };
  
  memcpy(Paws, &data, sizeof(struct Paws));
  
  // Paws__register_Threading();
  // Paws__register_Unit();
  
  // Paws__register_Fork();
  // Paws__register_Execution();
  
  // Paws__register_Number();
  // Paws__register_Label();
}


/*  `construct()` must be called before any part of the Paws API may be used. With compilers supporting
 *  `__attribute__((constructor))` (such as `clang` on LLVM) this will be handled for you. If you are targetting
 *  cross-platform compilation, it’s advisable to call `construct()` anyway, as it’s a noop if the environment
 *  has already been constructed.
 */
bool    EXTERNIFY(constructed) = false;
void extern __constructor e(construct)(void) {
  if ( !EXTERNIFY(constructed) ) // »
    Paws__register_Paws();
  
  EXTERNIFY(constructed) = true;
}


# endif //!defined(PAWS_IMPLEMENTATION) && !defined(DECLARATIONS)
