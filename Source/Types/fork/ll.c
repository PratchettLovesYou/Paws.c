/*  `ll` is Paws’ doubly-linked-list data structure; the core storage format responsible for `fork`s’ element
 *  storage (and, thusly, the element storage behind every `thing` in Paws’ libspace.)
 *  
 *  NOTE: This is not a traditional linked-list! There are two major differences of which you need to be aware:
 *        
 *        - We don’t iterate `element`s until reaching a `NULL` pointer; instead, we store (and maintain) the
 *          length (in `element`s) and iterate based on that. This means that directly manipulating the `length`
 *          of an `ll` (or manipulating the `first` or `last` pointers) is very dangerous.
 *          Use the provided functions!
 *        - When `element`s are rearranged, they *do not* unnecessarily drop their assocations with other
 *          `element`s: they will attempt to retain them, if at all possible. We use this to splice sublists of
 *          `element`s onto eachother, but it makes it more difficult to avoid “zombie elements.” I repeat: Use
 *          the provided functions!
 *        - This is not a ‘purist’ implementation of the linked-lists you learned in your data structures and
 *          algorithms class; we don’t pass around individual nodes. Instead, we define a wrapper type that
 *          stores metadata about the linked-list structure; this wrapper (the `ll` type) is what we pass around
 *          and store as our “linked list,” instead of a given `element` reference.
 */
# if !defined(LL_DECLARATIONS)
#   define    LL_DECLARATIONS

# if !defined(DECLARATIONS)
#   define LL_C__BEHEST
#   define DECLARATIONS
# endif //!defined(DECLARATIONS)
#     include "Core.h"
#     include "Types/Types.h"

#     include <limits.h>
# if defined(LL_C__BEHEST)
#   undef DECLARATIONS
# endif //defined(LL_C__BEHEST)


          struct e(element);
          struct e(ll);
typedef   struct e(element)*        e(element);
typedef   struct e(ll)*             e(ll);

typedef   unsigned long long int    e(ll_size);

struct e(element) {
  e(thing)      thing;
  e(element)    next;
  e(element)    previous; };
struct e(ll) {
  e(element)    first;
  e(element)    last;
  e(ll_size)    length; };


struct E(Element) {
  // Functions ==============
  /// `Element` family functions
e(element)    (*allocate)   ( e(thing) thing );
  
  /// `struct element` instance functions
  void        (*prefix)     ( e(element) this, e(element) other );
  void        (*affix)      ( e(element) this, e(element) other );
} IF_INTERNALIZED(extern *Element);

struct E(LL) {
  // Functions ==============
  /// `LL` family functions
e(ll)         (*allocate)            (void);
  
  /// `struct ll` instance functions
  void        (*anterior_insert)    ( e(ll) this, e(element) child, e(ll_size) idx );
  void        (*posterior_insert)   ( e(ll) this, e(element) child, e(ll_size) idx );
  void        (*prefix)             ( e(ll) this, e(element) child );
  void        (*affix)              ( e(ll) this, e(element) child );
e(element)    (*at)                 ( e(ll) this,                   e(ll_size) idx );
} IF_INTERNALIZED(extern *LL);

void    extern MAKE_EXTERNAL(register_Element)   (void);
void    extern MAKE_EXTERNAL(register_LL)        (void);



# endif //!defined(LL_DECLARATIONS)
# if !defined(LL_IMPLEMENTATION) && !defined(DECLARATIONS) /* =========================================== BODY */
#   define    LL_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


element   static Element__allocate   (thing thing);

void      static element__prefix     (element this, element other);
void      static element__affix      (element this, element other);

     IF_EXTERNALIZED(static) struct Element * // »
                                    Element   = NULL;
void Paws__register_Element(void) { Element   = malloc(sizeof( struct Element ));
  
  struct Element // »
  auto data = {
    .allocate   = Element__allocate,
    
    .prefix     = element__prefix,
    .affix      = element__affix
  };
  
  memcpy(Element, &data, sizeof( struct Element )); }


ll        static LL__allocate            (void);

void      static ll__anterior_insert     (ll this, element child, ll_size idx);
void      static ll__posterior_insert    (ll this, element child, ll_size idx);
void      static ll__prefix              (ll this, element child);
void      static ll__affix               (ll this, element child);
element   static ll__at                  (ll this,                ll_size idx);

