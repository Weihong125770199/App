#!/bin/bash

ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
install_path=${ROOT}/mini_root/rootfs/bin


MYDIR=`dirname $0`
cd ${MYDIR}
export CC=${arm_gcc} INSTALL_PATH=${install_path} ROOT_PATH=${ROOT}
make 
make install 
cd -



