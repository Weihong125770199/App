ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
toolchain_path=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc}  LDFLAGS=-L${rootfs_path}/lib
./configure  --prefix=${rootfs_path} \
	--host=arm-linux bash_cv_wcwidth_broken=yes 

make SHLIB_LIBS=-lncurses
sudo make install
cd -



#export CC=/home/weihong/carplay-bsp/AutoPlay-BSP/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc \
#	 LDFLAGS=-L/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/lib
#./configure --host=arm-linux --prefix=/home/weihong/carplay-bsp/AutoPlay-BSP/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc bash_cv_wcwidth_broken=yes 
