
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
  <title>点云重建ui</title>
  <meta name="renderer" content="webkit">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
  <meta name="apple-mobile-web-app-status-bar-style" content="black">
  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="format-detection" content="telephone=no">

  <link rel="stylesheet" href="${pageContext.request.contextPath}/css/layui.css"  media="all">
        <script src="${pageContext.request.contextPath}/js/jquery-1.11.1.min.js" charset="UTF-8"> </script>

    <script src="${pageContext.request.contextPath}/ajaxUpload.js" charset="UTF-8"> </script>
  <script src="${pageContext.request.contextPath}/layui.js" charset="utf-8"></script>

</head>
<body class="layui-layout-body">
<div class="layui-layout layui-layout-admin">
  <div class="layui-header">
    <div class="layui-logo">点云重建ui</div>
    <!-- 头部区域（可配合layui已有的水平导航） -->
    <ul class="layui-nav layui-layout-left">
      <li class="layui-nav-item"><a href="">控制台</a></li>
      <li class="layui-nav-item"><a href="">管理</a></li>
      <li class="layui-nav-item"><a href="">用户</a></li>
      <li class="layui-nav-item">
        <a href="javascript:;">其它系统</a>
        <dl class="layui-nav-child">
          <dd><a href="">邮件管理</a></dd>
          <dd><a href="">消息管理</a></dd>
          <dd><a href="">授权管理</a></dd>
        </dl>
      </li>
    </ul>
    <ul class="layui-nav layui-layout-right">
      <li class="layui-nav-item">
        <a href="javascript:;">
          <img src="http://t.cn/RCzsdCq" class="layui-nav-img">
          DHU
        </a>
        <dl class="layui-nav-child">
          <dd><a href="">基本资料</a></dd>
          <dd><a href="">安全设置</a></dd>
        </dl>
      </li>

    </ul>
  </div>

  <div class="layui-side layui-bg-cyan">
    <div class="layui-side-scroll">
      <!-- 左侧导航区域（可配合layui已有的垂直导航） -->
      <ul class="layui-nav layui-nav-tree layui-bg-cyan"  lay-filter="test">
        <li class="layui-nav-item layui-nav-itemed layui-bg-cyan">
          <a class="" href="javascript:;">PCL重建</a>
          <dl class="layui-nav-child">
            <dd><a href="${pageContext.request.contextPath}/triangle">贪婪投影三角化</a></dd>
            <dd><a href="${pageContext.request.contextPath}/poisson">泊松表面重建</a></dd>
            <dd><a href="${pageContext.request.contextPath}/MacCube">Marching Cube重建</a></dd>
          </dl>
        </li>
        <li class="layui-nav-item layui-nav-itemed">
          <a href="javascript:;">jhu开源重建算法</a>
          <dl class="layui-nav-child">
            <dd><a href="${pageContext.request.contextPath}/jhupoisson">改进泊松表面重建</a></dd>
            <dd><a href="${pageContext.request.contextPath}/jhuSSD">SDD重建</a></dd>
          </dl>
        </li>
        <li class="layui-nav-item layui-nav-itemed">
          <a href="javascript:;">点云滤波</a>
          <dl class="layui-nav-child">
            <dd><a href="${pageContext.request.contextPath}/passingThrough">直通滤波器</a></dd>
            <dd><a href="${pageContext.request.contextPath}/radius">半径滤波器</a></dd>
            <dd><a href="${pageContext.request.contextPath}/statistic">统计滤波器</a></dd>

          </dl>
        </li>

        <li class="layui-nav-item"><a href="${pageContext.request.contextPath}/addNormal">点云增加法向量</a></li>
        <li class="layui-nav-item"><a href="${pageContext.request.contextPath}/voxelGrid">体素化点云</a></li>
        <li class="layui-nav-item"><a href="${pageContext.request.contextPath}/trim">三维网格优化</a></li>
      </ul>
    </div>
  </div>

  <div class="layui-body">
    <!-- 内容主体区域 -->
    <blockquote class="layui-elem-quote layui-text">
      请注意,必须为ply格式，且参数不能为空!
    </blockquote>

    <fieldset class="layui-elem-field layui-field-title" style="margin-top: 20px;">
      <legend>贪婪投影三角化</legend>
    </fieldset>

    <%--<form class ="layui-form" id="myform"  method="post" >--%>
      <%--< class="layui-form-item">--%>


        <%--<label class="layui-form-label">输入点云</label>--%>
          <%--<input type="file" name="record" /><br/><br/>--%>
      <%--<input type="button" class="layui-btn  value="提交" />--%>
        <%--&lt;%&ndash;<button type="button" class="layui-btn" id="test3" onclick="doUpload()">上传文件</button>&ndash;%&gt;--%>

      <%--</div>--%>

    <%--</form>--%>

    <%--<form class="layui-form" action="">--%>
      <%--<div class="layui-form-item">--%>
        <%--<label class="layui-form-label">输入点云</label>--%>
        <%--<div class="layui-input-block">--%>
          <%--&lt;%&ndash;<button type="button" class="layui-btn" id="test3"><i class="layui-icon"></i>上传文件</button>&ndash;%&gt;--%>
        <%--</div>--%>
      <%--</div>--%>
      <form id="myform"  method="post" >
          <br>
          &nbsp;输入点云文件：<input type="file" name="record" />
          <input class="layui-btn" type="button" onclick="doUpload()" value="提交" />
          <br/><br/>
          <br/>

      </form>

      <form class="layui-form" action="getParam-1">
      <div class="layui-form-item">
        <div class="layui-inline">
          <label class="layui-form-label">搜索半径</label>
          <div class="layui-input-inline">
            <input value = 0.1 style="width: 50px" type="tel" name="radius"  autocomplete="off" class="layui-input">
          </div>
        </div>
        <div class="layui-inline">
          <label class="layui-form-label">最近邻距离的乘子</label>
          <div class="layui-input-inline">
            <input value = 2.5 style="width: 50px" type="tel" name="multiple"  autocomplete="off" class="layui-input">
          </div>
        </div>
      </div>
      <div class="layui-form-item">
        <div class="layui-inline">
          <label class="layui-form-label">最近邻点的最大数量</label>
          <div class="layui-input-inline">
            <input value = 300 style="width: 50px" type="tel" name="number"  autocomplete="off" class="layui-input">
          </div>
        </div>
        <div class="layui-inline">
          <label class="layui-form-label">最大平面角(π)</label>
          <div class="layui-input-inline">
            <input value = 0.5 style="width: 50px" type="tel" name="maxAngleFlat"  autocomplete="off" class="layui-input">
          </div>
        </div>
      </div>
      <div class="layui-form-item">
        <div class="layui-inline">
          <label class="layui-form-label">每个三角的最小角度(π)</label>
          <div class="layui-input-inline">
            <input value = 0.03 style="width: 50px" type="tel" name="minAngle"  autocomplete="off" class="layui-input">
          </div>
        </div>
        <div class="layui-inline">
          <label class="layui-form-label">每个三角的最大角度(π)</label>
          <div class="layui-input-inline">
            <input value = 0.84 style="width: 50px" type="tel" name="maxAngle"  autocomplete="off" class="layui-input">
          </div>
        </div>
      </div>

      <div class="layui-form-item">
        <label class="layui-form-label">法向量一致</label>
        <div class="layui-input-block">
          <input type="checkbox" name="coherence" lay-skin="switch" lay-text="ON|OFF">
        </div>
      </div>




          <div class="layui-form-item">
              <div class="layui-input-block">
                  <button class="layui-btn"  lay-filter="demo1">立即运行</button>
                  <button type="reset" class="layui-btn layui-btn-primary">重置</button>
              </div>
          </div>
    </form>

    <div style="width: 216px; margin: 60px;">
    <!-- layui 2.2.5 新增 -->
    <a href="ply" class="layui-btn layui-btn-fluid" onclick="">显示网格</a>
  </div>
    <a href="${pageContext.request.contextPath}/upload/${mesh}" download="${mesh}" class="layui-btn layui-btn-fluid" onclick="">下载生成的网格</a>

    <div class="layui-row">
          <div class="layui-col-xs12 layui-col-md8">
              <div class="grid-demo grid-demo-bg1">




              </div>
          </div>
      </div>

    <script src="${pageContext.request.contextPath}/layui.js" charset="utf-8"></script>
    <!-- 注意：如果你直接复制所有代码到本地，上述js路径需要改成你本地的 -->
    <script>
        layui.use(['form', 'layedit', 'laydate'], function(){
            var form = layui.form
                ,layer = layui.layer
                ,layedit = layui.layedit
                ,laydate = layui.laydate;

            //日期
            laydate.render({
                elem: '#date'
            });
            laydate.render({
                elem: '#date1'
            });

            //创建一个编辑器
            var editIndex = layedit.build('LAY_demo_editor');

            //自定义验证规则
            form.verify({
                title: function(value){
                    if(value.length < 5){
                        return '标题至少得5个字符啊';
                    }
                }
                ,pass: [/(.+){6,12}$/, '密码必须6到12位']
                ,content: function(value){
                    layedit.sync(editIndex);
                }
            });

            //监听指定开关
            form.on('switch(switchTest)', function(data){
                layer.msg('开关checked：'+ (this.checked ? 'true' : 'false'), {
                    offset: '6px'
                });
                layer.tips('温馨提示：请注意开关状态的文字可以随意定义，而不仅仅是ON|OFF', data.othis)
            });

            //监听提交
            form.on('submit(demo1)', function(data){
                layer.alert(JSON.stringify(data.field), {
                    title: '最终的提交信息'
                })
                return false;
            });

            //表单初始赋值
            form.val('example', {
                "username": "DHU" // "name": "value"
                ,"password": "123456"
                ,"interest": 1
                ,"like[write]": true //复选框选中状态
                ,"close": true //开关状态
                ,"sex": "女"
                ,"desc": "我爱 layui"
            })


        });
    </script>

  </div>

  <div class="layui-footer">
    <!-- 底部固定区域 -->
    点云重建 2018 @ Donghua University
  </div>
</div>

</body>
</html>
