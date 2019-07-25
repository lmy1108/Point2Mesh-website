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
#include <sstream>
using namespace std;
using namespace pcl;
double stringToNum(const string& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}
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
    string param8 = argv[10];
    double Degree = stringToNum(param1);
    double Depth = stringToNum(param2);
    double IsoDivide = stringToNum(param3);
    double SamplesPerNode = stringToNum(param4);
    double Scale = stringToNum(param5);
    double SolverDivide = stringToNum(param6);
    bool is_Confidence;
    bool isManifold;
    if (param7 == "ON") {
        is_Confidence = true;
    }
    else {
        is_Confidence = false;
    }
    if (param8 == "ON") {
        isManifold = true;
    }
    else {
        isManifold = false;
    }
    pcl::PointCloud < pcl::PointXYZRGB > ::Ptr raw_cloud(new pcl::PointCloud<pcl::PointXYZRGB>); //创建点云对象指针，用于存储输入
    if (pcl::io::loadPLYFile(inputPath, *raw_cloud) == -1) {
        PCL_ERROR("Could not read ply file!\n");
        return -1;
    }
    
    
    //直通滤波法
    PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>());
    PassThrough<PointXYZRGB> filter;
    filter.setInputCloud(raw_cloud);
    /*
     
     
     filter.filter(*cloud);
     filter.setFilterFieldName("z");
     filter.setFilterLimits(0.0, 1.0);        //设置在过滤字段的范围
     filter.filter(*cloud);
     
     pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;   //创建滤波器对象
     sor.setInputCloud(raw_cloud);                           //设置待滤波的点云
     //sor.setMeanK(50);                               //设置在进行统计时考虑查询点临近点数
     //sor.setStddevMulThresh(1.0);
     */
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
    
    //创建搜索树
    pcl::search::KdTree<pcl::PointXYZRGBNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointXYZRGBNormal>);
    tree2->setInputCloud(cloud_with_normals);
    //创建Poisson对象，并设置参数
    pcl::Poisson<pcl::PointXYZRGBNormal> pn;
    pn.setConfidence(is_Confidence); //是否使用法向量的大小作为置信信息。如果false，所有法向量均归一化。
    pn.setDegree(Degree); //设置参数degree[1,5],值越大越精细，耗时越久。
    pn.setDepth(Depth); //树的最大深度，求解2^d x 2^d x 2^d立方体元。由于八叉树自适应采样密度，指定值仅为最大深度。
    pn.setIsoDivide(IsoDivide); //用于提取ISO等值面的算法的深度
    pn.setManifold(isManifold); //是否添加多边形的重心，当多边形三角化时。 设置流行标志，如果设置为true，则对多边形进行细分三角话时添加重心，设置false则不添加
    pn.setSamplesPerNode(SamplesPerNode); //设置落入一个八叉树结点中的样本点的最小数量。无噪声，[1.0-5.0],有噪声[15.-20.]平滑
    pn.setScale(Scale); //设置用于重构的立方体直径和样本边界立方体直径的比率。
    pn.setSolverDivide(SolverDivide); //设置求解线性方程组的Gauss-Seidel迭代方法的深度
    //pn.setIndices();
    
    //设置搜索方法和输入点云
    pn.setSearchMethod(tree2);
    pn.setInputCloud(cloud_with_normals);
    //创建多变形网格，用于存储结果
    pcl::PolygonMesh mesh;
    //执行重构
    pn.performReconstruction(mesh);
    //添加颜色
    PointCloud<PointXYZRGB> cloud_color_mesh;
    pcl::fromPCLPointCloud2(mesh.cloud, cloud_color_mesh);
    pn.setOutputPolygons(false); //是否输出多边形网格（而不是三角化移动立方体的结果）
    
    pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
    kdtree.setInputCloud(cloud);
    // K nearest neighbor search
    int K = 5;
    std::vector<int> pointIdxNKNSearch(K);
    std::vector<float> pointNKNSquaredDistance(K);
    for (int i = 0; i<cloud_color_mesh.points.size(); ++i)
    {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        float dist = 0.0;
        int red = 0;
        int green = 0;
        int blue = 0;
        uint32_t rgb;
        
        if (kdtree.nearestKSearch(cloud_color_mesh.points[i], K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
        {
            for (int j = 0; j < pointIdxNKNSearch.size(); ++j)
            {
                r = cloud->points[pointIdxNKNSearch[j]].r;
                g = cloud->points[pointIdxNKNSearch[j]].g;
                b = cloud->points[pointIdxNKNSearch[j]].b;
                red += int(r);
                green += int(g);
                blue += int(b);
                dist += 1.0 / pointNKNSquaredDistance[j];
                
                //std::cout << "red: " << int(r) << std::endl;
                //std::cout << "green: " << int(g) << std::endl;
                //std::cout << "blue: " << int(b) << std::endl;
                //cout << "dis:" << dist << endl;
            }
        }
        cloud_color_mesh.points[i].r = int(red / pointIdxNKNSearch.size() + 0.5);
        cloud_color_mesh.points[i].g = int(green / pointIdxNKNSearch.size() + 0.5);
        cloud_color_mesh.points[i].b = int(blue / pointIdxNKNSearch.size() + 0.5);
    }
    
    
    //保存网格图
    toPCLPointCloud2(cloud_color_mesh, mesh.cloud);
    pcl::io::savePLYFile(outputPath, mesh);
    
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
    
    return 0;
}
