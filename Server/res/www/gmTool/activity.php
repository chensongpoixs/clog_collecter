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
<link rel="stylesheet" type="text/css" href="easyui/uploadify.css" />
<link rel="stylesheet" type="text/css" href="css/activity.css" />
</head>
<body class="easyui-layout">

<div data-options="region:'center'" style="overflow:auto;width:100%;height:100%;">
	<table id="activitymanagerlist" ></table>
</div>

 <div id="activitymanager_menu">
    <div region="north" border="false" style="border-bottom:1px solid #ddd;height:28px;padding:2px 2px 2px 2px;background:#fafafa;">  
		<div style="float:left;">
			<input id="activitymanager_menu_searchbox" >.</input>
			<div id="activitymanager_menu_item" style="width:120px">
				<div name="activitymanager_menu_id" lang>activity_php_0</div>
				<div name="activitymanager_menu_type" lang>activity_php_1</div>
				<div name="activitymanager_menu_name" lang>activity_php_2</div>
                <div name="activitymanager_menu_server" lang>activity_php_3</div>
				<div name="activitymanager_menu_channel" lang>common_channel</div>
			</div>
		</div>

		<div class="datagrid-btn-separator" style="width:10px;"></div>
		<div style="float:left;">
			<?php
				if(has_privilege(4041))
				{
					echo '<a id="activitymanager_menu_add" href="#" class="easyui-linkbutton" plain="true" icon="icon-add" ><span lang>activity_php_4</span></a>';
				}
				if(has_privilege(4042))
				{
					echo '<a id="activitymanager_menu_change" href="#" class="easyui-linkbutton" plain="true" icon="icon-edit"><span lang>activity_php_6</span></a>';
				}
				if(has_privilege(4043))
				{
					echo '<a id="activitymanager_menu_delete" href="#" class="easyui-linkbutton" plain="true" icon="icon-remove"><span lang>activity_php_5</span></a>';
				}
				if(has_privilege(4044))
				{
					echo '<a id="activitymanager_menu_import" href="#" class="easyui-linkbutton" plain="true" icon="icon-save"><span lang>activity_php_46</span></a>';
				}
			?>
            
			<a id="activitymanager_menu_export" href="export_activity.php" class="easyui-linkbutton" plain="true"><span lang>activity_php_47</span></a>
            <a id="activitymanager_menu_refresh" href="#" class="easyui-linkbutton" plain="true" icon="icon-reload"><span lang>activity_php_7</span></a>
			
        </div>  
    </div>
</div>  

<!--<form id="form_players_id" action="operatefile.php" method="post" enctype="multipart/form-data"> </form> -->
<form id="activitymanager_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_0</th>
      		<th><input id="activitymanager_id" /></th>
      	</tr>
        <tr>
      		<th lang>activity_php_8</th>
      		<th><input id="activitymanager_enable" /></th>
      	</tr>
        <tr>
      		<th lang>activity_php_1</th>
      		<th><input id="activitymanager_type" /></th>
      	</tr>
		<tr>
      		<th lang>activity_php_2</th>
      		<th><input id="activitymanager_name" /></th>
      	</tr>
        <th lang>activity_php_10</th>
 			<th><input id="activitymanager_show_time" /></th>
 		</tr>
        <tr>
			<th lang>activity_php_11</th>
			<th><input id="activitymanager_start_time"/></th>
		</tr>
        <tr>
            <th lang>activity_php_12</th>
      		<th><input id="activitymanager_end_time"/></th>
      	</tr>
        <tr>
      		<th lang>activity_php_13</th>
      		<th><input id="activitymanager_disappear_time"/></th>
      	</tr>
        <tr>
      		<th lang>activity_php_14</th>
      		<th><input id="activitymanager_servers"/></th>
      		<th colspan="2"><a id="activitymanager_btn_servers" href="#" class="easyui-linkbutton" plain="true" icon="icon-add"><span lang>activity_php_15</span></a></th>
      	</tr>
		<tr>
      		<th lang>common_channel</th>
      		<th><input id="activitymanager_channel"/></th>
      	</tr>
		<tr>
      		<th lang>activity_php_49</th>
      		<th><input id="activitymanager_image" /></th>
      	</tr>
		<tr>
      		<th lang>common_desc</th>
      		<th><input id="activitymanager_desc" /></th>
      	</tr>
      	<tr>
      		<th lang>activity_php_17</th>
      		<th><textarea id="activitymanager_content" cols="30" rows="5" style="resize:none;"></textarea></th>
            <th><a id="activitymanager_content_btn" href="#" class="easyui-linkbutton" plain="true" icon="icon-add"><span lang>activity_php_16</span></a></th>
      	</tr>
	</table>
</form>

