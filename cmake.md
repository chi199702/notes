# 一、重要概念

## 1. 项目目录结构

> 项目目录结构的组织方式（持续更新改进）

```shell
├── build
│   └── bin
├── CMakeLists.txt
├── COPYRIGHT
├── doc
│   └── document.md
├── include
├── README.md
├── run.sh
└── src
    ├── CMakeLists.txt
    ├── test.cpp
    └── test.h
```

| 目录/文件          | 含义                                                         |
| ------------------ | ------------------------------------------------------------ |
| build              | 存放 cmake 或 make 构建编译后的源文件                        |
| build/bin          | 存放 make 后的 target，也可以不使用该目录而直接将文件存放在 build 目录下 |
| CMakeLists.txt     | 项目主目录下的 CMakeLists.txt                                |
| COPYRIGHT          | 版权说明文件                                                 |
| doc                | 项目相关文件说明                                             |
| include            | 暴露给外界的接口`.h`文件，通常需要<u>安装</u>到 /usr/local/include/project_name/ 下面 |
| README.md          | 项目 README.md 文件                                          |
| run.sh             | 项目运行脚本                                                 |
| src                | 项目源代码位置(头文件和源文件都应该放在这里)                 |
| src/CMakeLists.txt | 子模块目录下的 CMakeLists.txt，每个模块都应该拥有自己独立的 CMakeLists.txt |

## 2. 动态库/静态库

项目执行时会到多个系统路径中去寻找动态库，可以添加第三方动态库路径到<u>系统搜索动态库路径</u>中就可以使用第三方动态库了。

[Ubuntu18.04系统下，gcc生成静态库、动态库的过程与使用方法及实例演训](https://www.pudn.com/news/63298f61272bb74d44d4a095.html#3_51)

> 这里只简单补充一下遗漏的知识点

使用`ldd`可以查看可执行文件引用了哪些动态库，另外，当静态库和动态库同时存在时，会调用动态库。

+ 静态库：链接时会将静态库中被引用的代码拷贝到可执行文件中，编译链接完成后，即使静态库也不影响程序运行。

+ 动态库：链接时不会将库中被引用的代码拷贝到可执行文件中，只记录重定位信息和符号表信息，在程序执行时才完成真正的链接。

## 3. 安装项目

一般简单的项目在编译生成`target`后直接运行即可。将一个项目进行安装就像使用`yum/apt install -y software_name`来对一个软件进行安装一样。安装完成后该过程包括：

1. 生成 makefile 等文件(cmake)。
2. 编译源代码，生成`target`和库文件等(make)。
3. 将可执行文件、执行脚本、文档说明、依赖的库文件等安装到系统的对应目录下(默认在`/usr/local/`目录或其子目录下)，配置环境变量等(make install)。

# 二、相关指令

> 指令大小写无关，参数和变量大小写相关；变量使用`${}`取值，但在`if`中可以直接使用变量名；字符串的表示中 "name" 和 name 是等价的。

> 构建、编译过程中产生的<u>所有文件</u>都是存放在 build 目录下，在存在<u>子模块</u>构建编译的情况下可以使用指令`add_subdirectory`将每个子模块的`target`和`.a/.so`输出到 build 下的子目录下，比如 3 个子模块分别输出到 build/moudule1、build/module2、build/module3 中。

1. cmake_minimum_required(VERSION 3.9)

   指定 cmake 的最低版本要求。

2. project(project_name)

   指定项目名称，project_name 随意。

3. set(varname, .cpp)

   为 varname 变量赋值 .cpp 文件。

   ```cmake
   SET(SRC_LIST main.cpp t1.cpp t2.cpp)
   ```

4. message(STATUS/SEND_ERROR/FATAL_ERROR, "message", ${varname})

   在构建过程中输出以 -- 为前缀的日志信息，参数 1 和 3 都可以省略。

   + STATUS：一般信息。

   + SEND_ERROR：错误信息，会继续执行构建过程。

   + FATAL_ERROR：错误信息，终止构建过程。

5. add_executable(target_name, .cpp/${})

   用于生成可执行文件，第一个参数指定`target`名字，第二个参数指定源文件(也可以用${变量}表示)。

   ```cmake
   add_executable(target_name main.cpp func.cpp)
   ```

6. add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])

   > 该指令立即解析执行源目录(source_dir)下的 CMakeLists.txt 文件，子模块的 /source_dir/CMakeLists.txt 中会有`add_executable/add_library`指令，该指令会马上构建出子模块的`target/library`，所以必须确保以将相应头文件路径包含进来(使用`include_directories`指令)。

   <u>通过使用在工程主目录的 CMakeLists.txt 中，source_dir 模块中必须要有 CMakeLists.txt，用于构建子模块</u>。指令意义为：先执行 source_dir 模块下的 CMakeLists.txt 文件，并将构建该子模块产生的`target/library`存放在 /build/binary_dir/ 下面。

   + source_dir: 指定源文件目录，比如 src，相对路径是 project_name/。
   + binary_dir: source_dir/CMakeLists.txt 输出文件的存放路径，比如 bin，若省略该参数，缺省值就是第一个参数 source_dir，相对路径是 project_name/build/。
   + EXCLUDE_FROM_ALL: 待学习……。

   ```cmake
   add_subdirectory(src, bin) # src 是 project_name/src 目录，bin 是 project_name/build/bin 目录
   ```

   > source_dir 的路径是相对于 project_name/ 的，而 binary_dir 的路径是相对于当前输出路径即 project_name/build/ 的；如果不指定参数 binary_dir ，那么所有编译w文件将存放在 project_name/build/source_dir 中。

