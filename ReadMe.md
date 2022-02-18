# SpaceWar

为1MGames游戏开发比赛制作的游戏。采用C++17开发。  
编译好的参赛作品在[这里](https://gitee.com/VisualGMQ/space-war/releases/v1.0.0)

## 编译方法

编译平台为MacOS（在MacOS Big Sur 11.6中编译成功且结果在1M以下），也可以在其他平台编译，但编译结果**不保证在1M以下**，仅仅是为了方便不同平台进行编译。

使用CMake 3.20及以上进行编译。需要拉取`glfw`作为子工程：

```bash
git submodule update --init --recursive
```

然后编译：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

如果想要使用`glew`，可以通过以下命令（默认用glad）:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DUSE_GLEW=ON
cmake --build build
```

cmake会在你的电脑上寻找`glew`。  

如果想要压缩文件至1M以下，你需要有`strip`程序和`upx`程序，并执行：

```bash
cmake --build build --target CompressExe
```

编译好后执行pack命令打包

```bash
cmake --build build --target Pack
```

最终的结果在`output`文件夹下：

* game：包含了游戏本体
* snapshot：包含了游戏的截图
* HowToPlay.md：游戏说明

## 游戏截图

![welcome](./snapshot/welcome.png)

![select](./snapshot/select_ship.png)

![gaming](./snapshot/gaming.png)

![gaming2](./snapshot/gaming2.png)

## 游戏操作

[游戏操作](./HowToPlay.md)
