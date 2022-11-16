#include <iostream>
#include "set.h"


/**
 Integer type equality functor

 @brief Integer type equality functor
 */
struct int_equal{
  bool operator()(int a, int b) const{
    return a == b; 
  }
}; 


/**
 Predicate functor, returns true if the passed value is even

 @brief Predicate functor
  
 */
struct is_even{
	bool operator()(int a){
		return (a%2==0); 
	}
};

/**
 Predicate functor, returns true if the value passed is greater than 10.

 @brief Predicate functor
 */

struct is_greater_than_10{
	bool operator()(int a){
		return a > 10; 
	}
}; 




/**
 Fundamental Methods Test

 @brief Fundamental Methods Test

 */
void fundamental_methods_test(){ 

	std::cout << "************* Fundamental tests of an integer set *************" << std::endl;

	//constructor test
	set<int, int_equal> s; 
	
	//add test

	s.add(0); 
	s.add(1); 
	s.add(20); 
	s.add(5); 
	s.add(11); 
	s.add(20); 

	

	std::cout << "Printing of s after insertions: " << std::endl;
	std::cout << s << std::endl; 

	//remove test 
		s.remove(0); 
		s.remove(11); 

	std::cout << "Printing of s after removals: " << std::endl;
	std::cout << s << std::endl; 

	//copy constructor test
	set<int, int_equal> s1(s); 
	std::cout << "Printing of s1 after copy constructor: " << std::endl;
	std::cout<<s1 << std::endl; 

	//allocation test 
	set<int ,int_equal> s2; 
	
	s2 = s; 

	std::cout << "Printing s2 after allocations with s: " << std::endl;
	std::cout << s2 << std::endl; 

	
}


/** 
 Use test of the set

 @brief Use test of the set
  
  */

void use_test(){

	std::cout << "************* Use test of an integer set *************"  << std::endl;


	int data[5]={20,4,56,202,44}; 

	set<int, int_equal> ss(data, data+5); 
	std::cout <<"Printing s3 after secondary constructor "<< std::endl;
	std::cout << ss << std::endl; 

	std::cout <<"ss dimension"<< std::endl;
	std::cout << ss.size() << std::endl; 

	std::cout << "Operator[] test, checked with an assert" << std::endl; 
	bool contr = (ss[0] == 20);
	assert(contr == true);  

	std::cout << "Operator== test between 2 set, checked with an assert" << std::endl; 
	set<int, int_equal> spp = ss; 
	ss.add(999); 
	bool contr2 = (ss == spp); 
	assert(contr2  == false); 
	

}

/**
 Testing the filter_out function

 @brief Testing the filter_out function
 */
	
void test_filter_out(){
	int data[5] = {3,10,6,7,76}; 

	set<int, int_equal> s3(data, data+5); 
	std::cout << "************* Testing the filter_out function *************" << std::endl;
	std::cout << "Printing with operator<<" << std::endl;
	std::cout << s3 << std::endl;

	is_even ie;
	std::cout << "filter_out call, is_even" << std::endl;
	std::cout << filter_out(s3,ie) << std::endl; 

	is_greater_than_10 igt; 
	std::cout << "filter_out call, is_greater_than_10" << std::endl;
	std::cout << filter_out(s3,igt) << std::endl; 


}

/**
 Testing the operator+ function

 @brief Testing the operator+ function
 */
	
void test_operator_plus(){
	int data1[5] = {1,2,3,4,5}; 
	int data2[10] = {1,2,3,4,5,6,7,8,9,10};

	set<int, int_equal> s10(data1, data1+5);
	set<int, int_equal> s11(data2, data2+10);
	set<int,int_equal> sum; 
	sum = s10+s11; 

	std::cout << "************* Testing the operator+ function *************" << std::endl;
	std::cout << "Printing with operator<<" << std::endl;
	std::cout << sum << std::endl;


}


/**
 Testing the operator- function

 @brief Testing the operator- function

 */

void test_operator_minus(){

	int data3[5] = {1,2,3,4,5}; 
	int data4[10] = {1,2,3,4,5,6,7,8,9,10};

	set<int, int_equal> s20(data3, data3+5);
	set<int, int_equal> s21(data4, data4+10);
	set<int,int_equal> minus; 
	minus = s20-s21; 

	std::cout << "************* Testing the operator- function *************" << std::endl;
	std::cout << "Printing with operator<<" << std::endl;
	std::cout << minus << std::endl;

}


/**
 Usage test on a non-constant set passed as a parameter

 @brief Usage test of the non-constant set

 @param s set to be used for testing 

 */

void test_set_int(set<int,int_equal> s){
	std::cout << "************* Test sul set di interi *************" << std::endl;

	std::cout<<"Entering values: 20, 48, 1000, 3, 198" << std::endl; 

	s.add(20); 
	s.add(48); 
	s.add(1000); 
	s.add(3); 
	s.add(198); 

	std::cout<<"Printing with operator<<" << std::endl; 
	std::cout<< s << std::endl; 

	std::cout<<"Set size: " << s.size() << std::endl; 

	std::cout<<"Printing with iterator" << std::endl;

	set<int,int_equal>::const_iterator i,ie; 

	for(i=s.begin(), ie=s.end(); i != ie; ++i)
	std::cout<<*i<<std::endl; 

	s.clear(); 
	std::cout<<"List size after clear() function: "<< s.size() << std::endl;

}


/**
 Usage test on a constant set passed as a parameter

 @brief Usage test of the constant set

 @param s set to be used for testing  

 */

