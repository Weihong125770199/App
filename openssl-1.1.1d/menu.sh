ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
arm_cross_prefix=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}


./config no-asm shared --prefix=${rootfs_path} \
       	--cross-compile-prefix=${arm_cross_prefix}

sed -i 's/-m64//g' Makefile
make 
sudo make install
cd -
