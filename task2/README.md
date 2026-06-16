# CPU Pipeline Memory Hierarchy Simulator

## Overview

The **CPU Pipeline Memory Hierarchy Simulator** is designed to demonstrate how modern processors interact with multi-level memory systems. The project simulates task execution, cache management, memory access latency, and FIFO-based cache replacement policies.

The simulator provides a simplified yet realistic representation of how CPUs improve performance through hierarchical memory structures such as L1, L2, and L3 caches before accessing main memory (RAM).

---

# 1. Task Structure

The simulator begins by defining a **Task** structure that represents a process or instruction stream executed by the CPU.

Each task contains:

| Attribute     | Description                                        |
| ------------- | -------------------------------------------------- |
| Task ID       | Unique identifier for the task                     |
| Burst Time    | Number of CPU cycles required for execution        |
| Memory Blocks | List of memory locations accessed during execution |

### Example

A task with:

* **Task ID:** T1
* **Burst Time:** 5 cycles
* **Memory Blocks:** M1, M4, M7

indicates that the CPU will spend 5 execution cycles processing the task while accessing the specified memory locations whenever required.

---

# 2. Cache Level Representation

The simulator models a realistic cache hierarchy using a dedicated **CacheLevel** class.

Each cache level stores:

* **Capacity** – Maximum number of memory blocks.
* **FIFO Queue** – Maintains insertion order.
* **Hash Set (`unordered_set`)** – Enables constant-time lookup operations.

### Responsibilities

* Fast memory block searches.
* Cache hit detection.
* FIFO replacement management.
* Capacity tracking.

The queue implements the FIFO replacement policy, while the hash set ensures efficient lookup performance.

---

# 3. Memory Block Lookup

Whenever a task requests a memory block, the simulator first checks whether the block already exists within the cache.

### Cache Hit

If the memory block is found:

* Data is immediately available.
* No lower memory level is accessed.
* Minimal latency is incurred.

### Cache Miss

If the memory block is absent:

* Lower cache levels are searched.
* RAM may need to be accessed.
* Additional latency is introduced.

---

# 4. Memory Block Insertion

When a cache miss occurs and free space is available:

1. The memory block is inserted into the cache.
2. The block is added to the FIFO queue.
3. The block is recorded in the hash set.

This guarantees accurate tracking of both insertion order and cache membership.

---

# 5. FIFO Cache Replacement Policy

When a cache reaches maximum capacity, the simulator applies the **FIFO (First-In First-Out)** replacement strategy.

### Replacement Process

1. Identify the oldest block (front of queue).
2. Remove the block from the hash set.
3. Remove the block from the queue.
4. Insert the new block into both data structures.

### Advantages

* Simple implementation.
* Low computational overhead.
* Predictable replacement behavior.

---

# 6. Multi-Level Memory Hierarchy

The simulator models the following hierarchy:

```text
CPU
 ↓
L1 Cache
 ↓
L2 Cache
 ↓
L3 Cache
 ↓
RAM
```

### Characteristics

| Memory Level | Speed    | Capacity |
| ------------ | -------- | -------- |
| L1 Cache     | Fastest  | Smallest |
| L2 Cache     | Fast     | Medium   |
| L3 Cache     | Moderate | Large    |
| RAM          | Slowest  | Largest  |

This hierarchy closely resembles modern processor architectures.

---

# 7. Memory Access Procedure

For every memory request:

1. Search L1 Cache.
2. If not found, search L2 Cache.
3. If not found, search L3 Cache.
4. If still not found, retrieve from RAM.

### Outcomes

**Cache Hit**

* Data found in one of the cache levels.

**Cache Miss**

* Data retrieved from RAM.
* Block inserted into cache hierarchy for future accesses.

---

# 8. Latency Calculation

Each memory level introduces a different access delay.

| Memory Level | Typical Latency |
| ------------ | --------------- |
| L1 Cache     | 4 cycles        |
| L2 Cache     | 12 cycles       |
| L3 Cache     | 40 cycles       |
| RAM          | 100+ cycles     |

The simulator accumulates latency values during execution to measure memory performance.

---

# 9. Task Execution Flow

For each task, the simulator performs the following sequence:

1. Read task information.
2. Execute CPU burst cycles.
3. Access required memory blocks.
4. Search the cache hierarchy.
5. Record cache hits and misses.
6. Apply FIFO replacement when necessary.
7. Calculate memory access latency.
8. Continue until task completion.

Once all burst cycles have been executed, the task is considered complete.

---

# 10. Educational Objectives

The primary objective of this simulator is to demonstrate how memory hierarchy influences overall CPU performance.

### Key Concepts Demonstrated

* CPU task execution
* Memory hierarchy design
* Cache hit and cache miss behavior
* FIFO cache replacement policy
* Multi-level caching
* Memory access latency
* Performance optimization through caching

---

# Conclusion

Modern processors operate significantly faster than main memory. To bridge this performance gap, cache memories store frequently accessed data closer to the CPU.

This simulator provides a practical understanding of:

* How cache hierarchies function
* Why cache hits improve performance
* How replacement policies affect efficiency
* The relationship between CPU execution and memory latency

By modeling realistic cache behavior, the project offers valuable insights into modern computer architecture and memory management systems.
