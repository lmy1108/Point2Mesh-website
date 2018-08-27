#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
double stringToNum(const string& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}
/*
 共9个参数，分别是输入，输出路径，六个double参数，一个bool参数，对应
 1. if (pcl::io::loadPLYFile(inputPath, *cloud) == -1) {
 
 2. pcl::io::savePLYFile(outputPath, triangles);
 
 3-9:
 gp3.setSearchRadius(radius); //设置连接点之间的最大距离（最大边长）用于确定k近邻的球半径（默认值 0）
 gp3.setMu(multiple); //设置最近邻距离的乘子，以得到5每个点的最终搜索半径（默认值 0）
 gp3.setMaximumNearestNeighbors(number); //设置搜索的最近邻点的最大数量
 gp3.setMaximumSurfaceAngle(M_PI * maxAngleFlat); // 45 degrees 最大平面角
 gp3.setMinimumAngle(M_PI * minAngle); // 10 degrees 每个三角的最小角度
 gp3.setMaximumAngle(M_PI * maxAngle); // 120 degrees 每个三角的最大角度
 gp3.setNormalConsistency(isNormal); //如果法向量一致，设置为true
 
 */
int main(int argc, char** argv)
{
    string inputPath = argv[1];
    string outputPath = argv[2];
    string param1 = argv[3];
    string param2 = argv[4];
    string param3 = argv[5];
    string param4 = argv[6];
    string param5 = argv[7];
    string param6 = argv[8];
    string param7 = argv[9];
    
    double radius = stringToNum(param1);
    double multiple = stringToNum(param2);
    double number = stringToNum(param3);
    double maxAngleFlat = stringToNum(param4);
    double minAngle = stringToNum(param5);
    double maxAngle = stringToNum(param6);
    bool isNormal;
    if(param7=="ON"){
        isNormal = true;
    }else{
        isNormal = false;
    }
    cout<<inputPath<<endl;
    cout<<outputPath<<endl;
    cout<<"radius:   "<<radius<<endl;
    cout<<"multiple:   "<<multiple<<endl;
    cout<<"isNormal"<<isNormal<<endl;
    
    
    
    
    
    //载入无序的XYZ型的点云数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPLYFile(inputPath, *cloud) == -1) {
        PCL_ERROR("Could not read ply file!\n");
        return -1;
    }
    /*if (pcl::io::loadPCDFile<pcl::PointXYZ>("depth_0.pcd", *cloud) == -1)
     {
     PCL_ERROR("Couldn't read the file!\n");  //若读取失败将提示
     return -1;
     }*/
    std::cerr << "点云读入完成" << std::endl;
    
    //估计法向量
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud);
    n.setInputCloud(cloud);
    n.setSearchMethod(tree);
    n.setKSearch(30);
    n.compute(*normals); //计算法线，结果存储在normals中
    //*normals 不能同时包含点的法向量和表面的曲率
    
    //将点云和法线放到一起
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
    //*cloud_with_normals = cloud + normals
    
    std::cerr << "估计法向量完成" << std::endl;
    
    //创建搜索树
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud(cloud_with_normals);
    
    //初始化GreedyProjectionTriangulation对象，并设置参数
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    //创建多多边形网格对象，用于存储结果
    pcl::PolygonMesh triangles;
    
    //设置GreedyProjectionTriangulation对象的参数
    //第一个参数影响很大
    gp3.setSearchRadius(radius); //设置连接点之间的最大距离（最大边长）用于确定k近邻的球半径（默认值 0）
    gp3.setMu(multiple); //设置最近邻距离的乘子，以得到5每个点的最终搜索半径（默认值 0）
    gp3.setMaximumNearestNeighbors(number); //设置搜索的最近邻点的最大数量
    gp3.setMaximumSurfaceAngle(M_PI * maxAngleFlat); // 45 degrees 最大平面角
    gp3.setMinimumAngle(M_PI * minAngle); // 10 degrees 每个三角的最小角度
    gp3.setMaximumAngle(M_PI * maxAngle); // 120 degrees 每个三角的最大角度
    gp3.setNormalConsistency(isNormal); //如果法向量一致，设置为true
    
    //输入点云和设置搜索方法
    gp3.setInputCloud(cloud_with_normals);
    gp3.setSearchMethod(tree2);
    
    //执行重构，结果保存在triangles中
    gp3.reconstruct(triangles);
    
    std::cerr << "重建完成" << std::endl;
    
    //保存网格图
    pcl::io::savePLYFile(outputPath, triangles);
    
    std::cerr << "显示结果..." << std::endl;
    
    //显示结果图
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(255, 255, 255); //设置背景
    viewer->addPolygonMesh(triangles, "my"); //设置显示的网格
    viewer->addCoordinateSystem(0.1); //设置坐标系
    viewer->initCameraParameters();
    while (!viewer->wasStopped()) {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
    
    //完成
    return 0;
}
