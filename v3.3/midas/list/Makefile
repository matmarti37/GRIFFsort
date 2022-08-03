all:
	echo Making read.
	(cd read r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: READ

	echo Making display.
	(cd display r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: DISPLAY

	echo Making midas2list.
	(cd midas2list r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: MIDAS2LIST

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

	echo Making HPGe_CC_TIP_time_difference.
	(cd HPGe_CC_TIP_time_difference r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_TIP_TIME_DIFFERENCE

	echo Making HPGe_CC_TIP_trigger_tsdiff.
	(cd HPGe_CC_TIP_trigger_tsdiff r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGe_CC_TIP_TRIGGER_TSDIFF.

	echo Making check_order.
	(cd check_order r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: CHECK_ORDER

	echo Making HPGe_CC_trigger.
	(cd HPGe_CC_trigger r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: HPGE_CC_TRIGGER

	echo Making TIP_t0.
	(cd TIP_t0 r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: TIP_t0

	echo Making TIP_trigger.
	(cd TIP_trigger r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIP_trigger

	echo Making TIP_time_difference.
	(cd TIP_time_difference r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIP_time_difference

	echo Making combine.
	(cd combine r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: COMBINE

	echo Making list2sfu.
	(cd list2sfu r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: LIST2SFU

	echo Making HPGe_CC_Trigger_tsns.
	(cd  HPGe_CC_Trigger_tsns r && make -is clean && make && make -is clean && cd ..)
	echo DONE: HPGe_CC_Trigger_tsns

	echo Making TIP_Trigger_tsns.
	(cd  TIP_Trigger_tsns r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIP_Trigger_tsns

	echo Making CC_fold.
	(cd  CC_fold r && make -is clean && make && make -is clean && cd ..)
	echo DONE: CC_fold

	echo Making TIP_fold.
	(cd  TIP_fold r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIP_fold

	echo Making copy_trigger.
	(cd  copy_trigger r && make -is clean && make && make -is clean && cd ..)
	echo DONE: copy_trigger

	echo Making clear_trigger.
	(cd  clear_trigger r && make -is clean && make && make -is clean && cd ..)
	echo DONE: clear_trigger

	echo Making apply_trigger.
	(cd  apply_trigger r && make -is clean && make && make -is clean && cd ..)
	echo DONE: apply_trigger

	echo Making add_trigger_to_Seg.
	(cd  add_trigger_to_Seg r && make -is clean && make && make -is clean && cd ..)
	echo DONE: add_trigger_to_Seg.

	echo Making add_trigger_to_Sup.
	(cd  add_trigger_to_Sup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: add_trigger_to_Sup.

	echo Making reset.
	(cd  reset && make -is clean && make && make -is clean && cd ..)
	echo DONE: reset.

	echo Making test_doubletrigger.
	(cd  test_doubletrigger && make -is clean && make && make -is clean && cd ..)
	echo DONE: test_doubletrigger.

clean:
	(cd read                        && make -is clean && cd ..)
	(cd display                     && make -is clean && cd ..)
	(cd midas2list                  && make -is clean && cd ..)
	(cd time_difference             && make -is clean && cd ..)
	(cd HPGe_CC_time_difference     && make -is clean && cd ..)
	(cd HPGe_CC_Seg_time_difference && make -is clean && cd ..)
	(cd HPGe_CC_Sup_time_difference && make -is clean && cd ..)
	(cd HPGe_CC_TIP_time_difference && make -is clean && cd ..)
	(cd HPGe_CC_TIP_trigger_tsdiff  && make -is clean && cd ..)
	(cd check_order                 && make -is clean && cd ..)
	(cd HPGe_CC_trigger             && make -is clean && cd ..)
	(cd TIP_t0                      && make -is clean && cd ..)
	(cd combine                     && make -is clean && cd ..)
	(cd list2sfu                    && make -is clean && cd ..)
	(cd HPGe_CC_Trigger_tsns        && make -is clean && cd ..)
	(cd TIP_Trigger_tsns            && make -is clean && cd ..)
	(cd CC_fold                     && make -is clean && cd ..)
	(cd TIP_fold                    && make -is clean && cd ..)
	(cd copy_trigger                && make -is clean && cd ..)
	(cd TIP_time_difference         && make -is clean && cd ..)
	(cd TIP_trigger                 && make -is clean && cd ..)
	(cd clear_trigger               && make -is clean && cd ..)
	(cd apply_trigger               && make -is clean && cd ..)
	(cd add_trigger_to_Seg          && make -is clean && cd ..)
	(cd add_trigger_to_Sup          && make -is clean && cd ..)
	(cd reset                       && make -is clean && cd ..)
	(cd test_doubletrigger          && make -is clean && cd ..)
	rm -f *~
