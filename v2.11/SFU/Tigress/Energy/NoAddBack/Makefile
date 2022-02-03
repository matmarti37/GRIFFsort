all:
	echo Making Tigress_ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ERaw.

clean:
	(cd ERaw         && make -is clean && cd ..)
	rm -f *~
