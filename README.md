Programming Assignment 1 - README
=================================

See `pg1.pdf` for the assignment.

Victoria Johnston ~ Programming assignment 1 ~ write up on complexities
_Your complexity analysis and other notes here_
In part 2 my implementation uses O(n^2). This is because it is putting n elements in a stack. Then each time it puts that stack of n elements into a stack of stacks. Therefore roughly n^2 will be used. When running test4 with my program, I got the following result:
Testing efficiency...
Killed
63.802299 seconds	3421.914062 Mbytes
speed requirement: failed
memory requirement: failed
My code is not very efficient and thats why the program was killed and both tests failed.

In my implementation of a linked list each time a stack is copied onto the undo list, the same locations in memory are pointed to as other stacks on the list. Therefore there is a less space being used up as each head points to the previous head.The program therefore uses O(n) which is much less than the implementation in part 2. The copy constructor is needed to help achieve this result as it helps set the head equal to the head of the stack being copied everytime a stack is being pushed into the undostack. When running this program with test4, here are the results:
Testing efficiency...
0.490925 seconds	5.941406 Mbytes
speed requirement: passed
memory requirement: passed

It is clear that my implementation of the calculator in part4 is much faster than part2 as it executed the program in a fraction of the time. It also saved a lot more memory and passed the speed and memory requirements

_Grader comments here_

Good commenting throughout the code. Also, it is a good practice to put class and struct definitions in header files.  Also, nice small 'main' function. It is also good to remove any large sections of commented code before submission.
