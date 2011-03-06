# include "fork.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Fork, allocate) { auto struct fork * // »
  a_fork_struct = Fork->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT( a_fork_struct != NULL );
  
  SUCCEED; }

CEST(Fork, initialize) { auto fork // »
  a_fork = Fork->allocate();
  
  Fork->initialize(a_fork);
  ASSERT( a_fork->content->first  == NULL );
  ASSERT( a_fork->content->last   == NULL );
  ASSERT( a_fork->content->length == 0    );
  
  SUCCEED; }

CEST(fork, naughtify) { auto fork rv, a_naughty, // »
  a_fork = Fork->create();
  
  rv = Fork->naughtify(a_fork);
  ASSERT(        a_fork->content->length        == 1          );
  ASSERT( LL->at(a_fork->content, 0)->thing.isa == Fork->Fork );
  
  a_naughty = LL->at(a_fork->content, 0)->thing.pointer;
  ASSERT( LL->at(a_naughty->content, 0)->thing.pointer == a_naughty );
  ASSERT( LL->at(a_naughty->content, 0)->thing.isa     == Fork->Fork );
  
  ASSERT( rv == a_naughty );
  
  SUCCEED; }

CEST(fork, thing) { auto fork // »
  a_fork = Fork->create();
  
  ASSERT( Fork->thing(a_fork).pointer == a_fork );
  ASSERT( Fork->thing(a_fork).isa     == Fork->Fork );
  
  SUCCEED; }

CEST(fork, insert) { auto fork // »
  a_fork = Fork->create();
  thing thing1 = Fork->thing(Fork->create()),
        thing2 = Fork->thing(Fork->create()),
        thing3 = Fork->thing(Fork->create()),
        thing4 = Fork->thing(Fork->create());
  
  /* Insert into empty fork */
  Fork->insert    (a_fork, thing2, 0);
  ASSERT( Fork->at(a_fork, 0).pointer == thing2.pointer );
  ASSERT(          a_fork->content->length == 1                   );
  
  /* Insert onto the front of fork */
  Fork->insert    (a_fork, thing1, 0);
  ASSERT( Fork->at(a_fork, 0).pointer == thing1.pointer );
  ASSERT(          a_fork->content->length == 2                   );
  
  /* Insert onto the end of fork */
  Fork->insert    (a_fork, thing4, 2);
  ASSERT( Fork->at(a_fork, 2).pointer == thing4.pointer );
  ASSERT(          a_fork->content->length == 3                   );
  
  /* Insert into fork */
  Fork->insert    (a_fork, thing3, 2);
  ASSERT( Fork->at(a_fork, 2).pointer == thing3.pointer );
  ASSERT(          a_fork->content->length == 4                   );
  
  SUCCEED; }

CEST(fork, prefix) {
  fork  a_fork = Fork->create();
  thing thing1 = Fork->thing(Fork->create()),
        thing2 = Fork->thing(Fork->create()),
        thing3 = Fork->thing(Fork->create());
  
  Fork->prefix    (a_fork, thing3);
  ASSERT( Fork->at(a_fork, 0).pointer == thing3.pointer );
  ASSERT(          a_fork->content->length == 1                   );
  
  Fork->prefix    (a_fork, thing2);
  ASSERT( Fork->at(a_fork, 0).pointer == thing2.pointer );
  ASSERT(          a_fork->content->length == 2                   );
  
  Fork->prefix    (a_fork, thing1);
  ASSERT( Fork->at(a_fork, 0).pointer == thing1.pointer );
  ASSERT(          a_fork->content->length == 3                   );
  
  SUCCEED; }

CEST(fork, affix) {
  fork  a_fork = Fork->create();
  thing thing1 = Fork->thing(Fork->create()),
        thing2 = Fork->thing(Fork->create()),
        thing3 = Fork->thing(Fork->create());
  
  Fork->affix     (a_fork, thing1);
  ASSERT( Fork->at(a_fork, 0).pointer == thing1.pointer );
  ASSERT(          a_fork->content->length == 1                   );
  
  Fork->affix     (a_fork, thing2);
  ASSERT( Fork->at(a_fork, 1).pointer == thing2.pointer );
  ASSERT(          a_fork->content->length == 2                   );
  
  Fork->affix     (a_fork, thing3);
  ASSERT( Fork->at(a_fork, 2).pointer == thing3.pointer );
  ASSERT(          a_fork->content->length == 3                   );
  
  SUCCEED; }

CEST(fork, at) {
  fork  a_fork = Fork->create();
  
  /* Empty `fork`s */
  ASSERT( Fork->at(a_fork, 5).pointer == NULL    );
  ASSERT( Fork->at(a_fork, 4).pointer == NULL    );
  ASSERT( Fork->at(a_fork, 1).pointer == NULL    );
  ASSERT( Fork->at(a_fork, 0).pointer == NULL    );
  
  thing thing1 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing1);
  thing thing2 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing2);
  thing thing3 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing3);
  
  /* Positive indicies */
  ASSERT( Fork->at(a_fork, 0).pointer == thing1.pointer );
  ASSERT( Fork->at(a_fork, 1).pointer == thing2.pointer );
  ASSERT( Fork->at(a_fork, 2).pointer == thing3.pointer );
  
  /* OOB indicies */
  ASSERT( Fork->at(a_fork, 5).pointer == NULL    );
  ASSERT( Fork->at(a_fork, 4).pointer == NULL    );
  
  SUCCEED; }
