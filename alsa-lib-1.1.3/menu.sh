ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc}
./configure  --prefix=${rootfs_path}  CC=${arm_gcc}\
     --host=arm-linux --disable-python 

make
sudo make install
cd -


