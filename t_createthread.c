#include "types.h"
#include "stat.h"
#include "user.h"

void thread_func(int *arg) {
  printf(1, "Thread with pid %d started with arg = %d\n", getpid(), *arg);
  printf(1, "Thread exiting with arg = %d\n", *arg);
  exit();
}

int
main(int argc, char *argv[])
{
  int arg1 = 111;
  int arg2 = 222;

  printf(1, "Main %d: creating threads...\n", getpid());

  int tid1 = create_thread(thread_func, &arg1);
  int tid2 = create_thread(thread_func, &arg2);
  join();
  join();
  printf(1, "Main: created threads tid1=%d tid2=%d\n", tid1, tid2);
  printf(1, "Main: all threads finished\n");

  exit();
}
