OBJ =  main.o vtscreen.o bike.o
APPNAME = main
INCLUDE = vtscreen.h main.h

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm

%.o : %.c $(INCLUDE)
	gcc -c -o $@ $<

clean :
	rm $(OBJ) $(APPNAME)

