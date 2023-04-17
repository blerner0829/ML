

#ifndef MAP_H
#define MAP_H
/* Map.h
 *
 * Abstract data type representing a map of key-value pairs with
 * unique keys. A subset of the std::map interface
 * http://www.cplusplus.com/reference/map/map/
 * Project UID db1f506d06d84ab787baf250c265e24e
 *
 * By Andrew DeOrio <awdeorio@umich.edu>
 *    Amir Kamil    <akamil@umich.edu>
 *    James Juett   <jjuett@umich.edu>
 * Updated
 *   2016-11-23
 *
 * DO NOT modify the public interface. Modify anything else you need to.
 */

#include "BinarySearchTree.h"
#include <cassert>  //assert
#include <utility>  //pair

template <typename Key_type, typename Value_type,
          typename Key_compare=std::less<Key_type> // default argument
         >
class Map {

private:
  // Type alias for an element, the combination of a key and mapped
  // value stored in a std::pair.
  // See http://www.cplusplus.com/reference/utility/pair/
  using Pair_type = std::pair<Key_type, Value_type>;
  

  // A custom comparator
/*
  class PairComp {
    public:
      bool operator()(const Pair_type& lhs, const Pair_type& rhs) const {
        if (lhs.second < rhs.second) {
          return true;
        } else if (rhs.second < lhs.second) {
          return false;
        } else {
          // If the keys are equal, compare the values
          return lhs.second < rhs.second;
        }
      }
  };
*/

// What do these specs say about the PairComp functor? https://eecs280staff.github.io/p5-ml/#building-on-the-bst
// The PairComp functor should compare the keys of the pairs, not the values.

//Based on the information above, implement a PairComp functor that compares the keys of the pairs, not the values.
//You can use the PairComp functor from the BinarySearchTree public tests as a starting point.
//You can also use the PairComp functor from the Map public tests as a starting point.

/*
class PairComp {
  private:
    Key_compare key_comp;

  public:
    PairComp() : key_comp() {}

    PairComp(Key_compare kc) : key_comp(kc) {}

    bool operator()(const Pair_type& lhs, const Pair_type& rhs) const {
      return Key_compare(lhs.first, rhs.first);
    }
};
*/
struct PairComp {
    Key_compare less;
    bool operator()(const Pair_type& lhs, const Pair_type& rhs) const {
      return less(lhs.first, rhs.first);
    }
    bool operator()(const Pair_type& lhs, const Key_type& rhs) const {
      return less(lhs.first, rhs);
    }
    bool operator()(const Key_type& lhs, const Pair_type& rhs) const {
      return less(lhs, rhs.first);
    }
  };
/*
  class PairComp {
    public:
      bool operator()(const Pair_type& lhs, const Pair_type& rhs) const {
        return lhs.first < rhs.first;
    }
  };
*/
  BinarySearchTree<Pair_type, PairComp> bst;

public:

  // OVERVIEW: Maps are associative containers that store elements
  // formed by a combination of a key value and a mapped value,
  // following a specific order.
  //
  // NOTE: This Map should be represented using a BinarySearchTree that
  //       stores (key, value) pairs. See Pair_type above. You will
  //       also need to define an appropriate comparator type (PairComp) for the
  //       BinarySearchTree to use in comparing elements, so that they
  //       are compared based on the key stored in the first member of
  //       the pair, rather than the built-in behavior that compares the
  //       both the key and the value stored in first/second of the pair.

  // Type alias for iterator type. It is sufficient to use the Iterator
  // from BinarySearchTree<Pair_type> since it will yield elements of Pair_type
  // in the appropriate order for the Map.
  using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;

  // You should add in a default constructor, destructor, copy
  // constructor, and overloaded assignment operator, if appropriate.
  // If these operations will work correctly without defining them,
  // you should omit them. A user of the class must be able to create,
  // copy, assign, and destroy Maps.

  Map() {
  }
/*
  // Copy constructor
  Map(const Map &other)
    : bst.root(copy_nodes_impl(other.bst.root)) {

    }
*/

// copy ctor
/*
  Map(const Map &other) {
    bst.BinarySearchTree(other);
  }
  */
/*
  Map(const Map &other) {
    bst.root = copy_nodes_impl(other.bst.root);
  }
  */
// assignment operator that Benny wrote
/*
  Map &operator=(const Map &other) {
    if (this == &other) {
      return *this;
    }

    bst(bst.begin());
    bst.root = copy_nodes_impl(other.bst.root);
    return *this;
  }
*/
  Map& operator=(const Map &other) {
  if (this != &other) {
    bst = other.bst;
  }
  return *this;
}
// assignment operator that Josh wrote
/*
  Map &operator=(const BinarySearchTree<Pair_type, PairComp> &rhs) {
    if (this == &rhs) {
      return *this;
    }
    destroy_nodes_impl(bst.root);
    bst.root = copy_nodes_impl(rhs.bst.root);
    return *this;
  }
*/

// another one not sure which works best
  /*
  // Assignment operator
  Map &operator=(const BinarySearchTree<Pair_type, PairComp> &rhs) {
    if (this == &rhs) {
      return *this;
    }

    bst(bst.begin());
    bst.root = copy_nodes_impl(rhs.bst.begin());
    return *this;
  }
*/
  // Destructor
  ~Map() = default;

  // EFFECTS : Returns whether this Map is empty.
  bool empty() const {
    return bst.empty();
  }

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
  size_t size() const{
    return static_cast<size_t>(bst.size());
  }

  // EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  // HINT: Since Map is implemented using a BinarySearchTree that stores
  //       (key, value) pairs, you'll need to construct a dummy value
  //       using "Value_type()".
  Iterator find(const Key_type& k) const {
    return bst.find({k, Value_type()});
  }


  // MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //
  // HINT:     In the case the key was not found, and you must insert a
  //           new element, use the expression {k, Value_type()} to create
  //           that element. This ensures the proper value-initialization is done.
  //
  // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
  // Implement a function using the RME above that encorporates the suggestion on Map_public_test.cpp lines 69-70.

 Value_type& operator[](const Key_type& k) {
    Iterator it = find(k);
    if (it != end()) {
      return it->second;
    }
    std::pair<Iterator, bool> result = insert({k, Value_type()});
    return result.first->second;
 }
 /*
 
  Value_type& operator[](const Key_type& k) {
    Iterator it = find(k);
    if (it != end()) {
      return it->second;
    }
    std::pair<Iterator, bool> result = insert(make_pair(k, Value_type()));
    return result.first->second;
  }
  */


  // MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
  std::pair<Iterator, bool> insert(const Pair_type &val){
    std::pair<Iterator, bool> result;
    if (find(val.first) != end()) {
      result.first = find(val.first);
      result.second = false;
    }
    else {
      result.first = bst.insert(val);
      result.second = true;
    }
    return result;
  }

  // EFFECTS : Returns an iterator to the first key-value pair in this Map.
  Iterator begin() const{
    return bst.begin();
  }

  // EFFECTS : Returns an iterator to "past-the-end".
  Iterator end() const{
    return bst.end();
  }
};

// You may implement member functions below using an "out-of-line" definition
// or you may simply define them "in-line" in the class definition above.
// If you choose to define them "out-of-line", here is an example.
// (Note that we're using K, V, and C as shorthands for Key_type,
// Value_type, and Key_compare, respectively - the compiler doesn't
// mind, and will just match them up by position.)
//    template <typename K, typename V, typename C>
//    typename Map<K, V, C>::Iterator Map<K, V, C>::begin() const {
//      // YOUR IMPLEMENTATION GOES HERE
//    }

#endif // DO NOT REMOVE!!!