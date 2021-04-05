all: 
	-g++ -c ./*/*.h ./*/*.cpp
	-mkdir .compiled
	-mv ./*/*.gch ./.compiled/
	-mv *.o .compiled/
	-g++ main.cpp -o main

.PHONY: clean

clean:
	-rm -f -r .compiled
	-rm -f main

