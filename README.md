# BiList<T> — Template Doubly Linked List

An implementation of a doubly linked list template supporting any data type.

## Features

- Template class `BiList<T>`  
- Proper memory management (no leaks)  
- Supports common operations: insertion, removal, search  
- Forward and backward traversal  
- Insertion and copying of sublists  
- Sorting via selection sort algorithm  

## Methods

| Method                                         | Description                                             |
|------------------------------------------------|---------------------------------------------------------|
| `BiList()`                                     | Constructor, creates an empty list                       |
| `~BiList()`                                    | Destructor, clears the list and frees memory            |
| `void clear()`                                 | Clears the entire list                                   |
| `BiNode<T>* get_back()`                        | Returns a pointer to the last node                       |
| `BiNode<T>* get_front()`                       | Returns a pointer to the first node                      |
| `void push_back(T x)`                          | Adds an element to the end of the list                   |
| `void push_front(T x)`                         | Adds an element to the front of the list                 |
| `void insert(T x, BiNode<T>* node)`            | Inserts a new element before the specified node          |
| `void insert(BiNode<T>* node, T x)`            | Inserts a new element after the specified node           |
| `void remove(BiNode<T>* node)`                  | Removes the specified node                               |
| `void forward_view()`                          | Prints the list from front to back                       |
| `void reverse_view()`                          | Prints the list from back to front                       |
| `BiNode<T>* find(T key)`                       | Finds and returns the node containing the given value    |
| `void slice_in(BiNode<T>* node, int index)`     | Inserts a copy of another list after the given index     |
| `void slice_out(BiNode<T>* node, int index1, int index2)` | Copies a sublist from this list and appends it to another list |
| `void swap(BiNode<T>* n1, BiNode<T>* n2)`       | Swaps the data of two nodes                              |
| `void sort()`                                  | Sorts the list in ascending order using selection sort  |

## Usage Example

```cpp
BiList<int> list;
list.push_back(10);
list.push_front(5);
auto node = list.find(10);
list.insert(node, 7);    // Insert 7 after 10
list.forward_view();     // Output: 5 10 7
list.sort();
list.reverse_view();     // Outputs the sorted list in reverse order
