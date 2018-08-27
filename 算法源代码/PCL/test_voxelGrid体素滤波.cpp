
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/ply_io.h>

using namespace std;
double stringToNum(const string& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}
int main (int argc, char** argv)
{
    string inputPath = argv[1];
    string outputPath = argv[2];
    string size = argv[3];
    double radius = stringToNum(size);
    
    
    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
    pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());
    
    // Fill in the cloud data
    pcl::PLYReader reader;
    // Replace the path below with the path where you saved your file
    reader.read (inputPath, *cloud); // Remember to download the file first!
    
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
    << " data points (" << pcl::getFieldsList (*cloud) << ").";
    
    // Create the filtering object
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (radius, radius, radius);
    sor.filter (*cloud_filtered);
    
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
    << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";
    
    pcl::PLYWriter writer;
    pcl::io::savePLYFile(outputPath, *cloud_filtered);
    
    return (0);
}

