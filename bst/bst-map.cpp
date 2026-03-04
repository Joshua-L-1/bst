#include "bst-map.h"

// static data members
template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator        
		CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::end_it        = CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator(nullptr);

template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator_const  
		CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::const_end_it  = CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator_const(nullptr);


//for the node class
template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Node(KEY_TYPE k, VALUE_TYPE val, Node* p, int h, int b, Node* l, Node* r) :
	key(k), value(val), parent(p), height(h), balance(b), left(l), right(r)
{
}

template< typename KEY_TYPE, typename VALUE_TYPE >
KEY_TYPE const& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Key() const {
	return key;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
VALUE_TYPE& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Value() {
	return value;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::Node* CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::first() {
	Node* node = this;
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node* CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::last() {
	Node* node = this;
	while (node->right != nullptr) {
		node = node->right;
	}
	return node;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node* CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::increment() {
	if (this->right != nullptr) {
		return this->last();
	}
	Node* node = this->parent;
	Node* prev = this;
	while (node != nullptr && prev == node->right) {
		prev = node;
		node = node->parent;
	}
	return node;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node* CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::decrement() {
	if (this->left != nullptr) {
		return this->left->last();
	}
	Node* node = this->parent;
	Node* prev = this;
	while (node != nullptr && prev == node->left) {
		prev = node;
		node = node->parent;
	}
	return node;
}

//start of bstmap implementation
//in implementation file 
//method's name and return value have to be fully qualified with
//all required namespace and class names (like CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap)
//but the argument list does not have to be:
//function argument list automatically falls into the method's namespace (Koenig lookup)
template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap(const BSTmap& rhs) : // ....
	pRoot(rhs.pRoot), size_(rhs.size_)
{
    // ...
}

////////////////////////////////////////////////////////////
// typename is used to help compiler to parse
template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::begin() {
	if (pRoot) return BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator(pRoot->first());
	else       return end_it;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap() {

}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE,VALUE_TYPE>& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::operator=(const BSTmap& rhs) {

}

template< typename KEY_TYPE, typename VALUE_TYPE >
VALUE_TYPE& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::operator[](KEY_TYPE const& rhs) {
	// Empty Tree
	if (pRoot == nullptr) {
		size_++;
		pRoot = new Node(key, VALUE_TYPE(), nullptr, 0, 0, nullptr, nullptr);
		return pRoot->value;
	}

	Node* prev = nullptr;
	Node* node = pRoot;

	while (node != nullptr) {
		if (node->key < key) {
			prev = node;
			node = node->right;
		}
		else if (node->key > key) {
			prev = node;
			node = node->left;

		}
		else {
			return node->value;
		}
	}
	size_++;
	node = new Node(key, VALUE_TYPE(), prev, 0, 0, nullptr, nullptr);
	if (prev->key < key)
		prev->right = node;
	else
		prev->left = node;
	return node->value;
}

//bstmap_interator
template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap_iterator::BSTmap_iterator(Node* p = nullptr) :
	p_node(p)
{
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator=(const BSTmap_iterator& rhs) {
	BSTmap_iterator it = rhs;
	return it;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
bool CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator!=(const BSTmap_iterator& rhs) {

}

template< typename KEY_TYPE, typename VALUE_TYPE >
bool CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator==(const BSTmap_iterator& rhs) {

}

//bstmap_interator_const
template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::BSTmap_iterator_const(Node* p = nullptr) :
	p_node(p)
{
}

template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator=(const BSTmap_iterator_const& rhs) {
	
}

template< typename KEY_TYPE, typename VALUE_TYPE >
bool CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator!=(const BSTmap_iterator_const& rhs) {

}

template< typename KEY_TYPE, typename VALUE_TYPE >
bool CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator==(const BSTmap_iterator_const& rhs) {

}

////////////////////////////////////////////////////////////
// do not change this code from here to the end of the file
/* figure out whether node is left or right child or root 
 * used in print_backwards_padded 
 */
template< typename KEY_TYPE, typename VALUE_TYPE >
char CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::getedgesymbol(const Node* node) const {
	const Node* parent = node->parent;
	if ( parent == nullptr) return '-';
	else                 return ( parent->left == node)?'\\':'/';
}

/* this is another "ASCII-graphical" print, but using 
 * iterative function. 
 * Left branch of the tree is at the bottom
 */
template< typename KEY_TYPE, typename VALUE_TYPE >
std::ostream& CS280::operator<<(std::ostream& os, BSTmap<KEY_TYPE,VALUE_TYPE> const& map) {
	map.print(os);
	return os;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
void CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::print(std::ostream& os, bool print_value ) const {
	if (pRoot) {
		BSTmap<KEY_TYPE,VALUE_TYPE>::Node* b = pRoot->last();
		while ( b ) { 
			int depth = getdepth(b);
			int i;
			/* printf(b); */

			char edge = getedgesymbol(b);
			switch (edge) {
				case '-': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key;
                    if ( print_value ) { os << " -> " << b->value; }
                    os << std::endl;
					break;
				case '\\': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << edge << std::endl;
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key;
                    if ( print_value ) { os << " -> " << b->value; }
                    os << std::endl;
					break;
				case '/': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key;
                    if ( print_value ) { os << " -> " << b->value; }
                    os << std::endl;
					for (i=0; i<depth; ++i) std::printf("       ");
					os << edge << std::endl;
					break;
			}
			b = b->decrement();
		}
	}
	std::printf("\n");
}

