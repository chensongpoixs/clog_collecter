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
				if(has_privilege(4011))
				{
					echo '<a href="#" id="addsingle" class="easyui-linkbutton" plain="true" icon="icon-add"><span lang>common_add</span></a>';
				}
				if(has_privilege(4012))
				{
					echo '<a href="#" id="updatesingle" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>common_edit</span></a>';
				}
				if(has_privilege(4013))
				{
					echo '<a href="#" id="delsingle" class="easyui-linkbutton" plain="true" icon="icon-remove"><span lang>common_remove</span></a>';
				}
			?>
			<a href="#" id="update" class="easyui-linkbutton" plain="true" icon="icon-reload"><span lang>serverinfopage_php_4</span></a>
		<!--	<a href="#" id="create_static" class="easyui-linkbutton" plain="true" icon="icon-ok"><span lang>serverinfopage_php_5</span></a> -->
		</div> 
	</div> 
</div> 

<!--style="position:absolute;left:90px;width:200px;" -->
<form id="manager_add" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<p ><span class="lable_name" lang>serverinfopage_php_6</span><input id="id" type="text" style="width:200px;height:22px;"></p>
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_7</span><input id="cur_id" type="text"   style="width:200px;height:22px;"></p>-->
	  <p ><span class="lable_name" lang>serverinfopage_php_8</span><input id="show_id" type="text"   style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>serverinfopage_php_9</span><input id="name" type="text" class="textbox" style="width:200px;height:22px;"></p>	
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_10</span><input id="ipport" class="textbox"  style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>serverinfopage_php_19</span><input id="rate" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>serverinfopage_php_11</span><select id="status"  value="1" style="width:200px;height:22px;"></select></p>	
	<p ><span class="lable_name" lang>serverinfopage_php_12</span><select id="platform"  value="0" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_13</span><select id="new"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_14</span><select id="suggest"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_18</span><select id="is_gm"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_15</span><input id="version" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>common_channel</span><input id="channel" style="width:200px;height:22px;"></p> -->
	<p ><span class="lable_name" lang>serverinfopage_php_16</span><input id="att_url" type="text" style="width:200px;height:22px;"></p>
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_17</span><input id="open_time"></p> -->
</form>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_channel.js"></script>
<script type="text/javascript" src="js/serverslist.js"></script>
</body>
</html>