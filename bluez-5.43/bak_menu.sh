export CC=/home/chenwh/carplay2/AutoPlay-BSP/toolchain/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc \
	-I/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/include/readline    \
	-I/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/include    \
	-I/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/include/glib-2.0    \
	-I/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/include/include/dbus-1.0    \
      	-L/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/lib
./configure --host=arm-linux --prefix=/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs \
        PKG_CONFIG_PATH=/home/chenwh/carplay2/AutoPlay-BSP/mini_root/rootfs/lib/pkgconfig  \
       	--disable-systemd --disable-udev --disable-cups --disable-obex --enable-library  \
	--sysconfdir=/etc \
	--libdir=/lib
