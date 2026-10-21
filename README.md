# AIScada —— AI-Native 工业组态软件

## 一句话定位

从零设计的国产 AI 原生工业组态软件。对象模型为核心，Runtime 为引擎，AI Agent 为智能接口，开放生态为壁垒。

## 环境要求（卡死，不要混用）

| 项目 | 版本 | 备注 |
|------|------|------|
| Qt | **6.8.4 LTS（EXACT）** | CMake 里锁死，装错编译不过 |
| CMake | ≥ 3.21 | |
| 编译器 | MSVC 2019 / GCC 11 / Clang 14 | C++20 |
| 操作系统 | Windows 10+ / Linux / 麒麟 / 统信 UOS | |

## 构建（三条命令）

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
ctest --test-dir build --output-on-failure
```

Windows 打包发布：

```bash
cd build
windeployqt6 --qmldir ../src/ui ../aiscada.exe
cpack -C Release
```

## 工程约定

### 依赖方向（单向，违反即架构腐烂）

```
ui  →  storage → runtime → protocols → core
                ↘ drivers ↗
ai  →  core
util → (无)
```

`core/` 里不得 include `ui/` 或 `runtime/` 的头文件。

### 编码规范

1. 所有工程对象继承 `Object`，通过 setter 改属性，禁止直接改成员。
2. id 是 UUID，引用永远用 id，禁止用名字或数组下标。
3. AI 写操作只走工具调用，写前必须确认。
4. 工程文件用 JSON + JSON Schema 校验，UTF-8 无 BOM，缩进 2 空格。
5. 值变化发 `valueChanged`，配置变化发 `objectChanged`，两套信号不能混。
6. 所有对象模型单元测试必须绿，才能合入主干。
7. 提交信息用英文祈使句：`Add Variable::setAddress notification signal`。

### 分支策略

- `main`：可发布状态，受保护
- `develop`：集成分支
- 功能分支：`feature/<模块>-<简述>`，如 `feature/ai-add-variable-tool`
- 一次 PR 只做一件事，必须带测试

## 已知坑（Qt 6.8.4）

- `AA_EnableHighDpiScaling` 等属性在 Qt 6 已移除，不要再写。
- `QVariant::Type` 部分枚举在 Qt 6 行为变化，用 `QMetaType` 接口。
- `Q_FOREACH` 弃用，改用范围 for。
- 信号槽用函数指针写法，旧宏写法无编译期检查。
- `find_package` 漏写组件会在链接期才报错，组件列表写在根 CMakeLists 里。

## 里程碑

| 时间 | 目标 | 验收 |
|------|------|------|
| 1 个月 | MVP 闭环 | 建变量、存盘、Modbus 读值、AI 新增变量 |
| 2 个月 | 组态可用 | 画画面、绑变量、Runtime、AI 侧边栏流式 |
| 3 个月 | 智能化 | 工具闭环、报警诊断、脚本生成、审计回滚 |
| 4 个月 | 多协议 | Modbus RTU/TCP + MQTT，OPC UA |
| 5 个月 | 迁移工具 | 能导入至少一家对手工程 |
| 6 个月 | 商业验证 | 3 家付费试点 |
