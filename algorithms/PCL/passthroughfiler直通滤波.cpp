
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>
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
    string limit1 = argv[4];
    string limit2 = argv[5];
    string fieldName = argv[3];
    double l1 = stringToNum(limit1);
    double l2 = stringToNum(limit2);
    
    
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    
    // Fill in the cloud data
    pcl::PLYReader reader;
    // Replace the path below with the path where you saved your file
    reader.read (inputPath, *cloud); // Remember to download the file first!
    
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
    << " data points (" << pcl::getFieldsList (*cloud) << ").";
    
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName (fieldName);
    pass.setFilterLimits (l1, l2);
    //    pass.setFilterFieldName ("z");
    //    pass.setFilterLimits (0.0, 1.0);
    //pass.setFilterLimitsNegative (true);
    pass.filter (*cloud_filtered);
    
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
    << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";
    
    pcl::PLYWriter writer;
    pcl::io::savePLYFile(outputPath, *cloud_filtered);
    
    return (0);
}

