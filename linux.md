## 一、Linux 发展历史

UNIX 和 Linux 是父子关系，Linux 是 UNIX 的发行版，除了 Linux 以外还有其他的 UNIX 发行版，但是其他的发行版都依靠特定的操作系统平台，硬件价格昂贵。

<div style="text-align:center">UNIX 主要发行版本</div>

| 操作系统 | 公司                          | 硬件平台                       |
| -------- | ----------------------------- | ------------------------------ |
| AIX      | IBM                           | PowerPC                        |
| HP-UX    | HP                            | PA-RISC                        |
| Solaris  | Sum                           | SPARC                          |
| Linux    | Red Hat Linux、Ubuntu Linux…… | IA(Intel、AMD、Cyrix、RISE...) |



## 二、Linux 系统安装

### 1. 分区类型

> 分区类型不是由 Linux 决定，而是由硬盘结构决定的，只要硬盘结构不变，分区类型就不变。

+ 主分区：最多只能有 4 个

+ 扩展分区（也是主分区的一种）（存在的目的就是突破 4 个分区）：
  + 最多只能有 1 个
  + 主分区加扩展分区最多有 4 个
  + 不能写入数据，只能包含逻辑分区

扩展分区只要是为了划分成逻辑分区，逻辑分区的数量也是有限制的。

### 2. 格式化

在分区完毕后，不能直接使用，需要对分区进行格式化，格式化主要是写入文件系统，写入文件系统的两个主要工作：

+ 将硬盘划分成等大小的数据块
+ 建立 inode 列表，查找文件的时候通过 inode 来查找，从而知道这个文件保存在哪几个数据块当中，找出来后再拼凑成一个完整的文件

### 3. 挂载

在格式化之后，再由系统为每个分区分配设备名，最后还需要进行挂载（对比 Windows 上的分配盘符）。

+ 必须进行挂载的分区
  + /
  + swap（内存 2 倍）
+ 推荐分区z
  + /boot（理论上必须进行分区挂载）

>Linux 中比较特别的一点是父目录和子目录可以挂载在不同的分区，比如 /home 和 / 可以挂载在不同的分区

> 分区是 Linux 开机后自动进行挂载的，但是 U 盘、移动硬盘、光盘等需要手动进行挂载

### 4. 远程登录管理工具

虚拟机网络配置模式

+ 桥接：利用宿主机的真实网卡进行通信，需要占用宿主机网络中的一个 ip 地址，这种模式的虚拟机类似一台网络中真正的一台计算机

> 这种模式的虚拟机的 IP 地址要设置成和宿主机的 IP 地址处于同一个网段

+ NAT：利用虚拟机软件在宿主机上创建的虚拟网卡进行通信，可以进入互联网，但是不能和局域网中的其他计算机进行通信，不占用宿主机网络的 ip 地址
+ Host-only：利用虚拟机软件在宿主机上创建的虚拟网卡进行通信，不可以进行互联网，但是不能和局域网中的其他计算机进行通信，不占用宿主机网络的 ip 地址

> NAT 和 Host-only 的网段和宿主机不同，需要进行地址转换，这两种模式的虚拟机都不能和他们网段中的其他虚拟机进行通信，其中 NAT 的虚拟机可以进入互联网，Host-only 的虚拟机不行

对 NAT 网络模式的思考：其实虚拟网卡应该也是利用宿主机的物理网卡进入互联网，这个过程只要进行地址转换即可；对于不能和局域网中（虚拟机所处的局域网）的其他机器通信的原因和一个局域网中的计算机不能和另一个局域网中的计算机直接通信是同一个道理。

### 5. Linux 各目录的作用

sbin 中的 s 是 super

| 目录名       | 目录作用                                                     |
| ------------ | ------------------------------------------------------------ |
| /bin/        | 存放系统命令的目录，普通用户和超级用户都可以执行。不过放在 /bin 下的命令在单用户模式下也可以执行 |
| /sbin/       | 保存和系统环境设置相关的命令，只有超级用户可以使用这些命令进行系统环境设置，但是有些命令可以允许普通用户查看 |
| /usr/bin/    | 存放系统命令的目录，普通用户和超级用户都可以执行。这些命令和系统启动无关，在单用户模式下不能执行 |
| /usr/sbin/   | 存放根文件系统不必要的系统管理命令，例如多数服务程序。只有超级用户可以使用。大家其实可以注意到 Linux 的系统，在所有 “sbin” 目录中保存的命令只有超级用户能使用，“bin” 目录中保存的命令所有用户都能使用 |
| /boot/       | 系统启动目录，保存系统启动相关的文件，如内核文件和启动引导程序（grub）文件等 |
| /dev/        | 设备文件保存位置。我们已经说过 Linux 中所有内容以文件形式保存，包括硬件。那么这个目录就是用来保存硬件设备文件的 |
| /etc/        | 配置文件保存位置。系统内所有采用默认安装方式（rpm安装）的服务的配置文件全部都保存在这个目录当中，如用户账号和密码，服务的启动脚本，常用服务的配置文件等 |
| /home/       | 普通用户的家目录。建立每个用户时，每个用户要有一个默认登录位置，这个位置就是这个用户的家目录，所有普通用户的家目录就是在 /home 下建立一个和用户名相同的目录。如用户 user1 的家目录就是 /home/user1 |
| /lib/        | 系统调用的函数库保存位置                                     |
| /lost+found/ | 当系统意外崩溃或机器意外关机，而产生一些文件碎片放在这里。当系统启动的过程中 fsck 工具会检查这里，并修复已经损坏的文件系统。这个目录只在每个分区中出现，例如 /lost+found 就是根分区的备份恢复目录，/boot/lost+found 就是 /boot 分区的备份恢复目录 |
| /media/      | 挂载目录。系统建议是用来挂载媒体设备的，例如软盘和光盘       |
| /mnt/        | 挂载目录，早期 Linux 中只有这一个挂载目录，并没有细分。现在这个目录系统建议挂载额外设备，如 U 盘，移动硬盘和其他操作系统的分区 |
| /misc/       | 挂载目录。系统建议用来挂载 NFS 服务的共享目录。我们在刚刚已经解释了挂载，童鞋们应该知道只有是一个已经建立的空目录就可以做为挂载点。那么系统虽然准备了 3 个默认挂载目录 /media、/mnt、/misc，但是到底在哪个目录中挂载什么设备都可以由管理员自己决定。例如超哥接触 Linux 的时候，默认挂载目录只有 /mnt 一个，所以养成了在 /mnt 下建立不同目录挂载不同设备的习惯。如 /mnt/cdrom 挂载光盘，/mnt/usb 挂载 U 盘，这都是可以的 |
| /opt/        | 第三方安装的软件保存位置。这个目录就是放置和安装其他软件的位置，我手工安装的源码包软件都可以安装到这个目录中。不过我还是更加习惯把软件放置到 /usr/local 目录当中，也就是说 /usr/local 目录也可以用来安装软件 |
| /proc/       | 虚拟文件系统，该目录中的数据并不保存到硬盘当中，而是保存到内存当中。主要保存系统的内核，进程，外部设备状态和网络状态灯。如 /proc/cpuinfo 是保存 CPU 信息的，/proc/devices 是保存设备驱动的列表的，/proc/filesystems 是保存文件系统列表的，/proc/net 是保存网络协议信息的 |
| /sys/        | 虚拟文件系统。和 /proc 目录相似，都是保存在内存当中的，主要是保存于内核相关信息的 |
| /root/       | 超级用户的家目录。普通用户家目录在 “/home” 下，超级用户家目录直接在 / 下 |
| /srv/        | 服务数据目录。一些系统服务启动之后，可以在这个目录中保存所需要的数据 |
| /tmp/        | 临时目录。系统存放临时文件的目录，该目录下所有用户都可以访问和写入。我们建议此目录中不能保存重要数据 |
| /usr/        | 系统软件资源目录。注意 usr 不是 user 的缩写，而是 “Unix Software Resource” 的缩写，所以不是存放用户数据，而是存放系统软件资源的目录。系统中安装的软件大多数保存在这里，所以除了 /usr/bin/ 和 /usr/sbin/ 这两个目录，我在介绍几个 /usr 下的二级目录 |
| /var/        | 动态数据保存位置。主要保存缓存、日志以及软件运行所产生的文件 |



## 三、Linux 常用命令

### 1. 目录处理命令

命令格式：命令	[-选项]	[参数]

说明：

1. 个别命令使用不遵循此格式
2. 当有多个选项时，可以写在一起
3. 简化选项与完整选项：-a 等于 --all

#### 1. ls

命令名称：ls

命令英文愿意：list

命令所处路径：/bin/ls

执行权限：所有用户

功能描述：显示目录文件

语法：ls [-ald] [文件/目录]

+ -a：显示所有文件，包括隐藏文件
+ -l：显示详细信息
+ -d：查看目录属性

> -rw-r--r--
>
> + 文件类型
>   + -：二进制文件
>   + d：目录
>   + l：软链接文件
> + rw-    r--    r-- ：user usergroup other

#### 2. mkdir

命令名称：mkdir

命令英文原意：make directories

命令所在路径：/bin/mkdir

执行权限：所有用户

语法：mkdir -p [目录名]

功能描述：创建新目录，其中选项 -p 表示递归创建

```shell
mkdir -p /tmp/Japan/boduo
```

#### 3. cd

命令名称：cd

命令英文原意：change directory

命令所在路径：shell 内置命令

执行权限：所有用户

语法：cd [目录]

功能描述：切换目录

```shell
cd /tmp/Japan/boduo
cd ..	# 返回上一级目录
```

> 每个目录下的 . 代表当前目录，.. 代表上一级目录

#### 4. pwd

命令名称：pwd

命令英文原意：print working directory

命令所在路径：/bin/pwd

执行权限：所有用户

语法：pwd

功能描述：显示当前所在目录

#### 5. rmdir

命令名称：rmdir

命令英文原意：remove empty directories

命令所在路径：/bin/rmdir

执行权限：所有用户

语法：rmdir [目录名]

功能描述：删除空目录

> 只能删除空目录

#### 6. cp

命令名称：cp

命令英文原意：copy

命令所在路径：/bin/cp

执行权限：所有用户

语法：cp -rp [原文件或目录] [目标目录]

+ -r：复制目录
+ -p：保留文件属性（比如：新文件的最后修改时间和源文件一致）

功能描述：删除空目录

#### 7. mv

命令名称：mv

命令英文原意：move

命令所在路径：/bin/mv

执行权限：所有用户

语法：mv [原文件/目录] [目标文件/目录]

功能描述：剪切文件、改名

#### 8. rm

命令名称：rm

命令英文原意：remove

命令所在路径：/bin/rm

执行权限：所有用户

语法：rm -rf [文件/目录]

+ -r 删除目录，用 rm 来删除有内容目录
+ -f 强制执行

功能描述：删除文件

### 2. 文件处理命令

#### 1. touch

命令名称：touch

命令所在路径：/bin/touch

执行权限：所有用户

语法：touch [文件名]

功能描述：创建空文件

#### 2. cat

命令名称：cat

命令所在路径：/bin/cat

执行权限：所有用户

语法：cat [文件名]

功能描述：显示文件内容

+ -n：显示行号

#### 3. tac

命令名称：tac

命令所在路径：/usr/bin/tac

执行权限：所有用户

语法：tac [文件名]

功能描述：反向显示文件内容

#### 4. more

命令名称：more

命令所在路径：/bin/more

执行权限：所有用户

语法：more [文件名]

(下面不是选项)

+ (空格)或 f：翻页
+ (Enter)：换行
+ q/Q：退出

功能描述：分页显示文件内容

#### 5. less

命令名称：less

命令所在路径：/usr/bin/usr

执行权限：所有用户

语法：less [文件名]

(下面不是选项)

+ (空格)或 f：翻页
+ (Enter)：换行
+ q/Q：退出
+ ⬆：向上翻一行
+ ⬇：向下翻一行
+ pageup：向上翻一页
+ pagedown：向上翻一页
+ /(搜索内容) + Enter：搜索内容；+ n 下一个关键字

功能描述：分页显示文件内容（可向上翻页）

#### 6. head

命令名称：head

命令所在路径：/usr/bin/head

执行权限：所有用户

语法：head [文件名]

+ -n x：显示前 x 行

功能描述：显示文件前面几行

#### 7. tail

命令名称：tail

命令所在路径：/usr/bin/tail

执行权限：所有用户

语法：tail [选项] [文件名]

+ -n x：显示后 x 行
+ -f：不退回终端的动态显示文件末尾内容，常用来查看日志文件

功能描述：显示文件后面几行

#### 8. ln

命令文件：ln

命令英文原意：link

命令所在路径：/bin/ln

执行权限：所有用户

语法：ln -s [源文件] [目标文件]

+ -s：创建软链接

功能描述：生成链接文件

```shell
ln -s /etc/issue /tmp/issue.soft	# 创建软链接
ln /etc/issue /tmp/issue.hard		# 创建硬链接
```

> 软链接：类似 Windows 的快捷方式
>
> 1. lrwxrwxrwx 的 l 表示软链接，所有软链接文件权限都为 rwxrwxrwx，说明任何用户都可以执行它，但是真正的权限说明要看源文件，所以这个软链接文件权限无意义
> 2. 表现形式：/tmp/issue.soft -> /etc/issue，➡指向的是源文件

> 硬链接：
>
> 1. 相当于源文件的拷贝，但是和源文件的内容保持同步更新
> 2. 硬链接文件和源文件和 i 节点是一样的，软链接文件则不同
> 3. 硬链接不能跨分区，软链接可以
> 4. 硬链接不能针对目录使用

### 3. 权限管理命令

#### 1. chmod

命令名称：chmod

命令英文原意：change the permissions mode of a file

命令所在路径：/bin/chmod

执行权限：所有用户

语法：chmod [{ugoa}{+-=}{rwx}] [文件/目录]

​							  [xxx] [文件/目录]

​							  -R：递归修改

功能描述：改变文件或目录权限

```shell
chmod g+w testfile # 给用户组增加 w 权限
chmod o-r testfile # 给用户组减少 r 权限
# Linux 中常用的修改权限形式
chmod 755 testfile	# rwxr-xr-x
chmod -R 755 a_dir	# 递归修改该目录下的所有文件
```

| 代表字符 | 权限     | 对文件的含义 | 对目录的含义               |
| -------- | -------- | ------------ | -------------------------- |
| r        | 读权限   | 可以查看文件 | 可以列出目录中的内容       |
| w        | 写权限   | 可以修改文件 | 可以在目录中创建、删除文件 |
| x        | 执行权限 | 可以执行文件 | 可以进入目录               |

> 注意理解权限对于目录的含义。比如，对于 dir/testfile 文件，即使用户对该文件的权限是 ---，但是若该用户对 dir 目录的权限是 -w-，该用户同样可以删除该文件

#### 2. chown

命令名称：chown

命令英文原意：change file ownership

命令所在路径：/bin/chown

执行权限：所有用户，但是只有 root 能修改成功

语法：chown [用户名] [文件/目录]

功能描述：改变文件或目录的所有者

> 只有 root 能修改成功

#### 3. chgrp

命令名称：chgrp

命令英文原意：change file group ownership

命令所在路径：/bin/chgrp

执行权限：所有用户，但是只有 root 能修改成功

语法：chgrp [用户名] [文件/目录]

功能描述：改变文件或目录的所属组

#### 4. umask

命令名称：umask

命令英文原意：the user file-creation mask

命令所在路径：shell 内置命令

执行权限：所有用户

语法：umask [-S]

+ -S：以 rwx 形式显示新建文件缺省权限

功能描述：显示、设置文件的缺省权限

> 一般来说不用修改 Linux 创建目录/文件时的缺省权限

### 4. 文件搜索命令

#### 1. find

命令名称：find

命令所在路径：/bin/find

执行权限：所有用户

语法：find [搜索范围] [匹配条件]

+ -name：根据文件名称查找

+ -iname：根据文件名称查找且不区分大小写

  ```shell
  find /etc -name init
  find /etc -iname init
  ```

+ -size：根据文件大小查找

  ```shell
  find / -size +204800	# 在根目录下查找大于 100MB 的文件
  find / -size -204800	# 在根目录下查找小于 100MB 的文件
  find / -size 204800		# 在根目录下查找等于 100MB 的文件
  ```

+ -user：根据所属用户查找

  ```shell
  find /home -user cwm	# 查找属于用户 cwm 的文件
  ```

+ -amin：根据访问时间查找

+ -cmin：根据文件属性查找

  ```shell
  find /etc -cmin -5	# 文件属性被修改的时间小于 5 分钟
  find /etc -cmin +5	# 文件属性被修改的时间大于 5 分钟
  find /etc -cmin 5	# 文件属性被修改的时间等于 5 分钟
  ```

+ -mmin：根据文件内容查找

+ -a：连接两个匹配条件

  ```shell
  find /etc -name init -a -user cwm	# 搜索 init 文件并且属于用户 cwm
  ```

+ -exec/-ok：对查询出来的结果执行命令

  ```shell
  find /etc -name inittab -exec ls -l {} \;
  ```

+ -type：根据文件类型查找

  + f：文件
  + d：目录
  + l：软链接文件

+ -inum：根据 i 节点查找

功能描述：文件搜索

#### 2. locate

命令名称：locate

命令所在路径：/usr/bin/locate

执行权限：所有用户

语法：locate [选项] 文件名

+ -i：忽略大小写的查找

功能描述：在文件资料库中查找文件

```shell
updatedb	# 更新资料库，locate 基于资料库进行搜索，所以
lodate -i init	# 不区分大小进行搜索
```

> locate 合适搜索系统配置文件，locate 搜索的位置不包含 /tmp

#### 3. which

命令名称：which

命令所在路径：/usr/bin/which

执行权限：所有用户

语法：which 命令

功能描述：搜索系统命令所在目录以及别名信息

```shell
which ls
which vim
```

#### 4. whereis

命令名称：whereis

命令所在路径：/usr/bin/whereis

执行权限：所有用户

语法：whereis 命令

功能描述：搜索系统命令所在目录以及与命令相关的帮助文档信息

#### 5. grep

命令名称：grep

命令所在路径：/bin/grep

执行权限：所有用户

语法：grep -iv [指定字串] [文件]

+ -i：不区分大小写
+ -v：排除指定字串

功能描述：在文件中搜寻字串匹配的行并输出

```shell
grep -i user /etc/xxx # 打印文件 /etc/xxx 中有关键字 user 所在的行
grep -v ^# /etc/xxx	# 打印文件 /etc/xxx 除了 # 开头的其他行
```

### 5. 帮助命令

#### 1. man

命令名称：man

命令英文原意：manual

命令所在路径：/usr/bin/man

执行权限：所有用户

语法：man [命令/配置文件]

+ 同 less 的使用方式

功能描述：获得帮助信息

```shell
man ls	# 查看 ls 命令的帮助信息
man service # 查看配置文件 /etc/service 的帮助信息, 不能使用"绝对路径"
```

#### 2. whatis

命令名称：whatis

执行权限：所有用户

语法：whatis [命令]

功能描述：获取命令帮助信息，该信息只描述命令的功能

```shell
[root@192 ~]# whatis ls
ls (1)               - list directory contents
```

#### 3. apropos

命令名称：apropos

执行权限：所有用户

语法：apropos [配置文件]

功能描述：获取配置文件的描述信息

#### 4. help

命令名称：help

命令所有路径：Shell 内置命令

执行权限：所有用户

语法：help 命令

功能描述：获得 Shell 内置命令的帮助信息

> Shell 内置命令是由 shell 提供的，并不是 Linux 内核所拥有的命令，所以对于内置命令使用 which 和 man 是失效的

### 6. 用户管理命令

#### 1. useradd

命令名称：useradd

命令所有路径：/usr/sbin/useradd

执行权限：root

语法：useradd 用户名

