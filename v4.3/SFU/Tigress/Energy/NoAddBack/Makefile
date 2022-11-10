all:
	echo Making Tigress_ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ERaw.

	echo Making Tigress_ECal.
	(cd ECal r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ECal.

	echo Making Tigress_ECalSum.
	(cd ECalSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ECalSum.

clean:
	(cd ERaw         && make -is clean && cd ..)
	(cd ECal         && make -is clean && cd ..)
	(cd ECalSum      && make -is clean && cd ..)
	rm -f *~