7. INSTALL

   用于安装项目，可安装文件、程序和脚本、目录或目录里面的文件；相对于路径 /usr/local/ 来安装，也可以写绝对路径。

   + ```cmake
     install(FILES COPYRIGHT README.md DESTINATION share/doc/cwm_project/) #将 COPYRIGHT README.md 安装到路径 /usr/local/share/doc/cwm_project/
     ```

   + ```cmake
     install(PROGRAMS run.sh DESTINATION bin/) # 将项目执行脚本安装到 /usr/local/bin/
     ```

   + ```cmake
     install(DIRECTORY doc DESTINATION share/doc/cwm_project/) # 将整个目录 doc 安装到 /usr/local/cwm_project/ 下面
     ```

   + ```cmake
     install(DIRECTORY doc/ DESTINATION share/doc/cwm_project/) # 将目录 doc/ 下的所有文件安装到 /usr/local/cwm_project/ 下面，不包含 doc 目录
     ```

   + ```cmake
     install(FILES cwm.h DESTINATION include/cwm) # 安装头文件到 /usr/local/include/cwm/ 下
     ```

   + ```cmake
     install(TARGETS hello_a hello_so LIBRARY DESTINATION lib ARCHIVE DESTINATION lib) # 静态库(ARCHIVE)和动态库(LIBRARY)都安装在 /usr/local/lib/ 
     ```

   > 可使用 cmake -D CMAKE_INSTALL_PREFIX=/path 选项来更改相对路径。

8. add_library(library_name SHARED/STATIC .cpp/${varname})

   用于生成动态库/静态库。

   + librara_name: 指定库名，比如 cwm，最终生成的库名为 libcwm.a/libcwm.so。
   + SHARED/STATIC: SHARED 为动态库，STATIC 为静态库。
   + .cpp/${varname}: 指定源文件。

9. set_target_properties(old_target_name PROPERTIES OUTPUT_NAME "new_target_name")

   常用在同时<u>需要生成相同名字的动态库和静态库</u>中。

   ```cmake
   add_library(hello_a STATIC hello.cpp) # 生成静态库
   set_target_properties(hello_a PROPERTIES OUTPUT_NAME "cwm") # 为静态库改名
   SET_TARGET_PROPERTIES(hello_a PROPERTIES CLEAN_DIRECT_OUTPUT 1) # 配合该条指令使用，用于清除旧文件
   
   add_library(hello_so SHARED hello.cpp) # 生成动态库
   set_target_properties(hello_so PROPERTIES OUTPUT_NAME "cwm") # 为动态库改名
   SET_TARGET_PROPERTIES(hello_so PROPERTIES CLEAN_DIRECT_OUTPUT 1) # 配合该条指令使用，用于清除旧文件
   SET_TARGET_PROPERTIES(hello_so PROPERTIES VERSION 1.0 SOVERSION 1) # 还可以为动态库指定版本号，VERSION 指代动态库版本，SOVERSION 指代 API 版本
   ```

   ```cmake
   # 当生成共享库后，可以使用 install 指令安装共享库和暴露给外界的头文件到系统中
   install(FILES cwm.h DESTINATION include/cwm) # 安装头文件到 /usr/local/include/cwm/ 下
   install(TARGETS hello_a hello_so LIBRARY DESTINATION lib ARCHIVE DESTINATION lib) #静态库(ARCHIVE)和动态库(LIBRARY)都安装在 /usr/local/lib/ 下面
   ```