功能描述：添加新用户

#### 2. passwd

命令名称：passwd

命令所在路径：/usr/bin/passwd

执行权限：所有用户

语法：passwd 用户名

功能描述：设置用户密码

> root 用户能为所有用户修改密码，并且不受密码规格限制
>
> 普通用户只能修改自己的密码，并受密码规则限制

#### 3. who

命令名称：who

命令所在路径：/usr/bin/who

执行权限：所有用户

语法：who

功能描述：查看登录用户信息

```shell
# 登录用户名	登录终端(tty：本地终端，pts：远程终端)	登录时间	IP 地址
[root@192 ~]# who
root     pts/0        2022-02-05 21:44 (192.168.0.104)
```

#### 4. w

命令名称：w

命令所在路径：/usr/bin/w

执行权限：所有用户

语法：w

功能描述：查看登录用户详细信息

```shell
# 1:08 —— 系统持续运行了多久
# 1 user —— 当前有几个用户登录
# load average —— 系统负载均衡
# IDLE   JCPU   PCPU —— 用户占用资源情况
# WHAT —— 用户在执行什么命令
[root@192 ~]# w
 22:53:10 up  1:08,  1 user,  load average: 0.00, 0.01, 0.03
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
root     pts/0    192.168.0.104    21:44    6.00s  0.02s  0.00s w
```

### 7. 压缩解压命令

#### 1. gzip

命令名称：gzip

命令英文原意：GNU zip

命令所在路径：/bin/gzip

执行权限：所有用户

语法：gzip [文件]

功能描述：压缩文件

压缩后文件格式：.gz

> 不保留源文件压缩
>
> 不能压缩目录

#### 2. gunzip

命令名称：gunzip

命令英文原意：GNU unzip

命令所在路径：/bin/gunzip

执行权限：所有用户

语法：gunzip [压缩文件]

功能描述：解压缩 .gz 的压缩文件

#### 3. tar

命令名称：tar

命令所在路径：/bin/tar

执行权限：所有用户

语法：tar [选项] [压缩后文件名] [目录]

+ -c：打包
+ -v：显示详细信息
+ -f：指定文件名，必要选项
+ -z：打包同时压缩

功能描述：打包[压缩]目录

压缩后文件格式：.tar.gz

```shell
tar -czf test.tar.gz test.cc
```

tar 命令解压缩语法：

+ -x：解包
+ -v：显示详细信息
+ -f：指定解压文件
+ -z：解压缩

```shell
tar -xzf test.tar.gz	# f 要放在选项的最后面
```

#### 8. zip

命令名称：zip

命令所在权限：/usr/bin/zip

执行权限：所有用户

语法：zip [选项] [压缩后文件名] [文件/目录]

+ -r：压缩目录

功能描述：压缩文件/目录

压缩后文件格式：.zip

```shell
zip test.cc test
zip -r test_dir test	# 压缩目录
```

#### 9. unzip

命令名称：unzip

命令所在路径：/usr/bin/unzip

执行权限：所有用户

语法：unzip [压缩文件]

功能描述：解压 .zip 的压缩文件

#### 10. bzip2

命令名称：bzip2

命令所在路径：/usr/bin/bzip2

执行权限：所有用户

语法：bzip2 [选项] [文件]

+ -k：产生压缩文件后保留原文件

功能描述：压缩文件

压缩后文件格式：.bz2

```shell
bzip2 -k test.cc	# 产生文件 test.cc.bz2
tar -cjf test.cc.bz2 test.cc	# tar 也可以打包压缩成 .bz2 
```

#### 11. bunzip2

命令名称：bunzip2

命令所在路径：/usr/bin/bunzip2

执行权限：所有用户

语法：bunzip2 [选项] [压缩文件]

+ -k：解压后保留压缩文件

功能描述：解压缩

压缩后文件格式：.bz2

```shell
bunzip2 -k test.cc.bz2
tar -xjf test.cc.bz2	# tar 也可以拆包
```

### 8. 网络命令

#### 1. write

命令名称：write

命令所在路径：/usr/bin/write

执行权限：所有用户

语法：write <用户名>

功能描述：给用户发信息，以 Ctrl + D 保存结束

> 需要接收用户在线

#### 2. wall

命令名称：wall

命令英文原意：write all

命令所在路径：/usr/bin/wall

执行权限：所有用户

语法：wall [message]

功能描述：发广播信息

#### 3. ping

命令名称：ping

命令所在路径：/bin/ping

执行权限：所有用户

语法：ping [选项] IP 地址

+ -c：指定发送次数

功能描述：测试网络连通性

```shell
ping -c 4 www.baidu.com
```

#### 4. ifconfig

命令名称：ifconfig

命令英文原意：interface configure

命令所在路径：/sbin/ifconfig

执行权限：root

语法：ifconfig 网卡名称 IP 地址

功能描述：查看和设置网卡信息

```shell
ifconfig eth0 192.168.70.104	# 设置网卡地址，但是一般不用这种方式
```

#### 5. mail

命令名称：mail

命令所在路径：/bin/mail

执行权限：所有用户

语法：mail [用户名]

功能描述：查看发送电子邮件

```shell
mail root
```

> 不需要用户在线

#### 6. last

命令名称：last

命令所在路径：/usr/bin/last

执行权限：所有用户

语法：last

功能描述：列出目前与过去登入系统的用户信息

#### 7. lastlog

命令名称：lastlog

命令所在路径：/usr/bin/lastlog

执行权限：所有用户

语法：lastlog

功能描述：检查某特定用户上次登录的时间

```shell
lastlog
lastlog -u 502	# 502 是 uid
```

#### 8. traceroute

命令名称：traceroute

命令所在路径：/bin/traceroute

执行权限：所有用户

语法：traceroute [域名/IP 地址]

功能描述：显示数据包到主机间的路径

```shell
traceroute www.baidu.com
```

#### 9. netstat

命令名称：netstat

命令所在路径：/bin/netstat

执行权限：所有用户

语法：netstat [选项]

+ -t：TCP 协议
+ -u：UDP 协议
+ -l：监听
+ -r：路由
+ -n：显示 IP 地址和端口号

功能描述：显示网络相关信息

```shell
netstat -tlun # 查看本机监听的端口
netstat -an	  # 查看本机所有的网络连接
netstat -rn	  # 查看本机路由表
```

#### 10. setup

命令名称：setup

命令所在路径：/usr/bin/setup

执行权限：root

语法：setup

功能描述：配置网络，只有 redhat 系统的 OS 才拥有此命令

#### 11. mount

命令名称：mount

命令所在路径：/bin/mount

执行权限：所有用户

语法：mount [-t 文件系统] 设备文件名 挂载点

功能描述：Linux 中分区是自动挂载的，但是 U 盘、移动硬盘、光盘等设备需要手动挂载

```shell
# 需要先 mkdir /mnt/cdrom 文件夹
# /dev/sr0：Linux 为 U 盘/移动硬盘/光盘 分配的设备名
mount /dev/sr0 /mnt/cdrom
```

### 9. 关机重启命令

#### 1. shutdown

语法：shutdown [选项] 时间

+ -c：取消前一个关机命令，比如取消上次的定时关机
+ -h：关机
+ -r：重启

```shell
shutdown -h now	# 现在立即关机
shutdown -h 15:29	# 在 15:29 关机
shutdown -r now	# 现在立即重启
```

```shell
# 其他关机命令、了解即可，最好是使用 shutdown
halt
poweroff
init 0
```

```shell
# 其他重启命令
reboot
init 6
```

#### 2. 系统运行级别

+ 0：关机
+ 1：单用户
+ 2：不完全多用户，不含 NFS 服务
+ 3：完全多用户
+ 4：未分配
+ 5：图形界面
+ 6：重启

```shell
# 查看系统运行级别
runlevel

cat /etc/inittab
id:3:initdefault:	# 修改 /etc/inittab 里面的这一行中的数字就能修改系统运行级别
```

#### 3. 退出登录命令

```shell
# 养成操作完成之后退出当前用户的登录的习惯
logout
```



## 四、vim 常用操作

> 懂得识别以下命令是在哪种模式下使用

### 1. 插入命令

| 命令 | 作用                 |
| ---- | -------------------- |
| a    | 在光标所在字符后插入 |
| A    | 在光标所在行尾插入   |
| i    | 在光标所在字符前插入 |
| I    | 在光标所在行行首插入 |
| o    | 在光标下插入新行     |
| O    | 在光标上插入新行     |

### 2. 定位命令

| 命令      | 作用      |
| --------- | --------- |
| :set nu   | 设置行号  |
| :set nonu | 取消行号  |
| gg/G      | 到第一行  |
| nG        | 到第 n 行 |
| :n        | 到第 n 行 |
| $         | 移至行尾  |
| 0         | 移至行首  |

### 3. 删除命令

| 命令    | 作用                          |
| ------- | ----------------------------- |
| x       | 删除光标所在处字符            |
| nx      | 删除光标所在处后 n 个字符     |
| dd      | 删除光标所在行，ndd 删除 n 行 |
| dG      | 删除光标所在行到文件末尾内容  |
| D       | 删除光标所在处到行尾内容      |
| :n1,n2d | 删除指定范围的行              |

### 4. 复制和剪切命令

| 命令 | 作用                        |
| ---- | --------------------------- |
| yy   | 复制当前行                  |
| nyy  | 复制当前行以下 n 行         |
| dd   | 剪切当前行                  |
| ndd  | 剪切当前行以下 n 行         |
| p/P  | 粘贴在当前光标所在行下/行上 |

### 5. 替换和取消命令

| 命令 | 作用                                  |
| ---- | ------------------------------------- |
| r    | 取代光标所在处字符                    |
| R    | 从光标所在处开始替换字符，按 Esc 结束 |
| u    | 取消上一步操作                        |

### 6. 搜索和搜索替换命令

| 命令              | 作用                                       |
| ----------------- | ------------------------------------------ |
| /string           | 搜索指定字符串，搜索时忽略大小写加 :set ic |
| n                 | 开始搜索后跳到下一个匹配字符处             |
| :%s/old/new/g     | 全文替换指定字符串                         |
| :n1,n2s/old/new/g | 在一定范围内替换指定字符串                 |

### 7. 保存和退出命令

| 命令            | 作用                                     |
| --------------- | ---------------------------------------- |
| :w              | 保存修改                                 |
| :w new_filename | 另存为指定文件                           |
| :wq             | 保存修改并退出                           |
| ZZ              | 快捷键，保存修改并退出                   |
| :q!             | 不保存修改并退出                         |
| :wq!            | 保存修改并退出(文件所有者及 root 可使用) |

### 8. vim 使用技巧

1. 导入其他文件内容到光标所在处

   ```shell
   # 编辑模式
   :r /etc/issue	# 将 /etc/issue 的内容导入到当前的编辑文件中
   ```

2. 导入命令执行结果到光标所在处

   ```shell
   # 编辑模式
   :r !命令
   ```

3. 定义快捷键

   ```shell
   # 编辑模式
   # 格式：map 快捷键 触发命令
   :map ^P I#<ESC> 	# ^P 是 CTRL + V + P 打出来的
   :map ^B 0x
   ```

4. 连续行注释

   ```shell
   :n1,n2s/^/#/g		# n1,n2 是行号
   :n1,n2s/^#//g
   :n1,n2s/^/\/\//g
   ```

5. 指定文本替换

   ```shell
   # 编辑模式下
   :ab mymail wming@hnu.edu.cn	# 在插入模式下输入 mymail 后再输入“空格”+“回车”就会替换成邮箱
   ```

6. 设置永久生效

   编辑自身用户家目录下的`.vimrc`文件，在里面添加"编辑模式"下的命令，比如添加`set nu`后之后使用 vim 都会显示行号。

## 五、软件包管理

> 不管是使用 rpm 还是 yum 安装软件包的方式，最终安装的都是二进制 rpm 包。其中 yum 在线安装解决了依赖问题，但是 yum 在线安装的源是可以指定为本地光盘（光盘里面包含了所有的 rpm 包）的。

### 1. 软件包管理简介

软件包分类：

+ 源码包
  + 脚本安装包（提供安装界面的源码包）
+ 二进制包（rpm 包/系统默认包）

> 源码包优点：
>
> + 开源，可以修改源代码
> + 可以自由选择所需的功能
> + 软件是编译安装，所以更加适合自己的系统，更加稳定也效率更高
> + 卸载方便
>
> 源码包缺点：
>
> + 安装过程繁杂
> + 编译过程较长
> + 难解决编译过程出现的错误

> 二进制包优点：
>
> + 包管理系统简单，只通过几个命令就可以实现包的安装、升级、查询和卸载
> + 安装速度快
>
> 二进制包缺点：
>
> + 已经进行编译处理，不能看到源代码
> + 功能选择不如源码包灵活
> + 具有依赖性

### 2. RPM 命令管理

1. RPM 包命名规则
   + httpd-2.2.15-15.el6.centos.1.i686.rpm
   + httpd：软件包名
   + 2.2.15：软件版本
   + 15：软件发布的次数
   + el6.centos：适合的 Linux 平台
   + i686：适合的硬件平台
   + rpm：rpm 包扩展名

2. RPM 包依赖性

   + 树形依赖：a—>b—>c

   + 环形依赖：a—>b—>c—>a

   + 模块依赖：模块依赖查询网络

     > 由于 RPM 包的依赖性问题，产生了 yum 在线安装（yum 管理不是必须联网，也可以从本地（比如 IOS 光盘）拉取） rpm 包的方式，centos 可以在指定的源服务器拉取上面的 rpm 包，并且自动拉取依赖关系链上的所有 rpm 包。

3. 包全名与包名

   包全名：操作的软件包没有安装时要使用包全名，而且要指明路径

   包名：操作的软件包已经安装时使用包名，系统会搜索 /var/lib/rpm 目录下的 rpm 数据库

4. rpm 安装

   语法：rpm [选项] 包全名

   + -i(install) 安装
   + -v(verbose) 显示安装信息
   + -h(hash) 显示进度
   + --nodeps 不检测依赖性(不能使用)

5. rpm 包升级

   语法：rpm -Uvh 包全名

   + -v(verbose) 显示安装信息
   + -h(hash) 显示进度
   + -U(upgrade) 升级

6. rpm 包卸载

   语法：rpm -e 包名

   + -e(erase) 卸载
   + --nodeps 不检查依赖性

7. 查询软件包是否安装

   语法：rpm -q 包名

   + -q(query) 查询

   + -a(all) 查询所有已经安装的 rpm 包

     ```shell
     # 查询所有已经安装过的 rpm 包
     rpm -qa
     ```

8. 查询软件包详细信息

   语法：rpm -qi 包名

   + -i(information) 查询软件包信息
   + -p(package) 查询未安装的包，`使用包全名`

9. 查询软件包的文件安装位置

   语法：rpm -ql 包名

   + -l(list) 列表
   + -p(package) 查询未安装的包

10. 查询系统文件属于哪个 RPM 包

    语法：rpm -qf 系统文件名

    + -f(file) 查询"系统文件"属于哪个软件包

11. 查询软件包的依赖性

    语法：rpm -qR 包名

    + -R(requires) 查询软件包的依赖性
    + -p(packge) 查询未安装包信息

12. RPM 包校验

    语法：rpm -V 已安装的包名

    + -V(verify)：校验指定 RPM 包中的文件

    验证内容中的 8 个信息的具体内容如下：

    |      |                                                 |
    | ---- | ----------------------------------------------- |
    | S    | 文件大小是否改变                                |
    | M    | 文件的类型或文件的权限(rwx)是否被改变           |
    | 5    | 文件 MD5 校验和是否改变(若改变则文件内容被修改) |
    | D    | 设备的中，从代码是否改变                        |
    | L    | 文件路径是否改变                                |
    | U    | 文件的属主(所有者)是否改变                      |
    | G    | 文件的属组(所属组)是否改变                      |
    | T    | 文件的修改时间是否改变                          |

    文件类型

    |                  |                                                     |
    | ---------------- | --------------------------------------------------- |
    | c(config file)   | 配置文件                                            |
    | d(documentation) | 普通文件                                            |
    | g(ghost file)    | “鬼”文件，很少见，就是该文件不应该被这个 RPM 包包含 |
    | l(license file)  | 授权文件                                            |
    | r(read me)       | 描述文件                                            |

13. RPM 包提取文件

    ```shell
    # . 代表当前路径
    rpm2cpio 包全名 | cpio -idv .文件绝对路径
    ```

    命令 cpio 介绍：

    语法：cpio [选项] < [文件/设备]

    + -i：copy-in 模式，还原
    + -d：还原时自动新建目录
    + -v：显示还原过程

    ```shell
    rpm -qf /bin/ls		# 查询 ls 命令属于哪个 rpm 包
    mv /bin/ls /tmp/	# 造成 ls 命令被删除的假象
    # 从 rpm 包 coreutils-8.4-19.el6.i686.rpm 中提取 ls 到当前目录的 /bin/ls 目录中
    rpm2cpio /mnt/cdrom/Package/coreutils-8.4-19.el6.i686.rpm | cpio -idv ./bin/ls
    ```

### 3. yum 命令管理

> 包名和包全名的概念只存在于 RPM 手动管理中，YUM 管理中只存在包名的概念。

1. IP 地址配置

   ```shell
   # RedHat 系统可以使用 setup 命令配置 IP 地址
   [root@192 ~]# setup
   ```

   ```shell
   # 修改网卡配置选项——ONBOOT="yes",该选项意思为启动该网卡
   [root@192 ~]# vim /etc/sysconfig/network-scripts/ifcfg-enp0s3
   ```

   ```shell
   # 重启网络服务
   [root@192 ~]# service network restart
   ```

   ```shell
   [root@192 ~]# vim /etc/yum.repos.d/CentOS-Base.repo
   
   # CentOS-Base.repo
   #
   # The mirror system uses the connecting IP address of the client and the
   # update status of each mirror to pick mirrors that are updated to and
   # geographically close to the client.  You should use this for CentOS updates
   # unless you are manually picking other mirrors.
   #
   # If the mirrorlist= does not work for you, as a fall back you can try the 
   # remarked out baseurl= line instead.
   #
   #
   
   [base]
   name=CentOS-$releasever - Base
   mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os&infra=$infra
   #baseurl=http://mirror.centos.org/centos/$releasever/os/$basearch/
   gpgcheck=1
   gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
   ```
   
   |            |                                                              |
   | ---------- | ------------------------------------------------------------ |
   | [base]     | 容器名称，一定要放在[]中                                     |
   | name       | 容器说明，可以自己随便写                                     |
   | mirrorlist | 镜像站点，这个可以注释掉                                     |
   | baseurl    | yum 源服务器地址。默认是 Centos 官方的 yum 源服务器，是可以使用的，如果觉得慢可以改成国内的 yum 源地址 |
   | enabled    | 此容器是否生效，如果不写或写成 enable=1 都是生效，写成 enable=0 就是不生效 |
   | gpgcheck   | 如果是 1 是指 RPM 的数字证书生效，如果是 0 则不生效          |
   | gpgkey     | 数字证书的公钥文件保存位置。不用修改                         |
   
