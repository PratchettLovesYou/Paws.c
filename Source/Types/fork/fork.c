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
  e(fork)                   (*create)(void);
    struct e(fork) *        (*allocate)(void);
  e(fork)                   (*initialize)         ( struct e(fork)* this );
  
  /// `struct fork` instance functions
  e(thing)                  (*thing)              ( e(fork) this );
                       void (*insert)             ( e(fork) this, e(thing) child, e(ll_size) idx );
                       void (*prefix)             ( e(fork) this, e(thing) child );
                       void (*affix)              ( e(fork) this, e(thing) child );
  e(thing)                  (*at)                 ( e(fork) this,                 e(ll_size) idx );
} IF_INTERNALIZED(extern *Fork);

extern    void MAKE_EXTERNAL(register_Fork)(void);



# endif //!defined(FORK_DECLARATIONS)
# if !defined(FORK_IMPLEMENTATION) && !defined(DECLARATIONS) /* ========================================= BODY */
#   define    FORK_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"

#   include <stdlib.h>
#   include <string.h>
#   include <stdbool.h>
# undef  DECLARATIONS


static fork                 Fork__create(void);
static struct fork *        Fork__allocate(void);
static fork                 Fork__initialize         (fork this);

static thing                fork__thing              (fork this);
static                 void fork__insert             (fork this, thing child, ll_size idx);
static                 void fork__prefix             (fork this, thing child);
static                 void fork__affix              (fork this, thing child);
static thing                fork__at                 (fork this,              ll_size idx);


  IF_EXTERNALIZED(static) struct Fork * // »
                                 Fork   = NULL;
void Paws__register_Fork(void) { Fork   = malloc(sizeof( struct Fork ));
                           Paws->Fork   = Fork;
  Paws__register_Element();
  Paws__register_LL();
  
  auto struct typeRepresentation // »
  type = { .family = Fork, .name = "fork" };
  
  auto struct Fork // »
  data = {
    .Fork         = malloc(sizeof( struct typeRepresentation )),
    
    .create       = Fork__create,
    .allocate     = Fork__allocate,
    .initialize   = Fork__initialize,
    
    .thing        = fork__thing,
    .insert       = fork__insert,
    .prefix       = fork__prefix,
    .affix        = fork__affix,
    .at           = fork__at };
  
  memcpy(data.Fork, &type, sizeof( struct typeRepresentation ));
  memcpy(Fork,      &data, sizeof( struct Fork )); }


fork Fork__create(void) {
  return Fork->initialize(Fork->allocate()); }

struct fork * Fork__allocate(void) {
  return malloc(sizeof( struct fork )); }

fork Fork__initialize(fork this) {
  this->content = LL->create();
  
  return this; }

thing fork__thing(fork this) { auto struct thing // »
  something = { .pointer = this, .isa = Fork->Fork };
  
  return something; }

void fork__insert(fork this, thing child, ll_size idx) {
  if (idx == 0)                          Fork->prefix(this, child);
  else if (idx == this->content->length) Fork->affix (this, child);
  else
    LL->posterior_insert(this->content, Element->create(child), idx); }

void fork__prefix(fork this, thing child) {
  LL->prefix(this->content, Element->create(child)); }

void fork__affix(fork this, thing child)  {
  LL->affix (this->content, Element->create(child)); }

thing fork__at(fork this, ll_size idx) { auto element // »
  e = LL->at(this->content, idx);
  
  if (e == NULL) return (thing){ NULL };
            else return e->thing; }

# endif //!defined(FORK_IMPLEMENTATION) && !defined(DECLARATIONS)
