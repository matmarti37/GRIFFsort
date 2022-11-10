all:
	echo Making EECalABSum.
	(cd EECalABSum r && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_EECalABSum.

	echo Making ECalABSum.
	(cd ECalABSum r && make && make -is clean && make && make -is clean && cd ..)
	echo DONE: Tigress_ECalABSum.

clean:
	(cd EECalABSum                 && make -is clean && cd ..)
	(cd ECalABSum                  && make -is clean && cd ..)
	rm -f *~
