ROOT=$1
arm_gcc=${ROOT}/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
rootfs_path=${ROOT}/mini_root/rootfs
MYDIR=`dirname $0`
cd ${MYDIR}
export CC=${arm_gcc}
./configure CFLAGS=-I${rootfs_path}/include LDFLAGS=-L${rootfs_path}/lib   \
 --prefix=${rootfs_path} \
 --with-sysroot=${rootfs_path} --host=arm-linux --enable-abstract-sockets \
 --with-system-socket=/var/run/dbus/system_bus_socket \
 --with-system-pid-file=/var/run/dbus/pid \
 --datarootdir=/share


make
sudo make install
cd -


