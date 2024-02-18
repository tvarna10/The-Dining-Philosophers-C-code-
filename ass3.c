/* Name: Thivian Varnacumaaran
 * Student#: 216377624
 * EECS 3221 Assignment 3
 * Task: The goal is to find a solution for the Dining Philosophers using semaphores while preventing deadlocks. POSIX C thread management should be used within the code. 
 * Procedure:Create the threads for the function. Create the test cases for the following function to work.
 Finally create the main thread which will execute the code, this would also include having a code to let the thread finish as well as destroying any unwanted semaphores. More detailed explanation of each function is down below 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5


/* Creating the threads and Semaphores for the code */

pthread_t philosophers[NUM_PHILOSOPHERS];//The Thread IDs for philosophers 
sem_t chopsticks[NUM_PHILOSOPHERS];// Semaphores for chopsticks 
sem_t max_eating;// Semaphore to limit the number of philosophers eating


/*The main function that executes each philosopher thread */

void *philosopher(void *arg) {

    int id = *(int *)arg;// Get philosopher ID
    int lft_chopstick = id;// ID of the left chopstick
    int rht_chopstick = (id + 1) % NUM_PHILOSOPHERS;// ID of the right chopstick

    /* Create the Test Cases for the function*/
    while (1) {

        printf("Philosopher %d is thinking\n", id);
        sleep(2); // The philosopher will think

        printf("Philosopher %d is hungry\n", id);
        sem_wait(&max_eating); // This will make sure that only 4 philoshphers will eat at a time

        sem_wait(&chopsticks[lft_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", id, lft_chopstick);// gets the left chopstick

        sem_wait(&chopsticks[rht_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", id, rht_chopstick);//gets the right chopstick

        printf("Philosopher %d is eating\n", id);
        sleep(5); // philospher is eating 

        sem_post(&chopsticks[lft_chopstick]);
        printf("Philosopher %d put down left chopstick %d\n", id, lft_chopstick);// philosopher will put down left chopstick

        sem_post(&chopsticks[rht_chopstick]);
        printf("Philosopher %d put down right chopstick %d\n", id, rht_chopstick);// philosopher will put down right chopstick

        sem_post(&max_eating);//having another philospher eat

        printf("Philosopher %d is relaxing\n", id);
        sleep(5); // Relaxing

        // Exit the thread after completing one cycle
        break;
    }

    return NULL;
}

/* Exection for the code starts*/
int main() {

    int ids[NUM_PHILOSOPHERS];
    sem_init(&max_eating, 0, NUM_PHILOSOPHERS - 1); // Initialize to 4 philosophers

// creating the philospher threads 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1); // Initialize to 1 philospher
        ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);


        }
    }

// waiting for the thread to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

// cleaning up and destroying any unwanted 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    sem_destroy(&max_eating);

    return 0;
}

