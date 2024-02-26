/***
 * student-sort.h:  check that students have used their own sort 
 * implementation and not std::sort
 */

#include <algorithm>

#ifndef SORTING_STUDENT_SORT_H
#define SORTING_STUDENT_SORT_H

struct student_sort_object {
    student_sort_object() { _x = -1; }
    student_sort_object(int x) { _x = x; }
    bool operator<(const student_sort_object& b) const { return _x < b._x; }
    bool operator>(const student_sort_object& b) const { return _x > b._x; }
    bool operator==(const student_sort_object& b) const { return _x == b._x; }
    int _x;
	static bool student_sort_passed;
};

bool  student_sort_object::student_sort_passed = true;

void set_student_sort_failure( const char* const n ) 
{ 
	/***
	 * No, this output is not buggy.  Turns out on at least one common CPP library distribution
	 * all four sorting routines lead to standard sort.
	 */
	std::cerr << std::endl;
	std::cerr << "Please don't use std::"<< n << " or it's variants to satisfy this project's sorting requirements." << std::endl;
	std::cerr << "Implement merge sort as specified in the project write-up." << std::endl << std::endl;
	student_sort_object::student_sort_passed = false; 
}

namespace std {
/***
 * template specializations
 * we don't need to provide constexpr (return value) specializations for sort because
 * since we invoke it from the SneakyStudentSort TEST we know the arguments on not themselves
 * constexpr.
 */

#define SNORT(ce,funcname) template<> \
	                    ce void funcname( vector<student_sort_object>::iterator, \
								vector<student_sort_object>::iterator ) \
						{ set_student_sort_failure( #funcname ); }

#define SNORTExc(funcname) template<class ExcPolicy> \
	                    void funcname( ExcPolicy&&, vector<student_sort_object>::iterator, \
								vector<student_sort_object>::iterator ) \
						{ set_student_sort_failure( #funcname ); }

#define SNORTCmp(ce,funcname) template<class Compare> \
	                    ce void funcname( vector<student_sort_object>::iterator, \
								vector<student_sort_object>::iterator, Compare ) \
						{ set_student_sort_failure( #funcname ); }

#define SNORTExcCmp(funcname) template<class ExcPolicy, class Compare> \
	                    void funcname( ExcPolicy&&, vector<student_sort_object>::iterator, \
								vector<student_sort_object>::iterator, Compare ) \
						{ set_student_sort_failure( #funcname ); }

/*** std::sort, std::partial_sort and partial_copy_sort ***/
#if __cplusplus < 202000L
// until C++ 20
#define SN_CONSTEXPR
#else
// since C++ 20
#define SN_CONSTEXPR constexpr
#endif

SNORT(SN_CONSTEXPR,sort)
SNORTCmp(SN_CONSTEXPR,sort)

template<>
SN_CONSTEXPR void partial_sort( vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator )
{ set_student_sort_failure( "partial_sort" ); }

template<class Compare>
SN_CONSTEXPR void partial_sort( vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator, Compare )
{ set_student_sort_failure( "partial_sort" ); }

template< class InputIt >
SN_CONSTEXPR vector<student_sort_object>::iterator partial_sort_copy( InputIt, 
		vector<student_sort_object>::iterator r, vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator )
{ set_student_sort_failure( "partial_copy_sort" ); return r; }

template< class InputIt, class Compare >
SN_CONSTEXPR vector<student_sort_object>::iterator partial_sort_copy( InputIt, 
		vector<student_sort_object>::iterator r, vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator, Compare )
{ set_student_sort_failure( "partial_copy_sort" ); return r; }


#if __cplusplus >= 201700L
// since C++ 17
SNORTExc(sort)
SNORTExcCmp(sort)

template< class ExcPolicy>
SN_CONSTEXPR void partial_sort( ExcPolicy&&, vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator )
{ set_student_sort_failure("partial_sort"); }

template< class ExcPolicy, class Compare>
SN_CONSTEXPR void partial_sort( ExcPolicy&&, vector<student_sort_object>::iterator,
		vector<student_sort_object>::iterator, vector<student_sort_object>::iterator, Compare )
{ set_student_sort_failure("partial_sort"); }


template< class ExcPolicy, class ForwardIt>
vector<student_sort_object>::iterator partial_sort_copy( ExcPolicy&& policy, 
		ForwardIt first, ForwardIt last,
		vector<student_sort_object>::iterator r, vector<student_sort_object>::iterator )
{ set_student_sort_failure("partial_copy_sort"); return r; }

template< class ExcPolicy, class ForwardIt, class Compare>
vector<student_sort_object>::iterator partial_sort_copy( ExcPolicy&& policy, 
		ForwardIt first, ForwardIt last,
		vector<student_sort_object>::iterator r, vector<student_sort_object>::iterator, Compare )
{ set_student_sort_failure("partial_copy_sort"); return r; }

#endif
#undef SN_CONSTEXPR


/*** std::stable_sort partitions on C++26 ***/
#if __cplusplus < 202600L
// until C++ 26
#define SN_CONSTEXPR
#else
// since C++ 26
#define SN_CONSTEXPR constexpr
#endif

SNORT(SN_CONSTEXPR,stable_sort)
SNORTCmp(SN_CONSTEXPR,stable_sort)

#if __cplusplus >= 201700L

// since C++ 17
SNORTExc(stable_sort)
SNORTExcCmp(stable_sort)

#endif
#undef SN_CONSTEXPR

} // namespace
 
TEST(SorterTest, SneakyStudentSort) {
	std::vector<student_sort_object> sorted(LARGE_SET_SIZE);
	// use a large vector because students may have hand coded
	// easier algorithms (bubble, insertion, for small vectors)
    for (int i = 0; i < LARGE_SET_SIZE; i++) {
        sorted.push_back(student_sort_object(i));
    }
	std::vector<student_sort_object> reversed( sorted );
	std::reverse( reversed.begin(), reversed.end() );
	// reset flag, its a global variable that students code could just as easily reach out and 
	// modify, so we need to not only be sure it remains true but also that the out of order vector
	// is in fact now ordered.
	student_sort_object::student_sort_passed = true;
    sorter(reversed, 3);
    ASSERT_TRUE(student_sort_object::student_sort_passed);
    ASSERT_TRUE(std::is_sorted(reversed.begin(), reversed.end()));
}

#endif
