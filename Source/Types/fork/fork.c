# if !defined(FORK_DECLARATIONS)
#   define    FORK_DECLARATIONS

# if !defined(DECLARATIONS)
#   define FORK_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Types/Types.h"

#     include "ll.c"
# if defined(FORK_C__BEHEST)
#   undef DECLARATIONS
# endif


struct e(fork) {
  e(ll)   content; };


struct E(Fork) {
  typeRepresentation    Fork;
  
  // Functions ==============
  /// `Fork` family functions
e(fork)     (*allocate)      (void);
  
  /// `struct fork` instance functions
e(thing)    (*thing)        ( e(fork) this );
e(fork)     (*naughtify)    ( e(fork) this );
  void      (*insert)       ( e(fork) this, e(thing) child, e(ll_size) idx );
  void      (*prefix)       ( e(fork) this, e(thing) child );
  void      (*affix)        ( e(fork) this, e(thing) child );
e(thing)    (*at)           ( e(fork) this,                 e(ll_size) idx );
} IF_INTERNALIZED(extern *Fork);

void    extern MAKE_EXTERNAL(register_Fork)    (void);



# endif //!defined(FORK_DECLARATIONS)
# if !defined(FORK_IMPLEMENTATION) && !defined(DECLARATIONS) /* ========================================= BODY */
#   define    FORK_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"

#   include <stdlib.h>
#   include <string.h>
#   include <stdbool.h>
# undef  DECLARATIONS


fork    static Fork__allocate          (void);

fork    static fork__naughtify         (fork this);
thing   static fork__thing             (fork this);
void    static fork__insert            (fork this, thing child, ll_size idx);
void    static fork__prefix            (fork this, thing child);
void    static fork__affix             (fork this, thing child);
thing   static fork__at                (fork this,              ll_size idx);


  IF_EXTERNALIZED(static) struct Fork * // »
                                 Fork         = NULL;
void Paws__register_Fork(void) { Fork         = malloc(sizeof( struct Fork ));
                           Paws->Fork         = Fork;
  
  struct typeRepresentation // »
  auto type = { .family = Fork, .name = "fork" };
  
  struct Fork // »
  auto data = {
    .Fork             = malloc(sizeof( struct typeRepresentation )),
    
    .allocate         = Fork__allocate,
    
    .naughtify        = fork__naughtify,
    .thing            = fork__thing,
    .insert           = fork__insert,
    .prefix           = fork__prefix,
    .affix            = fork__affix,
    .at               = fork__at };
  
  memcpy(data.Fork, &type, sizeof( struct typeRepresentation ));
  memcpy(Fork,      &data, sizeof( struct Fork ));
  
  Paws__register_Element();
  Paws__register_LL(); }


fork Fork__allocate(void) { fork // »
  auto this = malloc(sizeof( struct fork ));
  this->content = LL->allocate();
  
  return this; }

fork fork__naughtify(fork this) { fork // »
  auto naughty = Fork->allocate();
  
  Fork->insert(naughty, Fork->thing(naughty), 0);
  Fork->insert(   this, Fork->thing(naughty), 0);
  
  return naughty; }

thing fork__thing(fork this) { struct thing // »
  auto something = { .pointer = this, .isa = Fork->Fork };
  
  return something; }

void fork__insert(fork this, thing child, ll_size idx) {
  if (idx == 0)                          Fork->prefix(this, child);
  else if (idx == this->content->length) Fork->affix (this, child);
  else
    LL->posterior_insert(this->content, Element->allocate(child), idx); }

void fork__prefix(fork this, thing child) {
  LL->prefix(this->content, Element->allocate(child)); }

void fork__affix(fork this, thing child)  {
  LL->affix (this->content, Element->allocate(child)); }

thing fork__at(fork this, ll_size idx) { element // »
  auto e = LL->at(this->content, idx);
  
  if (e == NULL) return (thing){ {NULL} };
            else return e->thing; }

# endif //!defined(FORK_IMPLEMENTATION) && !defined(DECLARATIONS)
