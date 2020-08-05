#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

// green cloud
namespace gc
{
  const unsigned int level_max = 7;
  template <typename T> class SkipList
  {
  private:
    struct skip_node_struct
    {
      T element;
      struct skip_node_struct *skip_level[level_max];
      unsigned int level_count;
    };
    typedef struct skip_node_struct skip_node_t;
  private:
    skip_node_t head, tail;
  private:
    void init()
    {
      head.level_count = 0;
      tail.level_count = 0;

      for (unsigned int i = 0; i < level_max; i++)
      {
        head.skip_level[i] = &tail;
      }
    }

    void deinit()
    {
      while (head.skip_level[0] != &tail)
      {
        skip_node_t *ptr = head.skip_level[0];
        head.skip_level[0] = head.skip_level[0]->skip_level[0];
        delete ptr;
      }
    }
  public:
    SkipList()
    {
      init();
    }

    ~SkipList()
    {
      deinit();
    }

  public:
    void push(const T &element)
    {
      unsigned int level = ;

    }

  };
};

#endif // _SKIP_LIST_H_
