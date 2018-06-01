build: 
		g++ *.cpp -std=c++17
run:	build
		./a.out
		rm a.out