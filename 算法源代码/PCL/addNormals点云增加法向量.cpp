//点的类型的头文件
#include <pcl/point_types.h>
//点云文件IO（pcd文件和ply文件）
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
//kd树
#include <pcl/kdtree/kdtree_flann.h>
//特征提取
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/normal_3d.h>
//重构
#include <pcl/surface/gp3.h>
#include <pcl/surface/poisson.h>
//可视化
#include <pcl/visualization/pcl_visualizer.h>
//多线程
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <boost/thread/thread.hpp>
#include <pcl/filters/passthrough.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace pcl;
using namespace std;
int main(int argc, char** argv)
{
    string inputPath = argv[1];
    string outputPath = argv[2];
    pcl::PointCloud < pcl::PointXYZRGB > ::Ptr raw_cloud(new pcl::PointCloud<pcl::PointXYZRGB>); //创建点云对象指针，用于存储输入
    if (pcl::io::loadPLYFile(inputPath, *raw_cloud) == -1) {
        PCL_ERROR("Could not read ply file!\n");
        return -1;
    }
    
    
    //直通滤波法
    PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>());
    PassThrough<PointXYZRGB> filter;
    filter.setInputCloud(raw_cloud);
    
    filter.filter(*cloud);
    
    // 计算法向量
    
    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> n;//法线估计对象
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);//存储估计的法线的指针
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree->setInputCloud(cloud);
    n.setInputCloud(cloud);
    n.setSearchMethod(tree);
    n.setKSearch(20);
    //n.setRadiusSearch(5);//设置搜索半径
    n.compute(*normals); //计算法线，结果存储在normals中
    
    //将点云和法线放到一起
    for (size_t i = 0; i < normals->size(); ++i) {
        normals->points[i].normal_x *= -1;
        normals->points[i].normal_y *= -1;
        normals->points[i].normal_z *= -1;
    }
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
    
    //保存网格图
    
    // toPCLPointCloud2(cloud_color_mesh, mesh.cloud);
    pcl::io::savePLYFile(outputPath, *cloud_with_normals);
    /*
     // 显示结果图
     boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D viewer"));
     viewer->setBackgroundColor(255, 255, 255);
     viewer->addPolygonMesh(mesh, "my");
     //viewer->addCoordinateSystem(5);
     viewer->initCameraParameters();
     while (!viewer->wasStopped()) {
     viewer->spinOnce(100);
     boost::this_thread::sleep(boost::posix_time::microseconds(100000));
     }
     */
    
    return 0;
}
