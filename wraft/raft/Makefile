CFLAGS = -Wall
OBJECT = raft.o raft_impl.o wepoll.o wthrd.o wtime.o raft_blocks.o
wraft.a : $(OBJECT)
	ar rcs $@ $(OBJECT)

$(OBJECT) : *.h

.PHONY : clean
clean :
	-rm wraft.a $(OBJECT)
