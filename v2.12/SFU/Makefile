all:
	echo Making display.
	(cd  display && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY.

	echo Making Check.
	(cd  check && make -is clean && make && make -is clean && cd ..)
	echo DONE: Check.

	echo Making Tigress.
	(cd  Tigress && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS.

clean:
	(cd display         && make -is clean && cd ..)
	(cd check           && make -is clean && cd ..)
	(cd Tigress         && make -is clean && cd ..)
	rm -f *~
