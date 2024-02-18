# The-Dining-Philosophers-C-code-
**Task**

Implement a solution to the Dining Philosophers problem using semaphores, while avoiding possible deadlocks. You should use POSIX C thread management and Semaphores to implement your solution

**Requirements** 
1- Write a C program that generates a synchronization solution for exactly 5 philosophers.
2- For each philosopher create a separate thread. Ensure each thread is created correctly by
checking for return value of the system calls.
3- The main thread should wait for the philosopher threads to complete their execution. Once all
threads have exited, the main thread should destroy any semaphores and exit.
4- For every philosopher, the philosopher begins in thinking mode. Then the philosopher will try
to use the semaphore to check to see if their left chopstick and the right chopsticks are
available. If available, the philosopher should begin eating for exactly 5 seconds. After that,
the philosopher should put down the left and then the right chopsticks. Next the philosopher
will relax for exactly 5 seconds, after which the philosopher thread should exit.
5- During the phases of thinking, eating and relaxing, the thread should print out a message
saying ‘Philosopher [id] is in [state] mode’, where [id] is the id of the philosopher, and the
[state] indicate the philosopher’s state.
6- When a philosopher picks up a chopstick, the thread should print out a message saying
‘Philosopher [id] picked up [left/right] chopstick [cid]’, where [id] is the philosophers id,
[left/right] should indicate either left or right chopstick, and [cid] is the id of the chopstick.
7- Ensure only 4 philosophers should attempt to eat at a time to avoid deadlocks. Note, the orderby which philosophers eat is not important, as long as all 5 philosophers eventually eat.
