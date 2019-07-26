# Point2Mesh-website
Presentation Video(Chinese)<br>
https://www.bilibili.com/video/av30430488
## Front Pages
![image1](https://github.com/lmy1108/Point2Mesh-website/tree/master/images/mesh2.PNG
![image2](https://github.com/lmy1108/Point2Mesh-website/tree/master/images/mesh3.PNG

![image3](https://github.com/lmy1108/Point2Mesh-website/tree/master/images/mesh4.PNG
![image4](https://github.com/lmy1108/Point2Mesh-website/tree/master/images/test5.gif

## Purpose of design
In the research related to computer graphics, we usually need transform point cloud to meshes, the quality of meshes generated determines the outcome out further modeling, #D printing, etc. However, we usually need to adjust the patameters of the code(e.g. using libraries like PCL) and compile them over and over again. constructing a environment for different libraries is also a burden. Visualization also requires some extra work to be done. <br>  The Point2Mesh project deployed two most useful libraries: PCL and JHU open souorced library, the website can transform the point cloud into meshes using the parameters given by the user. Furthermore, it uses WebGL to visualize the result of the transformation. <br>  With this website, we can use only one server to process all the desired meshes and see the result right away. Other functions like filtering/mesh triming were also built in it.

### FrontEnd Visualization
Front End uses javascript to make mesh results visualize according to the given point cloud and parameters given.

### Service API
Use the java class to call the completed algorithm program, and pass the parameters and files sent from the front end to the generated executable program for related processing, and generate a grid file or a point cloud file for the program that needs to display the grid through webGL. Displayed in the front-end interface, and the result file is downloaded via java.
### Algorithms included:
#### 1) Greedy projection triangulation
First, the directed point cloud is projected into a local coordinate plane, and then the plane is triangulated in the coordinate plane, and a triangular mesh surface model is obtained according to the topological relationship of the three points in the plane. <br>
The main parameters are: search radius, multiplier of nearest neighbor distance, maximum number of nearest neighbors, maximum plane angle (π), minimum angle (π) of each triangle, maximum angle (π) of each triangle, normal vector Is it consistent?
The specific interface is as shown

 
#### 2).Poisson surface reconstruction
By expressing the surface reconstruction problem as Poisson problem, the Poisson equation is solved to obtain the implicit equation represented by the surface information described by the point cloud model. By extracting the isosurface from the equation, the surface model with geometric entity information is obtained. . <br>
The main parameters are: the parameter degree range [1, 5], the maximum depth of the tree, the depth of the algorithm used to extract the ISO isosurface, the minimum number of sample points falling into an octree node, and used for reconstruction. The ratio of the cube diameter to the sample boundary cube diameter, the depth of the Gauss-Seidel iterative method, whether the size of the normal vector is used as the information, and whether the center of gravity of the polygon is added.


#### 3)Marching Cube reconstruction
The moving cube method first stores eight adjacent data in the data field at eight vertices of a tetrahedral voxel. By calculating the intersection of the twelve ribs and the isosurfaces in the voxel, and constructing the triangular patches in the voxels, all the triangular patches divide the voxels into two regions, the isosurface and the equivalence. Finally, the triangular patches of all the voxels in this data field are connected to form an isosurface. Combine the isosurfaces of all cubes to create a complete 3D surface. <br>
Main parameters: anisotropy level, set square resolution, set percentage of square movement (Percentage-ExtendGrid).


 
#### 4)Jhu improved Poisson surface reconstruction
An improved Poisson surface reconstruction method at John Hopkins University. <br>
The main parameters are: B-spline degree, boundary type, depth, scale, number of samples per node (samplesPerNode), weight of each point (pointweight ), density, and confidence.


#### 5)Jhu-ssd reconstruction
Based on the original graph octree mixed finite element, finite difference efficient implementation of discretization and dual-travel cube isosurface extraction algorithm, a high-quality crack-free adaptive manifold polygon mesh is generated. <br>
The main parameters are: B-spline degree, depth, scale, number of samples per node (samplesPerNode), weight of each point (valueweight), gradient weight (gradientWeight) , biLapWeigh, density, and confidence.





#### 6)Point cloud filtering
straight-through filtering, radius filtering and statistical filtering
#### 7)Voxelized point cloud:
Create a three-dimensional voxel grid from the input point cloud data, and then in each voxel, use the center of gravity of all points in the voxel to approximate the other points in the voxel.

#### 8)Point cloud normalization (adding normalize vector)
For the undefined normal vector in the ply file, increase the normal vector.


#### 9)Triangular mesh optimization
For some generated meshes, this feature detects its thin portion based on parameters and cuts it. <br>
The main parameters are: the threshold of the surface shear.

## Envirnment && Deployment
### Set up PCL environment
http://pointclouds.org/documentation/tutorials/compiling_pcl_windows.php

### Build JHU Open source 
http://www.cs.jhu.edu/~misha/Code/PoissonRecon/Version10.07/


#### Install maven and pack the website
```
mvn clean package -DskipTests
```
