#include "raft.h"

int RaftServer::init(const raft_option_s &option)
{
  Consenuse::init();
  StateMachine::init(option.election_timeout_ms);
  
  __port = option.port;
}

int RaftServer::start()
{
  //  int r = start_server();
  int r = raft_server_accept_async();
  return r;
}


int RaftServer::raft_server_accepy_async()
{
  return 0;
}

// int RaftServer::start_server()
// {
//   // TODO:
// }





int main()
{
  return 0;
}
