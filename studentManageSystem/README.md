<!--
 * @Description: 
 * @Author: 
 * @Date: 2019-11-09 09:01:54
 * @Version: 3
 * @LastEditTime: 2019-11-09 13:24:42
 * @LastEditors: Liu Kai
 -->
# manage_information_students
## [例2]学生信息管理程序(数据结构C语言版 李云清)

### (1)问题描述:
学生信息包括:学号、姓名、年龄、性别、出生年月、地址、电话和Email等, 试设计一个学生信息管理程序. 实现学生信息的电于化管理. 要求: 使用文件方式存储数据, 采用链表组织学生数据. 
### (2)基本要求 系统应具有以下基本功能 
1. 系统以菜单方式工作
2. 学生信息录入功能(学生信息用文件保存) - 输入
3. 学生信息浏览功能 - 输出
4. 学生信息查询功能 - 按学号查询、按姓名杳询  
5. 学生信息的删除与修改
6. 学生信息的排序(按学号, 按年龄)
### (3)算法分析
本课程设计主要训练学生应用链表存储和管理信息的综合能力, 涉及链表的删除、查找、插入和排序等基本算法. 
# 写在前面: 
# 1.*ver4: 2019/11/9 更新*
 1. #### CSDN博客地址  https://blog.csdn.net/weixin_43905243/article/details/102492531
 2. 修复了创建数据文件(make)或删除数据文件(del)后, 查看数据文件(dir)时文件个数显示不正常的问题 `详情: 修改dir()函数检查到无数据文件时的返回值, 从-1改为0, case 14: remove删除后调用dir重新统计count的值`
# 2. *ver3: 2019/10/27更新*

 1. 对switch语句进行了维护, 可以通过命令的形式操作菜单, 并增加了help帮助选项
 2. 对链表中学号重复的情况进行了更改, 现在不允许学号重复, 但仍允许重名
 3. 允许用户建立 删除 查看已有数据库,  并能在不退出应用的情况下访问多个数据库, 运行前不需要手动建立数据文件

# 3.*ver2: 2019/10/11更新(原创建于2019/10/10)*

 1. 合并了main.c与funcBase.c文件
 2. 头文件重写使得更符合标准
 3. 修复了目标创建错误无法打开的问题(`详细:将char input_fileName[MaxFileName] ="manage_information_students\\StuData.dat"改为char input_fileName[MaxFileName] = "StuData.dat")`
 4. 增加了gcc命令使用说明

# 4.*gcc使用说明:*

 1. 将命令行转到文件目录下, 附上文档 [cmd命令](https://blog.csdn.net/yzyggu/article/details/90640888)
 2. 使用命令gcc dataBase.c main.c -o main编译生成main.exe(call.h不用编译),附上文档 [Windows命令行中使用gcc/g++同时编译多个文件](https://blog.csdn.net/qq_42704360/article/details/83176495)

