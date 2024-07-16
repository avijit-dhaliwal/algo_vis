# Algorithm Visualizer: Illuminating Search and Traversal

## Overview

This C-based project brings search algorithms and graph traversals to life through ASCII visualization. It's designed to provide an intuitive understanding of how these fundamental computer science concepts work in practice.

## Features

- **Array-based Search Visualizations:**
  - Linear Search
  - Binary Search (with step-by-step visualization)
  - Jump Search
  - Interpolation Search

- **Graph Traversal Visualizations:**
  - Depth-First Search (DFS)
  - Breadth-First Search (BFS)

- **ASCII-based Graphics:** Ensures compatibility across all terminal environments

## Sample Output

### Binary Search Visualization

Binary Search:

6 |###

7 |###

9 |####

9 |####

10 |#####

15 |########

18 |#########

20 |##########

25 |#############

29 |*************** <-- Current

35 |##################

45 |########################

60 |################################

64 |##################################

68 |####################################

71 |######################################

85 |#############################################

88 |###############################################

89 |###############################################

93 |##################################################

Left: 0, Right: 19, Mid: 9

## Graph Visualization and Traversals

This project includes a complex graph structure to better demonstrate the differences between DFS and BFS traversals.

### Graph Structure
0 --- 1 --- 3

|     |     |

|     |     |

2 --- 4 --- 7

|     |     |

|     |     |

5 --- 6 --- 9

\   /

\ /

8

### Depth-First Search (DFS)

Starting from vertex 0, the DFS traversal might produce:

DFS traversal: 0 1 3 7 9 4 2 5 8 6

DFS Tree:

0

├── 1

│   ├── 3

│   │   └── 7

│   │       └── 9

│   └── 4

└── 2

├── 5

│   └── 8

└── 6

### Breadth-First Search (BFS)

Starting from vertex 0, the BFS traversal would produce:

BFS traversal: 0 1 2 3 4 5 6 7 8 9

BFS Tree:

0

├── 1

│   ├── 3

│   │   └── 7

│   └── 4

├── 2

│   ├── 5

│   │   └── 8

│   └── 6

└── 9

This complex graph structure demonstrates how DFS explores deeply into the graph before backtracking, while BFS explores all neighbors at the current depth before moving to the next level.

## Technical Details

- **Language:** C
- **Key Concepts:**
  - Advanced memory management
  - Pointer manipulation
  - Complex data structures (graphs, linked lists)
  - Algorithm implementation

## Building and Running

```bash
gcc -o search_algorithms main.c search_algorithms.c -lm
./search_algorithms
```

## Code Structure

main.c: Driver code and visualization functions

search_algorithms.c: Core algorithm implementations

search_algorithms.h: Function declarations and data structures

## Algorithmic Insights

Binary Search: Demonstrates divide-and-conquer strategy

Jump Search: Shows square root step optimization

DFS vs BFS: Illustrates different graph exploration strategies

## Future Enhancements

Implement additional algorithms (e.g., A*, Dijkstra's)

Add colorized output for improved readability

Create an interactive mode for user-defined inputs

Extend to 2D grid-based pathfinding visualizations

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available under the MIT License.