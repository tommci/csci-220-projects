/**
 *  Defines template a specialization for std::vector which raises on compiler error on use
 *      authors     Anastasia Sokol
 * 
 *  TODO:
 *      this is a really poor way to communicate to students the class' expectations
 *      ideally this would fail as a regular test, and not as a compiler error
 *
 *      making things worse, it doesn't appear that static_assert will selectively fire
 *      _only_ when a template is instantiated.  at least not on clang 15. -- khellman
**/

#include <vector>
#include <list>
#include <array>
#include <map>
#include <string>

#ifndef SNEAKY_PREVENT_STD_CONTAINERS_H
#define SNEAKY_PREVENT_STD_CONTAINERS_H

class sneaky_t{};
//enum class specialization_test_type : std::size_t {};
template <class _> struct sneaky_false_t: std::false_type {};

namespace std {

// don't use std::format, requires C++20
// can't use static_assert as seems to fire whether the candidate stack creates
// a vector<sneaky_t> or not...
// #define SNEAKY_STATIC_ASSERT  static_assert(sneaky_false_t<sneaky_t>::value, "static-assert triggered" );
#define SNEAKY_STATIC_ASSERT
#define MSG(name) "\nCSCI220: Please avoid using the std::" #name " in your stack implementation.\n"
#define SNEAKY(name) template <> class name <sneaky_t> { SNEAKY_STATIC_ASSERT };
#define SNEAKY1(name,ty1,id1) template <ty1 id1 > \
	                          class name <sneaky_t, id1> { SNEAKY_STATIC_ASSERT };
#define SNEAKY3(name,ty1,id1,ty2,id2,ty3,id3) template <ty1 id1, ty2 id2, ty3, id3 > \
	                          class name <sneaky_t, id1, id2, id3> { SNEAKY_STATIC_ASSERT };
#define SNEAKYMAP(key_t) template <class Compare, class Allocator > \
                              class map <key_t, sneaky_t, Compare, Allocator > { SNEAKY_STATIC_ASSERT };

SNEAKY1(vector,class,Allocator)
SNEAKY1(list,class,Allocator)
SNEAKY1(array,size_t,size)

SNEAKYMAP(int)
SNEAKYMAP(unsigned)
SNEAKYMAP(long)
SNEAKYMAP(long long)
SNEAKYMAP(unsigned long )
SNEAKYMAP(unsigned long long)
SNEAKYMAP(float)
SNEAKYMAP(double)
SNEAKYMAP(std::string)
// macros rock :)


#undef SNEAKY_STATIC_ASSERT
#undef MSG
#undef SNEAKY
#undef SNEAKY1
#undef SNEAKYMAP
} // end namespace std
 
 
TEST(ProjectRequirements, PreventStdContainers) {
	/***
	 * This will not compile if a student is using a std:: container (vector, array)
	 * as the backing store for their Stack class.
	 ****
	 * Students:  if you're getting caught by this test it is most likely an issue
	 * with your stack.h implementation.    Double check the project write-up, we require
	 * that you use generic simple arrays allocated with new[] and freed with delete[]
	 * in your Stack implementation
	 ***/
    // create stack with specialized type 
    stack<sneaky_t> stack;

	// perform some i/o with the stack to trigger compile errors
	/** we could also change the template defs to have a private default ctor,
	 *  but that just obfuscates already non-trivial code...
	 **/
	stack.push( sneaky_t() );
	stack.push( sneaky_t() );
	stack.pop( );
	stack.pop( );
	   
    // if it compiles, the test passes
    ASSERT_TRUE(true);
}

#endif
