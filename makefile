all: clean compile run

clean:
	- rm *.out

compile:
	gcc *.c -o histo.out

run:
	./histo.out
