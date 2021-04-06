CFLAGS =
OBJECT = raft.o raft_impl.o wepoll.o wthrd.o wtime.o
wraft.a : $(OBJECT)
	ar rcs $@ $(OBJECT)

$(OBJECT) : *.h

.PHONY : clean
clean :
	-rm wraft.a $(OBJECT)
