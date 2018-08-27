<%--
  Created by IntelliJ IDEA.
  User: lmy
  Date: 2018/6/1
  Time: 下午1:24
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
    <script src="${pageContext.request.contextPath}/js/jquery-1.11.1.min.js" charset="UTF-8"> </script>

    <script src="${pageContext.request.contextPath}/ajaxUpload.js" charset="UTF-8"> </script>
</head>
<body>
<form id="myform"  method="post" >
    登录名<input type="text" name="loginName" />
    <br>
    上传录音<input type="file" name="record" />
    <input type="button" onclick="doUpload()" value="提交" />
</form>
</body>
</html>
