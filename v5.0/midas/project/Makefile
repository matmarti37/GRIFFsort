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

	echo Making project_TIP_HP.
	(cd TIP_HP r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_TIP_HP.

	echo Making project_TIP_energy.
	(cd TIP_energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_TIP_ENERGY.

	echo Making project_tsup0_energy.
	(cd tsup0_energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_TSUP0_ENERGY.

	echo Making project_channelHP_tsupRange.
	(cd channelHP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP_TSUPRANGE.

	echo Making project_pileup.
	(cd pileup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_PILEUP.

	echo Making project_channelHP_CC.
	(cd channelHP_CC r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP_CC.

	echo Making project_channelHP_tsupRange.
	(cd channelHP_tsupRange r && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP_TSUPRANGE.

clean:
	(cd channel    && make -is clean && cd ..)
	(cd channelHP  && make -is clean && cd ..)
	(cd channel_multi   && make -is clean && cd ..)
	(cd channelHP_multi && make -is clean && cd ..)
	(cd TIP_HP && make -is clean && cd ..)
	(cd TIP_energy && make -is clean && cd ..)
	(cd tsup0_energy && make -is clean && cd ..)
	(cd channelHP_tsupRange  && make -is clean && cd ..)
	(cd pileup && make -is clean && cd ..)
	(cd channelHP_CC && make -is clean && cd ..)
	(cd channelHP_tsupRange && make -is clean && cd ..)
	rm -f *~
