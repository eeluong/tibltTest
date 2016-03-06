#!/bin/bash
#
# copy libTICPUBLT.so to android file system for building tiblt test apps
# cd to .../externel/tibltTest
#
export ANDROID_PRODUCT=nextgen
export TIBLT_LIB=libTICPUBLT.so
#
cp -f $TIBLT_LIB ../../out/target/product/$ANDROID_PRODUCT/system/lib/$TIBLT_LIB
cp -f $TIBLT_LIB ../../out/target/product/$ANDROID_PRODUCT/obj/lib/$TIBLT_LIB
# show the directory contain
ls -asl ../../out/target/product/$ANDROID_PRODUCT/system/lib/$TIBLT_LIB
ls -asl ../../out/target/product/$ANDROID_PRODUCT/obj/lib/$TIBLT_LIB

