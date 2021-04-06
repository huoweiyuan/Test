#ifndef __RAFT_H__
#define __RAFT_H__

#include <stdint.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include "type.h"

namespace wyhuo
{

struct raft_node_list_struct
{
  int fd;
};
typedef struct raft_node_list_struct raft_node_list_s;

class Consenuse;
struct consenuse_thrd_info_struct
{
  pthread_t thrd_id;
  bool running;
  bool stop;
  Consenuse *consenuse;
};
typedef struct consenuse_thrd_info_struct consenuse_thrd_info_s;
void consenuse_thrd_info_init(consenuse_thrd_info_s *info);


enum role {follower, candidate, leader};
struct consenuse_timeout_struct
{
  // A follower will become a candidate if the waiting time is over
  // __start_election_timeout_ms.
  // Default value: 500 ms.
  int64_t __start_election_timeout_ms;

  // last time get message from leader or candidate
  int64_t __start_election_reset_time_ms;
};
typedef struct consenuse_timeout_struct consenuse_timeout_s;
class Consenuse
{
 private:

  // This node is in |__leader_item| item.
  // Default value: 0
  int64_t __current_item;
  // nodes info
  // <nodeid, node_info>
  std::map<int, raft_node_list_s> __node_list_map;

  // StateMachine's role.
  // Default value: follower.
  role __role;

  // conseuse thread info
  consenuse_thrd_info_s __info;

  consenuse_timeout_s __timeout_opt;

 public:
  Consenuse();
  ~Consenuse();
  int init();
 public:
  void redirect();
  int creat_thrd_consenuse();
  int destroy_thrd_consenuse();
 public:
  role get_role() const;
  const consenuse_timeout_s& timeout_opt() const;
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


class StateMachine
{
 private:


 public:
  StateMachine();
  ~StateMachine();
  int init(int64_t election_timeout_ms);
 public:

};


enum ep_event_wish {epno, epdel, epin, epout, epinout};
class NodeBlock
{
 private:
  // fd |int|, block |std::vector<uchar>|
  std::map<int, std::pair<ep_event_wish, std::vector<uchar> > > __write_cache;
 public:
  virtual ~NodeBlock() {}
 public:
  virtual ep_event_wish parse_block(int fd, const uchar *block,
                                    uint block_len) = 0;
  void build_block(int fd, std::vector<uchar> &block);
  ep_event_wish write_done(int fd);
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

#define EPOLL_WAIT_MAX_DEFAULT_SIZE (7)

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

struct raft_sock_struct
{
  int fd;
};
typedef struct raft_sock_struct raft_sock_s;
void raft_sock_init(raft_sock_s *raft_sock);

struct raft_ep_option_struct
{
  int epfd;
  int listenfd;
};
typedef struct raft_ep_option_struct raft_ep_option_s;
void raft_ep_option_init(raft_ep_option_s *ep_option);

class RaftServer : public Consenuse,
                   public Log,
                   public StateMachine,
                   public NodeBlock
{
 private:
  raft_option_s __option;
  raft_ep_option_s __ep_option;
  raft_thrd_main_info_s __info;
  std::list<raft_sock_s> __raft_sock_list;
 public:
  RaftServer();
  ~RaftServer();
 public:
  int init(const raft_option_s&);
  int start();
  int stop();
 private:
  // Accept connection in asynchronous way
  int server_accept_async();

  int creat_ep_listen();
  int destroy_ep_listen();

  // thread main
  int creat_thrd_main();
  int destroy_thrd_main();

  // disconnect all sock
  int destroy_raft_sockets();
 public:
  void add_raft_sock(const raft_sock_s &raft_sock);
  raft_thrd_main_info_s& get_thrd_info();
  const raft_ep_option_s& get_ep_option() const;

 public:
  ep_event_wish parse_block(int fd, const uchar *block, uint block_len);
};
}
#endif // __RAFT_H__
