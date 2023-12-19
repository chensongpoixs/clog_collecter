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
	<table id="loginfobox"></table>
</div>



<!--style="position:absolute;left:90px;width:200px;" -->
<form id="manager_add" style="margin:0;padding:5px 0 0 25px;color:#333;" >
	<p ><span class="lable_name" lang>clientlogsearch_php_0</span><input id="id" type="text" style="width:200px;height:22px;"></p>
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_7</span><input id="cur_id" type="text"   style="width:200px;height:22px;"></p>-->
	  <p ><span class="lable_name" lang>clientlogsearch_php_1</span><input id="client_type" type="text"   style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>clientlogsearch_php_2</span><input id="address" type="text" class="textbox" style="width:200px;height:22px;"></p>	
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_10</span><input id="ipport" class="textbox"  style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>serverinfopage_php_19</span><input id="rate" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>serverinfopage_php_11</span><select id="status"  value="1" style="width:200px;height:22px;"></select></p>	
	<p ><span class="lable_name" lang>serverinfopage_php_12</span><select id="platform"  value="0" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_13</span><select id="new"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_14</span><select id="suggest"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_18</span><select id="is_gm"  value="1" style="width:200px;height:22px;"></select></p>
	<p ><span class="lable_name" lang>serverinfopage_php_15</span><input id="version" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>common_channel</span><input id="channel" style="width:200px;height:22px;"></p> -->
	<p ><span class="lable_name" lang>clientlogsearch_php_3</span><input id="timestamp" type="text" style="width:200px;height:22px;"></p>
	<p ><span class="lable_name" lang>clientlogsearch_php_4</span><input id="log_file_url" type="text"   style="width:200px;height:22px;"></p>
	<!-- <p ><span class="lable_name" lang>serverinfopage_php_17</span><input id="open_time"></p> -->
</form>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_channel.js"></script>
<script type="text/javascript" src="js/client_log_search.js"></script>
</body>
</html>