test: leetcode.cc
	g++ -std=c++2a -g leetcode.cc -o leetcode -I/usr/local/include -L/usr/local/lib -lgtest -lpthread -fsanitize=address -fno-omit-frame-pointer
clean:
	rm -rf test

run:
	make clean
	make
	./test
