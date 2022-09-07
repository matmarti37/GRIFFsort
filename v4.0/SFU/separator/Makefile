all:
	echo Making TrigBits.
	(cd TrigBits && make -is clean && make && make -is clean && cd ..)
	echo DONE: TrigBits.

	echo Making particle_fold.
	(cd particle_fold && make -is clean && make && make -is clean && cd ..)
	echo DONE: particle_fold.

	echo Making PID.
	(cd PID && make -is clean && make && make -is clean && cd ..)
	echo DONE: PID.

clean:
	(cd TrigBits            && make -is clean && cd ..)
	(cd particle_fold       && make -is clean && cd ..)
	(cd PID                 && make -is clean && cd ..)
	rm -f *~
