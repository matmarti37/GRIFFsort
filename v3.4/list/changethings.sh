#!/bin/bash

folder="TIP_Trigger_tsns"

ini='-I\$(GRIFFsort)\/current\/midas\/state-machine'
fin='-I\$(GRIFFsort)\/current\/list\/state-machine'

sed -i "s/$ini/$fin/" $folder/*

ini='\$(GRIFFsort)\/current\/midas\/state-machine\/sort\_and\_assemble\_list.a'
fin='\$(GRIFFsort)\/current\/list\/state-machine\/read\_and\_sort\_list.a'

sed -i "s/$ini/$fin/" $folder/*

ini='BIN=\$(GRIFFsort)\/bin\/midas'
fin='BIN=\$(GRIFFsort)\/bin\/list'

sed -i "s/$ini/$fin/" $folder/*

ini='include \"sort\_and\_assemble\_list.h\"'
fin='include \"read\_and\_sort\_list.h\"'

sed -i "s/$ini/$fin/" $folder/*