void test_const_set_int(const set<int,int_equal> s){

		std::cout << "************* Const integer set test *************" << std::endl;

		//add non è chiamabile su un oggetto const

		std::cout<< "Printing with operator<<" << std::endl; 
		std::cout<< s << std::endl; 

		std::cout<< "List size: " << s.size() <<std::endl;

		std::cout<<"Printing with iterator" << std::endl; 

		set<int,int_equal>::const_iterator i,ie; 

		for(i=s.begin(), ie=s.end(); i!=ie; ++i) 
			std::cout<<*i<<std::endl; 

		//clear cannot be called on a const object


}

//---------------------------------------------------------------------------------------------------------------------

/**
 Functor for string equality. 

 @brief Functor for string equality. 
 */

struct equal_string{
	bool operator()(const std::string &a, const std::string &b) const{
		return (a==b); 
	}
}; 


/**
 Test of instantiated set on strings

 @brief Test of instantiated set on strings

 */

void test_set_of_stringhe(){

	std::cout << "************* String set test *************" << std::endl;

	set<std::string, equal_string> ss; 

	std::cout << "Entering values 'pippo', 'pluto', 'paperino', 'cip' " << std::endl;
	ss.add("pippo");
	ss.add("pluto"); 
	ss.add("paperino"); 
	ss.add("cip");
	ss.add("cip"); 

	std::cout<<"Printing with operator<<" << std::endl; 
	std::cout<< ss << std::endl; 

	std::cout<<"Set size: "<< ss.size() << std::endl; 

	std::cout<<"Operator[] in position 1 ('pluto') ==> " << ss[1] <<  std::endl;

	std::cout<<"Created a new set ssc with the copyconstructor on ss" << std::endl;
	set<std::string, equal_string> ssc(ss);   

	std::cout<<"Checked with an assert if ss == ssc" << std::endl; 
	assert(ss==ssc); 

}

//------------------------------------------------------------------------------------------------------------------

/**
 Struct point implementing a 2D point.

 @brief Struct point implementing a 2D point.
 */
struct point{
	int x; ///< x-coordinate of point
	int y; ///< y-coordinate of point

	point(int xx, int yy) : x(xx), y(yy) {}

	bool operator== (const point &p) const{
		return (this->x == p.x && this->y == p.y); 
	}
};

/**
 Redefinition of the stream << operator for a point. 
 Necessary for the stream operator of the set class. 

 */ 

std::ostream &operator<<(std::ostream &os, const point &p) {
	 std::cout<<"("<<p.x<<","<<p.y<<")";
	 return os;  
}


/**
 Functor for the comparison of equality between two points. 
 Return true if p1.x != p2.x. 

 @brief Functor comparison of two points
 */

struct equal_point {
	bool operator()(const point &p1, const point &p2) const {
		return (p1.x == p2.x) && (p1.y == p2.y); 
	}
}; 


/**
 	Predicate functor, returns true if the co-ordinates of the point passed both exceed the value 5.

 	@brief Predicate functor 
 */ 

struct is_greater_than_5_5{
	bool operator()(const point &p){
		return p.x > 5 && p.y>5; 
	}
};



/**
 Test of instantiated set on point objects

 @brief Test of instantiated set on point objects
 */ 

void test_set_of_point(){

	set<point, equal_point> sp; 

	std::cout << "************* Point set test *************" << std::endl;

	std::cout << "Entering values (1,1), (6,9), (3,0), (0,0), (4,0)" << std::endl;
	sp.add(point(1,1)); 
	sp.add(point(6,9)); 
	sp.add(point(3,0)); 
	sp.add(point(0,0)); 
	sp.add(point(4,0));
	sp.add(point(4,0));

	std::cout << "Removing the value (4,0)" << std::endl;
	sp.remove(point(4,0)); 

	std::cout << "Printing with operator<<" << std::endl;
	std::cout << sp << std::endl; 

	std::cout << "Set size: "<< sp.size() << std::endl; 

	std::cout << "Printing with iterator" << std::endl;

	set<point, equal_point>::const_iterator i,ie; 

	for(i=sp.begin(), ie=sp.end(); i!=ie; ++i)
		std::cout<<*i<<std::endl; 

	std::cout<<"Operator[] in position 0 ((1,1)) ==> " << sp[0] <<  std::endl;

	std::cout<<"Created a new set spc with the copyconstructor on sp" << std::endl;
	set<point, equal_point> spc(sp);   

	std::cout<<"Checked with an assert if sp == spc" << std::endl; 
	assert(sp==spc); 

	std::cout<<"I create a new set ssp for testing the other operators" << std::endl;
	set<point, equal_point> ssp; 
	ssp.add(point(1,0)); 
	ssp.add(point(0,0));

	std::cout<<"Printing of ssp after creation and addition of the elements: (1,0) and (0,0): " << std::endl; 
	std::cout<< ssp << std::endl; 


	std::cout << "Test operator+ between sp and ssp" << std::endl; 
	std::cout << ssp + sp << std::endl; 

	std::cout<<"Test operator- between sp and ssp" << std::endl; 
	std::cout << ssp - sp << std::endl; 

	is_greater_than_5_5 ig; 
	std::cout<<"filter_out function test is_greater_than_5_5" << std::endl; 
	std::cout << filter_out(sp,ig)<< std::endl; 


}


int main(){

	fundamental_methods_test(); 

	use_test(); 

	test_filter_out(); 

	test_operator_plus(); 

	test_operator_minus(); 

	set<int,int_equal> s; 

	test_set_int(s); 

	test_const_set_int(s); 

	test_set_of_stringhe(); 

	test_set_of_point(); 


	return 0; 
}