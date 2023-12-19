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
	<table id="privilege_list"></table>
</div>

<div id="tb">
	<div region="north" border="false" style="border-bottom:1px solid #ddd;height:28px;padding:2px 2px 2px 2px;background:#fafafa;">
	
		<div style="float:left;">
			<input id="gm_menu_searchbox" >.</input>
			<div id="gm_menu_item" style="width:120px">
				<div name="gm_menu_open_id" lang>common_account_id</div>
				<div name="gm_menu_name" lang>player_ban_php_11</div>
				<div name="gm_menu_player_id" lang>player_ban_js_4</div>
			</div>
		</div>

		<div class="datagrid-btn-separator" style="width:10px;"></div>
		<div style="float:left;">
			<?php
					echo '<a href="#" id="updatesingle" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>common_edit</span></a>';
					echo '<a href="#" id="update" class="easyui-linkbutton" plain="true" icon="icon-reload"><span lang>common_refresh</span></a>';
			?>
		</div> 
	</div>
</div> 


<form id="manager_add" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<table border="0">
        <tr>
      		<th lang>common_account_id</th>
      		<th><input id="account_id" class="easyui-numberbox" /></th>
      	</tr>
		<tr>
      		<th lang>gm_privilege_js_0</th>
      		<th><input id="privilege" class="easyui-numberbox" /></th>
      	</tr>
	</table>	
</form>


<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="js/json2.js"></script>
<script type="text/javascript" src="js/gm_privilege.js"></script>
</body>
</html>