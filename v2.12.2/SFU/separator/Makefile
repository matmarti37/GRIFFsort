all:
	echo Making TrigBits.
	(cd TrigBits && make -is clean && make && make -is clean && cd ..)
	echo DONE: TrigBits.

clean:
	(cd TrigBits            && make -is clean && cd ..)
	rm -f *~
