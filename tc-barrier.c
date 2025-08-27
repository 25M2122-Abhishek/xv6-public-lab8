#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

struct barrier{
  // ******************************
  // WPTHREAD -- START
  // ******************************
  // ADD VARIABLES YOU MIGHT NEED HERE

  int counter;
  int limit;
  int mutex;
  int turnstile1;
  int turnstile2;

  // ******************************
  // WPTHREAD -- END
  // ******************************
};

struct barrier bar;

void barrier_init(struct barrier* bar, int num_threads){
  // ******************************
  // WPTHREAD -- START
  // ******************************

  bar->limit = num_threads;
  bar->counter = num_threads;
  bar->mutex = semaphore_init(1);
  bar->turnstile1 = semaphore_init(0);
  bar->turnstile2 = semaphore_init(0);

  // ******************************
  // WPTHREAD -- END
  // ******************************
}

void barrier_place(struct barrier* bar){
  // ******************************
  // WPTHREAD -- START
  // ******************************
    semaphore_down(bar->mutex);
    bar->counter--;
    if (bar->counter == 0) {
      for (int i = 0; i < bar->limit; i++)
        semaphore_up(bar->turnstile1);
    }
    semaphore_up(bar->mutex);

    semaphore_down(bar->turnstile1);

    semaphore_down(bar->mutex);
    bar->counter++;
    if (bar->counter == bar->limit) {
      for (int i = 0; i < bar->limit; i++)
        semaphore_up(bar->turnstile2);
    }
    semaphore_up(bar->mutex);

    semaphore_down(bar->turnstile2);

  // ******************************
  // WPTHREAD -- END
  // ******************************

}

void work(int *thread_num){


    // barrier_place(&bar);
    // printf(1,"Section 1 of code | Thread Number: %d\n",*thread_num);
    // barrier_place(&bar);
    // printf(1,"Section 2 of code | Thread Number: %d\n",*thread_num);

    for(int i=0;i<3;i++){
        barrier_place(&bar);
        printf(1,"LOOP %d | Section 1 of code | Thread Number: %d\n",i,*thread_num);
        barrier_place(&bar);
        printf(1,"LOOP %d | Section 2 of code | Thread Number: %d\n",i,*thread_num);
    }

    exit();
}

int main(int argc, char *argv[]) {
    int N = 5;

    barrier_init(&bar,N);
    for(int i=0;i<N;i++) {
        create_thread(work, &i);
    }

    for(int i=0;i<N;i++) {
        join();
    }

    printf(1, "All threads joined, code completed\n");
    exit();
}