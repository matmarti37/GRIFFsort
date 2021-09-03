all:
	echo Making view_fragment.
	(cd fragment r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_FRAGMENT.

clean:
	(cd fragment             && make -is clean && cd ..)
	rm -f *~
