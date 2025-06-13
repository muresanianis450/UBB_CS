# 📚 SortedMultiMap – Binary Search Tree Implementation

This project implements an **Abstract Data Type (ADT)** called `SortedMultiMap` using a **Binary Search Tree (BST)** with a custom, array-based representation.  
Each key can be associated with **multiple values**, and all keys are maintained in sorted order according to a given **relation function**.

An `SMMIterator` class enables in-order traversal of the structure.

---

## 📁 Project Structure
```
├── SortedMultiMap.h / .cpp # Main multimap implementation
├── SMMIterator.h / .cpp # Iterator for in-order traversal
├── Main.cpp (optional) # Test/demo file
└── README.md # Project documentation
```

---

## ⚙️ Functionalities

### `SortedMultiMap` Methods

- `void add(TKey key, TValue value)`  
  ➤ Adds a key-value pair to the multimap.

- `bool remove(TKey key, TValue value)`  
  ➤ Removes a specific value associated with the key. Deletes the node if no values remain.

- `vector<TValue> search(TKey key) const`  
  ➤ Returns all values associated with a given key.

- `int size() const`  
  ➤ Returns the number of key-value pairs in the map.

- `bool isEmpty() const`  
  ➤ Checks whether the map is empty.

- `SMMIterator iterator() const`  
  ➤ Returns an iterator that enables in-order traversal.

---

## 🔁 `SMMIterator` Capabilities

- In-order traversal using an **explicit stack** (implemented via array).
- Supports **multiple values per key**.
- Methods:
    - `void first()` – Goes to the smallest key in the map.
    - `void next()` – Advances to the next key-value pair.
    - `bool valid() const` – Checks whether the iterator is in a valid state.
    - `TElem getCurrent() const` – Returns the current `(key, value)` pair.

---

## 🧠 Time Complexities Summary

| Operation            | Best Case | Average Case    | Worst Case | Total Complexity |
|----------------------|-----------|-----------------|------------|------------------|
| `add`                | 0(1)      | 0(log n)        | 0(n)       | O(n)             |
| `remove`             | 0(1)      | 0( log(n + m) ) | 0(n + m)   | O(h + m)         |
| `search`             | 0(1)      | 0(log n)        | 0(n)       | O(n)             |
| `iterator::next`     | O(1)      | 0(1)            | 0(n)       | O(n)             |
| `iterator::first`    | 0(1)      | 0(log n)        | 0(n)       | O(n)             |

> 'h' = height of the tree,
> `n` = number of nodes (keys),  
> `m` = number of values for a key.

---

## 🛠️ Notes

- The tree is **not self-balancing**, so performance degrades if data is inserted in sorted order.
- Memory is **manually managed**, and dynamic resizing is implemented.

---

## ✅ Status

✅ Core functionality implemented  
✅ Iterator supports all traversal features  
✅ Memory safe (manual cleanup implemented in destructor)

---