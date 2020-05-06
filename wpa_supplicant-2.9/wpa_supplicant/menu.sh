ROOT=$1 
rootfs_path=${ROOT}/mini_root/rootfs
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc 
ext_flags=-I${rootfs_path}/include 
ext_dbus=-I${rootfs_patch}/include/dbus-1.0
ext_libs=-I${rootfs_path}/lib
PKG_PATH=${rootfs_path}/lib/pkgconfig
#CFLAGS += -I/usr/local/openssl/include
#LIBS += -L/usr/local/openssl/lib


MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc} DESTDIR=${rootfs_path} PKG_CONFIG_PATH=${PKG_PATH}  MY_BASE=${ROOT} EXT_CFLAGS=${ext_flags} EXT_DBUS_CFLAGS=${ext_dbus} EXT_LIBS=${ext_libs}
make
make install
cd -