10. include_directories(path) —— 不建议使用

    用于指明项目<u>在编译时</u>可以去寻找头文件的路径。

    > 当项目的源文件和头文件不在同一目录路径时，在源文件代码中是找不到头文件的，此时就需要使用该指令添加头文件的查找路径，该指令的相对路径是相对当前 CMakeLists.txt 的路径即路径 project_name/，<u>有了该指令，头文件可以放在任何位置</u>。

    ```shell
    ├── build
    ├── CMakeLists.txt
    ├── COPYRIGHT
    ├── doc
    │   └── document.md
    ├── include
    │   └── test.h
    ├── README.md
    ├── run.sh
    └── src
        ├── CMakeLists.txt
        └── test.cpp
    ```

    ```cmake
    # 主目录下的 CMakeLists.txt
    project (TEST)
    
    message(STATUS " This is BINARY dir " ${TEST_BINARY_DIR})
    message(STATUS " This is SOURCE dir " ${TEST_SOURCE_DIR})
    include_directories(include) # 该指令需要放在前面，用来添加头文件搜索路径
    get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    message("include_dirs = ${dirs}") # 打印出 include_dirs = /home/cwm/projects/Test/include
    add_subdirectory(src bin) # 指定源目录下的 CMakeLists.txt 会被马上解析处理，所以需要注意该指令的书写位置
    ```

    ```cmake
    # src/CMakeList.txt
    ADD_EXECUTABLE(server test.cpp)
    ```

    ```c
    // test.cpp
    #include "test.h"	// 编辑时会报错，在 cmake 生成 compile_commands.json 文件后才不会报错
    
    int main(int argc, char* argv[]) {
        printf("hello,world\n");
        return 0;
    }
    ```

    ```c
    // test.h
    #include <stdio.h>
    ```

    ```shell
    cwm@ubuntu:~/projects/Test/build$ cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=1 ..
    ```

    >指定了选项`CMAKE_EXPORT_COMPILE_COMMANDS`后会在 build 目录下生成 compile_commands.json 文件，该文件为每个源文件描述了头文件信息(暂且这么说)，clangd 通过读取该文件可以知道头文件信息，此时再打开源文件就不会报找不到头文件的错误了(此时还没有进行`make`)。

