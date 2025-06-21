# Get Started
open with `vscode`
1. cmake
```bash
cmake -B build -G Ninja
```
2. build
```bash
ninja -C build
```
3. flash
```bash
ninja -C build flash
```

# Usage
## cmake build 
### for ninja
```bash
cmake -B build -G Ninja
```
### for make
```bash
cmake -B build
```

## ninja
### build
```bash
ninja -C build
```

### flash
```bash
ninja -C build flash
```

### clean
```bash
ninja -C build clean
```

or

```bash
rm -rf build
```

## STM32 Debug
## setting.json
```json
    "cortex-debug.armToolchainPath.linux": "/usr/local/arm-gnu-toolchain",
    "cortex-debug.openocdPath.linux": "/usr/bin/openocd",
    "cortex-debug.gdbPath.linux": "/usr/local/arm-gnu-toolchain/bin/arm-none-eabi-gdb",
```
## launch.json
For `f103c8t6`
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "STM32F103C8T6 Debug (OpenOCD SWD)",
            "cwd": "${workspaceFolder}",  // 使用新版变量名
            "executable": "${workspaceFolder}/build/${workspaceFolderBasename}.elf",  // 动态获取文件名
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            
            // 硬件接口配置
            "device": "stm32f103c8",
            "interface": "swd",
            "transport": "swd",  // 明确指定传输协议
            "adapterSpeed": 4000,  // 设置SWD时钟速度（kHz）
            
            // OpenOCD配置文件
            "configFiles": [
                "${workspaceFolder}/openocd.cfg",  // 自定义配置文件路径
            ],
            
            // 调试行为控制
            "runToEntryPoint": "main",
            "haltAtEntry": true,  // 在入口点暂停
            "showDevDebugOutput": true,  // 显示详细调试日志
            
            // 内存访问设置
            "memoryMap": "ram-only",  // 仅允许RAM访问（避免误写Flash）
            "overrideGDBServerCommands": [
                "set mem inaccessible-by-default off"
            ],
            
            // 复位控制序列
            "preLaunchCommands": [
                "monitor reset halt",    // 先复位并暂停
                "monitor adapter speed 4000",  // 设置适配器速度
                "monitor arm semihosting enable"  // 启用半主机（如需）
            ],
            "postLaunchCommands": [
                "monitor reset init",   // 初始化硬件
                "monitor sleep 200",   // 等待稳定
                "break main"            // 在main函数设断点
            ],
            
            // 可视化调试辅助
            // "svdFile": "${workspaceFolder}/STM32F103xx.svd",  // SVD文件路径
            // "rttConfig": {  // 实时传输(RTT)配置（可选）
            //     "enabled": true,
            //     "address": "auto",
            //     "decoders": [
            //         {
            //             "label": "RTT Output",
            //             "type": "console"
            //         }
            //     ]
            // }
        }
    ]
}
```
## openocd.cfg
```openocd.cfg
# openocd.cfg
source [find interface/jlink.cfg]
transport select swd
adapter speed 4000
source [find target/stm32f1x.cfg]
```
[# VSCode 加Cortex-Debug嵌入式调试方法](https://blog.csdn.net/qq_32348883/article/details/135213750)

## stm32 vscode clangd 
### can't find `<stdio.h>`
项目根目录建立.clangd文件
```.clangd
CompileFlags:
  Add:
    - "--target=arm-none-eabi"  # 关键：指定ARM目标
    - "-I/usr/local/arm-gnu-toolchain/arm-none-eabi/include"  # 工具链头文件路径
  DriverMode: cl  # 兼容GCC参数
```