#!/bin/bash

# 获取脚本所在目录的上层目录路径
current_dir=$(dirname "$(realpath "$0")")
parent_dir=$(dirname "$current_dir")


# 复制文件到上层其他文件夹
cp -f "$current_dir/CMakeLists.txt" "$parent_dir"
cp -f "$current_dir/rtconfig.h"     "$parent_dir/RT-Thread/"
cp -f "$current_dir/board.c"        "$parent_dir/Middlewares/Third_Party/RealThread_RTOS/bsp/_template/cubemx_config"
echo "文件已成功复制到目标文件夹。"


