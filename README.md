# 为什么要开这个项目
因为总是有未经授权的家伙访问我的服务器，于是就开一个黑名单机制好了

# 文件介绍
rapidjson文件夹的内容下是用来读取IP数据库的一个库，为了方便就直接引入了

ban.sh是用来自动生成黑名单并屏蔽用的

genbl.sh是用来生成不在白名单里的IP列表的，注意这只是测试了可执行文件的一个功能，实际代码已经被集成掉了

ipdb是ipip.net的免费IP数据库

ipdb.cpp是用来读取数据库的C++源文件，基于官方的demo修改

ipdb.hpp是用来读取数据库的C++头文件，基于官方的demo修改

IP-List.cpp是核心C++源文件

list.sh是用于列出日志里所有IP的详细信息的

make.sh是用来编译程序的

whitelist.txt是白名单地址，注意地址需要和程序输出的地址的格式一致，否则可能会无效


# 文件树
```
│  ban.sh
│  genbl.sh
│  IP-List.cpp
│  ipdb
│  ipdb.cpp
│  ipdb.hpp
│  list.sh
│  make.sh
│  README.md
│  whitelist.txt
│
└─rapidjson
    │  一大堆东西
```
