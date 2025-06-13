# SortedMultiMap – C++ Implementation using Coalesced Hashing

## 📘 Assignment Description

This project implements the **SortedMultiMap** Abstract Data Type (ADT) in C++ using a **hash table** with **coalesced chaining** for collision resolution. The implementation adheres strictly to the following constraints and specifications:

- **No use of STL containers or data structures** (except `std::vector` **only as a return type**).
- **No separate class** for the hash table or any underlying structure.
- The container must be implemented **directly and from scratch**.
- The hash table must be **dynamic**:
    - A load factor threshold **α** must be maintained.
    - The table should **resize and rehash** once the actual load factor exceeds α.

---

## 🧩 Data Structure Overview

### 🔗 Coalesced Hashing
- Combines **open addressing** and **separate chaining**.
- Collisions are resolved by placing the new element in the first available position and linking it logically to the chain of collided elements.

### 🗃️ Container Representation
- **Keys are unique**.
- Each key is associated with a **dynamic array** (custom implemented) that holds **multiple values**.
- The hash table holds `<key, dynamic array of values>` pairs.

---

## 🔁 Iteration

The `SortedMultiMapIterator` is constructed by:

1. Creating a **temporary array** of `<key, value_array>` pairs.
2. Sorting it based on the **relation (order)** defined.
3. Iterating over this sorted array.

---

## 🚫 Restrictions

- **Do not** use:
    - `std::map`, `std::unordered_map`, `std::list`, or any other STL containers.
    - Any data structure from third-party libraries.
- **Only** `std::vector` is allowed, and **only** to return results (not for internal representation).

---

## 📈 Features

- Insert key-value pairs into the sorted multi-map.
- Remove a specific key-value pair.
- Search for all values associated with a given key.
- Dynamic resizing and rehashing based on the load factor α.
- Sorted iteration over key-value pairs.