IF_EXTERNALIZED(static) struct LL * // »
                               LL   = NULL;
void Paws__register_LL(void) { LL   = malloc(sizeof( struct LL ));
  
  struct LL // »
  auto data = {
    .allocate           = LL__allocate,
    
    .anterior_insert    = ll__anterior_insert,
    .posterior_insert   = ll__posterior_insert,
    .prefix             = ll__prefix,
    .affix              = ll__affix,
    .at                 = ll__at
  };
  
  memcpy(LL, &data, sizeof( struct LL )); }


/* This method creates a new `element` for a given `thing`. `next` and `previous` will also be initialized to a
 * `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `element` as `e`.
 */
element Element__allocate(thing target) { element // »
  auto this = malloc(sizeof( struct element ));
  this->next     = NULL;
  this->previous = NULL;
  memcpy(&this->thing, &target, sizeof( struct thing ));
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  
  return this; }

/* This method inserts another element *before* this element in the chain of a linked list.
 * 
 * If there’s already a element attached before this element, and there *isn’t* one attached before the element
 * being inserted, then that next- element will be affixed to our new element, thus keeping the chain intact if
 * possible.
 * 
 * Note: See the notes on `Element->affix()`.
 */
void element__prefix(element this, element other) {
  if (this->previous != NULL) {
    if (other->previous == NULL)
      element__prefix(other, this->previous);
    else {
      this->previous->next = NULL;
      if (other->next != NULL)
        other->next->previous = NULL; } }
  
  other->next     = this;
  this->previous  = other; }

/* This method inserts another element *after* this element in the chain of a linked list.
 * 
 * If there’s already a element attached after this element, and there *isn’t* one attached after the element
 * being inserted, then that next-element will be affixed to our new element, thus keeping the chain intact if
 * possible.
 * 
 * Note: Realize that due to that copy-next mechanic, you can splice element-strings on top of eachother, but all
 *       elements *after* this element in the original chain will be lost.
 */
void element__affix(element this, element other) {
  if (this->next != NULL) {
    if (other->next == NULL)
      element__affix(other, this->next);
    else {
      this->next->previous = NULL;
      if (other->previous != NULL)
        other->previous->next = NULL; } }
  
  other->previous = this;
  this->next      = other; }


/* This method initializes a new `ll`, with no elements. The `first` and `last` are set to `NULL` pointers, and
 * `length` is initialized to zero. */
ll LL__allocate(void) { ll // »
  auto this = malloc(sizeof( struct ll ));
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this; }

void ll__anterior_insert(ll this, element child, ll_size idx) {
  if (idx == 0)
    /* TODO: Error condition, cannot anterior-insert at first position */;
  else {
    Element->affix(LL->at(this, idx - 1), child);
    this->length++; } }

void ll__posterior_insert(ll this, element child, ll_size idx) {
  if (idx == this->length)
    /* TODO: Error condition, cannot posterior-insert at last position */;
  else {
    Element->prefix(LL->at(this, idx), child);
    this->length++; } }

/* This method prefixes a new child `element` onto an `ll`. This will ensure that the first element in the `ll`,
 * after the appending, is the new one.
 * 
 * Takes two arguments, the prefixee (`this`), and a `element` to be prefixed onto it as a child.
 */
void ll__prefix(ll this, element child) {
  if (this->length < 1)
    this->last = child;
  else
    Element->prefix( this->first, child );
  this->first = child;
  this->length++; }

/* This method affixes a new child `element` onto an `ll`. This will ensure that the last element in the `ll`,
 * after the appending, is the new one.
 * 
 * Takes two arguments, the affixee (`this`), and a `element` to be affixed onto it as a child.
 */
void ll__affix(ll this, element child) {
  if (this->length < 1)
    this->first = child;
  else
    Element->affix( this->last, child );
  this->last = child;
  this->length++; }

/* This method returns a `element` at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `idx`.
 */
element ll__at(ll this, ll_size idx) { auto element result; ll_size i;
  
  if (idx >= this->length) return NULL;
  
  if (idx <= this->length / 2) {
    result = this->first;
    for (i = 0; i < idx; ++i)
      result = result->next;
  } else {
    result = this->last;
    for (i = this->length - 1; i > idx; --i)
      result = result->next;
  }
  
  return result; }


# endif //!defined(LL_IMPLEMENTATION) && !defined(DECLARATIONS)
