ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
arm_gpp=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
rootfs_path=${ROOT}/mini_root/rootfs
link_path="-L${ROOT}/mini_root/rootfs/lib -I${ROOT}/mini_root/rootfs/include"
inc_path=-I${ROOT}/mini_root/rootfs/include
MYDIR=`dirname $0`
cd ${MYDIR}
export CFLAGS=${link_path}
export CXXFLAGS=${link_path}
export CC=${arm_gcc} 
export CXX=${arm_gpp} 
export DESTDIR=${rootfs_path}
#autoheader
#autoreconf -vif
./bootstrap
./configure --host=arm-linux --prefix=${rootfs_path} \
        PKG_CONFIG_PATH=${rootfs_path}/lib/pkgconfig \
        --sysconfdir=/etc \
        --localstatedir=/var \
        --libdir=/lib \
        --enable-static \
		--exec_prefix=/


#-I/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/include/readline    \
#	-I/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/include    \
#      	-L/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/lib


make
make install 
cd -



