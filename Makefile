build:
	gcc walsh.c -o walsh
	gcc statistics.c -o statistics
	g++ -o prinel prinel.cpp
	g++ -o crypto crypto.cpp
run-p1:
	./walsh
run-p2:
	./statistics
run-p3:
	./prinel
run-p4:
	./crypto
clean:
	rm walsh
	rm statistics
	rm prinel
	rm crypto