2. 常用 yum 命令

   1. 查询

      ```shell
      # 查询所有可用软件包列表
      [root@192 yum.repos.d]# yum list
      
      # 搜索服务器上所有和关键字相关的包
      [root@192 yum.repos.d]# yum search 关键字
      ```

   2. 安装

      ```shell
      [root@192 yum.repos.d]# yum -y install 包名
      ```

      + install 安装
      + -y 自动回答 yes

   3. 升级

      ```shell
      [root@192 yum.repos.d]# yum -y update 包名
      ```

      + update 升级
      + -y 自动回答 yes

      ==如果不接包名，就会升级系统所有软件包，包括内核，慎用==

   4. 卸载
   
      ```shell
      [root@192 yum.repos.d]# yum -y remove 包名
      ```
   
   + remove 卸载
      + -y 自动回答 yes

      ==使用 yum 卸载的问题所在：卸载一个包会卸载该包所依赖的其他包，这些包可能会被其他软件包甚至内核所依赖，所以会导致其他软件或者内核出错。所以尽量不要卸载软件！！！==

   5. yum 软件组管理命令
   
      > 软件组相当于一个软件集合
   
      ```shell
      # 列出所有可用的软件组列表
      [root@192 yum.repos.d]# yum grouplist
      
      # 安装指定软件组
      [root@192 yum.repos.d]# yum groupinstall 软件组名
   
      # 卸载指定软件组
   [root@192 yum.repos.d]# yum groupremove 软件组名
      ```
   
   6. 光盘 yum 源搭建
   
      ```shell
      # 挂载光盘
      mount /dev/cdrom /mnt/cdrom/
      
      # 让网络 yum 源失效
      cd /etc/yum.repos.d/
      mv CentOS-Base.repo CentOS-Base.repo.bak
      mv CentOS-Debuginfo.repo CentOS-Debuginfo.repo.bak
      mv CentOS-Vault.repo CenOS-Vault.repo.bak
      
      # 修改光盘 yum 源文件
      vim CenOS-Media.repo
      ```
   
      ```shell
      # CentOS-Media.repo
      #
      #  This repo can be used with mounted DVD media, verify the mount point for
      #  CentOS-7.  You can use this repo and yum to install items directly off the
      #  DVD ISO that we release.
      #
      # To use this repo, put in your DVD and use it with the other repos too:
      #  yum --enablerepo=c7-media [command]
      #  
      # or for ONLY the media repo, do this:
      #
      #  yum --disablerepo=\* --enablerepo=c7-media [command]
      
      [c7-media]
      name=CentOS-$releasever - Media
      baseurl=file:///mnt/cdrom				# 修改处1——改为光盘的挂载地址
      #        file:///media/cdrom/			# 修改处2——注释
      #        file:///media/cdrecorder/		# 修改处3——注释
      gpgcheck=1
      enabled=1								# 修改处4——改为 1
      gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
      ```

### 4. 源码包和 RPM 包的区别

1. 安装位置

   RPM 包安装在默认位置

   |                 |                            |
   | --------------- | -------------------------- |
   | /etc/           | 配置文件安装位置           |
   | /usr/bin/       | 可执行的命令安装位置       |
   | /usr/lib/       | 程序所使用的函数库保存位置 |
   | /usr/share/doc/ | 基本的软件使用手册保存位置 |
   | /usr/share/man/ | 帮助文件保存位置           |

   源码包应该安装在指定目录当中，一般是`/usr/local/软件名/`

2. 安装位置不同所带来的影响

   rpm 包安装的服务可以使用系统服务管理命令(`service`)来管理，例如 rpm 包安装的 apache 的启动方法：

   ```shell
   /etc/rc.d/init.d/httpd start
   ```

   ```shell
   service httpd start
   ```

   > 上面两种方式都可以启动对应的服务。
   >
   > 由上可知`service` 命令也是去 rpm 包默认的安装位置中寻找是否有相关的服务。
   >
   > 可知路径`/etc/rc.d/init.d/`是 rpm 包安装软件后，软件的可执行服务命令的安装位置。

   由于源码包的安装位置是自定义的，所有接收不了系统服务管理命令的管理，**只能使用绝对路径的方式来启动服务**。

3. 源码包安装

   安装前注意事项：

   + 源代码保存位置：/usr/local/src/
   + 软件安装位置：/usr/local/
   + 如何确定安装过程报错：
     + 安装过程停止
     + 并出现 error/warning/no 的提示

   源码包安装过程

   + 下载源码包

   + 解压缩下载的源码包

   + 进入解压缩目录

   + 依次执行以下命令

     ```shell
     # 软件配置与检查
     ./configure
     ```

     > 1. 定义需要的功能选项
     > 2. 检查系统环境是否符合安装要求
     > 3. 把定义好的功能选项和检测系统环境的信息都写入 Makefile 文件，用于后续的编辑

     ```shell
     # 编译
     make
     ```

     > 如果编译过程出错，执行`make clean`，会清楚编译产生的临时文件，回归源码包最初始的状态。

     ```shell
     # 编译安装,这一步才进行真正的安装,安装目录才会写入内容
     make install
     ```

4. 源码包卸载

   > RPM 包需要使用命令删除，但是源码包不需要卸载命令，直接删除安装目录即可，不会遗留任何垃圾文件。

## 六、用户和用户组管理

### 1. 用户配置文件

> 在 Linux 中主要通过用户配置文件来查看和配置用户信息

1. 文件：/etc/passwd

   ```shell
   root:x:0:0:root:/root:/bin/bash
   bin:x:1:1:bin:/bin:/sbin/nologin
   daemon:x:2:2:daemon:/sbin:/sbin/nologin
   adm:x:3:4:adm:/var/adm:/sbin/nologin
   lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
   sync:x:5:0:sync:/sbin:/bin/sync
   shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
   halt:x:7:0:halt:/sbin:/sbin/halt
   mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
   operator:x:11:0:operator:/root:/sbin/nologin
   games:x:12:100:games:/usr/games:/sbin/nologin
   ftp:x:14:50:FTP User:/var/ftp:/sbin/nologin
   nobody:x:99:99:Nobody:/:/sbin/nologin
   systemd-network:x:192:192:systemd Network Management:/:/sbin/nologin
   dbus:x:81:81:System message bus:/:/sbin/nologin
   polkitd:x:999:998:User for polkitd:/:/sbin/nologin
   sshd:x:74:74:Privilege-separated SSH:/var/empty/sshd:/sbin/nologin
   postfix:x:89:89::/var/spool/postfix:/sbin/nologin
   cwm:x:1000:1000::/home/cwm:/bin/bash
   ```

   > `root:x:0:0:root:/root:/bin/bash`
   >
   > `cwm:x:1000:1000::/home/cwm:/bin/bash`
   >
   > 第 1 字段：用户名称
   >
   > 第 2 字段：密码标志，仅仅只是表示该用户拥有密码
   >
   > 第 3 字段：UID（用户 ID）
   >
   > + 0：超级用户
   > + 1-499：系统用户（伪用户）
   > + 500-65535：普通用户，分配范围不同系统不同？
   >
   > 第 4 字段：GID（用户初始组 ID）
   >
   > 第 5 字段：用户说明
   >
   > 第 6 字段：家目录
   >
   > 第 7 字段：登录之后的 Shell，若设置为`/sbin/nologin`可**禁止**该用户登录

   > 初始组：就是该用户一登录就立刻拥有这个用户组的相关权限，每个用户的初始组只能有一个，一般就是和这个用户的用户名相同的组名作为该用户的用户组。
   >
   > 附加组：用户可以加入其他多个用户组，并拥有这些组的权限，附加组可以有多个。

2. 文件：/etc/shadow

   ```shell
   root:$6$t/mDpEpuvGKaLS0p$GGdWJ1J1oNLecWUmbe2XHxZplC7/vD8BqqNkNfG9M32HxozQDKavXKZ.lHLvCTWJ8Q8d4QxY903gIE8SXwGui.::0:99999:7:::
   bin:*:17632:0:99999:7:::
   daemon:*:17632:0:99999:7:::
   adm:*:17632:0:99999:7:::
   lp:*:17632:0:99999:7:::
   sync:*:17632:0:99999:7:::
   shutdown:*:17632:0:99999:7:::
   halt:*:17632:0:99999:7:::
   mail:*:17632:0:99999:7:::
   operator:*:17632:0:99999:7:::
   games:*:17632:0:99999:7:::
   ftp:*:17632:0:99999:7:::
   nobody:*:17632:0:99999:7:::
   systemd-network:!!:19024::::::
   dbus:!!:19024::::::
   polkitd:!!:19024::::::
   sshd:!!:19024::::::
   postfix:!!:19024::::::
   cwm:$6$068DTlD3$hDt/ra7fB4OhVU1Sdl.hVhuKdslkk9KLJtcFvmC1KSeuD/xo8ZngZaJI0ctqWSZwJak/479e9dbgejxwQ90iB1:19028:0:99999:7:::
   ```

   >`root:$6$t/mDpEpuvGKaLS0p$GGdWJ1J1oNLecWUmbe2XHxZplC7/vD8BqqNkNfG9M32HxozQDKavXKZ.lHLvCTWJ8Q8d4QxY903gIE8SXwGui.::0:99999:7:::`
   >
   >`cwm:$6$068DTlD3$hDt/ra7fB4OhVU1Sdl.hVhuKdslkk9KLJtcFvmC1KSeuD/xo8ZngZaJI0ctqWSZwJak/479e9dbgejxwQ90iB1:19028:0:99999:7:::`
   >
   >第 1 字段：用户名称
   >
   >第 2 字段：密文密码，若是`!!`或`*`代表没有密码，不能登录
   >
   >第 3 字段：密码最后一次修改时间，用时间戳表示
   >
   >第 4 字段：两次密码修改的间隔时间
   >
   >第 5 字段：密码有效期
   >
   >第 6 字段：密码到期前的警告天数
   >
   >第 7 字段：密码过期后的宽限天数
   >
   >+ 0：代表密码过期后立即失效
   >+ -1：代表密码永不失效
   >
   >第 8 字段：账号失效时间
   >
   >第 9 字段：保留

   ```shell
   # 时间戳换算为日期
   date -d "1970-01-01 16066 days"
   
   # 把日期换算为时间戳
   echo $(($(date --date="2014/01/06"+%s)/86400+1))
   ```

3. 文件：/etc/group

   ```shell
   root:x:0:
   ……
   cwm:x:1000:
   ```

   > 第 1 字段：组名
   >
   > 第 2 字段：组密码标志
   >
   > 第 3 字段：GID
   >
   > 第 4 字段：组中附加用户

4. 文件：/etc/gshadow

   ```shell
   root:::
   ……
   cwm:!::
   ```

   > 第 1 字段：组名
   >
   > 第 2 字段：组密码，默认都是没有组密码的
   >
   > 第 3 字段：组管理员用户名
   >
   > 第 4 字段：组中附加用户，不显示初始用户

### 2. 用户管理相关文件

1. 用户的家目录

   + 普通用户：/home/用户名/，所有者和所属组都是此用户，权限是 700
   + 超级用户：/root/，所有者和所属组都是 root 用户，权限是 550

2. 用户的邮箱

   /var/spool/mail/用户名：信息只是存放在内核中，并没有邮箱服务器

3. 用户模板目录

   > 每个新建用户都拥有该目录下的模板文件，可以在该目录下定义新文件，新文件会出现在新建用户的目录下。

   /etc/skel/

### 3. 用户管理命令

1. 添加用户：useradd

   > 一般新建用户不带任何以下选项

   ```shell
   useradd cwm
   -u UID: 手工指定用户 UID 号
   -d 家目录： 手工指定用户家目录
   -c 用户说明： 手工指定用户说明
   -g 组名： 手工指定用户的初始组
   -G 组名： 指定用户的附加组
   -s shell： 手工指定用户的登录 shell。缺省值是 /bin/bash
   ```

   ```shell
   # 实例,但不推荐使用这些选项
   useradd -u 550 -g 组名 -G root -d /home/cwm -c "the handsome boy cwm" -s /bin/bash cwm
   ```

   使用`useradd`相当于修改了下面的配置文件

   ```shell
   /etc/passwd
   /etc/shadow
   /etc/group
   /etc/gshadow
   /home/用户名
   /var/spool/mail/lamp
   ```

   用户默认值文件：/etc/default/useradd，也就是说不使用选项的情况下创建的用户具有以下配置，该文件里面相关配置的说明(说明信息后面的数字表示对应 /etc/passwd 中用户信息的字段)：

   + GROUP=100	用户缺省组，不生效
   + HOME=/home	用户家目录
   + INACTIVE=-1	密码过期宽限天数(7)
   + EXPIRE=	密码失效时间(8)
   + SHELL=/bin/bash	默认 shell
   + SKEL=/etc/skel	模板目录
   + CREATE_MAIL_SPOOL=yes	是否建立邮箱

   用户默认值文件：/etc/login.defs，使用的不多

   + PASS_MAX_DAYS 99999    密码有效期(5)
   + PASS_MIN_DAYS 0    密码修改间隔(4)
   + PASS_MIN_LEN 5    密码最小 5 位
   + PASS_WARN_AGE 7    密码到期警告(6)
   + UID_MIN 500    最小和最大 UID 范围
   + GID_MAX 60000
   + ENCRYPT_METHOD SHA512    加密模式

2. 修改用户密码：passwd

   语法：passwd [选项] 用户名

   > 一般不加以下选项

   + -S    查询用户密码的密码状态，仅 root 用户可用。

   + -l    暂时锁定用户，仅 root 用户可用

   + -u    解锁用户，仅 root 用户可用

   + --stdin    可以将管道符输出的数据作为用户的密码

     ```shell
     [root@localhost ~]# echo "123" | passwd --stdin cwm
     ```

3. 修改用户信息：usermod/chage

   语法：usermod [选项] 用户名

   + -u UID： 修改用户的UID号

   + -c 用户说明： 修改用户的说明信息

     ```shell
     # 说明信息有空格需要加双引号
     usermod -c "test user" lamp
     ```

   + -G 组名： 修改用户的附加组

   + -L： 临时锁定用户（Lock）

   + -U： 解锁用户锁定（Unlock）

   语法：chage [选项] 用户名

   + -l： 列出用户的详细密码状态

   + -d 日期： 修改密码最后一次更改日期（/etc/shadow中的第 3 个字段），这是比较有用的一个选项

     ```shell
     # 这个命令其实是把密码修改日期归 0 了
     # 这样用户一登陆就要修改密码
     chage -d 0 lamp
     ```

   + -m 天数： 两次密码修改间隔（4字段）

   + -M 天数： 密码有效期（5字段）

   + -W 天数： 密码过期前警告天数（6字段）

   + -I 天数： 密码过后宽限天数（7字段）

   + -E 日期： 账号失效时间（8字段）

4. 删除用户：userdel

   语法：userdel [选项] 用户名

   + -r 删除用户的同时删除用户家目录，一般必须加这个选项

   > 这条命令相当于手工删除以下配置文件中该用户的信息
   >
   > /etc/passwd
   >
   > /etc/shadow
   >
   > /etc/group
   >
   > /etc/gshadow
   >
   > rm -rf /var/spool/mail/用户名
   >
   > rm -rf /home/用户名/

5. 查看用户 id

   ```shell
   [root@192 ~]# id cwm
   uid=1000(cwm) gid=1000(cwm) groups=1000(cwm)
   ```

6. 用户切换命令：su

   语法：su [选项] 用户名

   + \- ： 选项只使用“-”代表连带用户的环境 变量一起切换

     ```shell
     su - root
     ```

   + -c 命令： 仅执行一次命令，而不切换用户身份

     ```shell
     # #不切换成 root，但是执行 useradd 命令添加 user1 用户
     su - root -c "useradd user3"
     ```

### 4. 用户组管理命令

1. 添加用户组：groupadd

   语法：groupadd [选项] 组名

   + -g GID：指定组 ID

2. 修改用户组：groupmod

   语法：groupmod [选项] 组名

   + -g GID：修改组 ID
   + -n 新组名：修改组名

3. 删除用户组：groupdel

   语法：groupdel 组名

4. 把用户添加入组或从组中删除：gpasswd

   语法：gpasswd 选项 组名

   + -a 用户名：把用户加入组
   + -d 用户名：把用户从组中删除

## 七、权限管理

### 1. ACL 权限

> ACL 权限指的是为一个指定的用户添加权限，该用户不是文件所有者、不在文件所属组中、和 other 拥有不一样的权限。
>
> 如果给用户赋予了 ACL 权限，是需要和 mask 的权限"与"后才能得到用户的真正权限

1. 查看 ACL 权限：getfacle

   语法：getfacle 文件名

2. 设定 ACL 权限：setfacl

   语法：setfacl [选项] 文件名

+ -m：设定 ACL 权限

  ```shell
  # 修改最大有效权限
  setfacl -m m:rx 文件名
  # 给用户 sc 赋予 r-x 权限，使用 u:用户名:权限 的格式
  setfacl -m u:st:rx /project/
  # 给用户组设定 ACL 权限，使用 g:组名:权限 的格式
  setfacl -m g:tgroup2:rwx prject/
  ```

   + x：删除指定的 ACL 权限
  
     ```shell
     # 删除指定用户的 ACL 权限
     setfacl -x u:用户名 文件名
     
     # 删除指定用户组的 ACL 权限
     setfacl -x g:组名 文件名
     ```
  
   + -b：删除所有的 ACL 权限
  
     ```shell
     # 删除文件的所有 ACL 权限
     setfacl -b 文件名
     ```
  
   + -d：设定默认 ACL 权限
  
     ```shell
     # 如果给父目录设定了默认 ACL 权限,那么父目录中所有新建的子文件都会继承父目录的 ACL 权限
     setfacl -m d:u:用户名:权限 文件名
     ```
  
   + -k：删除默认 ACL 权限
  
   + -R：递归设定 ACL 权限
  
     ```shell
     setfacl -m u:用户名:权限 -R 文件名
     ```


### 2. SetUID

> + 只有可执行的二进制程序才能设定 SetUID 权限
> + 命令执行者需要对该程序拥有 x 执行权限
> + 命令执行者在执行该程序期间将获得该文件"所有者"的身份

比如：passwd 拥有 SetUID 权限，所以普通用户可以借助该命令获得 root 身份后往 shadow 文件写密码

```shell
# s 就表示 SetUID 权限
(LPR) cwm@node1:~$ ll /usr/bin/passwd
-rwsr-xr-x 1 root root 59640 Mar 14  2022 /usr/bin/passwd*
```

1. 设定 SetUID

   语法：chmod 4755 文件名

   或者：chmod u+s 文件名

2. 取消 SetUID

   语法：chmod 755 文件名

   或者：chmod u-s 文件名

### 3. SetGID

> 只有可执行的二进制程序才能设置 SetGID 权限
>
> 命令执行者要对该程序拥有 x 执行权限
>
> 用户在执行命令的时候，组身份将升级为该程序文件的"所属组"

```shell
# s 就表示 SetGID 权限
[root@localhost ~]# ll /usr/bin/locate
-rwx--s--x 1 root slocate 35612 8月 24 2010 /usr/bin/locate
```

> SetGID 对文件夹的作用，普通用户在进入文件夹后的组会变为文件夹的所属组

1. 设定 SetGID

   语法：chmod 2755 文件名

   或者：chmod g+s 文件名

2. 取消 SetGID

   语法：chmod 755 文件名

   或者：chmod g-s 文件名

### 4. SBIT 粘着位

> 若用户对某个目录拥有 w 写权限，则可以删除其他用户的文件，造成安全问题。SBIT 粘着位只对目录起作用。

1. 设置粘着位

   语法：chmod 1755 目录名

   或者：chmod o+t 目录名

2. 取消粘着位

   语法：chmod 777 目录名

   或者：chmod o-t 目录名

### 5. chattr

> i：对文件设置 i 属性，那么不允许对文件进行删除、改名，也不能添加和修改数据；如果对目录设置 i 属性，那么只能修改目录下文件的数据，但不允许建立和删除文件。

> a：对文件设置 a 属性，那么只能在文件中增加数据，但是不能删除也不能修改数据；如果对目录设置 a 属性，那么只允许在目录中建立和修改文件，但是不允许删除。、

1. 查看文件系统属性：lsattr

   语法：lsattr 选项 文件名

   + -a：显示所有文件和目录
   + -d：若目标是目录，仅列出目录本身的属性，而不是子文件的

### 6. sudo

