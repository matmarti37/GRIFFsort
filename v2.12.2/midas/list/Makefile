all:
	echo Making read.
	(cd read r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: READ

	echo Making negative_triggers.
	(cd negative_triggers r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: NEGATIVE_TRIGGERS

	echo Making display.
	(cd display r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: DISPLAY

	echo Making display_subruns.
	(cd display_subruns r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: DISPLAY_SUBRUNS

	echo Making midas2list.
	(cd midas2list r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MIDAS2LIST

	echo Making midas2list_subruns.
	(cd midas2list_subruns r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MIDAS2LIST_SUBRUNS

	echo Making time_difference.
	(cd time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIME_DIFFERENCE

	echo Making HPGe_CC_time_difference.
	(cd HPGe_CC_time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_TIME_DIFFERENCE

	echo Making HPGe_CC_Seg_time_difference.
	(cd HPGe_CC_Seg_time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_SEG_TIME_DIFFERENCE

	echo Making HPGe_CC_Sup_time_difference.
	(cd HPGe_CC_Sup_time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_SUP_TIME_DIFFERENCE

	echo Making HPGe_TIP_Sup_time_difference.
	(cd HPGe_CC_TIP_time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_TIP_DIFFERENCE

	echo Making separate_channels.
	(cd separate_channels r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: SEPARATE_CHANNELS

	echo Making separate_channels_lt.
	(cd separate_channels_lt r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: SEPARATE_HPGE_CHANNELS

	echo Making check_order.
	(cd check_order r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: CHECK_ORDER

	echo Making HPGe_CC_trigger.
	(cd HPGe_CC_trigger r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGE_CC_TRIGGER

	echo Making TIP_t0.
	(cd TIP_t0 r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIP_t0

	echo Making combine.
	(cd combine r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: COMBINE

	echo Making add_trigger_to_Seg.
	(cd add_trigger_to_Seg r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: ADD_TRIGGER_TO_SEG

	echo Making add_trigger_to_Sup.
	(cd add_trigger_to_Sup r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: ADD_TRIGGER_TO_SUP

	echo Making add_trigger_to_TIP.
	(cd add_trigger_to_TIP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: ADD_TRIGGER_TO_TIP

	echo Making list2sfu.
	(cd list2sfu r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: LIST2SFU

	echo Making marked_HPGe_CC_timing.
	(cd  marked_HPGe_CC_timing r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MARKED_HPGE_CC_TIMING

	echo Making marked_HPGe_Seg_timing.
	(cd  marked_HPGe_Seg_timing r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MARKED_HPGE_SEG_TIMING

	echo Making marked_HPGe_Sup_timing.
	(cd  marked_HPGe_Sup_timing r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MARKED_HPGE_SUP_TIMING

	echo Making marked_HPGe_TIP_timing.
	(cd  marked_HPGe_TIP_timing r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MARKED_HPGE_TIP_TIMING
clean:
	(cd read                        && make -is clean && cd ..)
	(cd negative_triggers           && make -is clean && cd ..)
	(cd display                     && make -is clean && cd ..)
	(cd display_subruns             && make -is clean && cd ..)
	(cd midas2list                  && make -is clean && cd ..)
	(cd midas2list_subruns          && make -is clean && cd ..)
	(cd time_difference             && make -is clean && cd ..)
	(cd HPGe_CC_time_difference     && make -is clean && cd ..)
	(cd HPGe_CC_Seg_time_difference && make -is clean && cd ..)
	(cd HPGe_CC_Sup_time_difference && make -is clean && cd ..)
	(cd HPGe_CC_TIP_time_difference && make -is clean && cd ..)
	(cd separate_channels           && make -is clean && cd ..)
	(cd separate_channels_lt        && make -is clean && cd ..)
	(cd check_order                 && make -is clean && cd ..)
	(cd HPGe_CC_trigger             && make -is clean && cd ..)
	(cd TIP_t0                      && make -is clean && cd ..)
	(cd combine                     && make -is clean && cd ..)
	(cd add_trigger_to_Seg          && make -is clean && cd ..)
	(cd add_trigger_to_Sup          && make -is clean && cd ..)
	(cd add_trigger_to_TIP          && make -is clean && cd ..)
	(cd list2sfu                    && make -is clean && cd ..)
	(cd marked_HPGe_CC_timing       && make -is clean && cd ..)
	(cd marked_HPGe_Seg_timing      && make -is clean && cd ..)
	(cd marked_HPGe_Sup_timing      && make -is clean && cd ..)
	(cd marked_HPGe_TIP_timing      && make -is clean && cd ..)
	rm -f *~
