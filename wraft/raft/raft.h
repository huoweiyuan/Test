#ifndef __RAFT_H__
#define __RAFT_H__

#include <stdint.h>
#include <vector>
#include <list>
#include <string>
#include "type.h"

namespace wyhuo
{
class Consenuse
{
 private:

  // This node is in |__leader_item| item.
  // Default value: 0
  int64_t __current_item;
 public:
  Consenuse();
  ~Consenuse();
  int init();
 public:

};

struct log_entry_struct
{
  int64_t __index;
  int64_t __term_id;
  std::vector<uchar> __data;
};
typedef struct log_entry_struct log_entry_s;

class Log
{
 private:
  // log entry store here in sequence index.
  std::list<log_entry_s*> __log;
};

enum role {follower, candidate, leader};
class StateMachine
{
 private:
  // A follower will become a candidate if the waiting time is over
  // __election_timeout_ms.
  // Default value: 500 ms.
  int64_t __election_timeout_ms;
  

  // StateMachine's role.
  // Default value: follower.
  role __role;
 public:
  StateMachine();
  ~StateMachine();
  int init(int64_t election_timeout_ms);
 public:
  role get_role() const;
};


struct raft_option_struct
{
  int64_t election_timeout_ms;

  // listen port for other raft node
  // Default value: 25567.
  int port;

  std::string host_ipv4;
};
typedef struct raft_option_struct raft_option_s;
void raft_option_init(raft_option_s *opt);


class RaftServer;
struct raft_thrd_main_info_struct
{
  pthread_t thrd_id;
  bool running;
  bool stop;
  RaftServer *raft_server;
};
typedef struct raft_thrd_main_info_struct raft_thrd_main_info_s;
void raft_thrd_main_info_init(raft_thrd_main_info_s *info);

class RaftServer : public Consenuse,
		   public Log,
		   public StateMachine
{
 private:
  raft_option_s __option;
  int __epfd;
  int __listenfd;
  raft_thrd_main_info_s __info;
 public:
  RaftServer();
  ~RaftServer();
 public:
  int init(const raft_option_s&);
  int start();
 private:
  // Accept connection in asynchronous way
  int server_accept_async();
  int creat_ep_listen();
  // thread main
  int creat_thrd_main();
};

}
#endif // __RAFT_H__
