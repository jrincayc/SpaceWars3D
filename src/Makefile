include rules.make

DIRS=utility physics graphics resources input app 

all: 
	for DIR in $(DIRS); do (cd $$DIR && make); done

clean: 
	for DIR in $(DIRS); do (cd $$DIR && make clean); done
