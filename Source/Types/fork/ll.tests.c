# include "ll.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
#   include <string.h>
# undef  DECLARATIONS


# define SOMETHING _make_something()//;

thing static _make_something(void) { auto struct thing // »
  something = { .pointer = NULL, .isa = NULL };
  
  return something; }

CEST(LL, allocate) { auto struct ll * // »
  a_ll_pointer = LL->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT( a_ll_pointer != NULL );
  
  SUCCEED; }

CEST(LL, initialize) { auto struct ll * // »
  a_ll_pointer = LL->allocate();
  
  LL->initialize(a_ll_pointer);
  ASSERT( (*a_ll_pointer).first  == NULL );
  ASSERT( (*a_ll_pointer).last   == NULL );
  ASSERT( (*a_ll_pointer).length == 0    );
  
  SUCCEED; }

CEST(ll, anterior_insert) { auto ll a_ll; auto element element1, element2, element3, elementA;
  a_ll = LL->create();
  element1 = Element->create(SOMETHING); LL->affix(a_ll, element1);
  element2 = Element->create(SOMETHING); LL->affix(a_ll, element2);
  element3 = Element->create(SOMETHING); LL->affix(a_ll, element3);
  elementA = Element->create(SOMETHING);
  
  /* TODO: Error condition */
  LL->anterior_insert(a_ll, elementA, 0);
  ASSERT( LL->at(a_ll, 0) == element1 );
  
  LL->anterior_insert(a_ll, elementA, 1);
  ASSERT( LL->at(a_ll, 0) == element1 );
  ASSERT( LL->at(a_ll, 1) == elementA );
  ASSERT( LL->at(a_ll, 2) == element2 );
  
  SUCCEED; }

CEST(ll, posterior_insert) { auto ll a_ll; auto element element1, element2, element3, elementA;
  a_ll = LL->create();
  element1 = Element->create(SOMETHING); LL->affix(a_ll, element1);
  element2 = Element->create(SOMETHING); LL->affix(a_ll, element2);
  element3 = Element->create(SOMETHING); LL->affix(a_ll, element3);
  elementA = Element->create(SOMETHING);
  
  /* TODO: Error condition */
  LL->posterior_insert(a_ll, elementA, a_ll->length);
  ASSERT( LL->at(a_ll, 0) == element1 );
  
  LL->posterior_insert(a_ll, elementA, 1);
  ASSERT( LL->at(a_ll, 0) == element1 );
  ASSERT( LL->at(a_ll, 1) == elementA );
  ASSERT( LL->at(a_ll, 2) == element2 );
  
  SUCCEED; }

CEST(ll, prefix) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  element1 = Element->create(SOMETHING);
  element2 = Element->create(SOMETHING);
  element3 = Element->create(SOMETHING);
  
  LL->prefix(a_ll, element3);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element3 );
  ASSERT( a_ll->last   == element3 );
  
  LL->prefix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element2 );
  ASSERT( a_ll->last   == element3 );
  
  LL->prefix(a_ll, element1);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  SUCCEED; }

CEST(ll, affix) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  element1 = Element->create(SOMETHING);
  element2 = Element->create(SOMETHING);
  element3 = Element->create(SOMETHING);
  
  LL->affix(a_ll, element1);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element1 );
  
  LL->affix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element2 );
  
  LL->affix(a_ll, element3);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  SUCCEED; }

CEST(ll, at) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  
  /* Empty `ll`s */
  ASSERT( LL->at(a_ll,  5) == NULL );
  ASSERT( LL->at(a_ll,  1) == NULL );
  ASSERT( LL->at(a_ll,  0) == NULL );
  
  element1 = Element->create(SOMETHING); LL->affix(a_ll, element1);
  element2 = Element->create(SOMETHING); LL->affix(a_ll, element2);
  element3 = Element->create(SOMETHING); LL->affix(a_ll, element3);
  
  /* Positive indicies */
  ASSERT( LL->at(a_ll,  0) == element1 );
  ASSERT( LL->at(a_ll,  1) == element2 );
  ASSERT( LL->at(a_ll,  2) == element3 );
  
  /* OOB indicies */
  ASSERT( LL->at(a_ll,  5) == NULL );
  ASSERT( LL->at(a_ll,  4) == NULL );
  
  SUCCEED; }


CEST(Element, allocate) { auto struct element * // »
  an_element_pointer = Element->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT( an_element_pointer != NULL );
  
  SUCCEED; }

CEST(Element, initialize) { auto struct element * // »
  an_element_pointer = Element->allocate();
  
  Element->initialize(an_element_pointer, SOMETHING);
  ASSERT( (*an_element_pointer).next     == NULL );
  ASSERT( (*an_element_pointer).previous == NULL );
  
  SUCCEED; }

CEST(element, prefix) { auto element // »
  element1 = Element->create(SOMETHING),
  element2 = Element->create(SOMETHING),
  element3 = Element->create(SOMETHING),
  elementA = Element->create(SOMETHING),
  elementB = Element->create(SOMETHING),
  elementC = Element->create(SOMETHING);
  
  
  /* A basic single prefix */
  /* > [***] node3
   * 
   *         node1
   * > [***]    └→ node3
   * 
   * > [***] node1 node3
   */
  Element->prefix(element3, element1);
  ASSERT( element1->previous == NULL     && element1->next == element3 );
  ASSERT( element3->previous == element1 && element3->next == NULL     );
  
  
  /* A single prefix that pushes old nodes */
  /* > [***] node1 node3
   * 
   *               node2
   * > [***] node1    └→ node3
   * 
   * > [***] node1 node2 node3
   */
  Element->prefix(element3, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-prefix that pushes old nodes */
  /* > [***] node1 node2 node3
   * 
   * > [***] nodeA nodeB nodeC
   * > [***] node1    └→ node2 node3
   * 
   *   [***] node1   …   [***] nodeC
   * > [***] nodeA nodeB node2 node3
   */
  Element->prefix(element2, elementB);
  ASSERT( elementA->previous == NULL     && elementA->next == elementB );
  ASSERT( elementB->previous == elementA && elementB->next == element2 );
  ASSERT( element2->previous == elementB && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  ASSERT( elementC->previous != elementB );
  ASSERT( element1->next     != element2 );
  
  
  SUCCEED; }

CEST(element, affix) { auto element // »
  element1 = Element->create(SOMETHING),
  element2 = Element->create(SOMETHING),
  element3 = Element->create(SOMETHING),
  elementA = Element->create(SOMETHING),
  elementB = Element->create(SOMETHING),
  elementC = Element->create(SOMETHING);
  
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Element->affix(element1, element3);
  ASSERT( element1->previous == NULL     && element1->next == element3 );
  ASSERT( element3->previous == element1 && element3->next == NULL     );
  
  
  /* A single affix that pushes old nodes */
  /* > node1 node3 [***]
   * 
   *         node2
   * > node1 ←┘    node3 [***]
   * 
   * > node1 node2 node3 [***]
   */
  Element->affix(element1, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC [***]
   *   nodeA [***]   …   node3 [***]
   */
  Element->affix(element2, elementB);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == elementB );
  ASSERT( elementB->previous == element2 && elementB->next == elementC );
  ASSERT( elementC->previous == elementB && elementC->next == NULL     );
  
  ASSERT( element3->previous != element2 );
  ASSERT( elementA->next     != elementB );
  
  
  SUCCEED; }
