ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
arm_gpp=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc}  CXX=${arm_gpp}  CPPFLAGS="-P -fPIC"
./configure  --prefix=${rootfs_path} \
     --enable-shared --enable-static \
     --host=arm

./configure --host=arm-linux --prefix=${rootfs_path} \
  CXX=${arm_gpp} \
  CC=${arm_gcc} 


make
sudo make install
cd -


