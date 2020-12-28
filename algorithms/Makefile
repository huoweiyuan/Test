test: leetcode.cc
	# g++ -std=c++2a -g leetcode.cc -o leetcode -fsanitize=address -fno-omit-frame-pointer -I/usr/local/include -L/usr/local/lib -lgtest -lpthread
	g++ -std=c++2a -g leetcode.cc -o leetcode -I/usr/local/include -L/usr/local/lib -lgtest -lpthread

clean:
	rm -rf leetcode

run:
	make clean
	make
	./leetcode
