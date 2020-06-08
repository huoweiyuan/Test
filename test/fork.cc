#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <assert.h>

int fork_proc();
pid_t pid;
static void sigchld(int n)
{
  std::cout << "Get SIGCHLD" << n << std::endl;
  // 当前进程在信号函数处理完成之后才会继续执行
  // while(1)
  // {
  //   std::cout << "f : SIGCHLD" << n << std::endl;
  //   sleep(2);
  // }

  // pid_t pid;
  int r = fork_proc();
  if (r < 0)
    return;
  else
  {
    std::cout << "f : SIGCHLD new pid" << pid << std::endl;
  }
}

int fork_proc()
{
  pid = fork(); // 复制上下文，形成新的进程
  if (pid == 0)
  {
    // sub proc
  }
  else if (pid > 0)
  {
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sigchld;
    sigaction(SIGCHLD, &act, NULL);

    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);
  }
  else
  {
    return -1;
  }
  return 0;
}

int main()
{
  int r = fork_proc();
  if (r < 0) return -1;
  while (1)
  {
    if (pid > 0)
    {
      std::cout << "f :" << pid << std::endl;
    }
    else // pid == 0
    {
      std::cout << "c :" << pid << std::endl;
      assert(false);
    }
    sleep(2);
  }
  return 0;
}
