ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
arm_cxx=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc}  CXX=${arm_cxx}
./configure --prefix=${rootfs_path}  \
        --host=arm-linux --docdir=${rootfs_path}/usr/share/doc/pcre-8.39 \
        --enable-unicode-properties --enable-pcre16 --enable-pcre32 --enable-pcregrep-libz \
        --enable-pcretest-libreadline --disable-static --enable-utf8 \
        CFLAGS=-I${rootfs_path}/include \
        LDFLAGS=-L${rootfs_path}/lib 


make
sudo make install
cd -


