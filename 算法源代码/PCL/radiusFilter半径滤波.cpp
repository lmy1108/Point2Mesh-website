
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
    string RadiusSearch = argv[3];
    string MinNeighborsInRadius = argv[4];
    double radiusSearch = stringToNum(RadiusSearch);
    double minNeighborsInRadius = stringToNum(MinNeighborsInRadius);
    
    
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGBA>);
    
    // Fill in the cloud data
    pcl::PLYReader reader;
    // Replace the path below with the path where you saved your file
    reader.read (inputPath, *cloud); // Remember to download the file first!
    
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
    << " data points (" << pcl::getFieldsList (*cloud) << ").";
    
    // build the filter
    pcl::RadiusOutlierRemoval<pcl::PointXYZRGBA> outrem;
    outrem.setInputCloud(cloud);
    outrem.setRadiusSearch(radiusSearch);
    outrem.setMinNeighborsInRadius (minNeighborsInRadius);
    //    outrem.setRadiusSearch(0.8);
    //    outrem.setMinNeighborsInRadius (2);
    // apply filter
    outrem.filter (*cloud_filtered);
    
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
    << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";
    
    pcl::PLYWriter writer;
    pcl::io::savePLYFile(outputPath, *cloud_filtered);
    
    return (0);
}

