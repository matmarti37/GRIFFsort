all:
	echo Making Tigress_ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ERaw.

	echo Making Tigress_ECal.
	(cd ECal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ECal.
clean:
	(cd ERaw         && make -is clean && cd ..)
	(cd ECal         && make -is clean && cd ..)
	rm -f *~
