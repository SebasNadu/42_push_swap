<picture>
	<img alt="libft" src="https://github.com/SebasNadu/42_push_swap/assets/98430438/7f67ff88-5828-436c-aa50-a2dc7ec71564">
</picture>

## About the project

Push swap is a project that consists in sorting data on a stack. You have at your disposal
two stacks, A and B, and a set of instructions to manipulate both stacks. The goal is to sort
the stack A in ascending order using the minimim number of instructions.

these are the available instructions:

- sa: swap a - swap the first 2 elements at the top of stack a.
- sb: swap b - swap the first 2 elements at the top of stack b.
- ss: sa and sb at the same time.
- pa: push a - take the first element at the top of stack b and put it at the top of stack a.
- pb: push b \_ take the first element at the top of stack a and put it at the top of stack b.
- ra: rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
- rb: rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
- rr: ra and rb at the same time.
- rra: reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
- rrb: reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
- rrr: rra and rrb at the same time.

## Usage

1- Clone the repository and enter it

```shell
git clone https://github.com/SebasNadu/42_get_next_line.git push_swap
cd push_swap
```

2- Run the Makefile

```shell
make
```

3- Run the program with a list of integers as arguments

```shell
./push_swap 3 80 94 2 0 20 19 1
or
./push_swap "3 80 94 2 0 20 19 1"
or
arg="3 80 94 2 0 20 19 1"; ./push_swap $arg
```

4- To check if the program is working correctly, you can use the checker program

```shell
./push_swap 3 80 94 2 0 20 19 1 | ./checker 3 80 94 2 0 20 19 1
OK
```

5- Or you can use this visualizer to see the operations between the stacks. Follow the instructions in the repository.

https://github.com/o-reo/push_swap_visualizer.git

## Implementation

#### Radix Sort

My implementation was quite a journey. Initially, I set out to find a straightforward sorting algorithm, which led me to implement radix sort.

Radix sort is a non-comparative sorting algorithm that sorts integers by grouping them based on individual digits that share the same significant position and value. Given that we only have two stacks to group the numbers, I opted to treat the integers as binary numbers and group them by their least significant bit (LSB).

While it performs admirably for small numbers, it proves inefficient for larger numbers due to the necessity of comparing each binary digit of the number. Furthermore, handling negative numbers requires special consideration.

To address these issues and enhance performance, I chose to implement a pre-sort algorithm (using merge sort) to organize the numbers and create an index for both the unsorted and sorted numbers. When utilizing the radix sort algorithm, we utilize the sorted index as a representation of the real number. This approach resolves the performance bottleneck with larger numbers and also accommodates negative numbers, as the index remains positive.

#### Greedy Sort

At this point, I was pretty happy with the performance, but I knew that with these performace I wouldn't be able to reach all the points in the project. Still, I decided to continue with other projects until I found an article about greedy sort.

In these new implementation I started dividing the group of numbers in 3: The first group are the lowest numbers, and they should be pushed onto the stack b. The second group are the middle numbers, and they should be pushed also to the stack b.

At this point the stack b should have the lower numbers at the bottom and the middle numbers at the top. Then I proceeded to push the higher numbers to the stack b. In all these operations I tried to use at maximum the instructions that affect both stacks.

At the end I left only 5 numbers in the stack a, which I then sorted. Now it's time to use the greedy sort algorithm to complete the sorting process.

The objective now is to push the numbers from the stack b to the stack a in the correct order. To achieve this, first we need to find the most efficient sequence of instructions, setting up the numbers of operations from each number of the stack b to the stack a, and taking the efficient one in the function get_min_rotate.

Then rotate the stack a and b to the correct position with the functions rotate_same, rotate_a, and rotate_b. And finally push the numbers to the stack a. The loop continues until the stack b is empty.

<picture>
	<img alt="libft" src="https://github.com/SebasNadu/42_push_swap/assets/98430438/b4cf1eca-96b2-45a9-ad32-62d9aeb03cb9">
</picture>

### Note

The implementations of radix sort and greedy sort are both in the source code. You can change the algorithm to radix sort if you want to test it. In the file push_swap.c, inside the function push_swap, change the function greedy_sort to binary_radix_sort and that's it.

