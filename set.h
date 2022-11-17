#ifndef SET_H
#define SET_H 
#include <ostream>
#include <cassert>
#include <iterator>
#include <cstddef>


/**
  @brief classe set

  The class implements a generic data set of type T.
  The elements must all be different, the control is
  realised through the negation of the functor which
  given two values a and b, returns true if they are equal.

*/

template<typename T, typename Eql>
class set{

	/**
    @brief node structure
 
    Internal node data structure, used for creating a set.
  	*/
	struct nodo{
		T value; ///< value to store. 
		nodo *next; ///< pointer to the next set node.

		/**
      		Default constructor
      		@post next == nullptr
    	*/
		nodo() : next(nullptr){}

		/**
      	Secondary constructor

      		@param v value to copy
      		@param n pointer to next

      		@post next == n
      		@post value == v
    	*/
		nodo(const T &v, nodo *n)  : value(v), next(n) {}

		/**
      	Secondary constructor

      		@param v value to copy

      		@post value == v
      		@post next == nullptr
    	*/
		explicit nodo(const T &v) : value(v), next(nullptr) {}


		/**
      	Secondary constructor

      		@param n pointer to the next node

      		@post next == n
    	*/
		explicit nodo(nodo *n) : next(n) {}

		
		/**
      	Copy constructor. Copy the data member by member.
      	In this case, being an internal set support structure,
      	I consider data sharing to be correct. 

      		@param other node to copy
    	*/
		nodo(const nodo &other) : value(other.value), next(other.next) {}	//copio i dati membro a membro lasciando la responsabilità alla classe set se usarlo o meno 


		/**
      	Assignment operator. 

      		@param other node to copy
      		@return reference to node this
    	*/
		nodo& operator=(const nodo &other){
			value = other.value; 
			next = other.next; 
			return *this; 
		}


		/**
      	Descructor. 
    	*/
		~nodo() {} //empty destructor because there is no creation of new elements to be managed with the method new

	};





	nodo *_head; ///< pointer to the first set node
	nodo *_tail;  ///< pointer to the last set node
	unsigned int _size; ///< set size
	Eql _equals; ///< functor for the comparison between T data.


public: 


	/**
    Default constructor.

    	@post _head == nullptr
    	@post _tail == nullptr
    	@post _size == 0
  	*/
	set() : _head(nullptr), _tail(nullptr), _size(0) {}



	/**
    Copy constructor

    	@param other set to copy

    	@post _size = other._size
  	*/
	set(const set &other) : _head(nullptr), _tail(nullptr), _size(0){

		nodo *curr = other._head; 
 
		//loop on the nodes of other, adding the value inside this.
	  //The add expecting a new may fail, so I handle
	 	//the possible exception with a try/catch block. 

		try{
			while(curr != nullptr){
				add(curr->value);
				curr = curr->next; 
			}

		}catch(...){

			clear(); 
			throw;
		}
	}
		




	/**
    Assignment operator

    	@param other set to copy

	    @return reference to set this

    	@post _size = other._size
  	*/
	set& operator=(const set &other){ //si da per scontato che i due tipi siano identici

		if(this != &other){
			set tmp(other); 
			std::swap(this->_head, tmp._head); 
			std::swap(this->_tail, tmp._tail);
			std::swap(this->_size, tmp._size);
		}

		return *this;
	}






	/**
    Distructor 

    	@post _head == nullptr
    	@post _tail == nullptr
    	@post _size == 0
  	*/
	~set(){
		clear(); 
	}



  	/**
    Empty the set

    	@post _head == nullptr
    	@post _tail == nullptr
    	@post _size == 0
  	*/
	void clear() {
    	nodo *curr = _head;

    	while (curr!=nullptr) {
      		nodo *cnext = curr->next;
      		delete curr;
      		curr = cnext;
    	}
    	_size = 0;
    	_tail = nullptr;
    	_head = nullptr;
  	}


