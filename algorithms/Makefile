test: leetcode.cc
	g++ -std=c++11 -g leetcode.cc -o a.out -fsanitize=address -fno-omit-frame-pointer -I/usr/local/include -L/usr/local/lib -lgtest -lpthread

clean:
	rm -rf a.out

run:
	make clean
	make
	./a.out
