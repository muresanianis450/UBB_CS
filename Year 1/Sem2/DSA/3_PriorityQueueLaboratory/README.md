# 🎉 Priority Queue using DLLA in C++ 🎉

## 📚 Project Requirements

This assignment involves implementing a **Priority Queue (PQ)** as an **Abstract Data Type (ADT)** in C++.  
Your implementation must follow these guidelines:

---

## 🧩 Functionality

- Implement a **Priority Queue** that stores **(element, priority)** pairs.
- Elements must be kept **ordered according to a given relation** between their priorities.
- The relation is provided and determines the queue's behavior (e.g., min-heap or max-heap style).

---

## 🧱 Data Structure: DLLA (Doubly Linked List on Array)

- Use a **DLLA** (Doubly Linked List on Array) as your underlying structure.
- Each node must store:
    - The `element` (value)
    - The `priority`
    - `next` and `prev` indices (no pointers allowed!)

---

## 🚫 Restrictions

- ❌ **Do not use STL containers** like `vector`, `list`, `deque`, etc.
- ✅ You **may only** use STL containers as a **return type** for the `search` operation, if implementing a `Multimap` or `SortedMultiMap`.

---

## 🎯 Operations to Implement

- `push(element, priority)` – Add an element to the queue based on priority.
- `top()` – Return the element with the highest (or lowest) priority based on the relation.
- `pop()` – Remove the top-priority element.
- `isEmpty()` – Check if the queue is empty.

---

## 🧪 Bonus Points

- Add **tests** to demonstrate the correctness of your implementation.
- Make sure to **handle edge cases** like:
    - Adding/removing from an empty queue
    - Inserting multiple elements with the same priority

---

## 🤖 Notes

- Make sure to write **clean, readable code** 🧼
- Include **comments** for clarity 📝
- Follow a **modular design** – separate header and implementation files 📁

---

## 🎨 Have Fun!

This project is a great opportunity to:
- Learn how to manually manage memory 💡
- Understand how linked data structures work behind the scenes 🔍
- Practice abstract thinking with ADTs 🧠

> Good luck, and happy coding! 🌈👩‍💻👨‍💻
