#ifndef __RAFT_H__
#define __RAFT_H__

#include <stdint.h>
#include <vector>
#include <list>

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
  role role() const;
};


struct raft_option_struct
{
  int64_t election_timeout_ms;
  int port;
};
typedef raft_option_struct raft_option_s;

class RaftServer : public Consenuse,
		   public Log,
		   public StateMachine
{
 private:
  // listen port for other raft node
  // Default value: 25567.
  int __port;

 public:
  RaftServer();
  ~RaftServer();
 public:
  int init(const raft_option_s&);
  int start();
 private:
  // Start listen port
  // int start_server();
  // Accept connection in asynchronous way
  int raft_server_accept_async();
  // 
  
};

}
#endif // __RAFT_H__
