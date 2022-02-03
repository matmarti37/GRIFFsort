all:
	echo Making Tigress_BGO_ERaw.
	(cd ERaw r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_BGO_ERaw.

clean:
	(cd ERaw         && make -is clean && cd ..)
	rm -f *~