  	/**
    Entroducing an element to the set mantaining the
    Eql functor condition.

    	@param value valore to entroducing to the set

    	@post _size = _size+1

    	@throw std::bad_alloc possible allocation exception
  	*/
	void add(const T &value){

		nodo *tmp = new nodo(value); 

		if(_size == 0){

			_head = tmp; 
			_tail = tmp; 
			_size = 1; 
			return; 
		}

		nodo *curr = _head; 
		int count =0;

		for(unsigned int i = 0; i<_size; ++i){
			if(!_equals(tmp->value, curr->value))
				count++; 

			curr = curr->next; 
		}

		//if count and size are equal, it means that there 
		//are no nodes with the same value to add, I add the 
		//value in the queue.
		
		if(count==_size){

			//Insertion at the end of the set
			_tail->next = tmp;
    		_tail = tmp;
    		_size++;
		}else{
			delete tmp; 
		}
	}


 	/**
    Removing an element to the set mantaining the
    Eql functor condition.

    	@param value value to remove from the set

    	@post _size = _size-1

  	*/
	void remove(const T &value){

		if(_size == 0)
			return; 

		nodo *curr = _head; 

		if((_size == 1) && (_equals(value, curr->value))) {

			delete curr;
			_head = nullptr; 
			_tail = nullptr; 
			_size--;
			return; 
		}

		nodo *prev = _head; 

		while(curr != nullptr){

			if(_equals(value, curr->value)){

				if(curr == _head){
					_head = curr->next; 
					delete curr;
					curr = nullptr;
					_size--;
					return; 
				}

				if(curr == _tail){
					prev->next = nullptr; 
					_tail = prev; 
					delete curr; 
					curr = nullptr;
					_size--;
					return; 
				}

				prev->next = curr->next; 
				delete curr; 
				curr = prev->next; 
				_size--;		
				return; 
				
			}else{

				prev = curr; 
				curr = curr->next; 
			}
		}
	}

	/**
	 Returns the set size 

	 @return _size 

	 */

	unsigned int size() const {
		return _size; 
	}



	/** 
	  	Constructor that creates a set filled with data taken
	  	from a sequence identified by a start iterator and an 
	  	end iterator. Iterators may be of any type. 

	  	@param b iterator of beginning of sequence 
	  	@param e iterator of ending of sequence

	  	@throw std::bad_alloc possible allocation exception
	  
	 */

	template <typename Q>
	set(Q b, Q e) : _head(nullptr), _size(0), _tail(nullptr) {

		try{

			for(; b!= e; ++b)
				add(static_cast<T>(*b)); 

		}catch(...){

			clear(); 
			throw; 
		}
		
	}


	/**
	 Global function which implement the stream operator.
	 The function is templated on the set and is friend 
	 because it goes to access the set's private data.

	 @param os output stream
	 @param ol ordered_list to be sent on the stream

	 @return output stream
	  
	  */


	friend std::ostream &operator<<(std::ostream &os, const set &s){

		nodo *curr = s._head; 
		while(curr != nullptr){
			os << curr->value << " "; 
			curr = curr->next;  
		}

		return os; 
	}


	/**
	 Function allowing read-only access to the i-th 
	 element via the [] operator. 

	

	 @param element position index to be extracted 

	 @return value at the i-th position
	  
	 */

	const T &operator[](unsigned int indice) const {

		assert(indice < _size); 

		nodo *curr = _head; 

		for(unsigned int i=0; i<indice; ++i){
			curr = curr->next; 
		}

		return curr->value; 

	}



	/**
	 Equality operator
	 Function which returns true if the input set contains 
	 the same value of set this.

	 @param b source set

	 @return bool 
	 */
	bool operator==(const set &b) const {

		if(this->_size != b._size)
			return false; 

		nodo *curr = _head; 


		for(unsigned int i=0; i< b._size; ++i){

			bool contr = true; 

			nodo *control = b._head; 


			for(unsigned int j=0; j<b._size; ++j){

				if(_equals(curr->value, control->value))
					contr = false; 

				control = control->next;  
			}

			if(contr)
				return false; 

			curr = curr->next; 
		} 

		return true; 
	}


