ROOT=$1
APP=${ROOT}/app

echo "root path${ROOT}"
$APP/libnl-3.2.28/menu.sh ${ROOT}
$APP/dhcp-4.2.5-P1/menu.sh ${ROOT}
$APP/openssl-1.1.1d/menu.sh ${ROOT}
$APP/hostapd-2.9/hostapd/menu.sh ${ROOT}
$APP/expat-2.2.0/menu.sh ${ROOT}
$APP/dbus-1.10.14/menu.sh ${ROOT}
$APP/ncurses-6.0/menu.sh ${ROOT}
$APP/readline-7.0/menu.sh ${ROOT}
$APP/alsa-lib-1.1.3/menu.sh ${ROOT}
$APP/libffi-3.2.1/menu.sh ${ROOT}
$APP/zlib-1.2.11/menu.sh ${ROOT}
$APP/pcre-8.39/menu.sh ${ROOT}
$APP/glib-2.48.2/menu.sh ${ROOT}
$APP/bluez-5.43/menu.sh ${ROOT}
$APP/iap_transfer/menu.sh ${ROOT}
#$APP/i2c-tools-4.1/menu.sh ${ROOT}

