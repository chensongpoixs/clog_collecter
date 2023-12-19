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
	<table id="comment_list"></table>
</div>

<div id="tb">
	<div region="north" border="false" style="border-bottom:1px solid #ddd;height:60px;padding:2px 2px 2px 2px;background:#fafafa;">
	
		<div style="float:left;">
			<label > <span lang>common_server_name</span> </label>
			<input id="server_id" />
		</div>
		
		<div class="datagrid-btn-separator" style="width:5px;"></div>
		<div style="float:left;">
			<input id="gm_menu_searchbox" >.</input>
			<div id="gm_menu_item" style="width:120px">
				<div name="gm_menu_open_id" lang>common_account_id</div>
				<div name="gm_menu_name" lang>player_ban_php_11</div>
				<div name="gm_menu_player_id" lang>player_ban_js_4</div>
				<div name="comment_menu_word" lang>comment_php_0</div>
				<div name="comment_menu_hero" lang>comment_php_1</div>
				<div name="comment_menu_like" lang>comment_php_3</div>
				<div name="comment_menu_id" lang>comment_php_4</div>
			</div>
		</div>
		
		<div >
			<?php
					//echo '<a href="#" id="addsingle" class="easyui-linkbutton" plain="true" icon="icon-add"><span lang>common_add</span></a>';
					echo '<a href="#" id="updatesingle" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>common_edit</span></a>';
					echo '<a href="#" id="delsingle" class="easyui-linkbutton" plain="true" icon="icon-remove"><span lang>common_remove</span></a>';
					echo '<a href="#" id="update" class="easyui-linkbutton" plain="true" icon="icon-reload"><span lang>common_refresh</span></a>';
			?>
		</div> 
		
	</div>
</div> 


<form id="comment_update" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<table border="0">
        <tr>
      		<th lang>comment_php_4</th>
      		<th><input id="com_id" class="easyui-numberbox" /></th>
      	</tr>
		<tr>
      		<th lang>comment_php_3</th>
      		<th><input id="com_like" class="easyui-numberbox" /></th>
      	</tr>
	</table>	
</form>

<form id="comment_add" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<table border="0">
        <tr>
      		<th lang>account_ban_js_11</th>
      		<th><input id="add_server_id" class="easyui-numberbox" /></th>
      	</tr>
		<tr>
      		<th lang>player_ban_js_4</th>
      		<th><input id="add_player_id" class="easyui-numberbox" /></th>
      	</tr>
		 <tr>
      		<th lang>comment_php_1</th>
      		<th><input id="add_hero_id" class="easyui-numberbox" /></th>
      	</tr>
		<tr>
      		<th lang>player_ban_js_13</th>
      		<th><input id="add_name" class="easyui-textbox" /></th>
      	</tr>
		 <tr>
      		<th lang>comment_php_0</th>
      		<th><input id="add_word" class="easyui-textbox"/></th>
      	</tr>
		<tr>
      		<th lang>comment_php_3</th>
      		<th><input id="add_like_count" class="easyui-numberbox" /></th>
      	</tr>
	</table>	
</form>

<form id="comment_delete" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<table border="0">
        <tr>
      		<th lang>comment_php_5</th>
      	</tr>
	</table>	
</form>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="js/json2.js"></script>
<script type="text/javascript" src="js/comment_manage.js"></script>
</body>
</html>