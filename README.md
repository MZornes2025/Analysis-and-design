# CS 300 Portfolio Reflection

## Project Overview
This portfolio contains my work from CS 300: Data Structures and Algorithms, featuring:
- Runtime analysis of data structures (Project One)
- Binary Search Tree implementation for course management (Project Two)

## Reflection

### Problem Solved
The project addressed ABC University's need for an efficient course advising system. The key challenges were:
- Organizing 300+ CS courses with complex prerequisites
- Enabling fast course lookups for advisors
- Displaying courses in perfect alphanumeric order
- Handling growing catalog sizes efficiently

### Approach and Data Structure Importance
I approached this through:
1. **Analysis First**: Compared vectors, hash tables, and BSTs using Big-O notation
2. **BST Selection**: Chose binary search trees for their O(log n) search and automatic sorting
3. **Iterative Development**: Built prototypes for each structure before finalizing

Understanding data structures was crucial because:
- Different access patterns (random vs sequential) dramatically impact performance
- Memory locality affects real-world speed
- Proper structure choice reduces code complexity

### Overcoming Roadblocks
Key challenges and solutions:

| Challenge | Solution |
|-----------|----------|
| File path issues | Added path normalization and detailed error messages |
| Infinite loops | Implemented line counter safety limit (1000 lines) |
| Prerequisite validation | Created two-pass file loading system |
| User input errors | Added robust input validation |

### Expanded Design Approach
This project transformed my software design perspective by:
- Emphasizing **algorithmic thinking** before coding
- Showing how **data structure choice** is a design cornerstone
- Proving **defensive programming** saves debugging time
- Demonstrating that **clean abstractions** reduce technical debt

### Code Quality Evolution
My programming practice improved through:
1. **Maintainability**  
   - Used RAII principles for memory management  
   - Isolated BST logic from course handling

2. **Readability**  
   - Consistent naming (`courseNumber` vs `courseID`)  
   - Strategic comments explaining complex algorithms

3. **Adaptability**  
   - Designed for easy data structure swapping  
   - Built configurable file parsing  
   - Structured for future features (like degree planning)

## Portfolio Value
These artifacts demonstrate my ability to:
- Analyze algorithmic efficiency  
- Implement appropriate data structures  
- Create production-ready software  
- Document technical decisions clearly  

The complete code and analysis are available in the repository files.
