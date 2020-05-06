app目录文件的创建规则：
使用前缀，lib-，app-，sdk_, 统一命名管理。

增加APP或者开源包的步骤
1.在app目录下新建APP目录或者解压三方开源包到APP目录xxxx
2.修改app_build.sh，增加一条编译命令
  $APP/pcre-8.39/menu.sh ${ROOT}
  $APP/glib-2.48.2/menu.sh ${ROOT}
  $APP/bluez-5.43/menu.sh ${ROOT}
  $APP/xxxxx/menu.sh ${ROOT}

3.拷贝app/bluez-5.43/menu.sh 到 xxxxx

4.修改menu.sh 中cd ${MYDIR} 到cd - 之间的内容

cd ${MYDIR}

/********************************************************/
/*在此编写具体的配置编译命令*/
export CFLAGS=-L/home/weihong/carplay-bsp/AutoPlay-BSP/mini_root/rootfs/lib
export CC=${arm_gcc} 

make
sudo make install

/********************************************************/
cd -
 
5.单独执行app_build.sh 或者menu.sh 需要传入codebase 的根目录绝对路径，如下
  ./menu.sh /home/weihong/carplay-bsp/AutoPlay-BSP