<form id="activity_import_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table border="0">
		<tr>
			<th colspan="2"><input id="activity_import_btn" type="file" /></th>
		</tr>
		<!--tr>
			<th colspan="2"><input id="activity_import_sql_btn" type="file" /></th>
		</tr-->
		<tr>
			<th lang>activity_php_48</th>
			<th><textarea id="activity_import_result" cols="40" rows="10" style="resize:none;" readonly="true"></textarea></th>
		</tr>

	</table>
</form>

<form id="activity_shop_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_23</th>
      		<th><input id="activity_shop_type" /></th>
      	</tr>
		<tr>
			<table id="activity_shop_table"></table>
		</tr>
    </table>
    
</form>

<form id="activity_dialog_servers" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table id="activity_server_list"></table>
</form>
<div id="activity_server_menu">
       <div region="north" border="false" style="border-bottom:1px solid #ddd;height:28px;padding:2px 2px 2px 2px;background:#fafafa;">

		<div style="float:left;">
			<input id="activity_server_menu_searchbox"  /input>
			<div id="activity_server_menu_item" style="width:120px">
			<div name="activity_server_menu_id" lang>activity_php_36</div>
			<div name="activity_server_menu_show_id" lang>activity_php_37</div>
			</div>
		</div>
       </div>
</div>

<!--  支付活动 -->
<form id="activity_pay_dialog" style="overflow:auto;width:100%;height:100%;">
	<table id="activity_pay_table"></table>
</form>

<form id="activity_pay_item_dialog" style="overflow:auto;margin:0;padding:5px 3px 0px 3px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_24</th>
      		<th><input id="activity_pay_item_id" /></th>
      	</tr>
		<tr>
      		<th><label id="activity_pay_text" /></th>
      		<th><input id="activity_pay_value" /></th>
      	</tr>
		<tr>
			<table id="activity_pay_rewards"></table>
		</tr>
    </table>
</form>

<!--  战斗狂欢 -->
<form id="activity_battle_dialog" style="overflow:auto;margin:0;padding:5px 3px 0px 3px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_26</th>
      		<th><input id="activity_battle_scene_double" type="checkbox" /></th>
      	</tr>
		<tr>
      		<th lang>activity_php_27</th>
      		<th><input id="activity_battle_elite_scene_double" type="checkbox" /></th>
      	</tr>
    </table>
</form>

<!--  排行奖励 -->
<form id="activity_rank_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_52</th>
      		<th><input id="activity_rank_type" /></th>
      	</tr>
		<tr>
			<table id="activity_rank_table"></table>
		</tr>
    </table>
</form>
<form id="activity_rank_item_dialog" style="overflow:auto;margin:0;padding:5px 3px 0px 3px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_50</th>
      		<th><input id="activity_rank_min" /></th>
      	</tr>
		<tr>
      		<th lang>activity_php_51</th>
      		<th><input id="activity_rank_max" /></th>
      	</tr>
		<tr>
      		<table id="activity_rank_rewards"></table>
      	</tr>
    </table>
</form>

<!--  达成奖励 -->
<form id="activity_reach_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
	<table border="0">
        <tr>
      		<th lang>activity_php_53</th>
      		<th><input id="activity_reach_type" /></th>
      	</tr>
		<tr>
			<table id="activity_reach_table"></table>
		</tr>
    </table>
</form>

<!--  限时招募 -->
<form id="activity_limit_recruitment_dialog" style="overflow:auto;margin:0;padding:5px 0 0 25px;color:#333;">
  <table border="0">
        <tr>
          <th lang>activity_php_54</th>
          <th><input id="activity_limit_recruitment_id" /></th>
          <th lang>activity_php_55</th>
          <th><input id="activity_limit_recruitment_free" /></th>
          <th lang>activity_php_56</th>
          <th><input id="activity_limit_recruitment_one" /></th>
          <th lang>activity_php_57</th>
          <th><input id="activity_limit_recruitment_ten" /></th>
        </tr>
    <tr>
      <table id="activity_limit_recruitment_table"></table>
    </tr>
    </table>
</form>

<script type="text/javascript" src="easyui/jquery.min.js"></script>
<script type="text/javascript" src="easyui/jquery.easyui.min.js"></script>
<script type="text/javascript" src="easyui/locale/easyui-lang-zh_CN.js" ></script>
<script type="text/javascript" src="easyui/jquery.uploadify.js" ></script>
<script type="text/javascript" src="js/validatebox_regex.js"></script>
<script type="text/javascript" src="js/json2.js"></script>
<script type="text/javascript" src="js/language.js"></script>
<script type="text/javascript" src="data/data_define.js"></script>
<script type="text/javascript" src="data/data_channel.js"></script>
<script type="text/javascript" src="data/data_items.js"></script>
<script type="text/javascript" src="data/data_heros.js"></script>
<script type="text/javascript" src="data/activity_type.js"></script>
<script type="text/javascript" src="js/func_reward.js"></script>
<script type="text/javascript" src="js/activity.js"></script>
</body>
</html>