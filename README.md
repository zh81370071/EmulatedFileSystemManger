# EmulatedFileSystemManger
//本次课程设计编程实现了一个以“多用户、多级目录结构文件系统的设计与 实现”为主题的模拟 UNIX 文件系统
该系统能实现 UNIX 文件系统的大部分管理
功能，如多用户的登入、登出及权限管理，系统初始化，系统的退出保存，文件
及目录的创建、修改和删除，多级目录，目录切换等基本功能，通过成组链接法
对空闲磁盘块进行分配与回收。此外，该文件系统还提供指令及文件目录名的自
动补全，文件及目录的复制、粘贴、剪切、重命名、查找和创建快捷方式，格式
化等扩展功能，能对用户输入的错误命令进行错误提示，还能高效管理磁盘的 i
节点、SFD、数据区等。且提供友好的用户界面，交互体验较好，使用过程中会
有明确的交互性语句提示，提供不同颜色的提示强化效果，指令帮助说明清晰，
程序健壮性和容错性较好。
此外，本文件系统使用合理的数据结构表示超级块、i 结点区、目录及数
据区等，使用多级索引方式存储文件内容，使用成组链接法对空闲磁盘法进行分
配和回收。使用位势图的数据结构来统一分配回收空闲目录和 i 结点，充分模拟
了 Unix 系统的各个功能模块

如有需要联系81370071@qq.com
