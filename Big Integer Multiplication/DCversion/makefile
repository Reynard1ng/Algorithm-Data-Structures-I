main: main.cpp biginteger.h calculation_biginteger.o fundamental_biginteger.o
	g++ -o main main.cpp calculation_biginteger.o fundamental_biginteger.o
calculation_biginteger.o: calculation_biginteger.cpp biginteger.h
	g++ -c calculation_biginteger.cpp
fundamental_biginteger.o: fundamental_biginteger.cpp
	g++ -c fundamental_biginteger.cpp
clear:
	rm -rf main calculation_biginteger.o fundamental_biginteger.o