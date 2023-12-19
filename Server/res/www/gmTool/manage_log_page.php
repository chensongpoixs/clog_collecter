<?php
	require_once('./header.php');
?> 
<!DOCTYPE html>
<html>
<head>
<title> </title>
<meta charset="UTF-8" />
<link rel="stylesheet" type="text/css" href="easyui/themes/default/easyui.css" />
<link rel="stylesheet" type="text/css" href="easyui/themes/icon.css" />
<link rel="stylesheet" type="text/css" href="css/serverinfor.css" >

</head>
<body class="easyui-layout">

<div data-options="region:'center'" style="width:100%;height:100%">
	<table id="log_table"></table>
</div>

<div id="tb">
	<div region="north" border="false" style="border-bottom:1px solid #ddd;height:28px;padding:2px 2px 2px 2px;background:#fafafa;">
		<div style="float:left;">
			<input id="sss" /input>
			<div id="mmm" style="width:120px"> 
			<div name="account" lang>manager_log_php_0</div> 
			<div name="type" lang>manager_log_php_1</div> 
			</div> 
		</div>
    </div>  
</div> 


<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="js/manage_log.js"></script>
<script type="text/javascript" src="js/json2.js"></script>
</body>
</html>