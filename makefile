N = 1000000
t = 10

RUN: 
	gcc -c -pthread ./src/naive.c -lm -lrt -o ./obj/naive.o
	gcc -c -pthread ./src/load_balance.c -lm -lrt -o ./obj/load_balance.o
	gcc -pthread ./obj/naive.o -lm -lrt -o ./bin/naive 
	gcc -pthread ./obj/load_balance.o -lm -lrt -o ./bin/load_balance
	./bin/naive $(N) $(t) ./output/naive_output.txt
	./bin/load_balance $(N) $(t) ./output/load_balance_output.txt
	gcc ./src/plot.c -o ./bin/plot 
	./bin/plot

clean:
	rm ./bin/*
	rm ./obj/*
	rm ./output/*