1. 设置普通用户可以使用的 sudo 命令

   ```shell
   # 实际修改的是 /etc/sudoers 文件
   [root@localhost ~]# visudo
   ```

   ```shell
   #用户名 被管理主机的地址=（可使用的身份） 授权命令（绝对路径）
   root ALL=(ALL) ALL
   sc   ALL=/sbin/shutdown -r now # 允许 sc 用户使用重启命令
   # %wheel ALL=(ALL) ALL
   #%组名 被管理主机的地址=（可使用的身份） 授权命令（绝对路径）
   ```

   ```shell
   # sc 重启必须使用完整命令，sudo shutdown -r now 是无效的
   sudo /sbin/shutdown -r now
   ```

2. 借助 root 身份执行命令

   语法：sudo 完整命令

## 八、文件系统管理

### 1. 文件系统常用命令

#### 1. df

命令名称：df [选项] [挂载点]

命令作用：查看分区已使用空间、可使用空间、挂载点等信息

选项：

+ -a 显示所有的文件系统信息，包括特殊文件系统，如 /proc、/sysfs
+ -h 使用习惯单位显示容量，如 KB，MB 或 GB 等
+ -T 显示文件系统类型
+ -m 以 MB 为单位显示容量
+ -k 以 KB 为单位显示容量。默认就是以 KB 为单位

#### 2. du

命令名称：du [选项] [目录/文件名]

命令作用：查看文件和目录大小

选项：

+ -a 显示每个子文件的磁盘占用量。默认只统计 子目录的磁盘占用量
+ -h 使用习惯单位显示磁盘占用量，如 KB，MB 或 GB 等
+ -s 统计总占用量，而不列出子目录和子文件的占用量

> 常用使用方法：du -sh * 列出当前目录下所有目录和文件的总大小

> du 命令和 df 命令的区别
>
> + df 命令是从文件系统考虑的，不光要考虑文件占用的空间，还要统计被命令或程序占用的空间（最常见的就是文件已经删除，但是程序并没有释放空间）
> + du 命令是面向文件的，只会计算文件或目录占用的空间
>
> 所以会看到 du 统计的空间比 df 统计的空间少

#### 3. mount

```shell
# 查询系统中已经挂载的设备，-l 会显示卷标名称
mount [-l]

# 依据配置文件 /etc/fstab 的内容，自动挂载，一般用于修改 /etc/fstab 后尝试挂载文件中的所有分区看是否出错
mount -a
```

挂载命令格式

```shell
mount [-t 文件系统] [-L 卷标名] [-o 特殊选项] 设备文件名 挂载点
```

选项：

+ -t 文件系统：加入文件系统类型来指定挂载的类型，可以ext3、ext4 、iso9660等文件系统

+ -L 卷标名： 挂载指定卷标的分区，而不是安装设备文件名挂载

+ -o 特殊选项：可以指定挂载的额外选项

  | 参数          | 说明                                                         |
  | ------------- | ------------------------------------------------------------ |
  | atime/noatime | 更新访问时间/不更新访问时间。访问分区文件时，是否更新文件的访问时间，默认为更新 |
  | async/sync    | 异步/同步，默认为异步                                        |
  | auto/noauto   | 自动/手动，mount –a命令执行时，是否会自动安装/etc/fstab文件内容挂载，默认为自动 |
  | defaults      | 定义默认值，相当于rw,suid,dev,exec,auto,nouser,async这七个选项 |
  | exec/noexec   | 执行/不执行，设定是否允许在文件系统中执行可执行文件，默认是exec允许 |
  | remount       | 重新挂载已经挂载的文件系统，一般用于指定修改特殊权限         |
  | rw/ro         | 读写/只读，文件系统挂载时，是否具有读写权限，默认是rw        |
  | suid/nosuid   | 具有/不具有SUID权限，设定文件系统是否具有SUID和SGID的权限，默认是具有 |
  | user/nouser   | 允许/不允许普通用户挂载，设定文件系统是否允许普通用户挂载，默认是不允许，只有root可以挂载分区 |
  | usrquota      | 写入代表文件系统支持用户磁盘配额，默认不支持                 |
  | grpquota      | 写入代表文件系统支持组磁盘配额，默认不支持                   |

  ```shell
  # 重新挂载 /home 分区，并使用 noexec 权限
  mount -o remount,noexec /home
  ```

挂载光盘

```shell
# 首先要建立挂载点，就是建立目录
mkdir /mnt/cdrom

# 将光盘挂载到以上目录，由于光盘默认是挂载成 iso9660 文件系统，所以不加 -t iso9660 也可以
mount -t iso9660 /dev/cdrom /mnt/cdrom
mount /dev/sr0 /mnt/cdrom	# 两条命令效果一样，因为 /dev/cdrom 是 /dev/sr0 的软连接
```

卸载光盘命令

```shell
# umount 设备文件名或者挂载名
umount /mnt/cdrom
```

挂载 U 盘

```shell
# 查看当前系统拥有的所有硬盘
fdisk -l
# fat 是 fat16 文件系统，vfat 是 fat32 文件系统
mount -t vfat /dev/sdb1 /mnt/usb
```

#### 4. fsck

命令功能：修复文件系统，但是一般不要使用

命令格式：fsck [选项] 分区设备文件名

+ -a：不用显示用户提示，自动修复文件系统
+ -y：自动修复。和 -a 作用一致，不过有些文件系统只支持 -y

#### 5. dumpe2fs

命令功能：显示磁盘状态命令

命令格式：dumpe2fs 分区设备文件名

### 2. 分区

1. 先查看系统硬盘情况

   ```shell
   fdisk -l
   ```

2. 选择硬盘进行分区

   ```shell
   fdisk /dev/sdb
   ```

   | 命令    | 说明                                                         |
   | ------- | ------------------------------------------------------------ |
   | a       | 设置可引导标记                                               |
   | b       | 编辑 bsd 磁盘标签                                            |
   | c       | 设置 DOS 操作系统兼容标记                                    |
   | d(常用) | 删除一个分区                                                 |
   | l       | 显示已知的文件系统类型。82 为 Linux swap 分区，83 为 Linux 分区 |
   | m(常用) | 显示帮助菜单                                                 |
   | n(常用) | 新建分区                                                     |
   | o       | 建立空白 DOS 分区表                                          |
   | p       | 显示分区列表                                                 |
   | q       | 不保存退出                                                   |
   | s       | 新建空白SUN磁盘标签                                          |
   | t       | 改变一个分区的系统 ID                                        |
   | u       | 改变显示记录单位                                             |
   | v       | 验证分区表                                                   |
   | w(常用) | 保存退出                                                     |
   | x       | 附加功能（仅专家）                                           |

3. 分区完成后若提示需要重启可输入以下命令代替重启

   ```shell
   partprobe
   ```

4. 格式化分区

   ```shell
   mkfs -t ext4 /dev/sdb1
   ```

5. 挂载分区

   ```shell
   mount /disk1
   mount /dev/sdb1 /disk1
   ```

### 3. 分区自动挂载

> 通过修改 /etc/fstab 文件，系统启动时会根据该文件来自动进行分区挂载

+ 第一字段：分区设备文件名或UUID（硬盘通用唯一识别码），可以通过`dumpe2fs /dev/sdxx`来查看 UUID
+ 第二字段：挂载点
+ 第三字段：文件系统名称
+ 第四字段：挂载参数
+ 第五字段：指定分区是否被dump备份，0代表不备份，1代表每天备份，2代表不定期备份
+ 第六字段：指定分区是否被fsck检测，0代表不检测，其他数字代表检测的优先级，那么当然1的优先级比2高

==当由于 /etc/fstab 文件错误导致系统启动失败时的补救措施==

此时仍然能进入系统，使用 root 登录系统后正确修改 /etc/fstab 文件，如果发现由于 / 分区是只读权限不能修改，则重新挂载 / 分区为 rw 权限

```shell
mount -o remount,rw /
```

## 九、Shell 基础

### 1. 简介

Shell 是一个命令行解释器，它为用户提供了一个向 Linux 内核发送请求以便运行程序的界面系统级程序，用户可以用 Shell 来启动、挂起、停止甚至是编写一些程序。

Shell 还是一个功能相当强大的编程语言，易编写，易调试，灵活性较强。Shell 是解释执行的脚本语言，在 Shell 中可以直接调用 Linux 系统命令。

Shell 的分类：

+ Bourne Shell：从 1979 起 Unix 就开始使用 Bourne Shell，Bourne Shell 的主文件名为 sh。
+ C Shell： C Shell 主要在 BSD 版的 Unix 系统中使用，其语法和 C 语言相类似而得名

Shell 的两种主要语法类型有 Bourne 和 C，这两种语法彼此不兼容。Bourne 家族主要包括 sh、ksh、Bash、psh、zsh；C 家族主要包括：csh、tcsh

Bash： Bash与sh兼容，现在使用的Linux就是使用Bash作为用户的基本Shell。

### 2. echo

命令格式：echo [选项] [输出内容]

选项：

+ -e：支持反斜线控制的字符转换

| 控制字符 | 作用                                                         |
| -------- | ------------------------------------------------------------ |
| \\\      | 输出 \ 本身                                                  |
| \a       | 输出警告音                                                   |
| \b       | 退格键，也就是向左删除键                                     |
| \c       | 取消输出行末的换行符。和“-n”选项一致                         |
| \e       | ESCAPE 键                                                    |
| \f       | 换页符                                                       |
| \n       | 换行符                                                       |
| \r       | 回车键                                                       |
| \t       | 制表符，也就是 Tab 键                                        |
| \v       | 垂直制表符                                                   |
| \0nnn    | 按照八进制 ASCII 码表输出字符。其中 0 为数字零，nnn 是三位八进制数 |
| \xhh     | 按照十六进制 ASCII 码表输出字符。其中 hh 是两位十六进制数    |

```shell
[cwm@10 ~]$ echo -e "ab\bc"	# 删除左侧字符
ac
[cwm@10 ~]$ echo -e "a\tb\tc\nd\te\tf"	# 制表符与换行符
a	b	c
d	e	f
[cwm@10 ~]$ echo -e \
> "\x61\t\x62\t\x63\n\x64\t\x65\t\x66"	# 按照十六进制ASCII码也同样可以输出
a	b	c
d	e	f
#输出颜色
#30m=黑色，31m=红色，32m=绿色，33m=黄色
#34m=蓝色，35m=洋红，36m=青色，37m=白色
[cwm@10 ~]$ echo -e "\e[1;31m abcd \e[0m"
 abcd # abcd 是红色显示的
```

### 3. 编写第一个脚本

> #!/bin/bash 是必须存在的，不是注释，bash 必须要全部小写

```shell
[cwm@10 ~]$ vim hello.sh
#!/bin/bash
# The first program
# Author:chiweiming (Email:wming@hnu.edu.cn)
echo -e "chiweiming is the most honest man in the World"
```

```shell
[cwm@10 ~]$ chmod 755 hello.sh
[cwm@10 ~]$ ./hello.sh
chiweiming is the most honest man in the World
```

脚本执行方式：

+ 赋予执行权限，直接执行

  ```shell
  chmod 755 hello.sh
  ./hello.sh
  ```

+ 通过 bash 调用执行脚本

  ```shell
  bash hello.sh
  ```

### 4. bash 的基本功能

#### 1. 历史命令与命令补全

历史命令格式：history [选项] [历史命令保存文件]

选项：

+ -c：清空历史命令，不建议使用
+ -w：把缓存中的历史命令写入历史命令保存文件 ~/.bash_history

历史命令默认会保存1000条,可以在环境变量配置文件/etc/profile中进行修改

历史命令的调用：

+ 使用上、下箭头调用以前的历史命令
+ 使用“!n”重复执行第n条历史命令
+ 使用“!!”重复执行上一条命令
+ 使用“!字串”重复执行最后一条以该字串开头的命令

------

在 Bash 中，命令与文件补全是非常方便与常用的功能，我们只要在输入命令或文件时，按“Tab”键就会自动进行补全。

#### 2. 命令别名与常用快捷键

命令别名：alias 别名='原命令'

```shell
[cwm@10 ~]$ alias
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l.='ls -d .* --color=auto'
alias ll='ls -l --color=auto'
alias ls='ls --color=auto'
alias vi='vim'
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
```

命令执行时顺序

1. 第一顺位执行用绝对路径或相对路径执行的命令。
2. 第二顺位执行别名。
3. 第三顺位执行Bash的内部命令。
4. 第四顺位执行按照$PATH环境变量定义的目录查找顺序找到的第一个命令。

==让别名永久生效，需要在自己的用户环境变量文件中自行编写脚本==

```shell
[cwm@10 ~]$ vi ~/.bashrc
```

删除别名：unalias 别名

------

| 快捷键     | 作用                                                         |
| ---------- | ------------------------------------------------------------ |
| ctrl+A     | 把光标移动到命令行开头。如果我们输入的命令过长，想要把光标移动到命令行开头时使用。 |
| ctrl+E     | 把光标移动到命令行结尾。                                     |
| **ctrl+C** | 强制终止当前的命令。                                         |
| **ctrl+L** | 清屏，相当于clear命令。                                      |
| **ctrl+U** | 删除或剪切光标之前的命令。我输入了一行很长的命令，不用使用退格键一个一个字符的删除，使用这个快捷键会更加方便 |
| ctrl+K     | 删除或剪切光标之后的内容。                                   |
| **ctrl+Y** | 粘贴ctrl+U或ctrl+K剪切的内容。                               |
| **ctrl+R** | 在历史命令中搜索，按下ctrl+R之后，就会出现搜索界面，只要输入搜索内容，就会从历史命令中搜索。 |
| **ctrl+D** | 退出当前终端。                                               |
| ctrl+Z     | 暂停，并放入后台。这个快捷键牵扯工作管理的内容，我们在系统管理章节详细介绍。 |
| ctrl+S     | 暂停屏幕输出。                                               |
| ctrl+Q     | 恢复屏幕输出。                                               |

#### 3. 输入输出重定向

1. 标准输入输出

   | 设备   | 设备文件名  | 文件描述符 | 类型         |
   | ------ | ----------- | ---------- | ------------ |
   | 键盘   | /dev/stdin  | 0          | 标准输入     |
   | 显示器 | /dev/stdout | 1          | 标准输出     |
   | 显示器 | /dev/stderr | 2          | 标准错误输出 |

2. 输出重定向

   | 类型                       | 符号                       | 作用                                                         |
   | -------------------------- | -------------------------- | ------------------------------------------------------------ |
   | 标准输出重定向             | 命令 > 文件                | 以覆盖的方式，把命令的正确输出输出到指定的文件或设备当中。   |
   |                            | 命令 >> 文件               | 以追加的方式，把命令的正确输出输出到指定的文件或设备当中。   |
   | 标准错误输出重定向         | 错误命令 2>文件            | 以覆盖的方式，把命令的错误输出输出到指定的文件或设备当中。   |
   |                            | 错误命令 2>>文件           | 以追加的方式，把命令的错误输出输出到指定的文件或设备当中。   |
   | 正确输出和错误输出同时保存 | 命令 > 文件 2>&1           | 以覆盖的方式，把正确输出和错误输出都保存到同一个文件当中。   |
   |                            | **命令 >> 文件 2>&1**      | **以追加的方式，把正确输出和错误输出都保存到同一个文件当中。** |
   |                            | 命令 &>文件                | 以覆盖的方式，把正确输出和错误输出都保存到同一个文件当中。&>文件之间没有空格 |
   |                            | **命令 &>>文件**           | **以追加的方式，把正确输出和错误输出都保存到同一个文件当中。&>>文件之间没有空格** |
   |                            | **命令 >> 文件1 2>>文件2** | **把正确的输出追加到文件1中，把错误的输出追加到文件2中。**   |

