#include "types.h"
#include "stat.h"
#include "user.h"

void thread_func(int *arg) {
  printf(1, "Thread with pid/thread_id %d started with arg = %d\n", getpid(), *arg);
  printf(1, "Thread exiting with arg = %d\n", *arg);
  exit();
}

int
main(int argc, char *argv[])
{
  int arg1 = 111;
  int arg2 = 222;

  printf(1, "Main with pid %d: creating threads...\n", getpid());

  create_thread(thread_func, &arg1);
  create_thread(thread_func, &arg2);
  
  printf(1, "Thread with pid %d joined!\n", join());
  printf(1, "Thread with pid %d joined!\n", join());
  
  printf(1, "Main: all threads finished\n");

  exit();
}
