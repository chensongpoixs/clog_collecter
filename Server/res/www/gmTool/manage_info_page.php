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
	<table id="serverinfobox"></table>
</div>

<div id="tb">
	<div region="north" border="false" style="border-bottom:1px solid #ddd;height:28px;padding:2px 2px 2px 2px;background:#fafafa;">  
		<div style="float:left;"> 
			<?php 
			if(has_privilege(5001))
			{
				echo '<a href="#" id="addsingle" class="easyui-linkbutton" plain="true" icon="icon-add"><span lang>manager_info_php_0</span></a>';
			}
			?>
			
			<?php 
			if(has_privilege(5002))
			{
				echo '<a href="#" id="updatesingle" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>manager_info_php_1</span></a>';
			}
			?>
			
			<?php 
			if(has_privilege(5003))
			{
				echo '<a href="#" id="delsingle" class="easyui-linkbutton" plain="true" icon="icon-remove"><span lang>manager_info_php_2</span></a>';
			}
			?>
			
			<?php 
			if(has_privilege(5004))
			{
				echo '<a href="#" id="reset_password" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>manager_info_php_3</span></a></a>';
			}
			?>
			
			<a href="#" id="update" class="easyui-linkbutton" plain="true" icon="icon-reload"><span lang>manager_info_php_4</span></a>
			<a href="#" id="mod_password" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>manager_info_php_8</span></a>
		</div> 
	</div> 
</div> 

<!--style="position:absolute;left:90px;width:200px;" -->
<form id="manager_add" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<p ><span class="lable_name" lang>manager_info_php_5</span><input id="account" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>manager_info_php_6</span><input id="password" type="text" class="easyui-textbox" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>manager_info_php_11</span><input id="realname" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>manager_info_php_7</span><input id="privilege"/></p>
</form>

<form id="manager_password" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<p ><span class="lable_name" lang>manager_info_php_6</span><input id="password_src" type="password" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>manager_info_php_9</span><input id="password21" type="password" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>manager_info_php_10</span><input id="password22" type="password" style="width:200px;height:22px;"></p>
</form>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_priv.js"></script>
<script type="text/javascript" src="js/manage_info.js"></script>
</body>
</html>