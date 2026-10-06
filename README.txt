打开方法：
1. 双击“基于多态的职工管理系统.slnx”。
2. 在 Visual Studio 中选择“生成解决方案”。
3. 若 Visual Studio 提示重定目标，请接受使用当前安装的工具集和 Windows SDK。

主要源码：
- 职工管理系统.cpp：程序入口和菜单
- workerManager.cpp/.h：增删改查、排序、文件读写
- worker.h：抽象职工基类
- employee、manager、boss：三种派生职工类型
- empFile.txt：职工数据文件
