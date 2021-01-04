is_pi=$(shell uname -a | grep raspberry)
test: leetcode.cc
ifeq ($(is_pi), )
	g++ -std=c++11 -g leetcode.cc -o a.out -fsanitize=address -fno-omit-frame-pointer -I/usr/local/include -L/usr/local/lib -lgtest -lpthread
else	
	g++ -std=c++11 -g leetcode.cc -o a.out -I/usr/local/include -L/usr/local/lib -lgtest -lpthread
endif
clean:
	rm -rf a.out

run:
	make clean
	make
	./a.out