11. target_include_directories

    [关于 targe_include_directories 的 PUBLIC/PRIVATE/INTERFACE](https://zhuanlan.zhihu.com/p/82244559)

    > 和`include_directories`一样都可以指定`target/library`所要寻找的头文件路径，但是推荐使用该指令，因为`include_directories`导致全局包含，向下传递，也就是说在当前目录的 CMakeLists.txt 使用了该指令添加搜索路径后，其下所有的子目录也默认包含了该路径，这样就会导致子目录中的模块进行构建编译时也会到该路径下寻找头文件，这是不必要的，导致结构不清晰的。

    `target_include_directories`中的`target`必须是使用`add_executable/add_library`构建的，所以必须放在这两条命令之后。

    使用该指令能让编译结构更清晰，使用的优先级的高于`include_directories`。

    个人认为大部分情况都应该使用`PRIVATE`。

    ```shell
    ├── build
    ├── CMakeLists.txt
    ├── COPYRIGHT
    ├── doc
    │   └── document.md
    ├── include
    ├── main.c
    ├── README.md
    ├── run.sh
    └── src
        ├── CMakeLists.txt
        ├── mul.c
        ├── sub.c
        ├── test.c
        └── test.h
    ```

    ```cmake
    # 外层 CMakeLists.txt
    cmake_minimum_required(VERSION 3.9)
    project (TEST)
    
    add_subdirectory(src bin)
    add_executable(server main.c)
    target_link_libraries(server PRIVATE add)	# 这里的 add 是子模块 src 生成的
    target_include_directories(server PRIVATE src)
    ```

    > src 子模块生成动态库在 project_name/build/bin 目录下，而使用`target_link_libraries`不需要使用`target_link_directories`来指定库查找路径，因为是内部生成的。

    ```c
    // main.c
    #include <stdio.h>
    #include "test.h"
    
    int main(int argc, char* argv[]) {
        int a, b;
        a = 10;
        b = 20;
        printf("%d + %d = %d\n", a, b, add(a, b));
        return 0;
    }
    ```

    ```cmake
    # src/CMakeLists.txt
    cmake_minimum_required(VERSION 3.9)
    project(add)
    aux_source_directory(. ALL_SOURCE)
    add_library(add SHARED ${ALL_SOURCE})
    ```

    ```c
    // test.h
    #include <stdio.h>
    
    int add(int x, int y);
    ```

    ```c
    // test.c
    int add(int x, int y) {
        return x + y;
    }
    ```

12. target_link_directories/link_directories

    官方不建议使用这两种指令，取而代之的是配合`find_library`使用`target_link_libraries`

13. find_library

    ```shell
    find_library(
              <VAR>
              name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
              [HINTS [path | ENV var]... ]
              [PATHS [path | ENV var]... ]
              [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
              [PATH_SUFFIXES suffix1 [suffix2 ...]]
              [DOC "cache documentation string"]
              [NO_CACHE]
              [REQUIRED]
              [NO_DEFAULT_PATH]
              [NO_PACKAGE_ROOT_PATH]
              [NO_CMAKE_PATH]
              [NO_CMAKE_ENVIRONMENT_PATH]
              [NO_SYSTEM_ENVIRONMENT_PATH]
              [NO_CMAKE_SYSTEM_PATH]
              [NO_CMAKE_INSTALL_PREFIX]
              [CMAKE_FIND_ROOT_PATH_BOTH |
               ONLY_CMAKE_FIND_ROOT_PATH |
               NO_CMAKE_FIND_ROOT_PATH]
    )
    ```

    用于查找`library`。

    [CMake中find_library的使用](https://blog.csdn.net/fengbingchun/article/details/127232175)

    + NAMES: 指定要搜索库的名称

      ```cmake
      # 在系统默认搜索路径中搜索 libopencv_core.so 库
      find_library(var NAMES opencv_core)
      find_library(var NAMES libopencv_core.so)
      ```

      > 如果搜索成功后绝对路径会存放在`var`中，但后面继续使用`find_library`命令却不会再改变`var`的值

      ```cmake
      # 在系统默认搜索路径中搜索 libopencv_core.so 库
      find_library(var NAMES opencv_core)
      # 如果搜索成功，下面语句将不会改变 var 的值
      find_library(var NAMES opencv_highgui) # 此时 var 的值仍然是 /usr/lib/x86_64-linux-gnu/libopencv_core.so
      ```

      > 使用`unset`指定来清除`var`的值可解决此问题

      ```cmake
      # 在系统默认搜索路径中搜索 libopencv_core.so 库
      find_library(var NAMES opencv_core)
      unset(var CACHE)
      find_library(var NAMES opencv_highgui) # 此时 var 的值是 /usr/lib/x86_64-linux-gnu/libopencv_highgui.so
      ```

    + HINTS/PATHS: 除了搜索系统的默认路径外，外加搜索`HINTS/PATHS`指定的路径(路径后面的`/`可有可无)。

      ```cmake
      find_library(var NAMES opencv_core PATHS /opt/opencv3.1/lib/)	# 先搜索系统路径，再搜索 PATHS 指定的路径
      find_library(var NAMES opencv_core HINTS /opt/opencv3.1/lib/)	# 先搜索 HINTS 指定的路径，再搜索系统路径
      ```

    + PATH_SUFFIXES: 若在`HINTS/PATHS`路径中没有找到，则继续在`PATHS/PATH_SUFFIXES`或`HINTS/PATH_SUFFIXES`指定的路径中去寻找

      ```cmake
      # 搜索：(1)/opt/opencv3.1/ (2)/opt/opencv3.1/lib/
      find_library(var NAMES opencv_core PATHS /opt/opencv3.1 PATH_SUFFIXES lib)
      ```

    + REQUIRED: 若使用`find_library`指令未能找到库，则停止执行构建并报错

      ```cmake
      # 将触发error，停止后续的执行:CMake Error at test_find_library.cmake:67 (find_library): Could not find var using the following names: opencv_xxxx
      find_library(var NAMES opencv_xxxx REQUIRED) 
      ```

    + NO_DEFAULT_PATH: 表明不需要去系统默认路径中寻找库

      ```cmake
      # 指定不使用默认路径,path最后带不带"/"均可
      find_library(var NAMES opencv_core PATHS /opt/opencv3.1/lib/ NO_DEFAULT_PATH)
      ```

14. target_link_libraries(target_name libname)

    用于指明项目使用了哪些静态库/动态库，该指令要放在指令`add_executable/add_library`的后面(不然哪里来的`target/library`进行链接)。

    > libname 只需要写库名即可，比如 libadd.so(库文件名) 中的 lib，libname 可以是项目中构建出来的库，也可以是已经存在于系统路径中的第三方库

    ```shell
    # 已经将自己制作的库放在该路径中
    cwm@ubuntu:~$ ll /usr/local/lib
    total 16
    drwxr-xr-x  5 root root     77 Feb 18 11:40 ./
    drwxr-xr-x 11 root root    143 Feb 14 08:54 ../
    -rw-r--r--  1 root root  15640 Feb 18 11:40 libadd.so
    drwxr-xr-x  3 root root     20 Feb 14 10:10 node_modules/
    drwxrwsr-x  4 root staff    48 Feb 14 10:06 python2.7/
    drwxrwsr-x  3 root staff    27 Feb 23  2022 python3.8/
    ```

    ```shell
    # 头文件也已经安装
    cwm@ubuntu:~$ ll /usr/local/include/cwm/
    total 4
    drwxr-xr-x 2 root root 20 Feb 18 11:40 ./
    drwxr-xr-x 4 root root 34 Feb 18 11:40 ../
    -rw-r--r-- 1 root root 23 Feb 18 11:32 test.h
    ```

    ```shell
    ├── build
    ├── CMakeLists.txt
    ├── main.c
    └── src
    ```

    ```c
    // main.c
    #include <stdio.h>
    #include <cwm/test.h>
    
    int main(int argc, char* argv[]) {
    ▏   return 0;
    }
    ```

    ```cmake
    # CMakeLists.txt
    cmake_minimum_required(VERSION 3.9)
    project(use_so)
    add_executable(server main.c)
    target_link_libraries(server add)
    ```

    >因为 libadd.so 已经存在系统的默认搜索路径，所以不需要额外指定搜索路径。否则的话就先要使用`find_library`来查找到库的绝对路径，再使用`target_link_libraries`。

15. aux_source_directory(dir varname)

    [cmake 的 aux_source_directory](https://blog.csdn.net/sinat_31608641/article/details/122373670)

    将 dir 目录下的所有源文件都读取到变量`varname`中。

# 三、相关变量

1. <project_name>_BINARY_DIR: project_name/build，随着工程名变化而变化
2. <project_name>_SOURCE_DIR: project_name，随着工程名变化而变化
3. PROJECT_BINARY_DIR：同 <project_name>_BINARY_DIR，不随着工程名变化而变化
4. PROJECT_SOURCE_DIR：同 <project_name>_SOURCE_DIR，不随着工程名变化而变化
5. CMAKE_CURRENT_SOURCE_DIR: CMakeLists.txt 所在的路径

# 四、FAQ

1. 包含第三方库头文件

   > 这种情况发生在项目使用系统存在的第三方库时，无关项目内部头文件存放位置问题。

   使用第三方库头文件时，路径应该写成`#include<library_name/xxxx.h>`，因为一般第三方头文件都是放在`/usr/local/include/library_name/`下，系统只会搜索到 include ，不会递归搜索下面的子目录。

   当头文件存放位置不在系统默认的搜索路径时，可以使用`include_directories(path)`来手动指定路径。

2. 找不到库

   > undefined reference to `function_name()`

   原因可能有下：

   1. 动态库文件没有放在系统搜索路径下。

      将动态库移动到`/usr/local/lib/`或其子目录下面，将路径添加到系统的动态库搜索路径中(`/usr/local/lib/`已经是系统的搜索路径了)。

   2. CMakeLists.txt 未使用`target_link_libraries`指明项目使用了哪些库。

   3. C++ 调用 C 库，需要使用`extern "C"`来引入头文件。

3. 为什么把第三方库放到系统搜索路径下后还要手动指出用了哪个库？

   [Linux下GCC 编译时为什么要指定链接库？如何指定链接库 ？](https://blog.csdn.net/lee244868149/article/details/38707127)

   即使第三方库已经放在了`/usr/local/lib/`等系统搜索目录下，也需要手动指定使用哪个库。因为 gcc 默认只载入 c/c++ 标准库，其它的库也载入的话程序就太大了，而且 gcc 也不会去寻找系统中的所有库，所以需要使用`target_link_libraries`手动指出用了哪个库。还需要注意的是`.so`大多只是一个链接，链接到`.so.x`这样的真正动态库，而`ld`只会搜索`.so`文件，当只有`.so.x/.so.x.x.so`时，需要手动进行`ln -s`。