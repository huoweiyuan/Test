#include "raft_blocks.h"
#include "byte_order.h"

using std::vector;
using std::list;

// | block len(4) | raft cmd type(1) |
static int build_head_block(vector<uchar> &block, const raft_head_s &head)
{
  uchar tmp[5];
  uchar *ptr = tmp;

  ptr += sizeof(uint); // offset len size
  *ptr = static_cast<uchar>(head.type);

  block.insert(block.end(), tmp, tmp + 5);
  return 0;
}

static int parse_head_block(raft_head_s &head, const uchar *block)
{
  block += sizeof(uint); // offset len size
  head.type = static_cast<raft_cmd_type>(*block);
  return 0;
}

int build_appendentries_block(vector<uchar> &block,
                              const raft_appendentries_s &append)
{
  if (block.empty() != true) return -1;
  uchar tmp[8];
  block.reserve(sizeof_raft_appendentries(append) + sizeof(uint32) * 2 +
                sizeof(uint32) * append.entries.size());
  int r = build_head_block(block, append.head);

  uint8net(tmp, append.term);
  block.insert(block.end(), tmp, tmp + sizeof(uint64));

  uint8net(tmp, append.leader_id);
  block.insert(block.end(), tmp, tmp + sizeof(uint64));

  uint8net(tmp, append.prev_log_index);
  block.insert(block.end(), tmp, tmp + sizeof(uint64));

  uint8net(tmp, append.prev_log_term);
  block.insert(block.end(), tmp, tmp + sizeof(uint64));

  uint4net(tmp, append.entries.size());
  block.insert(block.end(), tmp, tmp + sizeof(uint32));

  for (list<vector<uchar> >::const_iterator iter = append.entries.begin();
       iter != append.entries.end();
       ++iter) {
    uint4net(tmp, (*iter).size());
    block.insert(block.end(), tmp, tmp + sizeof(uint32));

    block.insert(block.end(), (*iter).begin(), (*iter).end());
  }

  uint8net(tmp, append.leader_commit);
  block.insert(block.end(), tmp, tmp + sizeof(uint64));

  // write len at head
  uint4net(&block[0], block.size());
  return 0;
}

int parse_appendentries_block(raft_appendentries_s &append,
                              const uchar *block, uint len)
{
  int r = parse_head_block(append.head, block);
  return 0;
}

int build_appendentries_r_block(vector<uchar> &block,
                                const raft_appendentries_r_s &append_r)
{
  int r = build_head_block(block, append_r.head);
  return 0;
}

int parse_appendentries_r_block(raft_appendentries_r_s &append_r,
                                const uchar *block, uint len)
{
  int r = parse_head_block(append_r.head, block);
  return 0;
}
