#ifndef _RAFT_BLOCKS_H_
#define _RAFT_BLOCKS_H_

#include "type.h"

#include <list>
#include <vector>
#include <string.h>

enum raft_cmd_type {APPENDENTRIES, APPENDENTRIES_R};
struct raft_head_struct
{
  raft_cmd_type type;
};
typedef struct raft_head_struct raft_head_s;

inline void raft_head_init(raft_head_s *head)
{
  memset(head, 0, sizeof(raft_head_s));
}

struct raft_appendentries_struct
{
  raft_head_s head;
  uint64 term;
  uint64 leader_id;
  uint64 prev_log_index;
  uint64 prev_log_term;
  std::list<std::vector<uchar> > entries; // empty for heartbeat
  uint64 leader_commit; // leader's commit index
};
typedef struct raft_appendentries_struct raft_appendentries_s;
#define sizeof_raft_appendentries(T) (sizeof(T.head) + T.entries.size() + \
                                      sizeof(uint64) * 5)
inline void raft_appendentries_init(raft_appendentries_s *append)
{
  raft_head_init(&(append->head));
  append->term = 0;
  append->leader_id = 0;
  append->prev_log_index = 0;
  append->prev_log_term = 0;
  append->leader_commit = 0;
}

struct raft_appendentries_reply_struct
{
  raft_head_s head;
  uint64 term;
  uint success;
};
typedef struct raft_appendentries_reply_struct raft_appendentries_r_s;
#define sizeof_raft_appendentries_r(T) (sizeof(T.head) + sizeof(uint64) + \
                                        sizeof(uint))
inline void raft_appendentries_r_init(raft_appendentries_r_s *append_r)
{
  memset(append_r, 0, sizeof(raft_appendentries_r_s));
}

inline void raft_appendentries_r_set(raft_appendentries_r_s *append_r,
                                     uint64 term, uint success)
{
  append_r->head.type = APPENDENTRIES_R;
  append_r->term = term;
  append_r->success = success;
}

#define raft_cmd_type_offset (sizeof(uint))
#define parse_raft_cmd_type(T) \
  (static_cast<raft_cmd_type>(*(T + raft_cmd_type_offset)))

int build_appendentries_block(std::vector<uchar> &block,
                              const raft_appendentries_s &append);
int parse_appendentries_block(raft_appendentries_s &append,
                              const uchar *block, uint len);
int build_appendentries_r_block(std::vector<uchar> &block,
                                const raft_appendentries_r_s &append);
int parse_appendentries_r_block(raft_appendentries_r_s &append_r,
                                const uchar *block, uint len);

#endif // _RAFT_BLOCKS_H_
