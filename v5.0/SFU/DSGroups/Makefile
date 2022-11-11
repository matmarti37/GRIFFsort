all:
	echo Making HitPattern.
	(cd HitPattern r && make -is clean && make && make -is clean && cd ..)
	echo DONE: HITPATTERN

clean:
	(cd HitPattern       && make -is clean && cd ..)
	rm -f *~