3. 输入重定向

   两种格式：

   1. 命令 < 文件名

   2. 命令 << 标识符

      ……

      标识符

   命令格式：wc [选项] [文件名

   选项：

   + -c：统计字节数
   + -w：统计单词数
   + -l：统计行数

#### 4. 多命令顺序执行与管道符

| 多命令执行符 | 格式             | 作用                                                         |
| ------------ | ---------------- | ------------------------------------------------------------ |
| ;            | 命令1;命令2      | 多个命令顺序执行，命令之间没有任何逻辑联系                   |
| &&           | 命令1 && 命令2   | 逻辑与<br/>当命令1正确执行，则命令2才会执行<br/>当命令1执行不正确，则命令2不会执行 |
| \|\|         | 命令1 \|\| 命令2 | 逻辑或<br/>当命令1 执行不正确，则命令2才会执行<br/>当命令1正确执行，则命令2不会执行 |

```shell
[cwm@10 ~]$ ls;date;cd ~;pwd
hello.sh
Sat Dec 31 05:54:19 CST 2022
/home/cwm
```

------

管道符命令格式：命令1 | 命令2

功能描述：命令1 的正确输出作为命令2 的输入，**利用管道符可以将操作对象是文件的命令转换为操作另一条命令的输出**

```shell
[cwm@10 ~]$ ll /etc | more
total 1304
-rw-r--r--.  1 root root       16 Dec 29 21:55 adjtime
-rw-r--r--.  1 root root     1518 Jun  7  2013 aliases
drwxr-xr-x.  2 root root     4096 Dec 29 21:51 alternatives
-rw-------.  1 root root      541 Apr 11  2018 anacrontab
-rw-r--r--.  1 root root       55 Apr 11  2018 asound.conf
drwxr-x---.  3 root root     4096 Dec 29 21:51 audisp
drwxr-x---.  3 root root     4096 Dec 29 22:01 audit
drwxr-xr-x.  2 root root     4096 Dec 29 21:51 bash_completion.d
```

```shell
# grep 命令本来是作用于文件的
[cwm@10 ~]$ ll /etc | grep -i "yum"
drwxr-xr-x.  6 root root     4096 Dec 29 21:51 yum
-rw-r--r--.  1 root root      970 Apr 13  2018 yum.conf
drwxr-xr-x.  2 root root     4096 Apr 13  2018 yum.repos.d
```

#### 5. 通配符与其他特殊符号

1. 通配符

   | 通配符 | 作用                                                         |
   | ------ | ------------------------------------------------------------ |
   | ?      | 匹配一个任意字符                                             |
   | *      | 匹配0个或任意多个任意字符，也就是可以匹配任何内容            |
   | []     | 匹配中括号中任意一个字符。例如：[abc]代表一定匹配一个字符，或者是a，或者是b，或者是c |
   | [-]    | 匹配中括号中任意一个字符，-代表一个范围。例如：[a-z]代表匹配一个小写字母 |
   | [^]    | 逻辑非，表示匹配不是中括号内的一个字符。例如：\[^0-9]代表匹配一个不是数字的字符 |

   ```shell
   [root@localhost ~]# cd /tmp/
   [root@localhost tmp]# rm -rf *
   [root@localhost tmp]# touch abc
   [root@localhost tmp]# touch abcd
   [root@localhost tmp]# touch 012
   [root@localhost tmp]# touch 0abc
   [root@localhost tmp]# ls ?abc
   [root@localhost tmp]# ls [0-9]*
   [root@localhost tmp]# ls [^0-9]*
   ```

2. bash 中其他特殊符号

   | 符号 | 作用                                                         |
   | ---- | ------------------------------------------------------------ |
   | ' '  | 单引号。在单引号中所有的特殊符号，如“$”和“`”(反引号)都没有特殊含义。 |
   | " "  | 双引号。在双引号中特殊符号都没有特殊含义，但是“$”、“`”和“\”是例外，拥有“调用变量的值”、“引用命令”和“转义符”的特殊含义。 |
   | ``   | 反引号。反引号括起来的内容是系统命令，在Bash中会先执行它。和$()作用一样，不过推荐使用$()，因为反引号非常容易看错。 |
   | $()  | 和反引号作用一样，用来引用系统命令。                         |
   | #    | 在Shell脚本中，#开头的行代表注释。                           |
   | $    | 用于调用变量的值，如需要调用变量name的值时，需要用$name的方式得到变量的值。 |
   | \    | 转义符，跟在\之后的特殊符号将失去特殊含义，变为普通字符。如\$将输出“$”符号，而不当做是变量引用。 |

   ```shell
   [cwm@10 ~]$ echo "$name"
   cwm
   [cwm@10 ~]$ echo '$name'
   $name
   [cwm@10 ~]$ echo '$(date)'
   $(date)
   [cwm@10 ~]$ echo "$(date)"
   Sat Dec 31 06:18:25 CST 2022
   ```

### 5. bash 变量

变量定义注意事项：

1. 在Bash中，变量的默认类型都是字符串型，如果要进行数值运算，则必修指定变量类型为数值型。
2. 变量的值如果有空格，需要使用单引号或双引号包括。
3. 在变量的值中，可以使用“\”转义符。
4. 如果需要增加变量的值，那么可以进行变量值的叠加。不过变量需要用双引号包含“$变量名”或用${变量名}包含。
5. 如果是把命令的结果作为变量值赋予变量，则需要使用反引号或$()包含命令。
6. 环境变量名建议大写，便于区分。

#### 1. 用户自定义变量

1. 变量定义

   ```shell
   [cwm@10 ~]$ name=chiweiming
   [cwm@10 ~]$ set | grep chiweiming
   name=chiweiming
   ```

2. 变量叠加

   ```shell
   # 两种叠加方式
   [cwm@10 ~]$ name="$name"888
   [cwm@10 ~]$ set | grep chiweiming
   name=chiweiming888
   
   [cwm@10 ~]$ name=${name}666
   [cwm@10 ~]$ set | grep chiweiming
   name=chiweiming888666
   
   # 用冒号：进行变量叠加好像也可以，PATH 就是使用这种方式
   [cwm@10 ~]$ name=chiweiming
   [cwm@10 ~]$ echo $name
   chiweiming
   [cwm@10 ~]$ name=$name:/1234
   [cwm@10 ~]$ echo $name
   chiweiming:/1234
   ```

3. 变量调用

   ```shell
   [cwm@10 ~]$ echo $name
   chiweiming888666
   ```

4. 变量查看

   ```shell
   # set 输出 4 种环境变量
   [cwm@10 ~]$ set
   BASH=/bin/bash
   BASHOPTS=checkwinsize:cmdhist:expand_aliases:extquote:force_fignore:histappend:hostcomplete:interactive_comments:login_shell:progcomp:promptvars:sourcepath
   BASH_ALIASES=()
   BASH_ARGC=()
   BASH_ARGV=()
   BASH_CMDS=()
   BASH_LINENO=()
   BASH_SOURCE=()
   BASH_VERSINFO=([0]="4" [1]="2" [2]="46" [3]="2" [4]="release" [5]="x86_64-redhat-linux-gnu")
   BASH_VERSION='4.2.46(2)-release'
   COLUMNS=253
   DIRSTACK=()
   ```

5. 变量删除

   ```shell
   [cwm@10 ~]$ unset name
   [cwm@10 ~]$ set | grep chiweiming
   [cwm@10 ~]$ 
   ```

#### 2. 环境变量

> 这种变量中主要保存的是和系统操作环境相关的数据。用户自定义变量只在当前的Shell中生效，而环境变量会在当前Shell和这个Shell的所有子Shell当中生效。如果把环境变量写入相应的配置文件，那么这个环境变量就会在所有的Shell中生效

1. 设置环境变量

   ```shell
   # 这种方式是临时设置的变量，重新登录 shell 后变量消失
   [cwm@10 ~]$ export name=chiweiming
   [cwm@10 ~]$ env | grep name
   name=chiweiming
   ```

2. 查看环境变量

   ```shell
   [cwm@10 ~]$ env
   XDG_SESSION_ID=23
   HOSTNAME=10.0.2.15
   SELINUX_ROLE_REQUESTED=
   TERM=xterm
   SHELL=/bin/bash
   HISTSIZE=1000
   SSH_CLIENT=192.168.10.1 3955 22
   SELINUX_USE_CURRENT_RANGE=
   SSH_TTY=/dev/pts/0
   USER=cwm
   ```

3. 删除环境变量

   ```shell
   [cwm@10 ~]$ unset name
   ```

------

两个重要的环境变量

+ PATH：系统查找命令的路径

  ```shell
  # 临时改变环境变量 PATH
  [cwm@10 ~]$ PATH="$PATH":/root
  [cwm@10 ~]$ echo $PATH
  /usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/cwm/.local/bin:/home/cwm/bin:/root
  ```

+ PS1：定义系统提示符额变量

  \d：显示日期，格式为“星期 月 日” 

  \h：显示简写主机名。如默认主机名“localhost” 

  \t：显示24小时制时间，格式为“HH:MM:SS” 

  \T：显示12小时制时间，格式为“HH:MM:SS” 

  \A：显示24小时制时间，格式为“HH:MM” 

  \u：显示当前用户名 

  \w：显示当前所在目录的完整名称 

  \W：显示当前所在目录的最后一个目录 

  \\#：执行的第几个命令 

  \\$：提示符。如果是root用户会显示提示符为“#”，如果是普通用户会显示提示符为“$”

#### 3. 位置参数变量

> 这种变量主要是用来向脚本当中传递命令行参数或数据的，变量名不能自定义，变量作用是固定的。

| 位置参数变量 | 作用                                                         |
| ------------ | ------------------------------------------------------------ |
| $n           | n为数字，$0代表命令本身，$1-$9代表第一到第九个参数，十以上的参数需要用大括号包含，如${10}. |
| $*           | 这个变量代表命令行中所有的参数，$*把所有的参数看成一个整体   |
| $@           | 这个变量也代表命令行中所有的参数，不过$@把每个参数区分对待   |
| $#           | 这个变量代表命令行中所有参数的个数                           |

$* 和 $@ 的区别在 for 循环中表现比较明显

```shell
#!/bin/bash
num1=$1
num2=$2
sum=$(($num1+$num2))
echo $sum
```

```shell
#!/bin/bash
echo "A total of $# parameters"
#使用$#代表所有参数的个数
echo "The parameters is: $*"
#使用$*代表所有的参数
echo "The parameters is: $@"
#使用$@也代表所有参数
```

```shell
#!/bin/bash
for i in "$*"
#$*中的所有参数看成是一个整体，所以这个for循环只会循环一次
    do
    	echo "The parameters is: $i"
    done
x=1
for y in "$@"
#$@中的每个参数都看成是独立的，所以“$@”中有几个参数，就会循环几次
    do
        echo "The parameter$x is: $y"
        x=$(( $x +1 ))
    done
```

#### 4. 预定义变量

> 是Bash中已经定义好的变量，变量名不能自定义，变量作用也是固定的。

| 预定义变量 | 作用                                                         |
| ---------- | ------------------------------------------------------------ |
| $?         | 最后一次执行的命令的返回状态。如果这个变量的值为0，证明上一个命令正确执行；如果这个变量的值为非0（具体是哪个数，由命令自己来决定），则证明上一个命令执行不正确了。 |
| $$         | 当前进程的进程号（PID）                                      |
| $!         | 后台运行的最后一个进程的进程号（PID）                        |

```shell
#!/bin/bash
# Author: shenchao （E-mail: shenchao@lampbrother.net）
echo "The current process is $$"
#输出当前进程的PID。
#这个PID就是variable.sh这个脚本执行时，生成的进程的PID
find /root -name hello.sh &
#使用find命令在root目录下查找hello.sh文件
#符号&的意思是把命令放入后台执行，工作管理我们在系统管理章节会详细介绍
echo "The last one Daemon process is $!"
```

------

命令格式：read [选项] [变量名]

命令功能：接收键盘输入并赋值给变量

选项：

+ -p “提示信息”：在等待read输入时，输出提示信息
+ -t 秒数： read命令会一直等待用户输入，使用此选项可以指定等待时间
+ -n 字符数： read命令只接受指定的字符数，就会执行
+ -s： 隐藏输入的数据，适用于机密信息的 输入

```shell
#!/bin/bash
# Author: shenchao （E-mail: shenchao@lampbrother.net）
read -t 30 -p "Please input your name: " name
#提示“请输入姓名”并等待30秒，把用户的输入保存入变量name中
echo "Name is $name "
read -s -t 30 -p "Please enter your age: " age
#年龄是隐私，所以我们用“-s”选项隐藏输入
echo -e "\n"
echo "Age is $age "
read -n 1 -t 30 -p "Please select your gender[M/F]: " gender
#使用“-n 1”选项只接收一个输入字符就会执行（都不用输入回车）
echo -e "\n"
echo "Sex is $gender"
```

### 6. bash 的运算符

#### 1. 数值运算与运算符

声明变量类型命令格式：declare [+/-] [选项] 变量名

选项：

+ -：给变量设定类型属性
+ +：取消变量的类型属性
+ -i：将变量声明为整数型（integer）
+ -x：将变量声明为环境变量
+ -p：显示指定变量的被声明的类型

1. 使用 declare 进行数值运算

   ```shell
   [root@localhost ~]# aa=11
   [root@localhost ~]# bb=22
   #给变量aa和bb赋值
   [root@localhost ~]# declare -i cc=$aa+$bb
   ```

2. expr或let数值运算工具

   ```shell
   [root@localhost ~]# aa=11
   [root@localhost ~]# bb=22
   #给变量aa和变量bb赋值
   [root@localhost ~]# dd=$(expr $aa + $bb)
   #dd的值是aa和bb的和。注意“+”号左右两侧必须有空格
   ```

3. $((运算式))”或“$[运算式]”**（常用）**

   ```shell
   [root@localhost ~]# aa=11
   [root@localhost ~]# bb=22
   [root@localhost ~]# ff=$(( $aa+$bb ))
   [root@localhost ~]# gg=$[ $aa+$bb ]
   ```

------

| 优先级 | 运算符                              | 说明                               |
| ------ | ----------------------------------- | ---------------------------------- |
| 13     | -, +                                | 单目负、单目正                     |
| 12     | !, ~                                | 逻辑非、按位取反或补码             |
| 11     | * , / , %                           | 乘、除、取模                       |
| 10     | +, -                                | 加、减                             |
| 9      | << , >>                             | 按位左移、按位右移                 |
| 8      | < =, > =, < , >                     | 小于或等于、大于或等于、小于、大于 |
| 7      | == , !=                             | 等于、不等于                       |
| 6      | &                                   | 按位与                             |
| 5      | ^                                   | 按位异或                           |
| 4      | \|                                  | 按位或                             |
| 3      | &&                                  | 逻辑与                             |
| 2      | \|\|                                | 逻辑或                             |
| 1      | =,+=,-=,*=,/=,%=,&=, ^=,=, <<=, >>= | 赋值、运算且赋值                   |

#### 2. 变量测试与内容替换

| 变量置换方式 | 变量y没有设置                      | 变量y为空值            | 变量y设置值      |
| ------------ | ---------------------------------- | ---------------------- | ---------------- |
| x=${y-新值}  | x=新值                             | x为空                  | x=$y             |
| x=${y:-新值} | x=新值                             | x=新值                 | x=$y             |
| x=${y+新值}  | x为空                              | x=新值                 | x=新值           |
| x=${y:+新值} | x为空                              | x为空                  | x=新值           |
| x=${y=新值}  | x=新值<br/>y=新值                  | x为空<br/>y值不变      | x=$y<br/>y值不变 |
| x=${y:=新值} | x=新值<br/>y=新值                  | x=新值<br/>y=新值      | x=$y<br/>y值不变 |
| x=${y?新值}  | 新值输出到标准错误输出（就是屏幕） | x为空                  | x=$y             |
| x=${y:?新值} | 新值输出到标准错误输出             | 新值输出到标准错误输出 | x=$y             |

```shell
[root@localhost ~]# unset y
#删除变量y
[root@localhost ~]# x=${y-new}
#进行测试
[root@localhost ~]# echo $x
new
#因为变量y不存在，所以x=new
[root@localhost ~]# y=""
#给变量y赋值为空
[root@localhost ~]# x=${y-new}
#进行测试
[root@localhost ~]# echo $x
[root@localhost ~]# y=old
#给变量y赋值
[root@localhost ~]# x=${y-new}
#进行测试
[root@localhost ~]# echo $x
old
```

### 7. 环境变量配置文件

```shell
[root@localhost ~]# source 配置文件
#或
[root@localhost ~]# . 配置文件
```

> 写进环境变量配置文件的环境变量会永久生效

> 环境变量配置文件中主要是定义对系统的操作环境生效的系统默认环境变量，比如PATH、HISTSIZE、PS1、HOSTNAME等默认环境变量。

![image-20230205010250910](https://github.com/chi199702/notes/blob/main/image/image-20230205010250910.png?raw=true)

上图中，前面的配置文件调用后面的配置文件，后面的配置文件重新定义的变量会覆盖前面的变量，所以一般用追加的方式补充环境变量，比如环境变量 PATH

+ 全局环境配置文件：/etc/profile、/etc/profile.d/*.sh、/etc/bashrc
+ 用户环境配置文件：~/.bash_profile、~/.bashrc

1. /etc/profile 中定义的变量
   + USER变量
   + LOGNAME变量
   + MAIL变量
   + PATH变量
   + HOSTNAME变量
   + HISTSIZE变量
   + umask
   + 调用/etc/profile.d/*.sh文件
2. ~/.bash_profile 的作用
   + 调用了~/.bashrc文件。
   + 在PATH变量后面加入了“:$HOME/bin”这个目录
3. ~/.bashrc 的作用
   + 定义默认别名
   + 调用/etc/bashrc
4. /etc/bashrc 的作用
   + PS1变量
   + umask
   + PATH变量
   + 调用/etc/profile.d/*.sh文件

### 8. 其他配置文件和登录信息

#### 1. 注销时生效的环境变量配置文件

~/.bash_logout

#### 2. 历史命令记录配置文件

~/bash_history

#### 3. Shell 登录信息

本地终端欢迎信息： /etc/issue

| 转义符 | 作用                             |
| ------ | -------------------------------- |
| \d     | 显示当前系统日期                 |
| \s     | 显示操作系统名称                 |
| \l     | 显示登录的终端号，这个比较常用   |
| \m     | 显示硬件体系结构，如i386、i686等 |
| \n     | 显示主机名                       |
| \o     | 显示域名                         |
| \r     | 显示内核版本                     |
| \t     | 显示当前系统时间                 |
| \u     | 显示当前登录用户的序列号         |

------

远程终端欢迎信息： /etc/issue.net

+ 转义符在/etc/issue.net文件中不能使用
+ 是否显示此欢迎信息，由ssh的配置文件/etc/ssh/sshd_config决定，加入“Banner /etc/issue.net”行才能显示（记得重启SSH服务）

------

登陆后欢迎信息：/etc/motd

不管是本地登录，还是远程登录，都可以显示此欢迎信息

## 十、Shell 编程

### 1. 正则表达式

+ 正则表达式用来在文件中匹配符合条件的字符串，正则是包含匹配。grep、awk、sed等命令可以支持正则表达式。
+ 通配符用来匹配符合条件的文件名，通配符是完全匹配。ls、find、cp这些命令不支持正则表达式，所以只能使用shell自己的通配符来进行匹配了。

| 元字符    | 作用                                                         |
| --------- | ------------------------------------------------------------ |
| *         | 前一个字符匹配0次或任意多次。                                |
| .         | 匹配除了换行符外任意一个字符。                               |
| ^         | 匹配行首。例如：^hello会匹配以hello开头的行。                |
| $         | 匹配行尾。例如：hello&会匹配以hello结尾的行。                |
| []        | 匹配中括号中指定的任意一个字符，只匹配一个字符。<br/>例如：[aoeiu] 匹配任意一个元音字母，[0-9] 匹配任意一位数字， \[a-z][0-9]匹配小写字和一位数字构成的两位字符。 |
| [^]       | 匹配除中括号的字符以外的任意一个字符。例如：\[^0-9] 匹配任意一位非数字字符，\[^a-z] 表示任意一位非小写字母。 |
| \         | 转义符。用于取消讲特殊符号的含义取消。                       |
| \\{n\\}   | 表示其前面的字符恰好出现n次。例如：[0-9]\\{4\\} 匹配4位数字，\[1]\[3-8][0-9]\\{9\\} 匹配手机号码。 |
| \\{n,\\}  | 表示其前面的字符出现不小于n次。例如： [0-9]\\{2,\\} 表示两位及以上的数字。 |
| \\{n,m\\} | 表示其前面的字符至少出现n次，最多出现m次。例如： [a-z]\\{6,8\\} 匹配6到8位的小写字母。 |

```shell
# “*”前一个字符匹配0次，或任意多次
grep "a*" test_rule.txt     # 匹配所有内容，包括空白行
grep "aa*" test_rule.txt    # 匹配至少包含有一个a的行
grep "aaa*" test_rule.txt   # 匹配最少包含两个连续a的字符串
grep "aaaaa*" test_rule.txt # 则会匹配最少包含四个个连续a的字符串
```

```shell
# “.” 匹配除了换行符外任意一个字符
grep "s..d" test_rule.txt # “s..d”会匹配在s和d这两个字母之间一定有两个字符的单词
grep "s.*d" test_rule.txt # 匹配在s和d字母之间有任意字符
grep ".*" test_rule.txt   # 匹配所有内容
```

```shell
# “^”匹配行首，“$”匹配行尾
grep "^M" test_rule.txt    # 匹配以大写“M”开头的行
grep "n$" test_rule.txt    # 匹配以小写“n”结尾的行
grep -n "^$" test_rule.txt # 会匹配空白行,-n 是显示行号的选项
```

```shell
# “[]” 匹配中括号中指定的任意一个字符，只匹配一个字符
grep "s[ao]id" test_rule.txt # 匹配s和i字母中，要不是a、要不是o
grep "[0-9]" test_rule.txt   # 匹配任意一个数字
grep "^[a-z]" test_rule.txt  # 匹配用小写字母开头的行
```

```shell
# “[^]” 匹配除中括号的字符以外的任意一个字符
grep "^[^a-z]" test_rule.txt    # 匹配不用小写字母开头的行
grep "^[^a-zA-Z]" test_rule.txt # 匹配不用字母开头的行
```

```shell
# “\” 转义符
grep "\.$" test_rule.txt #匹配使用“.”结尾的行
```

```shell
# “\{n\}”表示其前面的字符恰好出现n次
grep "a\{3\}" test_rule.txt     # 匹配a字母连续出现三次的字符串
grep "[0-9]\{3\}" test_rule.txt # 匹配包含连续的三个数字的字符串
```

```shell
# “\{n,\}”表示其前面的字符出现不小于n次
grep "^[0-9]\{3,\}[a-z]" test_rule.txt #匹配最少用连续三个数字开头的行
```

```shell
# “\{n,m\}”匹配其前面的字符至少出现n次，最多出现m次
grep "sa\{1,3\}i" test_rule.txt #匹配在字母s和字母i之间有最少一个a，最多三个a
```

### 2. 字符截取命令

#### 1. cut

> grep 命令截取的是文件内容的「行」，cut 命令截取的是文件内容的「列」

命令格式：cut [选项] 文件名

- -f 列号：提取第几列
- -d 分隔符：按照指定分隔符分割列

```shell
# 用冒号:做为分隔符提取 /etc/passwd 文件的第一列的用户名
[cwm@10 ~]$ cut -d ":" -f 1,2 /etc/passwd
root
bin
daemon
adm
lp
sync
shutdown
halt
mail
operator
games
ftp
nobody
systemd-network
dbus
polkitd
sshd
postfix
chrony
cwm

# 提取第 1,2 列
[cwm@10 ~]$ cut -d ":" -f 1,2 /etc/passwd
root:x
bin:x
daemon:x
adm:x
lp:x
sync:x
shutdown:x
halt:x
mail:x
operator:x
games:x
ftp:x
nobody:x
systemd-network:x
dbus:x
polkitd:x
sshd:x
postfix:x
chrony:x
cwm:x
```

==cut 命令不能使用空格作为分隔符，若要使用空格进行分隔，去使用 awk==

#### 2. printf

命令格式：printf '输出类型输出格式' 输出内容

输出类型：

+ %ns：   输出字符串。n是数字指代输出几个字符
+ %ni：    输出整数。n是数字指代输出几个数字
+ %m.nf：输出浮点数。m和n是数字，指代输出的整数 位数和小数位数。如%8.2f代表共输出8位数， 其中2位是小数，6位是整数。

输出格式：

+ \a： 输出警告声音
+ \b：输出退格键，也就是Backspace键
+ \f：清除屏幕
+ \n：换行
+ \r：回车，也就是Enter键
+ \t：水平输出退格键，也就是Tab键
+ \v：垂直输出退格键，也就是Tab键

```shell
[cwm@10 ~]$ printf '%s %s %s\n' 1 2 3 4 5 6
1 2 3
4 5 6
[cwm@10 ~]$
```

#### 3. awk

> awk 默认是使用空格和制表符来作为分隔符

在awk命令的输出中支持print和printf命令

+ print：print会在每个输出之后自动加入一个换行符（Linux默认没有print命令）
+ printf：printf是标准格式输出命令，并不会自动加入换行符，如果需要换行，需要手工加入换行符

命令格式：awk '条件1{动作1} 条件2{动作2}……' 文件名

条件：

一般使用关系表达式作为条件

+ x > 10
+ x >= 10
+ x <= 10

动作：

+ 格式化输出
+ 流程控制语句

```shell
# awk 用制表符来分隔每一行后，每个字段依次赋值给 $1 ~ $n 变量
[cwm@10 ~]$ cat student.txt 
ID	Name	PHP	Linux	MySQL	Average
1	Liming	82	95	86	87.66
2	Sc	74	96	87	85.66
3	Gao	99	83	93	91.66
[cwm@10 ~]$ awk '{printf $2 "\t" $6"\n"}' student.txt 
Name	Average
Liming	87.66
Sc	85.66
Gao	91.66
```

------

+ 由于 awk 命令是先读取文件内容后再进行格式输出，所以第一行会直接被赋值给一个变量导致无法分隔，BEGIN 事件一般用于作用于文本的第一行内容。
+ 使用 FS 内置变量进行分隔符设置。
+ END 事件和 BEGIN 事件相反，在最后进行文本输出。

```shell
[cwm@10 ~]$ awk '{FS=":"} {print $1 "\t" $3}' /etc/passwd
root:x:0:0:root:/root:/bin/bash	# 第一行没有进行分隔
bin	1
daemon	2
adm	3
lp	4
sync	5
shutdown	6
halt	7
mail	8
operator	11
games	12
ftp	14
nobody	99
systemd-network	192
dbus	81
polkitd	999
sshd	74
postfix	89
chrony	998
cwm	1000

# 使用 BEGIN 事件后正确分隔
[cwm@10 ~]$ awk 'BEGIN{FS=":"} {print $1 "\t" $3}' /etc/passwd
root	0
bin	1
daemon	2
adm	3
lp	4
sync	5
shutdown	6
halt	7
mail	8
operator	11
games	12
ftp	14
nobody	99
systemd-network	192
dbus	81
polkitd	999
sshd	74
postfix	89
chrony	998
cwm	1000
```

```shell
# END 事件
[cwm@10 ~]$ awk 'BEGIN{FS=":"} {print $1 "\t" $3} END{print "处理结束啦!"}' student.txt 
ID	Name	PHP	Linux	MySQL	Average	
1	Liming	82	95	86	87.66	
2	Sc	74	96	87	85.66	
3	Gao	99	83	93	91.66	
处理结束啦!
```

```shell
# 使用关系运算符作为判断条件
[cwm@10 ~]$ cat student.txt | grep -v "Name" | awk '$6>=87{print $2}'
Liming
Gao
```

#### 4. sed

> sed 是一种几乎包括在所有 UNIX 平台（包括 Linux）的轻量级流编辑器。sed主要是用来将数据进行选取、替换、删除、新增的命令。

==sed 和 vim 的使用区别是：sed 是一个流编辑器，并且可以使用管道符==

命令格式：sed [选项] '[动作]' 文件名

选项：

+ -n：一般sed命令会把所有数据都输出到屏幕 ， 如果加入此选择，则只会把经过sed命令处理的行输出到屏幕。
+ -e：允许对输入数据应用多条sed命令编辑
+ -i：用sed的修改结果直接修改读取数据的文件， 而不是由屏幕输出

动作：

+ a \： 追加，在当前行后添加一行或多行。添加多行时，除最后 一行 外，每行末尾需要用“\”代表数据未完结。
+ c \： 行替换，用c后面的字符串替换原数据行，替换多行时，除最后一行外，每行末尾需用“\”代表数据未完结。
+ i \： 插入，在当期行前插入一行或多行。插入多行时，除最后一行 外，每行末尾需要用“\”代表数据未完结。
+ d： 删除，删除指定的行。
+ p： 打印，输出指定的行。
+ s： 字串替换，用一个字符串替换另外一个字符串。格式为“行范围s/旧字串/新字串/g”（和vim中的替换格式类似）。

==加了 -i 选项后才会修改原文件内容==

```shell
# 查看文件的第二行
# 由于没有使用 -n 选项，其他未被 sed 命令处理的内容也会输出
[cwm@10 ~]$ sed '2p' student.txt 
ID	Name	PHP	Linux	MySQL	Average
1	Liming	82	95	86	87.66
1	Liming	82	95	86	87.66
2	Sc	74	96	87	85.66
3	Gao	99	83	93	91.66
[cwm@10 ~]$ sed -n '2p' student.txt 
1	Liming	82	95	86	87.66
[cwm@10 ~]$ 
```

```shell
# 删除第二行到第四行的数据，但不修改文件本身
[cwm@10 ~]$ sed '2,4d' student.txt 
ID	Name	PHP	Linux	MySQL	Average
[cwm@10 ~]$
```

```shell
# 在第二行后追加 hello
[cwm@10 ~]$ sed '2a hello' student.txt 
ID	Name	PHP	Linux	MySQL	Average
1	Liming	82	95	86	87.66
hello
2	Sc	74	96	87	85.66
3	Gao	99	83	93	91.66

# 在第二行前插入两行数据,原文件内容不会改变
[cwm@10 ~]$ sed '2i hello \
> world' student.txt
ID	Name	PHP	Linux	MySQL	Average
hello 
world
1	Liming	82	95	86	87.66
2	Sc	74	96	87	85.66
3	Gao	99	83	93	91.66
```

```shell
# 第 2 行数据替换成 no such person
[cwm@10 ~]$ sed '2c no such person' student.txt 
ID	Name	PHP	Linux	MySQL	Average
no such person
2	Sc	74	96	87	85.66
3	Gao	99	83	93	91.66
```

```shell
# 在第三行中，把74换成99
[cwm@10 ~]$ sed '3s/74/99/g' student.txt 
ID	Name	PHP	Linux	MySQL	Average
1	Liming	82	95	86	87.66
2	Sc	99	96	87	85.66
3	Gao	99	83	93	91.66
```

```shell
# sed 操作的数据直接写入文件
[cwm@10 ~]$ sed -i '3s/74/99/g' student.txt 
[cwm@10 ~]$ cat student.txt 
ID	Name	PHP	Linux	MySQL	Average
1	Liming	82	95	86	87.66
2	Sc	99	96	87	85.66
3	Gao	99	83	93	91.66
```

```shell
# 同时把“Liming”和“Gao”替换为空
[cwm@10 ~]$ sed -e 's/Liming//g; s/Gao//g' student.txt 
ID	Name	PHP	Linux	MySQL	Average
1		82	95	86	87.66
2	Sc	99	96	87	85.66
3		99	83	93	91.66
```

### 3. 字符处理命令

排序命令：sort [选项] 文件名

选项：

+ -f： 忽略大小写
+ -n： 以数值型进行排序，默认使用字符串型排序
+ -r： 反向排序
+ -t： 指定分隔符，默认的分隔符是制表符
+ -k n[,m]： 按照指定的字段范围排序。从第n字段开始， m字段结束（默认到行尾）

```shell
# 排序用户信息文件
[cwm@10 ~]$ sort /etc/passwd
adm:x:3:4:adm:/var/adm:/sbin/nologin
bin:x:1:1:bin:/bin:/sbin/nologin
chrony:x:998:996::/var/lib/chrony:/sbin/nologin
cwm:x:1000:1000:WeiMing Chi:/home/cwm:/bin/bash
daemon:x:2:2:daemon:/sbin:/sbin/nologin
dbus:x:81:81:System message bus:/:/sbin/nologin
ftp:x:14:50:FTP User:/var/ftp:/sbin/nologin
games:x:12:100:games:/usr/games:/sbin/nologin
halt:x:7:0:halt:/sbin:/sbin/halt
lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
nobody:x:99:99:Nobody:/:/sbin/nologin
operator:x:11:0:operator:/root:/sbin/nologin
polkitd:x:999:998:User for polkitd:/:/sbin/nologin
postfix:x:89:89::/var/spool/postfix:/sbin/nologin
root:x:0:0:root:/root:/bin/bash
shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
sshd:x:74:74:Privilege-separated SSH:/var/empty/sshd:/sbin/nologin
sync:x:5:0:sync:/sbin:/bin/sync
systemd-network:x:192:192:systemd Network Management:/:/sbin/nologin
```

```shell
# 指定分隔符是“：”，用第三字段开头，第三字段结尾排序，就是只用第三字段排序
[root@localhost ~]# sort -t ":" -k 3,3 /etc/passwd

# 把字段当做是数值进行比较排序
[root@localhost ~]# sort -n -t ":" -k 3,3 /etc/passwd
```

------

统计命令：wc [选项] 文件名

选项：

+ -l： 只统计行数
+ -w： 只统计单词数
+ -m： 只统计字符数

### 4. 条件判断

两种判断格式：

+ test -e 文件名

  ```shell
  [cwm@10 ~]$ ls
  canshu1.sh  hello.sh  student.txt
  [cwm@10 ~]$ test -e ~/student.txt 
  [cwm@10 ~]$ echo $?
  0
  ```

+ [ -e 文件名 ]，注意括号旁边必须要留有空格，这种方式最为常用

  ```shell
  [cwm@10 ~]$ [ -e ~/student.txt1 ]
  [cwm@10 ~]$ echo $?
  1
  ```

------

#### 1. 判断文件类型

| 判断选项    | 作用                                                         |
| ----------- | ------------------------------------------------------------ |
| -b 文件     | 判断该文件是否存在，并且是否为块设备文件（是块设备文件为真） |
| -c 文件     | 判断该文件是否存在，并且是否为字符设备文件（是字符设备文件为真） |
| **-d 文件** | **判断该文件是否存在，并且是否为目录文件（是目录为真）**     |
| **-e 文件** | **判断该文件是否存在（存在为真）**                           |
| **-f 文件** | **判断该文件是否存在，并且是否为普通文件（是普通文件为真）** |
| -L 文件     | 判断该文件是否存在，并且是否为符号链接文件（是符号链接文件为真） |
| -p 文件     | 判断该文件是否存在，并且是否为管道文件（是管道文件为真）     |
| -s 文件     | 判断该文件是否存在，并且是否为非空（非空为真）               |
| -S 文件     | 判断该文件是否存在，并且是否为套接字文件（是套接字文件为真） |

```shell
# 判断 /root 是不是目录
[cwm@10 ~]$ [ -d /root ] && echo "YES" || echo "NO"
YES
```

#### 2.判断文件权限

| **判断选项** | **作用**                                                     |
| ------------ | ------------------------------------------------------------ |
| **-r 文件**  | **判断该文件是否存在，并且是否该文件拥有读权限（有读权限为真）** |
| **-w 文件**  | **判断该文件是否存在，并且是否该文件拥有写权限（有写权限为真）** |
| **-x 文件**  | **判断该文件是否存在，并且是否该文件拥有执行权限（有执行权限为真）** |
| -u 文件      | 判断该文件是否存在，并且是否该文件拥有SUID权限（有SUID权限为真） |
| -g 文件      | 判断该文件是否存在，并且是否该文件拥有SGID权限（有SGID权限为真） |
| -k 文件      | 判断该文件是否存在，并且是否该文件拥有SBit权限（有SBit权限为真） |

```shell
# 使用这种方式只要有一个 w 权限即返回真
[cwm@10 ~]$ [ -w student.txt ] && echo "有写权限" || echo "无写权限"
有写权限
```

#### 3. 比较两个文件

| 判断选项        | 作用                                                         |
| --------------- | ------------------------------------------------------------ |
| 文件1 -nt 文件2 | 判断文件1的修改时间是否比文件2的新（如果新则为真）           |
| 文件1 -ot 文件2 | 判断文件1的修改时间是否比文件2的旧（如果旧则为真）           |
| 文件1 -ef 文件2 | 判断文件1是否和文件2的Inode号一致，可以理解为两个文件是否为同一个文件。这个判断用于判断硬链接是很好的方法 |

```shell
# 创建硬连接
[cwm@10 ~]$ ln ~/student.txt /tmp/stu.txt

# 查看两个文件的 inode
[cwm@10 ~]$ ll -i student.txt 
659070 -rw-rw-r--. 2 cwm cwm 97 Jan  1 03:18 student.txt
[cwm@10 ~]$ ll -i /tmp/stu.txt 
659070 -rw-rw-r--. 2 cwm cwm 97 Jan  1 03:18 /tmp/stu.txt

# 判断两个文件的 inode 是否相等
[cwm@10 ~]$ [ student.txt -ef /tmp/stu.txt ] && echo "YES" || echo "NO"
YES
```

#### 4. 比较两个整数

==linux 脚本中判断两个整数不能使用关系符==

| 判断选项        | 作用                                       |
| --------------- | ------------------------------------------ |
| 整数1 -eq 整数2 | 判断整数1是否和整数2相等（相等为真）       |
| 整数1 -ne 整数2 | 判断整数1是否和整数2不相等（不相等位置）   |
| 整数1 -gt 整数2 | 判断整数1是否大于整数2（大于为真）         |
| 整数1 -lt 整数2 | 判断整数1是否小于整数2（小于位置）         |
| 整数1 -ge 整数2 | 判断整数1是否大于等于整数2（大于等于为真） |
| 整数1 -le 整数2 | 判断整数1是否小于等于整数2（小于等于为真） |

```shell
[cwm@10 ~]$ [ 23 -ge 22 ] && echo "YES" || echo "NO"
YES
[cwm@10 ~]$ [ 23 -le 22 ] && echo "YES" || echo "NO"
NO
```

#### 5. 判断字符串

| 判断选项       | 作用                                           |
| -------------- | ---------------------------------------------- |
| -z 字符串      | 判断字符串是否为空（为空返回真）               |
| -n 字符串      | 判断字符串是否为非空（非空返回真）             |
| 字串1 ==字串2  | 判断字符串1是否和字符串2相等（相等返回真）     |
| 字串1 != 字串2 | 判断字符串1是否和字符串2不相等（不相等返回真） |

```shell
[cwm@10 ~]$ name=chiweiming
[cwm@10 ~]$ [ -z "$name" ] && echo "YES" || echo "NO"
NO

[cwm@10 ~]$ [ "$a" == "$b" ] && echo "YES" || echo "NO"
NO

[cwm@10 ~]$ a=11
[cwm@10 ~]$ b=22
[cwm@10 ~]$ [ "$a" == "$b" ] && echo "YES" || echo "NO"
NO
```

#### 6. 多重条件判断

| 判断选项       | 作用                                                 |
| -------------- | ---------------------------------------------------- |
| 判断1 -a 判断2 | 逻辑与，判断1和判断2都成立，最终的结果才为真         |
| 判断1 -o 判断2 | 逻辑或，判断1和判断2有一个成立，最终的结果就为真     |
| ! 判断         | 逻辑非，使原始的判断式取反，注意 ! 后面要加 1 个空格 |

```shell
# 判断变量aa是否有值，同时判断变量aa的是否大于23
# 因为变量aa的值不大于23，所以虽然第一个判断值为真，返回的结果也是假
[cwm@10 ~]$ aa=11
[cwm@10 ~]$ [ -n "$aa" -a "$aa" -gt 23 ] && echo "YES" || echo "NO"
NO
```

### 5. 流程控制

#### 1. if 语句

if 语句格式：

```shell
if [ 条件判断式 ];then
	……
fi

# 或者

if [ 条件判断式 ]
	then
		程序
fi
```

+ if语句使用fi结尾，和一般语言使用大括号结尾不同
+ [ 条件判断式 ]就是使用test命令判断，所以中括号和条件判断式之间必须有空格
+ then后面跟符合条件之后执行的程序，可以放在[]之后，用“；”分割。也可以换行写入，就不需要“；”了

if 多分支语句：

```shell
if [ 条件判断式1 ]
	then
		程序
    elif [ 条件判断式2 ]
    	then
    		程序
    ……
    else
    	程序
fi
```

------

例子1：判断分区使用率

```shell
#!/bin/bash

# 统计 / 分区的使用率
# 作者：池伟鸣 (Email: wming@hnu.edu.cn)

rate=$(df -h | grep "/$" | awk '{print $5}' | cut -d "%" -f 1) # 求出 / 分区使用率

if [ $rate -ge 80 ]
        then
                echo "警告！/ 分区即将爆满！！！"
fi
```

------

例子2：备份 /etc 目录

```shell
#!/bin/bash

# 备份 /etc 目录
# 作者：池伟鸣

date=$(date +%y%m%d) # 计算时间戳
size=$(du -sh /etc)  # 统计 /etc 目录的大小

if [ -d /tmp/etc_back ] # 判断当前目录是否存在
        then
                echo "Date: $date !" &>/tmp/etc_back/etcinfo.txt
                echo "date size: $size" &>>/tmp/etc_back/etcinfo.txt
                cd /tmp/etc_back
                tar -zcf etc_$date.tar.gz /etc etcinfo.txt &>/dev/null
                rm -rf /tmp/etc_back/etcinfo.txt
        else
                mkdir /tmp/etc_back
                echo "Date: $date !" &>/tmp/etc_back/etcinfo.txt
                echo "date size: $size" &>>/tmp/etc_back/etcinfo.txt
                cd /tmp/etc_back
                tar -zcf etc_$date.tar.gz /etc etcinfo.txt &>/dev/null
                rm -rf /tmp/etc_back/etcinfo.txt
fi
```

------

例子3：判断某个服务是否已经启动

```shell
#!/bin/bash

# 使用 nmap 命令扫描服务器端口, 将 ssh 的状态赋值给变量 port
port=$(nmap -sT 192.168.10.10 | grep "tcp" | grep "ssh$" | awk '{print $2}')

if [ "$port"=="open" ]
        then
                echo "$(date) ssh is ok!" &>/tmp/shell.log
        else
                service sshd start &>/dev/null
                echo "$(date) restart ssh !!" &>>/tmp/shell-err.log
fi
```

------

例子4：判断用户输入的是什么文件

```shell
#!/bin/bash

# 接收用户输入，将文件名赋值给 file
read -p "Please input a filename: " file
if [ -z "$file" ]	# 判断用户输入是否为空
        then
                echo "Error, please input a filename"
                exit 1
        elif [ ! -e "$file" ]	# 判断用户输入是否是某个文件名
                then
                        echo "your input is not a file!"
                        exit 2
        elif [ -f "$file" ]		# 用户输入的是文件名
                then
                        echo "$file is a regulare file!"
        elif [ -d "$file" ]		# 用户输入的是目录名
                then
                        echo "$file is a directory!"
        else
                echo "$file is an other file!"
fi
```

#### 2. case 语句

命令格式，不需要进行手动 break

```shell
case $变量名 in
	"值1")
		程序1
		;;
	"值2")
		程序2
		;;
	……
	*)
		类似 default，程序3
		;;
esac
```

```shell
#!/bin/bash
#判断用户输入
# Author: shenchao （E-mail: shenchao@lampbrother.net）
read -p "Please choose yes/no: " -t 30 cho
case $cho in
	"yes")
		echo "Your choose is yes!"
		;;
	"no")
		echo "Your choose is no!"
		;;
	*)
		echo "Your choose is error!"
		;;
esac
```

#### 3. for 循环

语法一

```shell
for 变量 in 值1 值2 值3……
	do
		程序
	done
```

```shell
#!/bin/bash

for time in morning noon afternoon evening
        do
                echo "This time is $time!"
        done
```

```shell
#!/bin/bash
#批量解压缩脚本
# Author: shenchao （E-mail: shenchao@lampbrother.net）
cd /lamp
ls *.tar.gz > ls.log
for i in $(cat ls.log)
	do
		tar -zxf $i &>/dev/null
	done
rm -rf /lamp/ls.log
```

语法二

```shell
for ((初始值; 循环控制条件; 变量变化))
	do
		程序
	done
```

```shell
#!/bin/bash

s=0
for((i=1; i<=100; i=i+1))
        do
                s=$(( $s+$i ))
        done
echo $s
```

```shell
#!/bin/bash
#批量添加指定数量的用户
# Author: shenchao （E-mail: shenchao@lampbrother.net）
read -p "Please input user name: " -t 30 name
read -p "Please input the number of users: " -t 30 num
read -p "Please input the password of users: " -t 30 pass
if [ ! -z "$name" -a ! -z "$num" -a ! -z "$pass" ]
	then
		y=$(echo $num | sed 's/[0-9]//g')
		if [ -z "$y" ]
			then
			for (( i=1;i<=$num;i=i+1 ))
				do
					/usr/sbin/useradd $name$i &>/dev/null
					echo $pass | /usr/bin/passwd --stdin $name$i &>/dev/null
				done
		fi
fi
```

#### 4. while 循环

```shell
while [条件判断式]
	do
		程序
	done
```

```shell
#!/bin/bash
#从1加到100
# Author: shenchao （E-mail: shenchao@lampbrother.net）
i=1
s=0
while [ $i -le 100 ]
#如果变量i的值小于等于100，则执行循环
	do
        s=$(( $s+$i ))
        i=$(( $i+1 ))
	done
echo "The sum is: $s"
```

------

until循环，和while循环相反，until循环时只要条件判断式不成立则进行循环，并执行循环程序。一旦循环条件成立，则终止循环。

```shell
until [条件判断式]
	do
		程序
	done
```

```shell
#!/bin/bash
#从1加到100
# Author: shenchao （E-mail: shenchao@lampbrother.net）
i=1
s=0
until [ $i -gt 100 ]
#循环直到变量i的值大于100，就停止循环
    do
        s=$(( $s+$i ))
        i=$(( $i+1 ))
    done
echo "The sum is: $s"
```

## 十一、服务管理

### 1. 服务介绍

![image-20230205010404399](https://github.com/chi199702/notes/blob/main/image/image-20230205010404399.png?raw=true)

+ 独立的服务：服务单独运行于内存中，直接可以调用
+ 基于 xineted 的服务：这些服务藏于 xineted 后面，接受 xineted 的管理，不直接运行于内存中，要想调用这些服务，必须通过 xineted 来调用，所以调用速度较慢
+ 源码包服务：和独立服务最大的不同就是安装位置不同，不能使用 service 、chkconfig 等命令来查看管理

查看已安装的服务方式：

+ 查看 RPM 包安装的服务：chkconfig --list

  ```shell
  # 0-6 表示 7 个运行级别，表示该服务在对应的运行级别下是否允许自启动
  [cwm@10 ~]$ chkconfig --list
  
  Note: This output shows SysV services only and does not include native
        systemd services. SysV configuration data might be overridden by native
        systemd configuration.
  
        If you want to list systemd services use 'systemctl list-unit-files'.
        To see services enabled on particular target use
        'systemctl list-dependencies [target]'.
  
  netconsole     	0:off	1:off	2:off	3:off	4:off	5:off	6:off
  network        	0:off	1:off	2:on	3:on	4:on	5:on	6:off
  ```

+ 查看源码包安装的服务：只能去`/usr/local/`下查看是否有对应的服务的安装

### 2. RPM 包服务管理

#### 1. 独立服务的管理

RPM 包安装的服务的文件放置位置：

+ /etc/init.d/：启动脚本位置
+ /etc/sysconfig/：初始化环境配置文件位置
+ /etc/：配置文件位置
+ /etc/xinetd.conf：xinetd配置文件
+ /etc/xinetd.d/：基于xinetd服务的启动脚本
+ /var/lib/：服务产生的数据放在这里
+ /var/log/：日志

------

独立服务的启动方式：

+ 使用绝对路径的方式（推荐）：/etc/init.d/独立服务名 start | stop | restart | status
+ 使用 redhat 独有的方式：service 独立服务名 start | stop | restart | status

------

独立服务的自启动方式：

+ （推荐）修改 /etc/rc.d/rc.local 文件：每当系统重启都会执行该文件中的脚本，所以可以将服务的启动脚本写在里面即可。
+ chkconfig [--level 运行级别] [独立服务名] [on|off]
+ 使用 ntsysv 命令管理自启动

#### 2. 基于 xinetd 服务的管理

> 此种服务越来越少，理解即可

```shell
# 安装xinetd与telnet
[root@localhost ~]# yum -y install xinetd
[root@localhost ~]# yum -y install telnet-server
```

```shell
# xinetd服务的启动
[root@localhost ~]# vi /etc/xinetd.d/telnet
service telnet # 服务的名称为telnet
{
    flags = REUSE # 标志为REUSE，设定TCP/IP socket可重用
    socket_type = stream # 使用TCP协议数据包
    wait = no # 允许多个连接同时连接
    user = root # 启动服务的用户为root
    server = /usr/sbin/in.telnetd # 服务的启动程序
    log_on_failure += USERID # 登陆失败后，记录用户的ID
    disable = no # 服务不启动
}

# 重启xinetd服务
[root@localhost ~]# service xinetd restart
```

```shell
# xinetd服务的自启动
[root@localhost ~]# chkconfig telnet on
# 或者通过 ntsysv
```

==xinetd 服务的启动和自启动是连通的，即一旦启动就会自启动，一旦开启自启动就会启动==

### 3. 源码包服务管理

使用绝对路径，调用启动脚本来启动。不同的源码包的启动脚本不同。可以查看源码包的安装说明，查看启动脚本的方法。

```shell
# 比如 apache 源码包启动
/usr/local/apache2/bin/apachectl start|stop
```

------

源码包服务的自启动

```shell
[root@localhost ~]# vi /etc/rc.d/rc.local 
#加入 
/usr/local/apache2/bin/apachectl start
```

------

让源码包服务能被服务管理命令识别（不推荐这么做）

```shell
# 让源码包的apache服务能被service命令管理启动
ln -s /usr/local/apache2/bin/apachectl /etc/init.d/apache
```

```shell
# 让源码包的apache服务能被chkconfig与ntsysv命令管理自启动
vi /etc/init.d/apache 
# 加入以下内容（指定httpd脚本可以被chkconfig命令管理。格式是： chkconfig： 运行级别 启动顺序 关闭顺序）
# chkconfig: 35 86 76 
# description: source package apache
```

```shell
[root@localhost ~]# chkconfig --add apache
#把源码包apache加入chkconfig命令
```

### 4. 服务管理总结

![image-20230205010454276](https://github.com/chi199702/notes/blob/main/image/image-20230205010454276.png?raw=true)

## 十二、系统管理

### 1. 进程管理

#### 1. 查看进程

##### 1. ps

```shell
# 查看系统中所有进程，使用BSD操作系统格式
[cwm@kunpeng etc]$ ps aux | more
USER        PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root          1  0.0  0.0 160384 12224 ?        Ss    2022   0:23 /usr/lib/systemd/systemd --
root          2  0.0  0.0      0     0 ?        S     2022   0:00 [kthreadd]
root          3  0.0  0.0      0     0 ?        I<    2022   0:00 [rcu_gp]
root          4  0.0  0.0      0     0 ?        I<    2022   0:00 [rcu_par_gp]
root          6  0.0  0.0      0     0 ?        I<    2022   0:00 [kworker/0:0H-ev]
root          8  0.0  0.0      0     0 ?        I     2022   0:05 [kworker/u256:0-]
root          9  0.0  0.0      0     0 ?        I<    2022   0:00 [mm_percpu_wq]
root         10  0.0  0.0      0     0 ?        S     2022   0:00 [ksoftirqd/0]
root         11  0.0  0.0      0     0 ?        I     2022   2:04 [rcu_sched]
root         12  0.0  0.0      0     0 ?        S     2022   0:00 [migration/0]
root         14  0.0  0.0      0     0 ?        S     2022   0:00 [cpuhp/0]
root         15  0.0  0.0      0     0 ?        S     2022   0:00 [cpuhp/1]
root         16  0.0  0.0      0     0 ?        S     2022   0:00 [migration/1]
root         17  0.0  0.0      0     0 ?        S     2022   0:00 [ksoftirqd/1]
root         19  0.0  0.0      0     0 ?        I<    2022   0:00 [kworker/1:0H-ev]

# 查看系统中所有进程，使用Linux标准命令格式
[cwm@kunpeng etc]$ ps -le | more
F S   UID    PID   PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0      1      0  0  80   0 -  2506 -      ?        00:00:23 systemd
1 S     0      2      0  0  80   0 -     0 -      ?        00:00:00 kthreadd
1 I     0      3      2  0  60 -20 -     0 -      ?        00:00:00 rcu_gp
1 I     0      4      2  0  60 -20 -     0 -      ?        00:00:00 rcu_par_gp
1 I     0      6      2  0  60 -20 -     0 -      ?        00:00:00 kworker/0:0H-ev
1 I     0      8      2  0  80   0 -     0 -      ?        00:00:05 kworker/u256:0-
1 I     0      9      2  0  60 -20 -     0 -      ?        00:00:00 mm_percpu_wq
1 S     0     10      2  0  80   0 -     0 -      ?        00:00:00 ksoftirqd/0
1 I     0     11      2  0  80   0 -     0 -      ?        00:02:04 rcu_sched
1 S     0     12      2  0 -40   - -     0 -      ?        00:00:00 migration/0
1 S     0     14      2  0  80   0 -     0 -      ?        00:00:00 cpuhp/0
1 S     0     15      2  0  80   0 -     0 -      ?        00:00:00 cpuhp/1
1 S     0     16      2  0 -40   - -     0 -      ?        00:00:00 migration/1
1 S     0     17      2  0  80   0 -     0 -      ?        00:00:00 ksoftirqd/1
1 I     0     19      2  0  60 -20 -     0 -      ?        00:00:00 kworker/1:0H-ev
```

==以 ps aux 的输出为准==

| 字段    | 作用                                                         |
| ------- | ------------------------------------------------------------ |
| USER    | 该进程是由哪个用户产生的                                     |
| PID     | 进程的ID号                                                   |
| %CPU    | 该进程占用CPU资源的百分比，占用越高，进程越耗费资源          |
| %MEM    | 该进程占用物理内存的百分比，占用越高，进程越耗费资源         |
| VSZ     | 该进程占用虚拟内存的大小，单位KB                             |
| RSS     | 该进程占用实际物理内存的大小，单位KB                         |
| TTY     | 该进程是在哪个终端中运行的。其中tty1-tty7代表本地控制台终端，tty1-tty6是本地的字符界面终端，tty7是图形终端。pts/0-255代表虚拟终端 |
| STAT    | 进程状态。常见的状态有：R：运行、S：睡眠、T：停止状态、s：包含子进程、+：位于后台 |
| START   | 该进程的启动时间                                             |
| TIME    | 该进程占用CPU的运算时间，注意不是系统时间                    |
| COMMAND | 产生此进程的命令名                                           |

##### 2. pstree

命令格式：pstree [选项]

+ -p：显示进程的PID
+ -u：显示进程的所属用户

##### 3. top

命令格式：top [选项]

+ -d 秒数： 指定top命令每隔几秒更新。默认是3秒

在top命令的交互模式当中可以执行的命令：

+ ?或h： 显示交互模式的帮助
+ P： 以CPU使用率排序，默认就是此项
+ M：以内存的使用率排序
+ N：以PID排序
+ q：退出top

==top 输出内容含义==

```shell
[cwm@kunpeng etc]$ ps -le | more
F S   UID    PID   PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
top - 16:53:41 up 7 days,  1:55,  2 users,  load average: 0.00, 0.00, 0.00
Tasks: 1162 total,   1 running, 560 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem : 26769120+total, 26102611+free,  4061440 used,  2603648 buff/cache
KiB Swap:  4194240 total,  4194240 free,        0 used. 24200704+avail Mem 

   PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND                   
106275 cwm       20   0  118912   8896   3712 R   0.7  0.0   0:00.10 top                       
103003 cwm       20   0  945536  91520  33088 S   0.3  0.0   0:10.72 node                       
103041 cwm       20   0  870336  62272  31232 S   0.3  0.0   0:05.71 node                       
     1 root      20   0  160384  12224   6016 S   0.0  0.0   0:23.93 systemd                   
     2 root      20   0       0      0      0 S   0.0  0.0   0:00.28 kthreadd                   
     3 root       0 -20       0      0      0 I   0.0  0.0   0:00.00 rcu_gp                     
```

| 第一行                         | 字段含义                                                     |
| ------------------------------ | ------------------------------------------------------------ |
| 16:53:41                       | 系统当前时间                                                 |
| up 7 days,  1:55               | 系统的运行时间，本机已经运行7天1小时55分钟                   |
| 2 users                        | 当前登录了两个用户                                           |
| load average: 0.00, 0.00, 0.00 | 系统在之前1分钟，5分钟，15分钟的平均负载。一般认为小于1时，负载较小。如果大于1，系统已经超出负荷 |

| 第二行            | 字段含义                                  |
| ----------------- | ----------------------------------------- |
| Tasks: 1162 total | 系统中的进程总数                          |
| 1 running         | 正在运行的进程数                          |
| 560 sleeping      | 睡眠的进程                                |
| 0 stopped         | 正在停止的进程                            |
| 0 zombie          | 僵尸进程。如果不是0，需要手工检查僵尸进程 |

| 第三行           | 字段含义                                                     |
| ---------------- | ------------------------------------------------------------ |
| %Cpu(s):  0.0 us | 用户模式占用的CPU百分比                                      |
| 0.0 sy           | 系统模式占用的CPU百分比                                      |
| 0.0 ni           | 改变过优先级的用户进程占用的CPU百分比                        |
| 100.0 id         | 空闲CPU的CPU百分比                                           |
| 0.0 wa           | 等待输入/输出的进程的占用CPU百分比                           |
| 0.0 hi           | 硬中断请求服务占用的CPU百分比                                |
| 0.0 si           | 软中断请求服务占用的CPU百分比                                |
| 0.0 st           | st（Steal time）虚拟时间百分比。就是当有虚拟机时，虚拟CPU等待实际CPU的时间百分比。 |

| 第四行                   | 字段含义               |
| ------------------------ | ---------------------- |
| KiB Mem : 26769120+total | 物理内存的总量，单位KB |
| 26102611+free            | 空闲的物理内存数量     |
| 4061440 used             | 已经使用的物理内存数量 |
| 2603648 buff/cache       | 作为缓冲的内存数量     |

| 第五行                   | 字段含义                     |
| ------------------------ | ---------------------------- |
| KiB Swap:  4194240 total | 交换分区（虚拟内存）的总大小 |
| 4194240 free             | 空闲交换分区的大小           |
| 0 used                   | 已经使用的交互分区的大小     |
| 24200704+avail Mem       | 可用交换内存总大小？         |

#### 2. 终止进程

##### 1. kill

命令使用示范：kill -数字 进程PID

```shell
# 查看可用的进程信号
[cwm@kunpeng etc]$ kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```

| 信号数字 | 信号名称 | 说明                                                         |
| -------- | -------- | ------------------------------------------------------------ |
| 1        | SIGHUP   | 该信号让进程立即关闭，然后重新读取配置文件之后重启。         |
| 2        | SIGINT   | 程序终止信号，用于终止前台进程。相当于输出ctrl+c快捷键。     |
| 8        | SIGFPE   | 在发生致命的算术运算错误时发出. 不仅包括浮点运算错误, 还包括溢出及除数为0等其它所有的算术的错误。 |
| 9        | SIGKILL  | 用来立即结束程序的运行. 本信号不能被阻塞、处理和忽略。一般用于强制终止进程。 |
| 14       | SIGALRM  | 时钟定时信号, 计算的是实际的时间或时钟时间. alarm函数使用该信号。 |
| 15       | SIGTERM  | 正常结束进程的信号，kill命令的默认信号。有时如果进程已经发生问题，这个信号是无法正常终止进程的，我们才会尝试SIGKILL信号，也就是信号9。 |
| 18       | SIGCONT  | 该信号可以让暂停的进程恢复执行，本信号不能被阻断。           |
| 19       | SIGSTOP  | 该信号可以暂停前台进程，相当于输入ctrl+z快捷键。本信号不能被阻断。 |

##### 2. killall

命令格式：killall [选项] [信号] 进程名

功能描述：按照进程名杀死进程

+ -i：交互式，询问是否要杀死某个进程
+ -I：忽略进程名的大小写

##### 3. pkill

命令格式：pkill [选项] [信号] 进程名

功能描述：按照进程名杀死进程

+ -t 终端号：按照终端号踢出用户

  ```shell
  [root@localhost ~]# w
  #使用w命令查询本机已经登录的用户
  [root@localhost ~]# pkill -t -9 pts/1
  #强制杀死从pts/1虚拟终端登录的进程
  ```

### 2. 工作管理

#### 1. 查看后台的工作

命令格式：jobs [选项]

+ -l：显示工作的 PID

注：`+`号代表最近那个放入后台的工作，也是工作恢复时，默认恢复的工作。`-`号代表倒数第二个放入后台的工作。

#### 2. 把进程放入后台

两种方式：

1. 命令后面加 &

   ```shell
   tar -zcf etc.tar.gz /etc &
   ```

2. 在命令的执行过程中按下`ctrl+z`快捷键

> 两种方式的区别：第一种方式程序会在后台继续运行，第二种方式程序在后台不运行。

#### 3. 将后台暂停的工作恢复到前台执行

命令格式：fg %工作号

其中 % 可以省略，工作号使用`jobs`命令查看

#### 4. 把后台暂停的工作恢复到后台执行

命令格式：bg %工作号

注意：恢复到后台执行的命令是不能和前台有交互的，否则就会恢复失败（比如 top 命令）。

### 3. 系统信息查看

#### 1. vmstat

命令格式：vmstat [刷新延时] [刷新次数]

```shell
[cwm@kunpeng ~]$ vmstat 3 3
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 260499648   3200 3032128    0    0     0     0    0    0  0  0 100  0  0
 0  0      0 260494848   3200 3032256    0    0     0     0  831  564  0  0 100  0  0
 0  0      0 260497728   3200 3032256    0    0     0     0  754  519  0  0 100  0  0
```

#### 2. dmesg

命令格式：dmesg

功能描述：查看开机时内核检测信息

#### 3. free

功能描述：查看内存使用状态

命令格式：free [选项]

+ -b： 以字节为单位显示
+ -k： 以KB为单位显示，默认就是以 KB为单位显示
+ -m： 以MB为单位显示
+ -g： 以GB为单位显示

> 缓存和缓冲的区别：
>
> 简单来说缓存（cache）是用来加速数据从硬盘中“读取”的，而缓冲（buffer）是用来加速数据“写入”硬盘的。

#### 4. CPU

```shell
cat /proc/cpuinfo
```

#### 5. uptime

```shell
# 显示系统的启动时间和平均负载，也就是top命令的第一行。w命令也可以看到这个数据。
[cwm@kunpeng ~]$ uptime
 13:26:50 up 7 days, 22:28,  1 user,  load average: 0.00, 0.00, 0.00
```

#### 6. 系统内核

命令格式：uname [选项]

+ -a： 查看系统所有相关信息
+ -r： 查看内核版本
+ -s： 查看内核名称

#### 7. 32/64位

```shell
[cwm@kunpeng ~]$ file /bin/ls
/bin/ls: ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 3.7.0, BuildID[sha1]=1dd6bc7dc7ec5ba5103d77a77608f48257831b8f, stripped
```

#### 8. 系统发行版本

```shell
[cwm@kunpeng ~]$ cat /etc/system-release
CentOS Linux release 7.9.2009 (AltArch)
```

#### 9. 查看进程打开或使用的文件信息

命令格式：lsof [选项]

+ -c 字符串： 只列出以字符串开头的进程打开 的文件
+ -u 用户名： 只列出某个用户的进程打开的文 件
+ -p pid： 列出某个PID进程打开的文件

### 4. 系统定时任务

1. 需要先开启服务 crond(默认是开启的)

   ```shell
   [root@localhost ~]# service crond restart
   ```

2. 使用 crontab 命令

   命令格式：crontab [选项]

   + -e： 编辑crontab定时任务
   + -l： 查询crontab任务
   + -r： 删除当前用户所有的crontab 任务

   定时任务格式：* * * * * command

   | 项目      | 含义                 | 范围                    |
   | --------- | -------------------- | ----------------------- |
   | 第一个“*” | 一小时当中的第几分钟 | 0-59                    |
   | 第二个“*” | 一天当中的第几小时   | 0-23                    |
   | 第三个“*” | 一个月当中的第几天   | 1-31                    |
   | 第四个“*” | 一年当中的第几月     | 1-12                    |
   | 第五个“*” | 一周当中的星期几     | 0-7（0和7都代表星期日） |

   | 特殊符号 | 含义                                                         |
   | -------- | ------------------------------------------------------------ |
   | *        | 代表任何时间。比如第一个“*”就代表一小时中每分钟都执行一次的意思 |
   | ,        | 代表不连续的时间。比如“0 8,12,16 * * * 命令”，就代表在每天的8点0分，12点0分，16点0分都执行一次命令 |
   | -        | 代表连续的时间范围。比如“0 5 * * 1-6命令”，代表在周一到周六的凌晨5点0分执行命令 |
   | */n      | 代表每隔多久执行一次。比如“*/10 * * * * 命令”，代表每隔10分钟就执行一遍命令 |

   ```shell
   [cwm@kunpeng ~]$ crontab -e
   45 22 * * * 命令	# 在22点45分执行命令
   0 17 * * 1 命令	# 每周1 的17点0分执行命令
   0 5 1,15 * * 命令	# 每月1号和15号的凌晨5点0分执行命令
   40 4 * * 1-5 命令	# 每周一到周五的凌晨4点40分执行命令
   */10 4 * * * 命令	# 每天的凌晨4点，每隔10分钟执行一次命令
   0 0 1,15 * 1 命令	# 每月1号和15号，每周1的0点0分都会执行命令。注意：星期几和几号最好不要同时出现，因为他们定义的都是天。非常容易让管理员混乱。
   ```

   ```shell
   */5 * * * * /bin/echo ”11” >> /tmp/test
   5 5 * * 2 /sbin/shutdown -r now
   0 5 1,10,15 * * /root/sh/autobak.sh
   ```

## 十三、日志管理

### 1. 日志简介

linux 的日志服务是 rsyslogd，linux 依靠这个服务来管理日志，确定 rsyslogd 服务已经启动：`ps aux | grep "rsyslogd"`

常见日志文件的位置和作用

| 日志文件             | 说明                                                         |
| -------------------- | ------------------------------------------------------------ |
| /var/log/cron        | 记录了系统定时任务相关的日志                                 |
| /var/log/cups        | 记录打印信息的日志                                           |
| /var/log/dmesg       | 记录了系统在开机时内核自检的信息。也可以使用dmesg命令直接查看内核自检信息 |
| /var/log/btmp        | 记录错误登录的日志。这个文件是二进制文件，不能直接vi查看，而要使用lastb命令查看，命令如下：<br/>[root@localhost log]# lastb<br/>root tty1 Tue Jun 4 22:38 - 22:38 (00:00)<br/>#有人在6月4日22:38使用root用户，在本地终端1登录错误 |
| **/var/log/lastlog** | **记录系统中所有用户最后一次的登录时间的日志。这个文件也是二进制文件，不能直接vi，而要使用lastlog命令查看** |
| /var/log/mailog      | 记录邮件信息                                                 |
| /var/log/message     | 记录系统重要信息的日志。这个日志文件中会记录Linux系统的绝大多数重要信息，如果系统出现问题时，首先要检查的就应该是这个日志文件 |
| /var/log/secure      | 记录验证和授权方面的信息，只要涉及账户和密码的程序都会记录。比如说系统的登录，ssh的登录，su切换用户，sudo授权，甚至添加用户和修改用户密码都会记录在这个日志文件中 |
| **/var/log/wtmp**    | **永久记录所有用户的登录、注销信息，同时记录系统的启动、重启、关机事件。同样这个文件也是一个二进制文件，不能直接vi，而需要使用last命令来查看** |
| **/var/run/utmp**    | **记录当前已经登录的用户的信息。这个文件会随着用户的登录和注销而不断变化，只记录当前登录用户的信息。同样这个文件不能直接vi，而要使用w，who，users等命令来查询** |

> 除了系统默认的日志之外，采用RPM方式安装的系统服务也会默认把日志记录在/var/log/目录中（源码包安装的服务日志是在源码包指定目录中）。不过这些日志不是由rsyslogd服务来记录和管理的，而是各个服务使用自己的日志管理文档来记录自身日志。

### 2. rsyslogd 服务

#### 1. 日志文件格式

基本日志格式包含以下四列：

+ 事件产生的时间
+ 发生事件的服务器的主机名
+ 产生事件的服务名或程序名
+ 事件的具体信息

#### 2. 配置文件

配置文件是 /etc/rsyslog.conf，对此文件的格式分析：

```shell
# 格式是：服务名称[连接符号]日志等级	日志记录位置
authpriv.*                                              /var/log/secure
# Log all the mail messages in one place.
mail.*                                                  -/var/log/maillog
# Log cron stuff
cron.*                                                  /var/log/cron
```

| 服务名称      | 说明                                                         |
| ------------- | ------------------------------------------------------------ |
| auth          | 安全和认证相关消息（不推荐使用authpriv替代）                 |
| authpriv      | 安全和认证相关消息（私有的）                                 |
| cron          | 系统定时任务cront和at产生的日志                              |
| daemon        | 和各个守护进程相关的日志                                     |
| ftp           | ftp守护进程产生的日志                                        |
| kern          | 内核产生的日志（不是用户进程产生的）                         |
| local0-local7 | 为本地使用预留的服务                                         |
| lpr           | 打印产生的日志                                               |
| mail          | 邮件收发信息                                                 |
| news          | 与新闻服务器相关的日志                                       |
| syslog        | 有syslogd服务产生的日志信息（虽然服务名称已经改为rsyslogd，但是很多配置都还是沿用了syslogd的，这里并没有修改服务名） |
| user          | 用户等级类别的日志信息                                       |
| uucp          | uucp子系统的日志信息，uucp是早期linux系统进行数据传递的协议，后来也常用在新闻组服务中 |

连接符号

+ “\*”：代表所有日志等级，比如：“authpriv.*”代表authpriv认证信息服务产生的日志，所有的日志等级都记录
+ “.”：代表只要比后面的等级高的（包含该等级）日志都记录下来。比如：“cron.info”代表cron服务产生的日志，只要日志等级大于等于info级别，就记录
+ “.=”：代表只记录所需等级的日志，其他等级的都不记录。比如：“*.=emerg”代表人和日志服务产生的日志，只要等级是emerg等级就记录。这种用法及少见，了解就好
+ “.!”：代表不等于，也就是除了该等级的日志外，其他等级的日志都记录。

| 等级名称 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| debug    | 一般的调试信息说明                                           |
| info     | 基本的通知信息                                               |
| notice   | 普通信息，但是有一定的重要性                                 |
| warning  | 警告信息，但是还不回影响到服务或系统的运行                   |
| err      | 错误信息，一般达到err等级的信息以及可以影响到服务或系统的运行了 |
| crit     | 临界状况信息，比err等级还要严重                              |
| alert    | 警告状态信息，比crit还要严重。必须立即采取行动               |
| emerg    | 疼痛等级信息，系统已经无法使用了                             |

日志可以存放的位置

+ 日志文件的绝对路径，如“/var/log/secure”
+ 系统设备文件，如“/dev/lp0”
+ 转发给远程主机，如“@192.168.0.210:514”
+ 用户名，如“root”
+ 忽略或丢弃日志，如“~”

### 3. 日志轮替

日志轮替指的是日志的**切割**和**删除**。Linux 系统会为用 RPM 包安装的服务进行日志管理，源码包安装的服务如果想交给 Linux 系统来管理必须**手动配置**。

如何配置管理 Linux 系统的日志轮替？通过配置`/etc/logrotate.conf`即可。

```shell
[cwm@kunpeng ~]$ vim /etc/logrotate.conf
# see "man logrotate" for details
# rotate log files weekly
weekly

# keep 4 weeks worth of backlogs
rotate 4

# create new (empty) log files after rotating old ones
create

# use date as a suffix of the rotated file
dateext

# uncomment this if you want your log files compressed
#compress

# RPM packages drop log rotation information into this directory
include /etc/logrotate.d

# no packages own wtmp and btmp -- we'll rotate them here
/var/log/wtmp {
    monthly
    create 0664 root utmp
        minsize 1M
    rotate 1
}

/var/log/btmp {
    missingok
    monthly
    create 0600 root utmp
    rotate 1
}

# system-specific logs may be also be configured here.
```

| 参数                    | 参数说明                                                     |
| ----------------------- | ------------------------------------------------------------ |
| daily                   | 日志的轮替周期是每天                                         |
| weekly                  | 日志的轮替周期是每周                                         |
| monthly                 | 日志的轮替周期是每月                                         |
| rotate 数字             | 保留的日志文件的个数。0指没有备份                            |
| compress                | 日志轮替时，旧的日志进行压缩                                 |
| create mode owner group | 建立新日志，同时指定新日志的权限与所有者和所属组。如create 0600 root utmp |
| mail address            | 当日志轮替时，输出内容通过邮件发送到指定的邮件地址。如mail shenc@lamp.net |
| missingok               | 如果日志不存在，则忽略该日志的警告信息                       |
| notifempty              | 如果日志为空文件，则不进行日志轮替                           |
| minsize 大小            | 日志轮替的最小值。也就是日志一定要达到这个最小值才会轮替，否则就算时间达到也不轮替 |
| size 大小               | 日志只有大于指定大小才进行日志轮替，而不是按照时间轮替。如size 100k |
| dateext                 | 使用日期作为日志轮替文件的后缀。如secure-20130605            |

其中日志文件的命名规则尤为重要。

如果配置文件中拥有“dateext”参数，那么日志会用日期来作为日志文件的后缀，例如“secure-20130605”。这样的话日志文件名不会重叠，所以也就不需要日志文件的改名，只需要保存指定的日志个数，删除多余的日志文件即可。

如果配置文件中没有“dateext”参数，那么日志文件就需要进行改名了。当第一次进行日志轮替时，当前的“secure”日志会自动改名为“secure.1”，然后新建“secure”日志，用来保存新的日志。当第二次进行日志轮替时，“secure.1”会自动改名为“secure.2”，当前的“secure”日志会自动改名为“secure.1”，然后也会新建“secure”日志，用来保存新的日志，以此类推。

------

==让系统来管理 apache 服务==

打开`/etc/logrotate.conf`加入下列内容

```shell
# access_log 是 apache 服务的日志配置文件，现在让系统来代替管理
/usr/local/apache2/logs/access_log {
	daily
	create
	rotate 30
}
```

------

日志管理命令格式：logrotate [选项] 配置文件名

+ -v：显示日志轮替过程。加了-v选项，会显示日志的轮替的过程
+ -f： 强制进行日志轮替。不管日志轮替的条件是否已经 符合，强制配置文件中所有的日志进行轮替

## 十四、启动管理

### 1. 启动引导程序 grub

#### 1. grub 配置文件

grub 中分区不同于 liunx 的分区

| 硬盘           | 分区           | Linux中设备文件名 | Grub中设备文件名 |
| -------------- | -------------- | ----------------- | ---------------- |
| 第一块SCSI硬盘 | 第一个主分区   | /dev/sda1         | hd(0,0)          |
|                | 第二个主分区   | /dev/sda2         | hd(0,1)          |
|                | 扩展分区       | /dev/sda3         | hd(0,2)          |
|                | 第一个逻辑分区 | /dev/sda5         | hd(0,4)          |
| 第二块SCSI硬盘 | 第一个主分区   | /dev/sdb1         | hd(1,0)          |
|                | 第二个主分区   | /dev/sdb2         | hd(1,1)          |
|                | 扩展分区       | /dev/sdb3         | hd(1,2)          |
|                | 第一个逻辑分区 | /dev/sdb5         | hd(1,4)          |

grub 的配置文件是：/boot/grub/grub.conf，文件中的内容含义：

+ default=0：默认启动第一个系统

+ timeout=5：等待时间，默认是5秒，就是系统启动时的选择倒计时

+ splashimage=(hd0,0)/grub/splash.xpm.gz：这里是指定grub启动时的背景图像文件的保存位置的

+ hiddenmenu：隐藏菜单

+ title CentOS (2.6.32-279.el6.i686)：title就是标题的意思，可以随便写

+ root (hd0,0)：是指启动程序的保存分区

+ kernel /vmlinuz-2.6.32-279.el6.i686 ro：定义内核加载时的选项

  root=UUID=b9a7a1a8-767f-4a87-8a2b-a535edb362c9

  rd_NO_LUKS KEYBOARDTYPE=pc KEYTABLE=us

  rd_NO_MD crashkernel=auto LANG=zh_CN.UTF-8 rd_NO_LVM

  rd_NO_DM rhgb quiet 

+ initrd /initramfs-2.6.32-279.el6.i686.img：指定了initramfs内存文件系统镜像文件的所在位置

#### 2. grub 加密

```shell
[root@localhost ~]# grub-md5-crypt
#生成加密密码串
```

```shell
[root@localhost ~]# vi /boot/grub/grub.conf
default=0
timeout=5
password --md5 $1$Y84LB1$8tMY2PibScmuOCc8z8U35/	# password 放在这里
splashimage=(hd0,0)/grub/splash.xpm.gz
hiddenmenu
…省略部分内容…
```

### 2. 系统修复模式

![image-20230205010613446](https://github.com/chi199702/notes/blob/main/image/image-20230205010613446.png?raw=true)

按 e （如果 grub 加密则需要先输入 grub 密码），然后选择第 2 项可以进入单用户模式，在单用户模式下可以进行：

1. 直接修改 root 密码
2. 修改系统默认运行级别

------

![image-20230205010640049](https://github.com/chi199702/notes/blob/main/image/image-20230205010640049.png?raw=true)

进入光盘模式后，再把整个系统挂载到光盘目录下，然后从光盘目录转换成系统根目录就可以操作系统的任何文件，直接穿透了系统！！！这里由于操作偏门就不再记录过多的笔记！！！

```shell
# 重要系统文件丢失，导致系统无法启动
bash-4.1# chroot /mnt/sysimage
#改变主目录
sh-4.1# cd /root
sh-4.1# rpm -qf /etc/inittab
#查询下/etc/inittab文件属于哪个包。
sh-4.1# mkdir /mnt/cdrom
#建立挂载点
sh-4.1# mount /dev/sr0 /mnt/cdrom
#挂载光盘
sh-4.1# rpm2cpio /mnt/cdrom/Packages/initscripts-8.45.3-1.i386.rpm | cpio -idv ./etc/inittab
#提取inittab文件到当前目录
sh-4.1# cp etc/inittab /etc/inittab
#复制inittab文件到指定位置
```

![image-20230205010753438](https://github.com/chi199702/notes/blob/main/image/image-20230205010753438.png?raw=true)

> 总结：
>
> 忘记 root 可以进入单用户模式修改！！！
>
> 系统损坏可以进入光盘模式操作整个系统盘来修复！！！

## 十五、备份与恢复

### 1. 备份策略

1. 完全备份（常用）：完全备份就是指把所有需要备份的数据全部备份，当然完全备份可以备份整块硬盘，整个分区或某个具体的目录

2. 增量备份（常用）

   ![image-20230205010831441](https://github.com/chi199702/notes/blob/main/image/image-20230205010831441.png?raw=true)

3. 差异备份

   ![image-20230205010843637](https://github.com/chi199702/notes/blob/main/image/image-20230205010843637.png?raw=true)

### 2. 备份相关命令

### 1. dump

命令格式：dump [选项] 备份之后的文件名 原文件或目录

功能描述：进行分区、目录、文件备份

+ -level： 就是我们说的0-9十个备份级别
  + 0 就是**完全备份**
  + 1-9 就是在前面的基础上进行**增量备份**
+ -f 文件名： 指定备份之后的文件名
+ -u： 备份成功之后，把备份时间记录在/etc/dumpdates文件
+ -v： 显示备份过程中更多的输出信息
+ -j： 调用bzlib库压缩备份文件，其实就是把备份文件压缩 为.bz2格式，默认压缩等级是2
+ -W： 显示允许被dump的分区的备份等级及备份时间

```shell
dump -0uj -f /root/boot.bak.bz2 /boot/
#备份命令。先执行一次完全备份，并压缩和更新备份时间
cat /etc/dumpdates
#查看备份时间文件
cp install.log /boot/
#复制日志文件到/boot分区
dump -1uj -f /root/boot.bak1.bz2 /boot/
#增量备份/boot分区，并压缩
dump –W
#查询分区的备份时间及备份级别的
```

```shell
dump -0j -f /root/etc.dump.bz2 /etc/
#完全备份/etc/目录，只能使用0级别进行完全备份，而不再支持增量备份
```

### 2. restore

命令格式：restore [模式选项] [选项]

功能描述：进行备份恢复

模式选项：restore命令常用的模式有以下四种，这四个模式不能混用。

+ -C：比较备份数据和实际数据的变化
+ -i： 进入交互模式，手工选择需要恢复的文件。
+ -t： 查看模式，用于查看备份文件中拥有哪些数据。
+ -r： 还原模式，用于数据还原。

选项：

+ -f： 指定备份文件的文件名

```shell
# 比较备份数据和实际数据的变化
mv /boot/vmlinuz-2.6.32-279.el6.i686 /boot/vmlinuz-2.6.32-279.el6.i686.bak
#把/boot目录中内核镜像文件改个名字
restore -C -f /root/boot.bak.bz2
#restore发现内核镜像文件丢失
```

```shell
# 查看模式
restore -t -f boot.bak.bz2
```

```shell
# 还原模式
#还原boot.bak.bz2分区备份
#先还原完全备份的数据
mkdir boot.test
cd boot.test/
restore -r -f /root/boot.bak.bz2
#解压缩
restore -r -f /root/boot.bak1.bz2
#恢复增量备份数据

#还原/etc/目录的备份etc.dump.bz2
restore -r -f etc.dump.bz2
#还原etc.dump.bz2备份
```

