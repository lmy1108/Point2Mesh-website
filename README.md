# Point2Mesh-website
演示视频<br>
https://www.bilibili.com/video/av30430488
## 1 Purpose of design
In the research related to computer graphics, we usually need transform point cloud to meshes, the quality of meshes generated determines the outcome out further modeling, #D printing, etc. However, we usually need to adjust the patameters of the code(e.g. using libraries like PCL) and compile them over and over again. constructing a environment for different libraries is also a burden. Visualization also requires some extra work to be done. 在图形学点云相关的研究中，我们常常需要使用PCL等相关的库将点云转化成网格，而转化成网格的质量决定了以后3D模型制作、三维打印的质量。然而在平时的研究中， 我们往往在调整参数以后需要一遍一遍的编译PCL等代码来进行实验，不仅搭建环境和修改代码费时费力，而且不易进行直观观察，我们的项目通过输入需要转换的点云文件经过算法调整处理输出结果文件，并且可以下载转换后的点云文件或者网格文件。这样只要有一台配置好环境的服务器，就可以直接进行点云文件的上传，在线的参数调整和前端显示及网格下载，节省了大量时间。<br><br>文件的主要格式为 ply。 主要算法有:贪婪投影三角化、泊松表面重建、Marching Cube 重建、jhu 改进泊松表面重 建、jhu-ssd 重建、点云滤波、体素化点云、点云增加法向量、三角网格优化。<br><br> 在实验中我们发现JHU开源库(改进泊松重建和SSD重建等)相比效果较好，所以也一起加入了系统
## 2 系统基本功能

### 前端显示
前端通过javascript网站制作显示功能。通过输入点云文件以及参数调整运行相关的算法功能，并且通过webGL互动展示网格效果。
### 后端调用
使用java类调用已完成的算法程序，将前端传来的参数与文件，传入生成的可执行程序中进行相关的处理，生成网格文件或点云文件，对于需要显示网格的程序通过webGL显示在前端界面，并且通过java下载结果文件。
### 算法基本功能和参数:
#### 1)贪婪投影三角化
先将有向点云投影到某一局部坐标平面内，再在坐标平面内进行平面内的三角化，根据平面内三位点的拓扑关系获得一个三角网格曲面模型。<br>
主要参数为：搜索半径、最近邻距离的乘子、最近邻点的最大数量、最大平面角(π)、每个三角的最小角度(π)、每个三角的最大角度(π)、法向量是否一致。
具体界面如图所示

 
#### 2).泊松表面重建
通过把表面重建问题表达成泊松问题，求解泊松方程来取得点云模型所描述的表面信息代表的隐性方程，通过对该方程进行等值面提取，从而得到具有几何实体信息的表面模型。<br>
主要参数为：参数degree范围[1,5]、树的最大深度、用于提取ISO等值面的算法的深度、落入一个八叉树结点中的样本点的最小数量、用于重构的立方体直径和样本边界立方体直径的比率、Gauss-Seidel迭代方法的深度、是否使用法向量的大小作为置信息、是否添加多边形的重心。


#### 3)Marching Cube重建
移动立方体法首先将数据场中八个位置相邻的数据分别存放在一个四面体体元的八个顶点处。通过计算该体元中十二条棱和等值面的交点，并构造体元中的三角面片，所有的三角面片把体元分成了等值面内与等值面外两块区域。最后连接此数据场中的所有体元的三角面片，构成等值面。合并所有立方体的等值面便可生成完整的三维表面。<br>
主要参数：各向异性等级、设置方格分辨率、设置方格移动百分比(Percentage-
ExtendGrid)。


 
#### 4)jhu改进泊松表面重建
jhu大学改进的泊松表面重建方法。<br>
主要参数为：B-spline角度(B-spline degree)、边界类型(boundary type)、深度(depth)、比例(scale)、每个结点的样本数(samplesPerNode)、每个点的权重(pointweight)、密度（density）、确定一致（confidence）。


#### 5)jhu-ssd重建
基于原始图八叉树混合有限元、有限差分的高效实现离散化和双行进多维数据集等值面提取算法，产生高质量无裂缝的自适应流形多边形网格。<br>
主要参数为：B-spline角度(B-spline degree)、深度(depth)、比例(scale)、每个结点的样本数(samplesPerNode)、每个点的权重(valueweight)、梯度权重(gradientWeight)、biLapWeigh、密度（density）、确定一致（confidence）。





#### 6)点云滤波
分为直通滤波、半径滤波与统计滤波

#### 7)体素化点云:
通过输入的点云数据创建一个三维体素栅格，然后在每个体素内，用体素中所有点的重心来近似显示体素中其他点.

#### 8)点云增加法向量
对于ply文件中未定义法向量的，增加法向量。


#### 9)三角网格优化
对于一些生成的网格，此功能会根据参数检测其稀薄的部分，并进行剪切。<br>
主要参数为：曲面剪切的阈值。
