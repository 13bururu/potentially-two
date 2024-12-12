all: mail

mail: mail.o main.o
	gcc -o mail mail.o main.o

clean:
	rm -f mail.o main.o mail



