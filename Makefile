MAIN = yshell
INIT = init
PROMPT = prompt
PARSER = parser
EXEC = executer

all : yshell

yshell: $(MAIN).o $(INIT).o $(PROMPT).o $(PARSER).o $(EXEC).o
	gcc -o yshell $(MAIN).o $(INIT).o $(PROMPT).o $(PARSER).o $(EXEC).o

$(MAIN).o: $(MAIN).c
	gcc -c $(MAIN).c

$(INIT).o: $(INIT).c
	gcc -c $(INIT).c

$(PROMPT).o: $(PROMPT).c
	gcc -c $(PROMPT).c

$(PARSER).o: $(PARSER).c
	gcc -c $(PARSER).c

$(EXEC).o: $(EXEC).c
	gcc -c $(EXEC).c

clean:
	rm -f *.o
