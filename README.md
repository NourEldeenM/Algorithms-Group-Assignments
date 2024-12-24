# Algorithms Assignments

This repository contains the assignments for the **CS321 - Algorithms Analysis and Design** course at **Cairo University - Faculty of Computer and Artificial Intelligence**. Each assignment folder contains tasks related to various algorithmic problems, along with descriptions and implementations.

## Assignment 1: Fibonacci Series, Search Algorithms, Heap, Priority Queue, and Heap Sort

### Assignment Description

#### Task 1: Fibonacci Series
Implement functions to compute the nth Fibonacci number using the following methods:
- **Recursion**
- **Divide and Conquer (Matrix Multiplication)**
- **Dynamic Programming**

#### Task 2: Search Algorithms
Implement both **Sequential Search** and **Binary Search** algorithms with iterative and recursive approaches:
- **Sequential Search (Iterative)**
- **Sequential Search (Recursive)**
- **Binary Search (Iterative)**
- **Binary Search (Recursive)**

#### Task 3: Heap, Priority Queue, and Heap Sort
1. **Heap Implementation**:
   - Insert elements and maintain heap property (heapify).
   - Extract maximum and minimum.
2. **Priority Queue**:
   - Use heap to build a priority queue.
   - Insert elements with priority and extract the highest priority element.
3. **Heap Sort**:
   - Use heap to sort an array by building a max heap and sorting through repeated extraction.

---

## Assignment 2: Hashing, Red-Black Tree, and Skip List

### Assignment Description

#### Task 1: Hashing and Collision Resolution Techniques
Define C++ functions to implement the following hashing and collision resolution methods:

1. **Hashing Techniques**:
   - Division Method
   - Multiplication Method
   - Mid Square Method
   - Folding Method

2. **Collision Resolution Techniques**:
   - Chaining Method
   - Open Addressing Method
   - Double Hashing

#### Task 2: Red-Black Tree
Implement the insertion and deletion operations of a red-black tree in C++. Your implementation should:
- Maintain the tree's balance and color properties.
- Support insertion of nodes while ensuring tree balance.
- Support deletion of nodes with appropriate restructuring to uphold red-black properties.

#### Task 3: Skip List
Implement a Skip List data structure in C++ with the following functionalities:
- **Insertion**: Add elements while maintaining probabilistic balancing.
- **Deletion**: Remove elements efficiently.
- **Searching**: Efficiently find elements in the skip list.

**Dynamic Problem**: Use the skip list to solve the following problem:
- **Dynamic Score Updates**: Handle frequent increases and decreases in player scores efficiently.
- **Leaderboard Retrieval**: Quickly retrieve the top N players.
- **Player Management**: Allow players to join, leave, and view their scores dynamically.

### Folder Contents:
- A C++ file for hashing and collision resolution functions.
- A C++ file for red-black tree implementation.
- A C++ file for skip list implementation and dynamic scoring program.

---

## Assignment 3: Dynamic Programming and Greedy Algorithms

### Assignment Description

#### Part 1: Dynamic Programming Problems

1. **Fair Division of Coins**
   - Problem: Given a set of coins, determine the most equitable division between two individuals such that the difference in total value is minimized.
   - Approach: Use a variation of the **0/1 Knapsack Algorithm** to calculate the minimal difference.

2. **Message Reconstruction**
   - Problem: Calculate the number of possible original messages based on specific replacement rules in an erroneous message.
   - Approach: Utilize **dynamic programming with modular arithmetic** to count valid combinations efficiently.

3. **Maximum Value Robbery**
   - Problem: Optimize the value of items stolen by considering weight constraints on a truck.
   - Approach: Solve using the **Knapsack Algorithm** to maximize the total value within given weight limits.

4. **Gold Retrieval from Sunken Treasures**
   - Problem: Maximize the gold collected by a diver, considering time and depth constraints.
   - Approach: Implement a **time-constrained knapsack algorithm** with depth-based constraints.

5. **Longest Increasing Subsequence**
   - Problem: Identify the length of the longest increasing subsequence in a given array.
   - Approach: Use **dynamic programming** to compute the sequence efficiently.

---

#### Part 2: Greedy Algorithms

1. **Cookie Distribution**
   - Problem: Maximize the number of content children by distributing cookies based on greed factors.
   - Approach: Sort children and cookies by size and greedily assign cookies to children with the smallest possible greed factor.

2. **Task Scheduling with Cooling**
   - Problem: Minimize the total intervals required to complete tasks while adhering to a cooling interval constraint.
   - Approach: Use a **greedy scheduling algorithm** to optimize task execution order and idle times.

3. **Valid Path in a Graph**
   - Problem: Determine if a valid path exists between two vertices in a graph.
   - Approach: Use a **union-find algorithm** or **breadth-first search (BFS)** for connectivity checks.

4. **Minimum Cost for Safe Roads**
   - Problem: Minimize the cost of a gift (in gold and silver coins) to ensure safe travel between all cities in a kingdom.
   - Approach: Employ **Kruskal's Algorithm** for a minimum spanning tree considering weighted costs.

5. **Sum of Minimum Distances**
   - Problem: Calculate the sum of minimum distances between all pairs of cities in a graph with distinct edge weights.
   - Approach: Utilize a **modified Floyd-Warshall Algorithm** or similar methods for shortest path calculations.

### Folder Contents:
- A C++ file for each problem, containing the code and implementation.

---

### Team Members
- **Yassin Ali** ([Yassin's GitHub](https://github.com/YassenAli))
- **Youssef Abdul Moneim** ([Youssef's GitHub](https://github.com/youssefabdulmoneim))
- **Nour Eldeen Mohamed** ([Nour's GitHub](https://github.com/NourEldeenM))