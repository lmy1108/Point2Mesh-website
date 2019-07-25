package com.dhu.controller;

import net.sf.jsqlparser.statement.select.SetOperation;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.multipart.MultipartHttpServletRequest;
import org.springframework.web.multipart.commons.CommonsMultipartFile;
import org.springframework.web.multipart.commons.CommonsMultipartResolver;
import pojo.PointcloudPath;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;


@Controller
public class testController {
    public String cloudPath;
    public String meshPath;
    public String cloudName;
    public String meshName;


    public String getPath(){
        return cloudPath;
    }

    @RequestMapping("/ply")
    public String ply(Model model) {
        model.addAttribute("mesh", meshName);
        return "showPly";
    }
    @RequestMapping("up2")
    public String up2(){return "ajaxUpload";}

    @RequestMapping("up")
    public String fileUp(Model model) {

        return "uploadFile";
    }
    @RequestMapping("/triangle")
    public String triangle() {
        return "pcl-triangle";
    }

    @RequestMapping("/poisson")
    public String pcl_poisson(){
        return "pcl-poisson";
    }

    @RequestMapping("/MacCube")
    public String macCube(){
        return "pcl-Cube";
    }
    @RequestMapping("/addNormal")
    public String addNormal(){
        return "pcl-addNormals";
    }
    @RequestMapping("/voxelGrid")
        public String voxelGrid() {
            return "pcl-voxelGrid";
        }
    @RequestMapping("/passingThrough")
    public String passing() {
        return "pcl-passingFilter";
    }
    @RequestMapping("/radius")
    public String radius() {
        return "pcl-radiusFilter";
    }
    @RequestMapping("/statistic")
    public String statistic() {
        return "pcl-statisticFilter";
    }

        @RequestMapping("/jhuSSD")
        public String jhuSSD(){
            return "jhu-SSD";
        }

    @RequestMapping("/trim")
    public String trim() {
        return "surfaceTrimmer";
    }

    @RequestMapping("/addNormalFunc")
    public String addNormalFunc(Model model){
        List<String> args2 = new ArrayList<>();
        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/addNormals");
        args2.add(cloudPath);
        args2.add(cloudPath);
        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

//        try {
//            Process proc =Runtime.getRuntime().exec(args);
//        } catch (IOException e) {
//
//            e.printStackTrace();
//        }
        model.addAttribute("cloud", cloudName);

        return "pcl-addNormal";
    }
    @RequestMapping("doVoxelGrid")
    public String doVoxelGrid(Model model, Double length){
        List<String> args2 = new ArrayList<>();
        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/voxelGridFilter");
        args2.add(cloudPath);
        args2.add(cloudPath+"_f.ply");
        args2.add(length.toString());

        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("cloud", cloudName+"_f.ply");
        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + cloudName +"_f.ply");

