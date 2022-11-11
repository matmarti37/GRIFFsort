all:
	echo Making view_fragment.
	(cd fragment r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_FRAGMENT.

	echo Making view_channel.
	(cd channel r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_CHANNEL.

	echo Making view_timing.
	(cd timing r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_TIMING.

	echo Making view_hist_tsup.
	(cd hist_tsup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_HIST_TSUP.

	echo Making view_table_hist_tsup.
	(cd table_tsup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_TABLE_HIST_TSUP.

	echo Making view_hist_tsup_range.
	(cd hist_tsup_range r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_HIST_TSUP_RANGE.

	echo Making view_table_tsup.
	(cd table_tsup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_TABLE_TSUP.


clean:
	(cd fragment               && make -is clean && cd ..)
	(cd channel                && make -is clean && cd ..)
	(cd timing   	           && make -is clean && cd ..)
	(cd hist_tsup              && make -is clean && cd ..)
	(cd table_tsup             && make -is clean && cd ..)
	(cd hist_tsup_range        && make -is clean && cd ..)
	(cd table_tsup             && make -is clean && cd ..)
	rm -f *~
