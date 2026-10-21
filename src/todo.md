C:\Work\Study\MyGame\              <-- 解决方案目录 (.sln)
├── MyGame.sln
├── vcpkg/                         <-- (可选) 包管理工具目录
├── ThirdParty\                    <-- 第三方库总目录（推荐）
│   ├── Qt\                        <-- 例如: Qt 6.x.x (完整安装或拷贝)
│   │   ├── include\
│   │   ├── lib\
│   │   ├── bin\                   <-- 运行时 dll 在这里
│   │   └── mkspecs\
│   ├── SDL2\                      <-- 其他游戏常用库
│   └── GLM\
└── MyGame\                        <-- 你的 C++ 项目目录 (.vcxproj)
    ├── MyGame.vcxproj
    ├── MyGame.vcxproj.filters
    ├── src\
    │   └── main.cpp
    ├── include\
    └── (Debug/Release 编译输出)