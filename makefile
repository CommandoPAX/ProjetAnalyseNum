output: main.o double_pendulum.o
	g++ -fPIC main.o double_pendulum.o -o d_pendulum

main.o: main.cpp double_pendulum.cpp
	g++ -fPIC -c main.cpp

source.o: double_pendulum.cpp
	g++ -fPIC -c double_pendulum.cpp

clean:
	rm *.o d_pendulum

fclean:
	rm *.o
