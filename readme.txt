# 21 April 2010
# $MYDROID should be to top level of android source file system
# To build tibltTest under android fs
# cp -Rfp tibltTest $MYDROID/external/tibltTest
# cd $MYDROID/external/tibltTest
# ./installLib2Build.sh
# cd $MYDROID
# make -j2
# cd $MYDROID/external/tibltTest
# export DISCIMAGE=<android_target_fs>
# ./installLib2Run.sh 
#
# To run tibltMain in adb or android console shell
# cd <android_target_fs>/system/bin
# ./tibltMain
# following the menu prompt and run some sample test
#
# The output files are in <android_target_fs>/system/bin/images
#
