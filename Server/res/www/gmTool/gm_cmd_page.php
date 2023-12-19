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
	<table border="0">
		<tr>
			<th lang>gm_cmd_php_0</th>
			<th><input id="gm_cmd_cmd" /></th>
		</tr>
		<!-- <tr>
			<th lang>common_server_id</th>
			<th><input id="gm_cmd_server_id" /></th>
		</tr>-->
		<tr>
			<th lang>gm_cmd_php_1</th>
			<th><input id="gm_cmd_desc" type="text" readonly="true" style="width:600px;"/></th>
		</tr>
		<tr>
			<th lang>gm_cmd_php_2</th>
			<th><input id="gm_cmd_demo" type="text" readonly="true" style="width:600px;"/></th>
		</tr>
		<tr>
			<th lang>gm_cmd_php_3</th>
			<th><input id="gm_cmd_para" type="text" style="width:600px"/></th>
		</tr>		
		<tr>
			<th lang>gm_cmd_php_4</th>
			<th><input id="gm_cmd_result" type="text" readonly="true" style="width:600px;"/></th>
		</tr>
		<tr>
			<th ><a id="gm_cmd_do" href="#" class="easyui-linkbutton"><span lang>gm_cmd_php_5</span></a></th>
		</tr>
	</table>
</div>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_cmd.js"></script>
<script type="text/javascript" src="js/gm_cmd.js"></script>
</body>
</html>