# include "fork.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Fork, allocate) { auto struct fork * // »
  a_fork_struct = Fork->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_fork_struct );
  
  SUCCEED; }

CEST(Fork, initialize) { auto fork // »
  a_fork = Fork->allocate();
  
  Fork->initialize(a_fork);
  ASSERT_NULL( a_fork->content->first );
  ASSERT_NULL( a_fork->content->last );
  ASSERT_ZERO( a_fork->content->length );
  
  SUCCEED; }

CEST(fork, thing) { auto fork // »
  a_fork = Fork->create();
  
  ASSERT_EQUAL( Fork->thing(a_fork).pointer, a_fork );
  ASSERT_EQUAL( Fork->thing(a_fork).isa,     Fork->Fork );
  
  SUCCEED; }

CEST(fork, insert) { auto fork a_fork; auto thing thing1, thing2, thing3, thing4;
  a_fork = Fork->create();
  thing1 = Fork->thing(Fork->create());
  thing2 = Fork->thing(Fork->create());
  thing3 = Fork->thing(Fork->create());
  thing4 = Fork->thing(Fork->create());
  
  /* Insert into empty fork */
  Fork->insert(a_fork, thing2, 0);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing2.pointer );
  ASSERT_EQUAL( a_fork->content->length, 1 );
  
  /* Insert onto the front of fork */
  Fork->insert(a_fork, thing1, 0);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing1.pointer );
  ASSERT_EQUAL( a_fork->content->length, 2 );
  
  /* Insert onto the end of fork */
  Fork->insert(a_fork, thing4, 2);
  ASSERT_EQUAL( Fork->at(a_fork, 2).pointer, thing4.pointer );
  ASSERT_EQUAL( a_fork->content->length, 3 );
  
  /* Insert into fork */
  Fork->insert(a_fork, thing3, 2);
  ASSERT_EQUAL( Fork->at(a_fork, 2).pointer, thing3.pointer );
  ASSERT_EQUAL( a_fork->content->length, 4 );
  
  SUCCEED; }

CEST(fork, prefix) { auto fork a_fork; auto thing thing1, thing2, thing3;
  a_fork = Fork->create();
  thing1 = Fork->thing(Fork->create());
  thing2 = Fork->thing(Fork->create());
  thing3 = Fork->thing(Fork->create());
  
  Fork->prefix(a_fork, thing3);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing3.pointer );
  ASSERT_EQUAL( a_fork->content->length, 1 );
  
  Fork->prefix(a_fork, thing2);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing2.pointer );
  ASSERT_EQUAL( a_fork->content->length, 2 );
  
  Fork->prefix(a_fork, thing1);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing1.pointer );
  ASSERT_EQUAL( a_fork->content->length, 3 );
  
  SUCCEED; }

CEST(fork, affix) { auto fork a_fork; auto thing thing1, thing2, thing3;
  a_fork = Fork->create();
  thing1 = Fork->thing(Fork->create()),
  thing2 = Fork->thing(Fork->create()),
  thing3 = Fork->thing(Fork->create());
  
  Fork->affix(a_fork, thing1);
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing1.pointer );
  ASSERT_EQUAL( a_fork->content->length, 1 );
  
  Fork->affix(a_fork, thing2);
  ASSERT_EQUAL( Fork->at(a_fork, 1).pointer, thing2.pointer );
  ASSERT_EQUAL( a_fork->content->length, 2 );
  
  Fork->affix(a_fork, thing3);
  ASSERT_EQUAL( Fork->at(a_fork, 2).pointer, thing3.pointer );
  ASSERT_EQUAL( a_fork->content->length, 3 );
  
  SUCCEED; }

CEST(fork, at) { auto fork a_fork; auto thing thing1, thing2, thing3;
  a_fork = Fork->create();
  
  /* Empty `fork`s */
  ASSERT_NULL( Fork->at(a_fork, 5).pointer );
  ASSERT_NULL( Fork->at(a_fork, 4).pointer );
  ASSERT_NULL( Fork->at(a_fork, 1).pointer );
  ASSERT_NULL( Fork->at(a_fork, 0).pointer );
  
  thing1 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing1);
  thing2 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing2);
  thing3 = Fork->thing(Fork->create()); Fork->affix(a_fork, thing3);
  
  /* Positive indicies */
  ASSERT_EQUAL( Fork->at(a_fork, 0).pointer, thing1.pointer );
  ASSERT_EQUAL( Fork->at(a_fork, 1).pointer, thing2.pointer );
  ASSERT_EQUAL( Fork->at(a_fork, 2).pointer, thing3.pointer );
  
  /* OOB indicies */
  ASSERT_NULL( Fork->at(a_fork, 5).pointer );
  ASSERT_NULL( Fork->at(a_fork, 4).pointer );
  
  SUCCEED; }
