all:
	echo Making project_channel.
	(cd channel r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNEL.

	echo Making project_channelHP.
	(cd channelHP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP.
	
	echo Making project_channel_multi.
	(cd channel_multi r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNEL_MULTI.
	
	echo Making project_channelHP_multi.
	(cd channelHP_multi r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP_MULTI.
	
	echo Making project_HitPattern.
	(cd HitPattern r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_HITPATTERN.

clean:
	(cd channel    && make -is clean && cd ..)
	(cd channelHP  && make -is clean && cd ..)
	(cd channel_multi   && make -is clean && cd ..)
	(cd channelHP_multi && make -is clean && cd ..)
	(cd HitPattern && make -is clean && cd ..)
	rm -f *~
