CC            = g++
CFLAGS        = -std=c++2a -O4 -Wall -Wextra -Wpedantic
# TODO ライブラリを追加 無ければ消去
# TODO ソースファイル.oを追加
OBJS          = Logger.o LoggerTest.cpp
# TODO myprogramを任意の名前に書き換え
PROGRAM       = LoggerTest

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

.cpp.o:
	$(CC) -c $< $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:;         rm -f *.o *~ $(PROGRAM)