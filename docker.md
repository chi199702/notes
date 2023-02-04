<div style="font-size:30px;text-align:center;"><b>docker</b></div>

## 一、docker的作用

[笔记记录于狂神的docker第一阶段视频](https://www.bilibili.com/video/BV1og4y1q7M4)

[docker官网](https://www.docker.com/)  [docker官方文档](https://docs.docker.com/)  [docker仓库](https://hub.docker.com/)

实现**(项目+环境)**一起打包。

## 二、docker和VM

+ 一个VM，拥有一整套硬件+软件，然后在这个系统上安装和运行软件。
+ docker容器无自己的内核和硬件，直接运行在宿主机的内核，容器之间互相隔离。

## 三、docker安装

按照官方文档走。docker-ce：社区版，docker-ee：企业版

## 四、配置docker的阿里云镜像加速

[阿里云](https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors)

```shell
sudo mkdir -p /etc/docker

sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://ot0jmucv.mirror.aliyuncs.com"]
}
EOF

sudo systemctl daemon-reload

sudo systemctl restart docker
```

## 五、docker常用命令

### 1. 帮助命令

[docker命令查询](https://docs.docker.com/reference/)

1. 显示docker版本

   ```shell
   docker version
   ```

2. 显示docker系统信息，包括镜像和容器的数量

   ```shell
   docker info
   ```

3. 查看docker某个命令帮助文档

   ```shell
   docker 命令 --help
   ```

### 2. 镜像命令

1. 查看镜像

   ```shell
   docker images
   ```

2. 搜索镜像

   ```shell
   docker search 镜像名
   ```

3. 拉取镜像

   ```shell
   docker pull 镜像名
   docker pull 镜像名:版本
   ```

4. 删除镜像

   ```shell
   docker rmi [多个]镜像ID、镜像名
   ```

5. 删除所有镜像

   ```shell
   docker rmi -f $(docker images -ap)
   ```

### 3. 容器命令

1. 新建并启动容器

   ```shell
   docker run [可选参数] 镜像ID
   
   # 参数说明
   --name="ContainerName"   # 容器名字
   -d                       # 后台方式运行
   -it                      # 使用交互方式运行，进入容器查看内容(docker run -it centos /bin/bash)
   -p                       # 指定容器的端口(-p 主机端口:容器端口)
   -P(大写)                  # 随机指定端口
   ```

2. 列出 running 容器

   ```shell
   docker ps [参数]
   
   # 参数说明
   无参数        # 正在运行的容器
   -a           # 正在运行的容器 + 历史运行的容器
   -n=?         # 显示最近创建的容器
   -q           # 只显示容器的编号
   ```

3. 启动、重启、停止、强制停止容器

   ```shell
   docker start 容器id
   docker restart 容器id
   docker stop 容器id
   docker kill 容器id
   ```

4. 退出但不停止容器

   ```shell
   ctrl + P + Q
   ```

5. 退出并停止容器

   ```shell
   exit    #容器内部指令
   ```

6. 删除容器

   ```shell
   docker rm 容器id                 # 不能删除 running 容器
   ```

7. 删除所有容器

   ```shell
   docker rm -f $(dockr ps -aq)
   docker ps -a -q | xargs docker rm    # 删除所有的容器
   ```

### 3. 常用其他命令

1. 后台启动容器

   ```shell
   docker run -d centos	# docker ps 发现centos停止了
   # 常见的坑:docker容器使用后台运行，就必须要有一个前台进程，否则无法与容器交互。
   ```

2. 查看日志

   ```shell
   docker logs -f -t --tail 10 容器id   # 显示指定容器的10条日志
   ```

3. 查看容器中进程信息

   ```shell
   docker top 容器id
   ```

4. 查看容器的元数据

   ```shell
   docker inspect 容器id
   ```

5. 进入当前正在运行的容器

   ```shell
   docker exec -it 容器id /bin/bash       # 进入容器并开启一个新的终端
   docker attach 容器id                   # 进入容器正在执行的终端
   ```

6. 从容器拷贝文件到宿主机

   ```shell
   # 要在宿舍机执行该命令
   docker cp 容器id:文件路径 宿主机路径(不用写目标文件名)   # 即使容器不运行也可以拷贝
   ```

7. 从宿主机拷贝文件到容器

   ```shell
   docker cp 宿主机路径 容器id:文件路径
   ```

8. 查看容器占用空间状态

   ```shell
   docker stats 容器ID
   ```

## 六、docker镜像讲解

### 1. 镜像的概念

> 镜像是一种轻量级、可执行的独立软件包，用来打包软件运行环境和基于运行环境开发的软件，它包含运行某个软件所需的所有内容，包括代码、运行时、库、环境变量和配置文件。

获取镜像的途径：

+ 从远程仓库下载
+ 其他宿主机拷贝
+ 制作一个镜像DockerFile

### 2. docker镜像加载原理

> UnionFS(联合文件系统)

UnionFS是一种分层、轻量级并且高性能的文件系统，它支持对文件系统的修改作为一次提交来一层层的叠加，同时可以将不同的目录挂载到同一个虚拟文件系统下。UnionFS是docker镜像的基础，镜像可以通过分层来进行继承，基于基础镜像(没有父镜像)，可以制作各种具体的应用镜像。

特性：一次同时加载多个文件系统，但从外面来看，只能看到一个文件系统，联合加载会把各层文件系统叠加起来，这样最终的文件系统会包含所有底层的文件和目录。

> docker镜像加载原理

docker的镜像实际上由一层层的文件系统组成，这种层级的文件系统就是UnionFS。

bootfs(boot file system)主要包含bootloader和kernel，bootloader主要是引导加载kernel，linux刚启动时会加载bootfs，在docker镜像的最底层是bootfs。这一层与我们典型的Linux/Unix系统是一样的，包含bootloader和kernel。当boot加载完成之后整个内核就都在内存中了，此时内存的使用权已由bootfs转交给内核，此时系统也会卸载bootfs。

rootfs(root file system)，在bootfs之上，包含的就是典型Linux系统中的`/dev,/proc,/bin,/etc`等标准目录和文件。rootfs就是各种不同的操作系统发行版，比如ubuntu，centos等。

一个精简的OS对应的rootfs很小是因为其只包含了最基本的命令行工具和程序库，底层直接使用宿主机的kernel，其本身只提供rootfs就可以了。可见不同的Linux发行版，bootfs基本是一致的，rootfs会有差别，因此不同的发行版可以公用bootfs(从docker容器角度来看，ubuntu/centos容器可以共存是因为它们底层使用的是相同的bootfs)。

### 3. 镜像分层

pull镜像的时候观察日志看到是分层下载的情况(镜像像是由多个base镜像组合起来的)。采用分层的好处莫过于资源共享，若有多个镜像都需要同一份base镜像，那么宿主机上只需要加载一份base镜像就可以被多个镜像使用。

**理解：**所有的镜像都起始于一个基础镜像层，当进行修改或添加新的内容时，就会在当前镜像层之上，创建新的镜像层。比如：基于ubuntu Linux 16.04创建一个新的镜像，这就是新镜像的第一层，如果在ubuntu系统上添加了python包，就会在基础镜像上创建第二个镜像层，如果继续添加一个安全补丁，就会创建第三个镜像层。

每一层可以包含多个文件(文件即应用，比如第一层包含了3个文件，第二层可以包含`mysql/redis/tomcat`3个文件)，在添加额外的镜像层后，在外部看镜像始终保持着当前所有镜像的组合(一共6个文件)。若上层镜像的文件是下层镜像的文件的升级版本，下层的该文件将会被覆盖。

**进阶：**docker通过存储引擎(新版本采用快照机制)的方式来实现镜像层堆栈，并保证多镜像层对外展示为统一的文件系统。Linux上可用的存储引擎有AUFS、Overlay2、Device Mapper、Btrfs以及ZFS。顾名思义，每种存储引擎都基于Linux中对应的文件系统或者块设备技术，并且每种存储引擎都有其独有的性能特点。docker在windows上仅支持windowsfilter一种存储引擎，该引擎基于NTFS文件系统之上实现了分层和CoW。

**特点：**docker镜像都是只读的，当容器启动时，一个新的可写层被加载到镜像的顶部，这个可写层就是我们通常说的容器层，容器层之下的都叫镜像层。

### 4. commit镜像

```shell
# commit 命令类似 VM 中的快照，为指定容器生成一个镜像
docker commit -m="describe information" -a="author" container_id image_name:tag
```

## 七、容器数据卷

> 问题：容器一旦删除，里面的数据也会消失。所以需要将数据进行持久化，应该有技术实现容器之间的数据共享(多个容器将目录挂载到同一个宿主机目录)，可以将容器的数据同步到宿主机。docker存在的卷技术，可以实现将容器内的目录挂载到宿舍机的目录上。

### 1. 使用数据卷

```shell
# 主机目录不存在会被创建
# 双向绑定：修改主机目录(即使容器stop)会同步到容器，修改容器目录也会同步到主机目录
# docker inspect container_id 的 json 文件 mount 标签查看挂载情况
# 可以使用多个 -v 标签
docker run -it -v host_path:container_path -v ......
```

### 2. 具名挂载和匿名挂载

1. 具名挂载：挂载时提供挂载卷名称(**推荐使用**)

   ```shell
   # 具名挂载
   # juming-nginx 非宿主机目录
   docker run -d -P --name nginx01 -v juming-nginx:/etc/nginx nginx
   ```

2. 匿名挂载：挂载时不提供挂载卷名称，由docker分配

   ```shell
   # 匿名挂载
   # /etc/nginx 为容器目录
   docker run -d -P --name nginx02 -v /etc/nginx nginx
   ```

3. 通过挂载名查看宿主机挂载卷目录

   ```shell
   # 列出所有挂在卷名称
   docker volume ls
   
   # 通过挂载卷名称查看在宿主机的挂载目录
   docker volume inspect mount_name
   ```

   **使用没有指定目录(具名/匿名)的挂载方式的情况下，挂载目录都是宿主机的`/var/lib/docker/volumes/xxx/_data`**

4. 区别具名/匿名/指定路径挂载

   + `-v container_path	# 匿名挂载` 
   + `-v volume_name:container_path # 具名挂载`
   + `-v /host_path:container_path # 指定路径挂载，/开头`

5. 拓展

   ```shell
   # ro —— readonly	只读：表明了在容器内不可改变container_path的内容，只能在宿主机改变
   docker run -d -P --name nginx03 -v volume_name:container_path:ro nginx
   
   # rw —— readwrite	读写(缺省值)
   docker run -d -P --name nginx04 -v volume_name:container_path:rw nginx
   ```

### 3. 初识dockerfile

> dockerfile 就是用来构建 docker image 的构建文件，其本质就是一个 shell 脚本，通过这个 shell 脚本可以生成一个image，image 是分层叠加的，shell 脚本中的每一条命令对应一个 image 里的一层。

```shell
# create a dockerfile
# shell command is up
# every command is a layer of image
FROM centos
VOLUME ["volume01","volume02"]
CMD echo "----end----"
CMD /bin/bash
```

`VOLUME ["volume01","volume02"]`命令会在此`image`对应的`container`内部创建`volume01/volume02`两个目录，并且这两个目录会挂载都宿舍机的缺省位置上，可见使用创建`dockerfile`的方式也可以实现容器目录的挂载(而且这是常用的方式)。

### 4. 数据卷容器

> 实现多个容器共享数据

```shell
# son_container 继承了 parent_container 的数据卷，比如上面创建的 volume01/volume02
# 不管在 son_container 或 parent_container 的 volume01/volume02 进行 IO 都会同步到其他 container
docker run -it --name son_container --volumes-from parent_container image_name
```

父子容器的数据卷之间是互相同步拷贝的操作，即使删除了父容器，子容器的数据卷中依旧存在数据。

## 八、dockerfile

### 1. dockerfile介绍

dockerfile 本质就是一个 shell 脚本，其是用来构建 docker image 的文件。

通过 dockerfile 构建 image 步骤：

1. 编写一个 dockerfile 文件
2. docker build 构建成为一个 image
3. docker run 运行 image
4. docker push 发布镜像(发布到 dockerhub、阿里云镜像仓库)

### 2. dockerfile的指令

dockerfile 脚本的基础知识：

+ 每个关键字(指令)都需要大写
+ 脚本从上往下依次执行
+ 每一个指令都会创建并提交一个新的镜像层

构建dockerfile的常用指令

```shell
FROM			# 基础 image (地基)
MAINTAINER       # image 维护者，格式：姓名 + 邮箱
RUN			    # image 构建时需要运行的命令
ADD			    # 基于基础 image add content，添加压缩包会自动解压
WORKDIR			# image 的工作目录
VOLUME           # 挂载的目录
EXPOSE			# 对外暴露的端口
CMD			    # 容器启动时要运行的命令(命令是可被替代的，所以只有最后一条命令生效)
ENTRYPOINT       # 容器启动时要运行的命令(命令是 append 的)
ONBUILD			# 当构建一个被继承的 dockerfile 时会自动触发该命令(了解)
COPY		    # 类似 ADD
ENV			    # 构建时设置环境变量
```

DIY a  mycentos：

```shell
# mydockerfile shell script
FROM centos
MAINTAINER cwm<wming@hnu.edu.cn>

ENV MYPATH /usr/local
WORKDIR $MYPATH	# set work_path

RUN yum -y install vim	# add new content
RUN yum -y install net-tools

EXPOSE 80

CMD echo $MYPATH
CMD echo "----end----"
CMD /bin/bash
```

Though mydockerfile build a image

```shell
# -f : dockerfile_path
# -t : image : tag
# don't forget .
docker build -f mydockerfile -t mycentos:1.0 .

# run result
# express a script express a step，all 10 steps
(base) xhb@ubuntu:~/cwm$ docker build -f mydockerfile -t mycentos:1.0 .
Sending build context to Docker daemon  2.048kB
Step 1/10 : FROM centos
latest: Pulling from library/centos
7a0437f04f83: Pull complete 
Digest: sha256:5528e8b1b1719d34604c87e11dcd1c0a20bedf46e83b5632cdeac91b8c04efc1
Status: Downloaded newer image for centos:latest
 ---> 300e315adb2f
Step 2/10 : MAINTAINER cwm<wming@hnu.edu.cn>
 ---> Running in 8ef23fc44097
Removing intermediate container 8ef23fc44097
 ---> 2e3268394999
Step 3/10 : ENV MYPATH /usr/local
 ---> Running in 2b301e38d2be
Removing intermediate container 2b301e38d2be
 ---> af8cb9c56939
Step 4/10 : WORKDIR $MYPATH
 ---> Running in 9201579e724f
Removing intermediate container 9201579e724f
 ---> f8307019cb07
Step 5/10 : RUN yum -y install vim
 ---> Running in 61b4602b5c7f
 ……
 ……
 ……
 
 # run mycentos:1.0
 # 进去就处于 /usr/local 目录下，WORKDIR $MYPATH 起作用了
(base) xhb@ubuntu:~/cwm$ docker run -it 15b8bdba1391
[root@7593603140d2 local]# ls
bin  etc  games  include  lib  lib64  libexec  sbin  share  src

[root@7593603140d2 local]# pwd
/usr/local

[root@7593603140d2 local]#
```

### 3. cat a image history

```shell
# 查看一个 image history
docker history image_id

# docker history 15b8bdba1391
# output
# 可以看到 image 对应的 dockerfile 内容
IMAGE          CREATED          CREATED BY                                      SIZE      COMMENT
15b8bdba1391   24 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "/bin…   0B        
8077a86f9244   24 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "echo…   0B        
d99cafaa8e71   24 minutes ago   /bin/sh -c #(nop)  CMD ["/bin/sh" "-c" "echo…   0B        
e359cd585392   24 minutes ago   /bin/sh -c #(nop)  EXPOSE 80                    0B        
46a6658af651   24 minutes ago   /bin/sh -c yum -y install net-tools             23.5MB    
ac31e0c25fd6   25 minutes ago   /bin/sh -c yum -y install vim                   58.2MB    
f8307019cb07   25 minutes ago   /bin/sh -c #(nop) WORKDIR /usr/local            0B        
af8cb9c56939   25 minutes ago   /bin/sh -c #(nop)  ENV MYPATH=/usr/local        0B        
2e3268394999   25 minutes ago   /bin/sh -c #(nop)  MAINTAINER cwm<wming@hnu.…   0B        
300e315adb2f   3 months ago     /bin/sh -c #(nop)  CMD ["/bin/bash"]            0B        
<missing>      3 months ago     /bin/sh -c #(nop)  LABEL org.label-schema.sc…   0B        
<missing>      3 months ago     /bin/sh -c #(nop) ADD file:bd7a2aed6ede423b7…   209MB
```

### 4. CMD 和 ENTRYPOINT

> CMD

```shell
# create a dockerfile call dockerfile_cmd_test
FROM centos
CMD ["ls","-a"]

# run the image
(base) xhb@ubuntu:~/cwm$ docker images
REPOSITORY                   TAG       IMAGE ID       CREATED          SIZE
cmd_test                     1.0       9e8079cc9449   17 minutes ago   209MB
mycentos                     1.0       15b8bdba1391   54 minutes ago   291MB

# 可以看到 run image 后就直接有内容输出，这就是 CMD ["ls","-a"] 的效果
# 注意：在 dockerfile 中只有最后一个 CMD 命令会被执行
(base) xhb@ubuntu:~/cwm$ docker run -it 9e8079cc9449
.   .dockerenv	dev  home  lib64       media  opt   root  sbin	sys  usr
..  bin		etc  lib   lost+found  mnt    proc  run   srv	tmp  var

# run image 时添加的 CMD 命令参数会替换掉 dockerfile 内的 CMD 命令，所以 docker run -it 9e8079cc9449 -l 是错误的
(base) xhb@ubuntu:~/cwm$ docker run -it 9e8079cc9449 ls -al
total 56
drwxr-xr-x   1 root root 4096 Mar 23 14:18 .
drwxr-xr-x   1 root root 4096 Mar 23 14:18 ..
-rwxr-xr-x   1 root root    0 Mar 23 14:18 .dockerenv
lrwxrwxrwx   1 root root    7 Nov  3 15:22 bin -> usr/bin
drwxr-xr-x   5 root root  360 Mar 23 14:18 dev
drwxr-xr-x   1 root root 4096 Mar 23 14:18 etc
drwxr-xr-x   2 root root 4096 Nov  3 15:22 home
lrwxrwxrwx   1 root root    7 Nov  3 15:22 lib -> usr/lib
lrwxrwxrwx   1 root root    9 Nov  3 15:22 lib64 -> usr/lib64
drwx------   2 root root 4096 Dec  4 17:37 lost+found
drwxr-xr-x   2 root root 4096 Nov  3 15:22 media
drwxr-xr-x   2 root root 4096 Nov  3 15:22 mnt
drwxr-xr-x   2 root root 4096 Nov  3 15:22 opt
dr-xr-xr-x 377 root root    0 Mar 23 14:18 proc
dr-xr-x---   2 root root 4096 Dec  4 17:37 root
drwxr-xr-x  11 root root 4096 Dec  4 17:37 run
lrwxrwxrwx   1 root root    8 Nov  3 15:22 sbin -> usr/sbin
drwxr-xr-x   2 root root 4096 Nov  3 15:22 srv
dr-xr-xr-x  13 root root    0 Mar 16 06:41 sys
drwxrwxrwt   7 root root 4096 Dec  4 17:37 tmp
drwxr-xr-x  12 root root 4096 Dec  4 17:37 usr
drwxr-xr-x  20 root root 4096 Dec  4 17:37 var
```

> ENTRYPOINT

```shell
# create a dockerfile call dockerfile_entrypoint_test
FROM centos
ENTRYPOINT ["ls","-l"]

# run the image
(base) xhb@ubuntu:~/cwm$ docker images
REPOSITORY                   TAG       IMAGE ID       CREATED          SIZE
entrypoint_test              1.0       ad8ddc86ce15   33 seconds ago   209MB
cmd_test                     1.0       9e8079cc9449   58 minutes ago   209MB
mycentos                     1.0       15b8bdba1391   2 hours ago      291MB
hello-world                  latest    d1165f221234   2 weeks ago      13.3kB
centos                       latest    300e315adb2f   3 months ago     209MB
ulissigroup/gaspy_feedback   latest    6718bcc6c7b6   9 months ago     2.71GB
ulissigroup/gaspy            latest    395ddce3314d   10 months ago    2.71GB
ubuntu                       15.10     9b9cb95443b5   4 years ago      137MB

(base) xhb@ubuntu:~/cwm$ docker run ad8ddc86ce15
total 48
lrwxrwxrwx   1 root root    7 Nov  3 15:22 bin -> usr/bin
drwxr-xr-x   5 root root  340 Mar 23 14:50 dev
drwxr-xr-x   1 root root 4096 Mar 23 14:50 etc
drwxr-xr-x   2 root root 4096 Nov  3 15:22 home
lrwxrwxrwx   1 root root    7 Nov  3 15:22 lib -> usr/lib
lrwxrwxrwx   1 root root    9 Nov  3 15:22 lib64 -> usr/lib64
drwx------   2 root root 4096 Dec  4 17:37 lost+found
drwxr-xr-x   2 root root 4096 Nov  3 15:22 media
drwxr-xr-x   2 root root 4096 Nov  3 15:22 mnt
drwxr-xr-x   2 root root 4096 Nov  3 15:22 opt
dr-xr-xr-x 379 root root    0 Mar 23 14:50 proc
dr-xr-x---   2 root root 4096 Dec  4 17:37 root
drwxr-xr-x  11 root root 4096 Dec  4 17:37 run
lrwxrwxrwx   1 root root    8 Nov  3 15:22 sbin -> usr/sbin
drwxr-xr-x   2 root root 4096 Nov  3 15:22 srv
dr-xr-xr-x  13 root root    0 Mar 16 06:41 sys
drwxrwxrwt   7 root root 4096 Dec  4 17:37 tmp
drwxr-xr-x  12 root root 4096 Dec  4 17:37 usr
drwxr-xr-x  20 root root 4096 Dec  4 17:37 var

# 追加方式 run image
(base) xhb@ubuntu:~/cwm$ docker run -it ad8ddc86ce15 -a
total 56
drwxr-xr-x   1 root root 4096 Mar 23 14:56 .
drwxr-xr-x   1 root root 4096 Mar 23 14:56 ..
-rwxr-xr-x   1 root root    0 Mar 23 14:56 .dockerenv
lrwxrwxrwx   1 root root    7 Nov  3 15:22 bin -> usr/bin
drwxr-xr-x   5 root root  360 Mar 23 14:56 dev
drwxr-xr-x   1 root root 4096 Mar 23 14:56 etc
drwxr-xr-x   2 root root 4096 Nov  3 15:22 home
lrwxrwxrwx   1 root root    7 Nov  3 15:22 lib -> usr/lib
lrwxrwxrwx   1 root root    9 Nov  3 15:22 lib64 -> usr/lib64
drwx------   2 root root 4096 Dec  4 17:37 lost+found
drwxr-xr-x   2 root root 4096 Nov  3 15:22 media
drwxr-xr-x   2 root root 4096 Nov  3 15:22 mnt
drwxr-xr-x   2 root root 4096 Nov  3 15:22 opt
dr-xr-xr-x 386 root root    0 Mar 23 14:56 proc
dr-xr-x---   2 root root 4096 Dec  4 17:37 root
drwxr-xr-x  11 root root 4096 Dec  4 17:37 run
lrwxrwxrwx   1 root root    8 Nov  3 15:22 sbin -> usr/sbin
drwxr-xr-x   2 root root 4096 Nov  3 15:22 srv
dr-xr-xr-x  13 root root    0 Mar 16 06:41 sys
drwxrwxrwt   7 root root 4096 Dec  4 17:37 tmp
drwxr-xr-x  12 root root 4096 Dec  4 17:37 usr
drwxr-xr-x  20 root root 4096 Dec  4 17:37 var
```

### 5. 实战：创建 Tomcat Image

> 目标：创建一个 Tomcat + jdk 的可供外部访问的 Tomcat Image

1. 准备 Tomcat、jdk 的压缩包

   ```shell
   (base) xhb@ubuntu:~/cwm$ ls
   apache-tomcat-9.0.44.tar.gz jdk-8u11-linux-x64.tar.gz
   ```

2. 编写 dockfile 文件( dockerfile 文件命名为：`Dockerfile`，这样才构建成 Image 时无须通过 `-f` 参数指定dockerfile)

   ```shell
   # 相当于在一个 centos 中安装了 tomcat + jdk
   FROM centos
   MAINTAINER cwm<wming@hnu.edu.cn>
   
   # 拷贝本地文件到指定容器目录
   COPY readme.txt /usr/local/readme.txt
   
   # ADD 命令会自动自动解压到指定目录
   ADD jdk-8u11-linux-x64.tar.gz /usr/local
   ADD apache-tomcat-9.0.44.tar.gz /usr/local
   
   RUN yum -y install vim
   
   ENV MYPATH /usr/local
   WORKDIR $MYPATH
   
   # 相当于 expose 了一个变量
   ENV JAVA_HOME /usr/local/jdk1.8.0_11
   ENV CLASSPATH $JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
   ENV CATALINA_HOME /usr/local/apache-tomcat-9.0.44
   ENV CATALINA_BASH /usr/local/apache-tomcat-9.0.44
   ENV PATH $PATH:$JAVA_HOME/bin:$CATALINA_HOME/bin:$CATALINA_HOME/lib
   ```

3. 构建 Image

   ```shell
   docker build -t mytomcat .
   
   # 13 个步骤就是 13 行代码
   (base) xhb@ubuntu:~/cwm$ docker build -t mytomcat .
   Sending build context to Docker daemon  170.5MB
   Step 1/13 : FROM centos
    ---> 300e315adb2f
   Step 2/13 : MAINTAINER cwm<wming@hnu.edu.cn>
    ---> Using cache
    ---> 2e3268394999
   Step 3/13 : COPY readme.txt /usr/local/readme.txt
    ---> 2047ceec301c
   Step 4/13 : ADD jdk-8u11-linux-x64.tar.gz /usr/local
    ---> 371a21588390
   Step 5/13 : ADD apache-tomcat-9.0.44.tar.gz /usr/local
    ---> 4ca17bf11c5f
   Step 6/13 : RUN yum -y install vim
    ---> Running in 14c2646addfc
    
   (base) xhb@ubuntu:~/cwm$ docker images
   REPOSITORY                   TAG       IMAGE ID       CREATED          SIZE
   mytomcat                     latest    6cc30dbd788c   13 seconds ago   607MB
   ```

4. Run Image

   ```shell
   # 将 tomcat 里面的两个卷挂载到宿主机
   (base) xhb@ubuntu:~/cwm$ docker run -it -p 9090:8080 --name cwm_tomcat -v /home/xhb/cwm/tomcat/test:/usr/local/apache-tomcat-9.0.44/webapps/test -v /home/xhb/cwm/tomcat/logs:/usr/local/apache-tomcat-9.0.44/logs 6cc30dbd788c /bin/bash
   
   ```
   
5. 配置 tomcat

   ```shell
   # tomcat / jdk 都已经解压并且自动删除了压缩包
   [root@db304fa79898 local]# ls    
   apache-tomcat-9.0.44  bin  etc	games  include	jdk1.8.0_11  lib  lib64  libexec  readme.txt  sbin  share  src
   
   # 在宿主机配置 tomcat
   # 编写 web.xml
   (base) xhb@ubuntu:~/cwm/tomcat/test/WEB-INF$ pwd
   /home/xhb/cwm/tomcat/test/WEB-INF
   (base) xhb@ubuntu:~/cwm/tomcat/test/WEB-INF$ cat web.xml 
   <?xml version="1.0" encoding="UTF-8"?>
   <web-app xmlns="http://java.sun.com/xml/ns/javaee"
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
   xsi:schemaLocation="http://java.sun.com/xml/ns/javaee
   http://java.sun.com/xml/ns/javaee/web-app_2_5.xsd"
   version="2.5">
   </web-app>
   
   # 编写 index.jsp
   (base) xhb@ubuntu:~/cwm/tomcat/test$ cat index.jsp 
   <%@ page language="java" contentType="text/html; charset=UTF-8"
   pageEncoding="UTF-8"%>
   <!DOCTYPE html>
   <html>
   <head>
   <meta charset="utf-8">
   <title>菜鸟教程(runoob.com)</title>
   </head>
   <body>
   Hello World!<br/>
   <%
   System.out.println("Hello,World");
   %>
   </body>
   </html>
   ```

   在华为昇腾服务器上无法外部访问，可能是防火墙问题。

### 6. 发布镜像

> 发布 image 到 dockerhub

```shell
# 登录 dockerhub
(base) xhb@ubuntu:~/cwm/tomcat/logs$ docker login -u jkchi
Password: 
WARNING! Your password will be stored unencrypted in /home/xhb/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded

(base) xhb@ubuntu:~/cwm/tomcat/logs$ docker images
REPOSITORY                   TAG       IMAGE ID       CREATED         SIZE
mytomcat                     latest    6cc30dbd788c   3 hours ago     607MB
entrypoint_test              1.0       ad8ddc86ce15   15 hours ago    209MB
cmd_test                     1.0       9e8079cc9449   16 hours ago    209MB
mycentos                     1.0       15b8bdba1391   16 hours ago    291MB
hello-world                  latest    d1165f221234   2 weeks ago     13.3kB
centos                       latest    300e315adb2f   3 months ago    209MB
ulissigroup/gaspy_feedback   latest    6718bcc6c7b6   9 months ago    2.71GB
ulissigroup/gaspy            latest    395ddce3314d   10 months ago   2.71GB
ubuntu                       15.10     9b9cb95443b5   4 years ago     137MB

# 必须要 tag 想要发布的 image，前面必须是自己的 dockhub 用户名
(base) xhb@ubuntu:~/cwm/tomcat/logs$ docker tag 6cc30dbd788c jkchi/mytomcat:1.0

(base) xhb@ubuntu:~/cwm/tomcat/logs$ docker images
REPOSITORY                   TAG       IMAGE ID       CREATED         SIZE
jkchi/mytomcat               1.0       6cc30dbd788c   3 hours ago     607MB
mytomcat                     latest    6cc30dbd788c   3 hours ago     607MB
entrypoint_test              1.0       ad8ddc86ce15   15 hours ago    209MB
cmd_test                     1.0       9e8079cc9449   16 hours ago    209MB
mycentos                     1.0       15b8bdba1391   16 hours ago    291MB
hello-world                  latest    d1165f221234   2 weeks ago     13.3kB
centos                       latest    300e315adb2f   3 months ago    209MB
ulissigroup/gaspy_feedback   latest    6718bcc6c7b6   9 months ago    2.71GB
ulissigroup/gaspy            latest    395ddce3314d   10 months ago   2.71GB
ubuntu                       15.10     9b9cb95443b5   4 years ago     137MB

(base) xhb@ubuntu:~/cwm/tomcat/logs$ docker push jkchi/mytomcat:1.0
The push refers to repository [docker.io/jkchi/mytomcat]
a437f9b5996c: Pushed 
184e745326b0: Pushed
```

> 发布 image 到阿里云

1. 在阿里云上创建命名空间

   <img src="C:\Users\MINGC\AppData\Roaming\Typora\typora-user-images\image-20210324140851484.png" alt="image-20210324140851484" style="zoom:50%;" />

2. 创建本地镜像仓库

   <img src="C:\Users\MINGC\AppData\Roaming\Typora\typora-user-images\image-20210324140827373.png" alt="image-20210324140827373" style="zoom:50%;" />

3. 进入镜像仓库查看操作步骤

   1. 登录阿里云Docker Registry

      ```shell
      (base) xhb@ubuntu:~$ sudo docker login --username=剑冢丶 registry.cn-hangzhou.aliyuncs.com
      Password: 
      WARNING! Your password will be stored unencrypted in /home/xhb/.docker/config.json.
      Configure a credential helper to remove this warning. See
      https://docs.docker.com/engine/reference/commandline/login/#credentials-store
      
      Login Succeeded
      ```

   2. 从 Registry 中拉取/推送镜像

      ```shell
      # pull image
      $ sudo docker pull registry.cn-hangzhou.aliyuncs.com/jichi/wming_images:[镜像版本号]
      
      # push image
      (base) xhb@ubuntu:~$ docker images
      REPOSITORY                   TAG       IMAGE ID       CREATED         SIZE
      jkchi/mytomcat               1.0       6cc30dbd788c   4 hours ago     607MB
      mytomcat                     latest    6cc30dbd788c   4 hours ago     607MB
      entrypoint_test              1.0       ad8ddc86ce15   16 hours ago    209MB
      cmd_test                     1.0       9e8079cc9449   17 hours ago    209MB
      mycentos                     1.0       15b8bdba1391   18 hours ago    291MB
      hello-world                  latest    d1165f221234   2 weeks ago     13.3kB
      centos                       latest    300e315adb2f   3 months ago    209MB
      ulissigroup/gaspy_feedback   latest    6718bcc6c7b6   9 months ago    2.71GB
      ulissigroup/gaspy            latest    395ddce3314d   10 months ago   2.71GB
      ubuntu                       15.10     9b9cb95443b5   4 years ago     137MB
      
      # 也需要 tag image
      (base) xhb@ubuntu:~$ docker tag 6cc30dbd788c registry.cn-hangzhou.aliyuncs.com/jichi/wming_images:1.0
      
      (base) xhb@ubuntu:~$ docker images
      REPOSITORY                                             TAG       IMAGE ID       CREATED         SIZE
      jkchi/mytomcat                                         1.0       6cc30dbd788c   4 hours ago     607MB
      mytomcat                                               latest    6cc30dbd788c   4 hours ago     607MB
      registry.cn-hangzhou.aliyuncs.com/jichi/wming_images   1.0       6cc30dbd788c   4 hours ago     607MB
      entrypoint_test                                        1.0       ad8ddc86ce15   16 hours ago    209MB
      cmd_test                                               1.0       9e8079cc9449   17 hours ago    209MB
      mycentos                                               1.0       15b8bdba1391   18 hours ago    291MB
      hello-world                                            latest    d1165f221234   2 weeks ago     13.3kB
      centos                                                 latest    300e315adb2f   3 months ago    209MB
      ulissigroup/gaspy_feedback                             latest    6718bcc6c7b6   9 months ago    2.71GB
      ulissigroup/gaspy                                      latest    395ddce3314d   10 months ago   2.71GB
      ubuntu                                                 15.10     9b9cb95443b5   4 years ago     137MB
      
      # push image
      (base) xhb@ubuntu:~$ docker push registry.cn-hangzhou.aliyuncs.com/jichi/wming_images:1.0
      The push refers to repository [registry.cn-hangzhou.aliyuncs.com/jichi/wming_images]
      a437f9b5996c: Layer already exists 
      184e745326b0: Layer already exists 
      ec8129afc1ec: Pushed 
      e5ac025733b6: Layer already exists 
      2653d992f4ef: Pushed 
      1.0: digest: sha256:075d842089a3e215e0565562ddfa6fb3c62013f207b82d1b7322cbc102fb18d5 size: 1373
      ```

      ![image-20210324150120201](C:\Users\MINGC\AppData\Roaming\Typora\typora-user-images\image-20210324150120201.png)

      层信息里面可以查看到 dockerfile 的内容

## 九、docker网络

### 1. docker0

> docker0 网络特点：缺省网络，不可通过域名访问。

```shell
# 查看宿主机网络可以看到 docker0 网络，这是 docker 为宿主机安装的网卡
(base) xhb@ubuntu:~$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eno1: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:3d brd ff:ff:ff:ff:ff:ff
3: eno2: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:3e brd ff:ff:ff:ff:ff:ff
4: eno3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    link/ether a8:49:4d:04:82:3f brd ff:ff:ff:ff:ff:ff
    inet 192.168.71.80/24 brd 192.168.71.255 scope global eno3
       valid_lft forever preferred_lft forever
    inet6 fe80::aa49:4dff:fe04:823f/64 scope link 
       valid_lft forever preferred_lft forever
5: eno4: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:40 brd ff:ff:ff:ff:ff:ff
6: endvnic: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 10:1b:54:b0:bb:d3 brd ff:ff:ff:ff:ff:ff
7: docker0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
    link/ether 02:42:ef:38:be:0b brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
    inet6 fe80::42:efff:fe38:be0b/64 scope link 
       valid_lft forever preferred_lft forever
135: veth2fc7e72@if134: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue master docker0 state UP group default 
    link/ether 06:16:1b:3c:95:e9 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet6 fe80::416:1bff:fe3c:95e9/64 scope link 
       valid_lft forever preferred_lft forever
```

> docker 如何处理容器之间的网络访问？

在 docker 中每启动一个容器，在宿主机和容器内部都会得到一个新的 ip 。docker 实现容器之间网络连接的技术为：桥接模式——evth-pair。

> evth-pair 就是一对虚拟的设备接口，它们成对出现，一端连着协议，一端彼此相连，一般用 evth-pair 充当桥梁。

docker 中只要容器被删除，对应的 evth-pair 就会被删除。

```shell
# 开启一个容器
[root@b5abcae60004 local]# ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
136: eth0@if137: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
    link/ether 02:42:ac:11:00:03 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 172.17.0.3/16 brd 172.17.255.255 scope global eth0
       valid_lft forever preferred_lft forever

# 容器增加了 136，宿主机增加了 137
[root@b5abcae60004 local]# (base) xhb@ubuntu:~$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eno1: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:3d brd ff:ff:ff:ff:ff:ff
3: eno2: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:3e brd ff:ff:ff:ff:ff:ff
4: eno3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    link/ether a8:49:4d:04:82:3f brd ff:ff:ff:ff:ff:ff
    inet 192.168.71.80/24 brd 192.168.71.255 scope global eno3
       valid_lft forever preferred_lft forever
    inet6 fe80::aa49:4dff:fe04:823f/64 scope link 
       valid_lft forever preferred_lft forever
5: eno4: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether a8:49:4d:04:82:40 brd ff:ff:ff:ff:ff:ff
6: endvnic: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 10:1b:54:b0:bb:d3 brd ff:ff:ff:ff:ff:ff
7: docker0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default 
    link/ether 02:42:ef:38:be:0b brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
    inet6 fe80::42:efff:fe38:be0b/64 scope link 
       valid_lft forever preferred_lft forever
135: veth2fc7e72@if134: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue master docker0 state UP group default 
    link/ether 06:16:1b:3c:95:e9 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet6 fe80::416:1bff:fe3c:95e9/64 scope link 
       valid_lft forever preferred_lft forever
137: vethf87764c@if136: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue master docker0 state UP group default 
    link/ether 56:69:83:29:67:5b brd ff:ff:ff:ff:ff:ff link-netnsid 1
    inet6 fe80::5469:83ff:fe29:675b/64 scope link 
       valid_lft forever preferred_lft forever
```

所以说容器之间的网络连接是通过宿主机的 docker0 进行桥接的

> 在 docker 中一个容器重启后 ip 地址会重新分配，如何通过一个容器名来进行容器的访问？
>
> 虽然可以通过 --link 实现，但是此方式已经过时

```shell
# --link 命令，tomcat03 可以通过容器名 ping tomcat02，但是 tomcat02 不能通过容器名 ping tomcat03
[cwm@localhost ~]$ docker run -d --name tomcat03 --link tomcat02 040bdb29ab37
06595bfbb012bbf7cd9d1c8feecabb972846e7a5cdf339e645f5fcb57ecdd525
[cwm@localhost ~]$ docker exec -it tomcat03 /bin/bash
root@06595bfbb012:/usr/local/tomcat# ping tomcat02
PING tomcat02 (172.17.0.3) 56(84) bytes of data.
64 bytes from tomcat02 (172.17.0.3): icmp_seq=1 ttl=64 time=0.085 ms
64 bytes from tomcat02 (172.17.0.3): icmp_seq=2 ttl=64 time=0.063 ms
64 bytes from tomcat02 (172.17.0.3): icmp_seq=3 ttl=64 time=0.072 ms
64 bytes from tomcat02 (172.17.0.3): icmp_seq=4 ttl=64 time=0.061 ms

# 查看 tomcat03 的 hosts 文件发现 tomcat03 容器简单的把 tomcat02 的 ip 地址映射成了主机名，所以本质上还是通过 ip 进行 ping
root@06595bfbb012:/usr/local/tomcat# cat /etc/hosts
127.0.0.1	localhost
::1	localhost ip6-localhost ip6-loopback
fe00::0	ip6-localnet
ff00::0	ip6-mcastprefix
ff02::1	ip6-allnodes
ff02::2	ip6-allrouters
172.17.0.3	tomcat02 cffbcf91d85c
172.17.0.4	06595bfbb012
```

### 2. 自定义网络

```shell
[cwm@localhost ~]$ docker network ls
NETWORK ID     NAME      DRIVER    SCOPE
0c5df0e7cb52   bridge    bridge    local
388cdb62634f   host      host      local
b473ad6f0f4f   none      null      local
```

docker 的网络模式：

+ bridge：桥接模式(缺省模式，自定义网络也使用桥接模式)

  ```shell
  docker run -d -p 8080:8080 --net bridge --name tomcat04 tomcat
  # 等价于
  docker run -d -p 8080:8080 --name tomcat04 tomcat
  ```

+ none：不配置网络

+ host：和宿主机共享网络

+ container：此模式能让容器连通(用的少，局限大)

```shell
# 自定义网络
# --driver bridge 网络模式
# --subnet 192.168.0.0/16 子网掩码
# --gateway 192.168.0.1 网关
# mynet 自定义网络名称
[cwm@localhost ~]$ docker network create --driver bridge --subnet 192.168.0.0/16 --gateway 192.168.0.1 mynet
2257dd62a1eabf163e9011886f22d8cdf429de571e2f12c03dd6420d69061e62

[cwm@localhost ~]$ docker network ls
NETWORK ID     NAME      DRIVER    SCOPE
0c5df0e7cb52   bridge    bridge    local
388cdb62634f   host      host      local
2257dd62a1ea   mynet     bridge    local
b473ad6f0f4f   none      null      local

[cwm@localhost ~]$ docker network inspect mynet
[
    {
        "Name": "mynet",
        "Id": "2257dd62a1eabf163e9011886f22d8cdf429de571e2f12c03dd6420d69061e62",
        "Created": "2021-03-26T09:50:55.311570651+08:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "192.168.0.0/16",
                    "Gateway": "192.168.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {},
        "Options": {},
        "Labels": {}
    }
]
```

> 使用自定义网络
>
> 好处：加入网络的容器能通过域名直接 ping 通

```shell
# 创建两个容器并加入自定义的 mynet 网络
[cwm@localhost ~]$ docker run -d -P --name tomcat_mynet_01 --net mynet tomcat
0dd77b825e17632ec318c474a4dc21b99a42425978f1243639172a9785148d3f

[cwm@localhost ~]$ docker run -d -P --name tomcat_mynet_02 --net mynet tomcat
bd8a5aa63fbfa0ad4eecf9b4b6b21c3ffc54361f74991a24b2a49d13ef917cf3

# 通过查看网络配置可以看到网络中拥有哪些容器
[cwm@localhost ~]$ docker network inspect mynet
[
    {
        "Name": "mynet",
        "Id": "2257dd62a1eabf163e9011886f22d8cdf429de571e2f12c03dd6420d69061e62",
        "Created": "2021-03-26T09:50:55.311570651+08:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "192.168.0.0/16",
                    "Gateway": "192.168.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "0dd77b825e17632ec318c474a4dc21b99a42425978f1243639172a9785148d3f": {
                "Name": "tomcat_mynet_01",
                "EndpointID": "636be055032b9f34ec8ae416511de0db7a323a07b2e20e857e67602322be4b7a",
                "MacAddress": "02:42:c0:a8:00:02",
                "IPv4Address": "192.168.0.2/16",
                "IPv6Address": ""
            },
            "bd8a5aa63fbfa0ad4eecf9b4b6b21c3ffc54361f74991a24b2a49d13ef917cf3": {
                "Name": "tomcat_mynet_02",
                "EndpointID": "8ea661b3886ce457a9daef8ddbf158d4fad442ab469dea8628dca33d6917afc5",
                "MacAddress": "02:42:c0:a8:00:03",
                "IPv4Address": "192.168.0.3/16",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {}
    }
]

# 通过域名直接 ping 通
[cwm@localhost ~]$ docker exec -it tomcat_mynet_01 ping tomcat_mynet_02
PING tomcat_mynet_02 (192.168.0.3) 56(84) bytes of data.
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=1 ttl=64 time=0.098 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=2 ttl=64 time=0.064 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=3 ttl=64 time=0.081 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=4 ttl=64 time=0.063 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=5 ttl=64 time=0.071 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=6 ttl=64 time=0.061 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=7 ttl=64 time=0.059 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=8 ttl=64 time=0.063 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=9 ttl=64 time=0.064 ms
64 bytes from tomcat_mynet_02.mynet (192.168.0.3): icmp_seq=10 ttl=64 time=0.060 ms
```

### 3. 网络连通

> 实现在不同网段中的容器能 ping 通。
>
> docker0(172.18.0.1) 网络中拥有两个容器 tomcat01(172.18.0.2)、tomcat02(172.18.0.3)
>
> mynet(192.168.0.1) 网络中拥有两个容器 tomcat_mynet_01(192.168.0.2)、tomcat_mynet_02(192.168.0.3)
>
> 实现：docker exec -it tomcat01 ping tomcat_mynet_01
>
> 实现机制：通过让容器连接到另一个网络，比如让 tomcat01 能连接到 mynet 网络

```shell
# 在 docker0 网络中添加两个 容器
[cwm@localhost ~]$ docker run -d -P --name tomcat01 tomcat
99110da3b57b47698926049ace82e5ab9543515bc1e3dd62cdc36e9f26e8ee7f

[cwm@localhost ~]$ docker run -d -P --name tomcat02 tomcat
265629582fb7becea9aa34f1da74159cbcf13bd0637a8281fa0d462821ecfb58

# docker0 网段多了 tomcat01、tomcat02 两个容器
[cwm@localhost ~]$ docker network inspect bridge
[
    {
        "Name": "bridge",
        "Id": "0c5df0e7cb5218dd9fd11574e4f0609d005fdf8380800298ebd3d9f1dd1f5edd",
        "Created": "2021-03-26T09:30:48.967634026+08:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "172.17.0.0/16",
                    "Gateway": "172.17.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "265629582fb7becea9aa34f1da74159cbcf13bd0637a8281fa0d462821ecfb58": {
                "Name": "tomcat02",
                "EndpointID": "b855bacf1c923a512fdad091c32143fbdc9ba338687a79d6aebdc1faef17a4aa",
                "MacAddress": "02:42:ac:11:00:03",
                "IPv4Address": "172.17.0.3/16",
                "IPv6Address": ""
            },
            "99110da3b57b47698926049ace82e5ab9543515bc1e3dd62cdc36e9f26e8ee7f": {
                "Name": "tomcat01",
                "EndpointID": "60bc6d31e35621a08daa7f2244e90f52b6ec7892695b957704bf60495efa26cc",
                "MacAddress": "02:42:ac:11:00:02",
                "IPv4Address": "172.17.0.2/16",
                "IPv6Address": ""
            }
        },
        "Options": {
            "com.docker.network.bridge.default_bridge": "true",
            "com.docker.network.bridge.enable_icc": "true",
            "com.docker.network.bridge.enable_ip_masquerade": "true",
            "com.docker.network.bridge.host_binding_ipv4": "0.0.0.0",
            "com.docker.network.bridge.name": "docker0",
            "com.docker.network.driver.mtu": "1500"
        },
        "Labels": {}
    }
]
```

`docker network connect`：实现一个容器连接到另一个网络，**双 ip**

```shell
# 将 tomcat01 tomcat02 连接到 mynet
[cwm@localhost ~]$ docker network connect mynet tomcat01

[cwm@localhost ~]$ docker network connect mynet tomcat02

# mynet 中多了 tomcat01 tomcat02
[cwm@localhost ~]$ docker network inspect mynet
[
    {
        "Name": "mynet",
        "Id": "2257dd62a1eabf163e9011886f22d8cdf429de571e2f12c03dd6420d69061e62",
        "Created": "2021-03-26T09:50:55.311570651+08:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "192.168.0.0/16",
                    "Gateway": "192.168.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "0dd77b825e17632ec318c474a4dc21b99a42425978f1243639172a9785148d3f": {
                "Name": "tomcat_mynet_01",
                "EndpointID": "636be055032b9f34ec8ae416511de0db7a323a07b2e20e857e67602322be4b7a",
                "MacAddress": "02:42:c0:a8:00:02",
                "IPv4Address": "192.168.0.2/16",
                "IPv6Address": ""
            },
            "265629582fb7becea9aa34f1da74159cbcf13bd0637a8281fa0d462821ecfb58": {
                "Name": "tomcat02",
                "EndpointID": "880bf1d94e04b3f4e2ee3e881d78918b1e4dc68f882856fcc08432d143835b45",
                "MacAddress": "02:42:c0:a8:00:05",
                "IPv4Address": "192.168.0.5/16",
                "IPv6Address": ""
            },
            "99110da3b57b47698926049ace82e5ab9543515bc1e3dd62cdc36e9f26e8ee7f": {
                "Name": "tomcat01",
                "EndpointID": "5f2b93da003c439bebf4cb98810e9af051b6a08b787662510f9c29a3021f195a",
                "MacAddress": "02:42:c0:a8:00:04",
                "IPv4Address": "192.168.0.4/16",
                "IPv6Address": ""
            },
            "bd8a5aa63fbfa0ad4eecf9b4b6b21c3ffc54361f74991a24b2a49d13ef917cf3": {
                "Name": "tomcat_mynet_02",
                "EndpointID": "8ea661b3886ce457a9daef8ddbf158d4fad442ab469dea8628dca33d6917afc5",
                "MacAddress": "02:42:c0:a8:00:03",
                "IPv4Address": "192.168.0.3/16",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {}
    }
]

# 直接使用域名 ping 通
[cwm@localhost ~]$ docker exec -it tomcat01 ping tomcat_mynet_01
PING tomcat_mynet_01 (192.168.0.2) 56(84) bytes of data.
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=1 ttl=64 time=0.195 ms
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=2 ttl=64 time=0.058 ms
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=3 ttl=64 time=0.072 ms
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=4 ttl=64 time=0.065 ms
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=5 ttl=64 time=0.062 ms
64 bytes from tomcat_mynet_01.mynet (192.168.0.2): icmp_seq=6 ttl=64 time=0.102 ms
```

## 十、docker compose

### 1. 简介

>docker compose还是针对单机的项目部署。
>
>官方简介：
>
>Compose is a tool for defining and running multi-container Docker applications. With Compose, you use a YAML file to configure your application’s services. Then, with a single command, you create and start all the services from your configuration. To learn more about all the features of Compose, see [the list of features](https://docs.docker.com/compose/#features).
>
>Compose works in all environments: production, staging, development, testing, as well as CI workflows. You can learn more about each case in [Common Use Cases](https://docs.docker.com/compose/#common-use-cases).
>
>Using Compose is basically a three-step process:
>
>1. Define your app’s environment with a `Dockerfile` so it can be reproduced anywhere.
>2. Define the services that make up your app in `docker-compose.yml` so they can be run together in an isolated environment.
>3. Run `docker compose up` and the [Docker compose command](https://docs.docker.com/compose/cli-command/) starts and runs your entire app. You can alternatively run `docker-compose up` using the docker-compose binary.

```yaml
# yaml 文件实例
version: "3.9"  # optional since v1.27.0
services:
  web:
    build: .
    ports:
      - "5000:5000"
    volumes:
      - .:/code
      - logvolume01:/var/log
    links:
      - redis
  redis:
    image: redis
volumes:
  logvolume01: {}
```

> docker-compose 是 docker 官方的开源项目，和 docker 是两个项目，需要另外安装。
>
> 简单来说，compose 可以一键运行 build、run 多个容器

Compose 的两个重要概念：

+ service：容器、应用，比如：web/redis/mysql
+ project：一组关联的容器，services

### 2. 安装

[官网教程](https://docs.docker.com/compose/install/)

1. Run this command to download the current stable release of Docker Compose:

   ```shell
   # 官方命令，速度很慢
   sudo curl -L "https://github.com/docker/compose/releases/download/1.28.6/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
   
   # 可以替换成 kuangshen 提供的地址，但是要 root 用户
   curl -L https://get.daocloud.io/docker/compose/releases/download/1.25.5/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
   ```

2. Apply executable permissions to the binary:

   ```shell
   sudo chmod +x /usr/local/bin/docker-compose
   ```

### 3. 初体验

[官方示例](https://docs.docker.com/compose/gettingstarted/)，可能需要更改`yaml`文件中的`version`

重点是 `yaml` 的编写，自我理解就是通过 `yaml` 文件将多个 container 连接了起来

```yaml
version: "3.9"	# 可能需要修改版本号
services:	    # 该 project 包含了两个 service
  web:
    build: .	# 通过 DockerFile 文件构建了 web image
    ports:
      - "5000:5000"
  redis:		# 从 docker hub pull redis
    image: "redis:alpine"
```

```shell
# 自动添加了 3 个 image
[cwm@localhost ~]$ docker images
REPOSITORY        TAG          IMAGE ID       CREATED             SIZE
composetest_web   latest       8e03c49660eb   About an hour ago   196MB
redis             alpine       933c79ea2511   2 months ago        31.6MB
python            3.7-alpine   72e4ef8abf8e   3 months ago        41.1MB

# 项目启动后拥有两个 container
[cwm@localhost ~]$ docker ps
CONTAINER ID   IMAGE             COMMAND                  CREATED             STATUS          PORTS                    NAMES
f3e1f8249c97   redis:alpine      "docker-entrypoint.s…"   About an hour ago   Up 20 seconds   6379/tcp                 composetest_redis_1
c19d86c147f9   composetest_web   "flask run"              About an hour ago   Up 20 seconds   0.0.0.0:5000->5000/tcp   composetest_web_1

# 自动创建了 composetest_default 网络
[cwm@localhost ~]$ docker network ls
NETWORK ID     NAME                  DRIVER    SCOPE
d5a55f58a48f   bridge                bridge    local
6dce5a42bf94   composetest_default   bridge    local
388cdb62634f   host                  host      local
2257dd62a1ea   mynet                 bridge    local
b473ad6f0f4f   none                  null      local

# 两个容器都处于同一个网络
[cwm@localhost ~]$ docker network inspect composetest_default 
[
    {
        "Name": "composetest_default",
        "Id": "6dce5a42bf948136d36e3fe48978430be77824925f661da03b8e507604382591",
        "Created": "2021-03-26T15:56:27.429460539+08:00",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "172.18.0.0/16",
                    "Gateway": "172.18.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": true,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "c19d86c147f94147206aaa1948eb9096a40ed445cc62839aa900e06ed8796b40": {
                "Name": "composetest_web_1",
                "EndpointID": "df0ed2bb215a2d55ecc8039d9fc2d0b534807639de53a8696a78b13239f7f515",
                "MacAddress": "02:42:ac:12:00:03",
                "IPv4Address": "172.18.0.3/16",
                "IPv6Address": ""
            },
            "f3e1f8249c973b1464e44b9c6fc8e2fa30d2ea32e628bec8e2cd83972f4a1708": {
                "Name": "composetest_redis_1",
                "EndpointID": "32f74ae66800d2f9e7bfce87da8e54fcb7c33cccb2391074296e96423eda6690",
                "MacAddress": "02:42:ac:12:00:02",
                "IPv4Address": "172.18.0.2/16",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {
            "com.docker.compose.network": "default",
            "com.docker.compose.project": "composetest",
            "com.docker.compose.version": "1.25.5"
        }
    }
]
```

### 4. yaml 文件编写规则

[Compose file reference](https://docs.docker.com/compose/compose-file/)

```yaml
# yaml 的 3 层架构
version:				# 版本
services:				# 服务
	xxx:			    # 服务名称
		xxxx:		    # 服务配置
		xxxx:
		xxxx:
    xxx:
    	xxxx:
    	xxxx:
    	xxxx:
# 其他如网络、卷、全局规则等配置
volumes:
networks:
configs:
```

### 5. 快速搭建 WordPress

[官方搭建过程](https://docs.docker.com/compose/wordpress/)

## 十一、docker swarm

[官方介绍](https://docs.docker.com/engine/swarm/)

```shell
(base) user@node0:~/cwm $ docker swarm --help

Usage:	docker swarm COMMAND

Manage Swarm

Commands:
  ca          Display and rotate the root CA
  init        Initialize a swarm
  join        Join a swarm as a node and/or manager
  join-token  Manage join tokens
  leave       Leave the swarm
  unlock      Unlock swarm
  unlock-key  Manage the unlock key
  update      Update the swarm

Run 'docker swarm COMMAND --help' for more information on a command.
```

```shell
(base) user@node0:~/cwm $ docker swarm init --help

Usage:	docker swarm init [OPTIONS]

Initialize a swarm

Options:
      --advertise-addr string                  Advertised address (format: <ip|interface>[:port])
      --autolock                               Enable manager autolocking (requiring an unlock key to start a stopped manager)
      --availability string                    Availability of the node ("active"|"pause"|"drain") (default "active")
      --cert-expiry duration                   Validity period for node certificates (ns|us|ms|s|m|h) (default 2160h0m0s)
      --data-path-addr string                  Address or interface to use for data path traffic (format: <ip|interface>)
      --data-path-port uint32                  Port number to use for data path traffic (1024 - 49151). If no value is set or is set to 0, the default port (4789)
                                               is used.
      --default-addr-pool ipNetSlice           default address pool in CIDR format (default [])
      --default-addr-pool-mask-length uint32   default address pool subnet mask length (default 24)
      --dispatcher-heartbeat duration          Dispatcher heartbeat period (ns|us|ms|s|m|h) (default 5s)
      --external-ca external-ca                Specifications of one or more certificate signing endpoints
      --force-new-cluster                      Force create a new cluster from current state
      --listen-addr node-addr                  Listen address (format: <ip|interface>[:port]) (default 0.0.0.0:2377)
      --max-snapshots uint                     Number of additional Raft snapshots to retain
      --snapshot-interval uint                 Number of log entries between Raft snapshots (default 10000)
      --task-history-limit int                 Task history retention limit (default 5)
```

```shell
# 在一个节点启动一个 swarm
(base) user@node0:~/cwm $ docker swarm init --advertise-addr 192.168.70.174
Swarm initialized: current node (pb3a0e2b99hnm37cxv53o92x9) is now a manager.

To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-1fxudsqs73ldfn05pbsh8irljumigx7asw8g5pxga6dewus1zl-9kfugxnc358s8n2hizogxagzc 192.168.70.174:2377

To add a manager to this swarm, run 'docker swarm join-token manager' and follow the instructions.
```

```shell
# 添加一个 worker
(base) user@node1:~/cwm$ sudo docker swarm join --token SWMTKN-1-1fxudsqs73ldfn05pbsh8irljumigx7asw8g5pxga6dewus1zl-9kfugxnc358s8n2hizogxagzc 192.168.70.174:2377
This node joined a swarm as a worker.
```

```shell
# 查看集群节点情况
(base) user@node0:~/cwm $ docker node ls
ID                            HOSTNAME            STATUS              AVAILABILITY        MANAGER STATUS      ENGINE VERSION
pb3a0e2b99hnm37cxv53o92x9 *   node0               Ready               Active              Leader              19.03.6
gmd1gb9zpavryczsw7rrb76e2     node1               Ready               Active                                  19.03.5
```

### 1. Raft 协议

> swarm 集群使用 Raft 协议，集群要拥有高可用性得拥有至少 3 个主节点且 > 1 台 master 节点存活。

在 swarm 集群中可以拥有多个 master 节点，但是只有一个 Leader 节点，其他 master 节点都是备用节点(处于 `Reachable` 状态)。狂神的**双主双从** swarm 集群实验表明：

1. 在 Leader 节点宕机后另一个候补 master 节点会成为 Leader 节点，**但是另外的候补 master 节点也不能正常使用！ swarm 集群已经不可用了**，当原来的 Leader 从宕机状态恢复正常后已经成为候补 master 节点了。
2. 如果 worker 节点离开了其所在的 swarm 集群，在任意一个 master `docker node ls`(只能在 master 节点使用管理命令，worker 只是用来工作的)后会看到离开 swarm 集群的节点 `STATUS` 处于 `DOWN`。

![Swarm mode cluster](https://docs.docker.com/engine/swarm/images/swarm-diagram.png)

狂神 3 主 1 从的 swarm 集群实验表明：

1.  Leader 节点宕机后其他两个主节点中的一个会成为新的 Leader 节点(此时是 2 主 1 从的可用 swarm 集群)。**上图的意义也表明了 swarm 集群至少得拥有 3 个 master 节点才能保证高可用性。**

> 在开启了 swarm 集群之后，容器的概念已经被替换成了服务，docker run image ——> docker service image
>
> docker run image 不具备扩缩容器
>
> docker service image 具有扩缩容器

### 2. 体会

> 在 swarm 集群之前的 docker 都是单机版的，swarm 集群拥有弹性、扩缩容的特性，单机版中的容器概念被替换成了 swarm 集群中的服务，单机版的 docker 用同一个 image 启动多个 container ，如今可以使用同一个 image 一键启动多个 service ，并且这多个 service 可以在 swarm 集群中动态的、弹性的增加、减少(扩缩容)数量。

```shell
# 开启一个 service
(base) user@node0:~/cwm $ docker service create --name my_nginx -p 8888:80 nginx
0lkfxmpz65szapbtpxz89um91
overall progress: 1 out of 1 tasks 
1/1: running   [==================================================>] 
verify: Service converged

# 在 REPLICAS 中看到该 service 只有一个副本
(base) user@node0:~/cwm $ docker service ls
ID                  NAME                MODE                REPLICAS            IMAGE               PORTS
0lkfxmpz65sz        my_nginx            replicated          1/1                 nginx:latest        *:8888->80/tcp
```

```shell
# 为 my_nginx 多开启 2 个副本(一共 3 个)
(base) user@node0:~/cwm $ docker service update --replicas 3 my_nginx 
my_nginx
overall progress: 3 out of 3 tasks 
1/3: running   [==================================================>] 
2/3: running   [==================================================>] 
3/3: running   [==================================================>] 
verify: Service converged

# 3 个 my_nginx 在 2 个节点的分配情况
(base) user@node0:~/cwm $ docker service ps my_nginx 
ID                  NAME                IMAGE               NODE                DESIRED STATE       CURRENT STATE            ERROR               PORTS
u9jyd5601k1x        my_nginx.1          nginx:latest        node1               Running             Running 14 minutes ago                       
udb6yabkdvl4        my_nginx.2          nginx:latest        node0               Running             Running 5 minutes ago                        
m3k8g1420zvb        my_nginx.3          nginx:latest        node0               Running             Running 6 minutes ago

# 192.168.70.174 有 2 个 nginx service
(base) user@node0:~/cwm $ docker ps
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS               NAMES
b2185dede1e4        nginx:latest        "/docker-entrypoint.…"   3 minutes ago       Up 3 minutes        80/tcp              my_nginx.2.udb6yabkdvl4tzc3zj2cb3frg
af10adbfc595        nginx:latest        "/docker-entrypoint.…"   3 minutes ago       Up 3 minutes        80/tcp              my_nginx.3.m3k8g1420zvbi5qjkf0p8ywdw

# 192.168.70.175 有 1 个 nginx service
(base) user@node1:~/cwm$ sudo docker ps
CONTAINER ID   IMAGE          COMMAND                  CREATED          STATUS          PORTS     NAMES
b9f45ec9509f   nginx:latest   "/docker-entrypoint.…"   12 minutes ago   Up 12 minutes   80/tcp    my_nginx.1.u9jyd5601k1xp4325qyh9r5mm
```

两个 ip 都可以访问 nginx

http://192.168.70.174:8888/

http://192.168.70.175:8888/

```shell
# 使用 scale 也可以实现动态扩缩容
(base) user@node0:~/cwm $ docker service scale my_nginx=10
my_nginx scaled to 10
overall progress: 10 out of 10 tasks 
1/10: running   [==================================================>] 
2/10: running   [==================================================>] 
3/10: running   [==================================================>] 
4/10: running   [==================================================>] 
5/10: running   [==================================================>] 
6/10: running   [==================================================>] 
7/10: running   [==================================================>] 
8/10: running   [==================================================>] 
9/10: running   [==================================================>] 
10/10: running   [==================================================>] 
verify: Service converged

# node0 和 node1 各 5 个 nginx
(base) user@node0:~/cwm $ docker service ps my_nginx 
ID                  NAME                IMAGE               NODE                DESIRED STATE       CURRENT STATE            ERROR               PORTS
u9jyd5601k1x        my_nginx.1          nginx:latest        node1               Running             Running 24 minutes ago                       
udb6yabkdvl4        my_nginx.2          nginx:latest        node0               Running             Running 15 minutes ago                       
m3k8g1420zvb        my_nginx.3          nginx:latest        node0               Running             Running 15 minutes ago                       
yyuddklzu4rp        my_nginx.4          nginx:latest        node0               Running             Running 55 seconds ago                       
uv2gfeey23nf        my_nginx.5          nginx:latest        node1               Running             Running 54 seconds ago                       
pz7ekgladtuj        my_nginx.6          nginx:latest        node0               Running             Running 53 seconds ago                       
fe6t906bj6u9        my_nginx.7          nginx:latest        node1               Running             Running 55 seconds ago                       
aw5yj76csi1x        my_nginx.8          nginx:latest        node0               Running             Running 54 seconds ago                       
1fknptcjf8qy        my_nginx.9          nginx:latest        node1               Running             Running 54 seconds ago                       
zvvvj383ee67        my_nginx.10         nginx:latest        node1               Running             Running 53 seconds ago
```

### 3. 概念总结

> docker swarm ：管理、编排集群。
>
> node：一个 node 就是一个 docker 节点，多个 node 就组成了 swarm 集群。
>
> service：任务，可以在 master node 和 worker node 中运行。
>
> task：容器中的命令。