#!/bin/bash
#
# copy libTICPUBLT.so to android target file system for running tiblt test apps
# cd to .../externel/tibltTest
#
#export DISCIMAGE=/home/nfs/eclair04082010
export ANDROID_PRODUCT=nextgen
export TIBLT_LIB=libTICPUBLT.so
#
echo "------------------------" 
echo "Andriod target path is $YOUR_PATH " 
echo "------------------------" 
#
cp -f $TIBLT_LIB $DISCIMAGE/system/lib/$TIBLT_LIB
cp -f ../../out/target/product/$ANDROID_PRODUCT/system/bin/tibltMain $DISCIMAGE/system/bin/tibltMain
cp -Rfp images $DISCIMAGE/system/bin/
#
ls -asl $DISCIMAGE/system/lib/$TIBLT_LIB
ls -asl $DISCIMAGE/system/bin/tibltMain
ls -sal  $DISCIMAGE/system/bin/images/*
