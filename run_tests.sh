#!/bin/bash

echo "=== Amaze-D Test Suite ==="
echo

echo "Test 1: Simple path (1 ant, direct connection)"
./amaze-d < tests/test_simple.txt
echo

echo "Test 2: Linear path (3 ants, 2 rooms)"
./amaze-d < tests/test.txt
echo

echo "Test 3: Linear path (4 ants, 5 rooms)"
./amaze-d < tests/test2.txt
echo

echo "Test 4: Multiple paths (5 ants, complex graph)"
./amaze-d < tests/test3.txt
echo

echo "=== All tests completed ==="
