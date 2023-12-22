<?php
	require_once('./header.php');
	if(!has_login())
	{
		header('location:index.php');
		exit();
	}
?>
<!DOCTYPE html>
<html>
<head>
<title lang>admin_php_0</title>
<meta charset="UTF-8" />
<link rel="stylesheet" type="text/css" href="easyui/themes/default/easyui.css" />
<link rel="stylesheet" type="text/css" href="easyui/themes/icon.css" />
<!--link rel="stylesheet" type="text/css" href="css/admin.css" -->
</head>
<body class="easyui-layout">

<div data-options="region:'north',title:'header',split:true,noheader:true" style="height:5px;">
<!--
	<span style="display:-moz-inline-box; display:inline-block; width:200px;"> 
			<div class="logo" lang>admin_php_0</div>
			<div class="logout"><span lang>admin_php_1</span>，<?php echo $_SESSION['admin']?> | <a href="logout.php" lang>admin_php_2</a></div>
	</span>
<span  style="padding:0px 0px 0px 100px; display:-moz-inline-box; display:inline-block; "> 
<font color="red"><h2><?php echo $name."&nbsp;&nbsp;&nbsp;&nbsp;"; echo "global:".$global_db_config["host"]."&nbsp;&nbsp;&nbsp;&nbsp;"; echo "login:".$login_db_config["host"];?></h2></font>
</span>
<<span style="line-height:50px; float:right; display:-moz-inline-box; display:inline-block; background:#FFFFFF">
	<input id="lang_select" style="width:100px;"/input>
</span>
-->
</div>   

<div data-options="region:'south',title:'footer',split:true,noheader:true" style="height:35px;line-height:30px;text-align:center;">
	&copy;<span lang>admin_php_3</span>
</div>  
  
<div data-options="region:'west',title:'导航',split:true,iconCls:'icon-world'" style="width:200px;padding:10px;">
<div class="easyui-accordion" data-options="fit:true,border:false,animate:true,plain:true">
	
	<!--<li id="five"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_8</span></a></li>
	<li id="six"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_9</span></a></li>
	<li id="senven"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_10</span></a></li>
	<li id="eight"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_11</span></a></li>-->    
	<!--<li id="ten"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_13</span></a></li>-->
	<?php 
	 
		if(has_priv_prefix(4))
		{
			echo '<div title="操作管理">';
			 
			if(has_priv_prefix(401))
			{
				echo '<li id="server_info"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_4</span></a></li>';
			}
			// if(has_priv_prefix(402))
			//{
			//	echo '<li id="client_log_search"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_5</span></a></li>';
			//}
			 if(has_priv_prefix(403))
			{
				echo '<li id="log_search"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_5</span></a></li>';
			}
			if(has_priv_prefix(407))
			{
				echo '<li id="gm_cmd"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_25</span></a></li>';
			} 
		   echo '</div>';
		}
	?>
	<div title="后台管理" selected >
		<li id="manage_info"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_15</span></a></li>
			<?php 
			if(has_privilege(501))
			{
				echo '<li id="manage_log"><a class="easyui-linkbutton" style="width:120px;padding=20px"><span lang>admin_php_16</span></a></li>';
			}
			?>
		<li id="logout"><a class="easyui-linkbutton" style="width:120px;padding=20px" href="logout.php"><span lang>admin_php_2</span></a></li>
	</div>
	</div>
</div> 
  
<div data-options="region:'center'" >
	<div id="tabs" style="fit:true;">
		<div title="起始页" iconCls="icon-house" style="padding:0 0;display:block;">
			<span lang>admin_php_14</span>
		</div>
	</div>
</div> 

<div data-options="region:'east',collapsed:true,title:'帮助',split:true,iconCls:'icon-world'"  style="width:400px;padding:10px;">
	<div id="aa" class="easyui-accordion" style="height:700px;fit:true;">
		   		
	</div>  
</div> 


<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="js/admin.js"></script>
</body>
</html>