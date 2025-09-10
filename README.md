# Satellite Position Visualizer卫星位置可视化工具

A Qt-based application for visualizing satellite positions in a skyplot, with intuitive representation of different satellite constellations and interactive features.

## Overview

This application provides a graphical interface to display satellite positions using a skyplot format, making it easy to visualize the distribution of satellites from major global navigation systems. It converts satellite polar coordinates (elevation and azimuth) to Cartesian coordinates for visual representation, with distinct colors for different satellite constellations.

## Features

- Sky grid visualization with elevation circles (0° to 90°)
- Azimuth lines with directional labels (N/E/S/W)
- Color-coded satellites by constellation (BDS, GPS, Galileo, GLONASS)
- Interactive satellite selection (click to view details)
- Legend explaining color coding
- Orientation compass
- Anti-aliased rendering for smooth graphics

## Screenshot
<img width="1203" height="947" alt="image" src="https://github.com/user-attachments/assets/0e3a460a-24fe-4b91-8fdf-0c50d43fbebf" />


## Dependencies

- Qt 5 or later
- C++11 or later compiler

## Installation

1. Clone this repository
   ```bash
   git clone https://github.com/yourusername/satellite-position-visualizer.git
   ```

2. Open the project in Qt Creator

3. Build and run the application

## Usage

The application comes with sample satellite data. Upon launching, you'll see:
- Colored circles representing satellites
- Concentric circles showing elevation angles
- Radial lines indicating azimuth directions
- Interactive elements:
  - Click on any satellite to view detailed information
  - Hover over satellites for quick identification

## Code Structure

- `satellitepositionview.h/cpp`: Main widget implementation
- `Satellite` struct: Data structure for satellite properties
- Key methods:
  - `paintEvent`: Main drawing function
  - `drawSkyGrid`: Renders the sky coordinate system
  - `drawSatellites`: Draws satellites based on their coordinates
  - `polarToCartesian`: Converts satellite coordinates for display
  - `drawLegend` and `drawCompass`: Render UI elements

## License

This project is licensed under the MIT License - see the LICENSE file for details.


# 卫星位置可视化工具

一款基于 Qt的应用程序，用于在天球图中可视化卫星位置，直观直观展示不同卫星星座并提供交互功能。

## 概述

该应用程序提供图形界面，以天球图格式显示卫星位置，便于可视化来自主要全球导航系统的卫星分布。它将卫星极坐标（仰角和方位角）转换为笛卡尔坐标进行可视化表示，并为不同卫星星座使用不同颜色进行区分。

## 功能特点

- 带有仰角圆（0°至90°）的天球网格可视化
- 带方向标签（北/东/南/西）的方位角线
- 按星座（北斗、GPS、伽利略、格洛纳斯）进行颜色编码的卫星
- 交互式卫星选择（点击查看详情）
- 解释颜色编码的图例
- 定位指北针
- 抗锯齿渲染，图形平滑

## 截图
<img width="1203" height="947" alt="image" src="https://github.com/user-attachments/assets/27a23b8e-44ec-4f47-afad-7ff772cf224e" />


*卫星位置可视化示例*

## 依赖项

- Qt 5 或更高版本
- C++11 或更高版本编译器

## 安装

1. 克隆此仓库
   ```bash
   git clone https://github.com/yourusername/satellite-position-visualizer.git
   ```

2. 在Qt Creator中打开项目

3. 构建并运行应用程序

## 使用方法

应用程序附带示例卫星数据。启动后，您将看到：
- 代表卫星的彩色圆圈
- 显示仰角的同心圆
- 指示方位的辐射线
- 交互元素：
  - 点击任何卫星查看详细信息
  - 悬停在卫星上可快速识别

## 代码结构

- `satellitepositionview.h/cpp`：主窗口部件实现
- `Satellite` 结构体：卫星属性的数据结构
- 主要方法：
  - `paintEvent`：主绘图函数
  - `drawSkyGrid`：渲染天球坐标系
  - `drawSatellites`：根据坐标绘制卫星
  - `polarToCartesian`：转换卫星坐标用于显示
  - `drawLegend` 和 `drawCompass`：渲染UI元素

## 许可证

本项目采用MIT许可证 - 详见LICENSE文件。
