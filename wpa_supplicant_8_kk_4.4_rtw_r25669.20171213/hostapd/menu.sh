ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
PKG_PATH=${rootfs_path}/lib/pkgconfig
ext_libs=${rootfs_path}/lib
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc} DESTDIR=${rootfs_path} PKG_CONFIG_PAT=${PKG_PATH}  MY_BASE=${ROOT}  EXT_LIBS=${ext_libs}
make
make install
cd -
