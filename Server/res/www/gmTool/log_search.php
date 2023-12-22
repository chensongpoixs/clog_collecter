 
<!DOCTYPE html>
<html>
<head>
<title> </title>
<meta charset="UTF-8" />
<link rel="stylesheet" type="text/css" href="easyui/themes/default/easyui.css" />
<link rel="stylesheet" type="text/css" href="easyui/themes/icon.css" />
<link rel="stylesheet" type="text/css" href="css/serverinfor.css" >

<style>
span{
display:-moz-inline-box; 
display:inline-block;
}
</style>

</head>

<body class="easyui-layout">

<div id="tb">
	<span class='lable_name' style="background-color:rgb(0,255,0);" lang>log_search_php_0</span>
	<input id="time" type="text" style="width:150px;height:22px;">
	<span>  ~  </span><input id="time1" type="text" style="width:150px;height:22px;"></span><br/>
	<span class='lable_name' style='background-color:rgb(0,255,0);' lang>log_search_php_1</span>
	<!-- <input id="client_type" name="client_name">-->
	<select id="client_type" class="easyui-combotree" type="text" style="width:100px;height:20px;"></select><br>
	<span class='lable_name' style="background-color:rgb(0,255,0);" lang>log_search_php_2</span>
	<input id="address" type="text" style="width:300px;height:20px;"></input><br/>
	
	 
</div>

<div  style="width:100%;height:100%">
	<table id="log_search_box"></table>
</div>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_channel.js"></script>
<script type="text/javascript" src="js/show_cch.js"></script>
<script type="text/javascript" src="js/log_search.js"></script>
</body>
</html>