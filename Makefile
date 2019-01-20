make:
	g++ -std=c++11 test.cpp -o matrix_test

clean:
	rm -rf *.o matrix_test

run:
	./matrix_test