	/**
	 	Iterators, iterate over the data entered in the main class.
	 	Since the set class uses data of type T, one must iterate 
	 	over this type of data. 
	*/

		class const_iterator {

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : ptr(nullptr){}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr) {}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr; 
			return *this; 
		}

		~const_iterator() {}

		// Returns the data reported by the iterator (dereferencing)
		reference operator*() const {
			return ptr->value;
		}

		// Returns the pointer to the datum referred to by the iterator
		pointer operator->() const {
			return &(ptr->value); 
		}
		
		// Post-increment iteration operator
		const_iterator operator++(int) {
			const_iterator tmp(*this); 
			ptr = ptr->next; 
			return tmp; 
		}

		// Pre-increment iteration operator
		const_iterator& operator++() {
			ptr = ptr->next; 
			return *this;
		}

		// Equality
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr); 
		}
		
		// Diversity
		bool operator!=(const const_iterator &other) const {
			return !(other == *this); 
		}

	private:
		//Member data

		// The container class must be placed friend of the iterator 
		// in order to use the initialisation constructor.
		friend class set; 

		// Private initialisation constructor used by the container 
		// class typically in the begin and end methods
		const_iterator(const nodo *p) : ptr(p) {}

		const nodo *ptr; 
		
		
	}; // const_iterator class
	
	// Returns the iterator at the beginning of the data sequence
	const_iterator begin() const {
		return const_iterator(_head);
	}
	
	// Returns the iterator at the end of the data sequence 
	const_iterator end() const {
		return const_iterator(nullptr);
	}

};




/**
	Global function returning a generic set with the
	elements of the set passed as a parameter that 
	satisfies the generic predicate of type P.

	@param s source set
	@param pred predicate

	@return s1 copy of the resulting set  
*/

template <typename T, typename Eql, typename P>	
set<T,Eql> filter_out(const set<T, Eql> &s, P pred){

	set<T,Eql> s1;

	typename set<T,Eql>::const_iterator b, e; 

	try{
		for(b = s.begin(), e=s.end(); b != e; ++b ){
			if(pred(*b))
				s1.add(*b); 
		}

	}catch(...){
		s1.clear(); 
		throw; 
	}

	return s1;
}


/**
 	Concatenation of sets
	Global function that returns a generic set filled with
	the elements of the first and second set passed as a parameter. 

	@param a first source set
	@param b second source set
  
  @return s1 copy of the resulting set 
  
 */
template<typename T, typename Eql> 
set<T,Eql> operator+(const set<T,Eql> &a, const set<T,Eql> &b) {

	set<T,Eql> s1; 

	typename set<T,Eql>::const_iterator ba, ea, bb, eb;  


	try{
		for(ba = a.begin(), ea=a.end(); ba != ea; ++ba ){
			
			s1.add(*ba); 
		}

		for(bb = b.begin(), eb=b.end(); bb != eb; ++bb ){
			
			s1.add(*bb); 
		}

	}catch(...){
		s1.clear(); 
		throw; 
	}
	
	return s1;
	
}




/**
 	Intersection of sets
 	Global function that returns a generic set filled with the 
 	common elements of the two sets passed as a parameter. 

 	@param a first source set
	@param b second source set

	@return s1 copy of the resulting set
  
  
  */
template<typename T, typename Eql> 
set<T,Eql> operator-(const set<T,Eql> &a, const set<T,Eql> &b) {

	set<T,Eql> s1; 

	typename set<T,Eql>::const_iterator ba, ea, bb, eb;

	try{

		for(ba = a.begin(), ea=a.end(); ba != ea; ++ba ){
			for(bb = b.begin(), eb=b.end(); bb != eb; ++bb ){

				if(*ba == *bb)
					s1.add(*ba);
			}
		}


	}catch(...){
		s1.clear(); 
		throw; 
	}

	
	return s1; 

}


#endif
