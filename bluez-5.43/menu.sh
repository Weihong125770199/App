ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
link_path=-L${ROOT}/mini_root/rootfs/lib
MYDIR=`dirname $0`
cd ${MYDIR}
export CFLAGS=${link_path}
export CC=${arm_gcc} 

./configure --host=arm-linux --prefix=${rootfs_path} \
        PKG_CONFIG_PATH=${rootfs_path}/lib/pkgconfig \
        --disable-systemd --disable-udev --disable-cups --disable-obex --enable-library  \
        --sysconfdir=/etc \
        --libdir=/lib


#-I/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/include/readline    \
#	-I/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/include    \
#      	-L/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/lib


make
sudo make install
cd -