        while(!file.exists()){}
        return voxelGrid();
    }

    @RequestMapping("doPassingThrough")
    public String doPassingThrough(Model model, String fieldName, Double high, Double low){
        List<String> args2 = new ArrayList<>();
        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/passingThrough");
        args2.add(cloudPath);
        args2.add(cloudPath);
        args2.add(fieldName);
        args2.add(high.toString());
        args2.add(low.toString());


        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("cloud", cloudName);

        return passing();
    }
    @RequestMapping("doRadiusFilter")
    public String doradiusFilter(Model model, Double radius, Double neighbor){
        List<String> args2 = new ArrayList<>();
        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/radiusFilter");
        args2.add(cloudPath);
        args2.add(cloudPath);
        args2.add(radius.toString());
        args2.add(neighbor.toString());

        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("cloud", cloudName);

        return radius();
    }

    @RequestMapping("doStatisticFilter")
    public String doStatisticFilter(Model model, Double kmeans, Double thres){
        List<String> args2 = new ArrayList<>();
        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/statisticFilter");
        args2.add(cloudPath);
        args2.add(cloudPath);
        args2.add(kmeans.toString());
        args2.add(thres.toString());

        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("cloud", cloudName);

        return statistic();
    }

    @RequestMapping("upload")
    public String fileUpload(@RequestParam("file") MultipartFile file, HttpServletRequest request) {
        // 判断文件是否为空
        if (!file.isEmpty()) {
            try {
                // 文件保存路径
                String realPath = request.getSession().getServletContext().getRealPath("/");
                String filePath = realPath.substring(0, realPath.indexOf("PointCloud")) + "PointCloud/target/PointCloud";

                ///Users/lmy/IdeaProjects/PointCloud/target/PointCloud
                ///Users/lmy/IdeaProjects/PointCloud/src/main/webapp

                File newFile = new File(filePath, file.getOriginalFilename());

                if (!newFile.getParentFile().exists()) {
                    newFile.getParentFile().mkdirs();
                }
//                String filePath = request.getSession().getServletContext() + file.getOriginalFilename();
                // 转存文件
                file.transferTo(new File(filePath + File.separatorChar + file.getOriginalFilename()));
                System.out.println(filePath);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        // 重定向
        return "success";
    }




    @RequestMapping("fileupload")
    public String fileupload(HttpServletRequest request, HttpServletResponse response, String loginName, Model model) throws Exception {
        //获取服务器中保存文件的路径

        String path = request.getSession().getServletContext().getRealPath("") + "upload/";
        System.out.println(path);
        model.addAttribute("path",path);
        //获取解析器
        CommonsMultipartResolver resolver = new CommonsMultipartResolver(request.getSession().getServletContext());
        //判断是否是文件
        if (resolver.isMultipart(request)) {
            //进行转换
            MultipartHttpServletRequest multiRequest = (MultipartHttpServletRequest) (request);
            //获取所有文件名称
            Iterator<String> it = multiRequest.getFileNames();
            while (it.hasNext()) {
                //根据文件名称取文件

                MultipartFile file = multiRequest.getFile(it.next());
                String fileName = file.getOriginalFilename();
                cloudName = fileName;
                meshName = cloudName + "_mesh.ply";
                String localPath = path + fileName;
                //创建一个新的文件对象，创建时需要一个参数，参数是文件所需要保存的位置
                File newFile = new File(localPath);
                PointcloudPath pointcloudPath = new PointcloudPath();
                cloudPath = localPath;
                meshPath = cloudPath + "_mesh.ply";
                //上传的文件写入到指定的文件中
                file.transferTo(newFile);
            }

        }
            return "success";
    }



    @RequestMapping("/getParam-1")
    public String getParam(Model model ,Double radius, Double multiple, Double number, Double maxAngleFlat, Double minAngle, Double maxAngle, String coherence) {
//        System.out.println(radius);
//        String argv = radius.toString() + " " + multiple.toString() + " " + number.toString() + " " + maxAngleFlat.toString() + " " + minAngle.toString() + " " + maxAngle.toString() + " " + coherence;
//        System.out.println(argv);
//        String[] args = {"aa","bb","cc"};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/PCLtriangle");
        args2.add(cloudPath);
        args2.add(meshPath);
        args2.add(radius.toString());
        args2.add(multiple.toString());
        args2.add(number.toString());
        args2.add(maxAngleFlat.toString());
        args2.add(minAngle.toString());
        args2.add(maxAngle.toString());
        if(coherence=="ON"){
            args2.add("ON");
    }else{
        args2.add("off");
    }
    String[] args = new String[args2.size()];

        args2.toArray(args);

        for (String t : args) {
        System.out.print(t+ " ");
    }
        try {
        Runtime.getRuntime().exec(args);
    } catch (IOException e) {

        e.printStackTrace();
    }
        model.addAttribute("mesh", meshName);
    File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
    file.delete();
    while(!file.exists()){}
        return ("pcl-triangle");

}


    @RequestMapping("/getParam-2")
    public String getParamPoisson(Model model, Double degree, Double depth, Double isoDivide, Double samples, Double scale, Double solverDivide, String confidence, String manifold) {


//        String argv = degree.toString() + " " + depth.toString() + " " + isoDivide.toString() + " " + samples.toString() + " " + scale.toString() + " " + solverDivide.toString() + " " + confidence + " " + manifold;
//
//        System.out.println(argv);
//
//        String[] args = {"exedest","dest1","dest2",degree.toString(),depth.toString(),isoDivide.toString(),samples.toString(),scale.toString(),solverDivide.toString(),confidence,manifold};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/PCLpoisson");
        args2.add(cloudPath);
        args2.add(meshPath);
        args2.add(degree.toString());
        args2.add(depth.toString());
        args2.add(isoDivide.toString());
        args2.add(samples.toString());
        args2.add(scale.toString());
        args2.add(solverDivide.toString());
        if(confidence=="ON"){
            args2.add("ON");
        }else{
            args2.add("off");
        }
        if(manifold=="ON"){
            args2.add("ON");
        }else{
            args2.add("off");
        }

        String[] args = new String[args2.size()];

        args2.toArray(args);
        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("mesh", meshName);
        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
        file.delete();

        while(!file.exists()){}
        return ("pcl-poisson");

    }

    @RequestMapping("/getParam-3")
    public String getParamMC(Model model, Double isoLevel, Double gridResolution, Double PercentageExtendGrid) {


//        String argv = isoLevel.toString() + " " + gridResolution.toString() + " " + PercentageExtendGrid.toString();
//        System.out.println(argv);
//
//        String[] args = {"exedest","dest1","dest2",isoLevel.toString(),gridResolution.toString(), PercentageExtendGrid.toString()};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/PCLmarchingCube");
        args2.add(cloudPath);
        args2.add(meshPath);
        args2.add(isoLevel.toString());
        args2.add(gridResolution.toString());
        args2.add(PercentageExtendGrid.toString());


        String[] args = new String[args2.size()];

        args2.toArray(args);
        for(String S : args){
            System.out.print(S+" ");
        }
        System.out.println(args);
        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }
        model.addAttribute("mesh", meshName);
        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
        file.delete();

        while(!file.exists()){}
        return ("pcl-Cube");

    }




    @RequestMapping("/jhupoisson")
    public String jhuPoisson(){
        return "jhu-poisson";
    }

    @RequestMapping("/getParam-j1")
    public String getParamjhuPoisson(Model model, Double degree, Double type, Double depth, Double scale, Double samplesPerNode,Double pointWeight,String density, String confidence ) {


//        String[] args = {"exedest",cloudPath,meshPath,degree.toString(),type.toString(), depth.toString(), scale.toString(), samplesPerNode.toString(), pointWeight.toString(),density,confidence};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/PoissonRecon");
        args2.add("--in");
        args2.add(cloudPath);
        args2.add("--out");
        args2.add(meshPath);

        if(degree != 2){
            args2.add("--degree");
            args2.add(degree.toString());
        }

        if(type != 3){
            args2.add("--bType");
            args2.add(type.toString());

        }
        if(depth != 8){
            args2.add("--depth");
            args2.add(depth.toString());

        }
        if(scale != 1.1){
            args2.add("--scale");
            args2.add(scale.toString());

        }
        if(samplesPerNode != 1.0){
            args2.add("--samplesPerNode");
            args2.add(samplesPerNode.toString());
        }
        if(pointWeight!=4.0){
            args2.add("--pointWeight");
            args2.add(pointWeight.toString());

        }
        if(density!=null){
            args2.add("--density");
        }
        if(confidence!=null){
            args2.add("--confidence");
        }

        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        System.out.println(args);
        try {
            Process proc =Runtime.getRuntime().exec(args);

        } catch (IOException e) {

            e.printStackTrace();
        }
        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
        file.delete();

        while(!file.exists()){}



        model.addAttribute("mesh", meshName);

        return ("jhu-poisson");

    }

    @RequestMapping("/getParam-j2")
    public String getParamjhuSSD(Model model, Double degree,  Double depth, Double scale, Double samplesPerNode,Double valueWeight,Double gradientWeight, Double biLap , String density, String confidence ) {


//        String[] args = {"exedest",cloudPath,meshPath,degree.toString(),type.toString(), depth.toString(), scale.toString(), samplesPerNode.toString(), pointWeight.toString(),density,confidence};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/SSDRecon");
        args2.add("--in");
        args2.add(cloudPath);
        args2.add("--out");
        args2.add(meshPath);

        if(degree != 2){
            args2.add("--degree");
            args2.add(degree.toString());
        }


        if(depth != 8){
            args2.add("--depth");
            args2.add(depth.toString());

        }
        if(scale != 1.1){
            args2.add("--scale");
            args2.add(scale.toString());

        }
        if(samplesPerNode != 1.0){
            args2.add("--samplesPerNode");
            args2.add(samplesPerNode.toString());
        }
        if(valueWeight!=1.0){
            args2.add("--valueWeight");
            args2.add(valueWeight.toString());

        }
        if(gradientWeight!=1.0){
            args2.add("--gradientWeight");
            args2.add(gradientWeight.toString());

        }
        if(biLap!=1.0){
            args2.add("--biLapWeight");
            args2.add(biLap.toString());

        }
        if(density!=null){
            args2.add("--density");
        }
        if(confidence!=null){
            args2.add("--confidence");
        }

        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        System.out.println(args);
        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }

        model.addAttribute("mesh", meshName);
        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
        file.delete();

        while(!file.exists()){}

        return ("jhu-SSD");

    }

    @RequestMapping("/trimmer")
    public String surfaceTrim (Model model, Double param) {


//        String[] args = {"exedest",cloudPath,meshPath,degree.toString(),type.toString(), depth.toString(), scale.toString(), samplesPerNode.toString(), pointWeight.toString(),density,confidence};
        List<String> args2 = new ArrayList<>();

        args2.add("/Users/lmy/Downloads/PoissonRecon/PoissonRecon/Bin/Linux/SurfaceTrimmer");
        args2.add("--in");
        args2.add(cloudPath);
        args2.add("--out");
        args2.add(meshPath);

        args2.add("--trim");
        args2.add(param.toString());


        String[] args = new String[args2.size()];

        args2.toArray(args);
        for (String t : args) {
            System.out.println(t+ " ");
        }

        System.out.println(args);
        try {
            Process proc =Runtime.getRuntime().exec(args);
        } catch (IOException e) {

            e.printStackTrace();
        }

        model.addAttribute("mesh", meshName);

        File file = new File("/Users/lmy/IdeaProjects/PointCloud/target/PointCloud/upload/" + meshName);
        file.delete();
        while(!file.exists()){}

        return trim();

    }






}


