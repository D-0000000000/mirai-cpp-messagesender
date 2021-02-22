# mirai-cpp-Messagesender

 mirai-cpp 发送消息用的机器人

## 使用方法

使用 Visual Studio 或 Visual Studio Code 直接打开整个文件夹即可。

编译目标为可执行文件，其主函数位于 **src/main.cpp** 。

头文件请添加到 **include** 目录中

源文件请添加到 **src** 目录中，并且不要忘记修改 **CMakeLists.txt**。（参考CMakeLists.txt中的注释进行修改）


mirai-cpp 的说明文档：[使用说明](https://github.com/cyanray/mirai-cpp/blob/master/doc/%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E.md)

## 用法

首先创建配置文件，在当前目录下创建一个名为`settings.txt`的文件，第一行为`authKey`，第二行为bot的QQ号，第三行为目标QQ群号，例如
```bash
AUTHKEY
1145144396
1919810777
```

运行
```bash
./qqmessagesender "message"
```
## 依赖

本项目基于https://github.com/cyanray/mirai-cpp/
