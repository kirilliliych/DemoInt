all:
	g++ -fno-elide-constructors demoint.cpp graphdrawer.cpp main.cpp -o demoint
	./demoint
