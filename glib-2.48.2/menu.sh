ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}

export CC=${arm_gcc}

echo ac_cv_type_long_long=yes>arm-linux.cache

echo glib_cv_stack_grows=no>>arm-linux.cache

echo glib_cv_uscore=no>>arm-linux.cache

echo ac_cv_func_posix_getpwuid_r=yes>>arm-linux.cache

./configure CFLAGS=-I${rootfs_path}/include LDFLAGS=-L${rootfs_path}/lib  --prefix=${rootfs_path}  --host=arm-linux \
	CC=${arm_gcc} \
        PKG_CONFIG_PATH=${rootfs_path}/lib/pkgconfig \
        --cache-file=arm-linux.cache --disable-rebuilds 


make
sudo make install
cd -

