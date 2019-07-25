#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include<pcl/PCLPointCloud2.h>
#include<iostream>
#include<string>

using namespace pcl;
using namespace pcl::io;
using namespace std;

int PCDtoPLYconvertor(string & input_filename ,string& output_filename)
{
    pcl::PCLPointCloud2 cloud;
    if (loadPCDFile(input_filename , cloud) < 0)
    {
        cout << "Error: cannot load the PCD file!!!"<< endl;
        return -1;
    }
    PLYWriter writer;
    writer.write(output_filename, cloud, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(),true,true);
    return 0;
    
}

int main()
{
    string input_filename = "pcd/table_scene_lms400.pcd";
    string output_filename = "ply/table_scene_lms400.ply";
    PCDtoPLYconvertor(input_filename , output_filename);
    return 0;
}

