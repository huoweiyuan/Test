all:client server

client:tcp_client.o
	g++ -o client tcp_client.o

server:tcp_server.o
	g++ -o server tcp_server.o

clean:
	rm -f client server *.o
# ————————————————
# 版权声明：本文为CSDN博主「harry_502」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
# 原文链接：https://blog.csdn.net/harry_502/article/details/69063097
