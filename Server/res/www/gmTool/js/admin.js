$(function () {
	
	$('#tabs').tabs(
	{
		fit : true,
		border : true
	});
	

	$('#server_info a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_0')))
		{
			$('#tabs').tabs('select',L('admin_js_0'));
		}
		else
		{
			//$('tabs').
			var content = '<iframe scrolling="auto" frameborder="0"  src="serverinfopage.php" style="width:100%;height:99%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_0'),
			content : content,
			fit : true,
			//closable : true,
			//href : 'serverinfopage.php',
			closed: true,
			closable : true
			});
		}
	});
	
	$('#client_log_search a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_1')))
		{
			$('#tabs').tabs('select',L('admin_js_1'));
		}
		else
		{
			//$('tabs').
			var content = '<iframe scrolling="auto" frameborder="0"  src="client_log_search.php" style="width:100%;height:99%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_1'),
			content : content,
			fit : true,
			//closable : true,
			//href : 'serverinfopage.php',
			closed: true,
			closable : true
			});
		}
	});
	
	 
	$('#js_data_info a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_14')))
		{
			$('#tabs').tabs('select',L('admin_js_14'));
		}
		else
		{
			var content = '<iframe scrolling="no" frameborder="0"  src="js_data_page.php" style="width:100%;height:95%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_14'),
			content : content,
			fit : true,
			closed: true,
			closable : true
			});
		}
	});
	
	 
    $('#gm_cmd a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_9')))
		{
			$('#tabs').tabs('select',L('admin_js_9'));
		}
		else
		{
			var content = '<iframe scrolling="no" frameborder="0"  src="gm_cmd_page.php" style="width:100%;height:99%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_9'),
			content : content,
			fit : true,
			closed: true,
			closable : true
			});
		}
	});
	
 
	$('#manage_log a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_11')))
		{
			$('#tabs').tabs('select',L('admin_js_11'));
		}
		else
		{
			//$('tabs').
			var content = '<iframe scrolling="auto" frameborder="0"  src="manage_log_page.php" style="width:100%;height:99%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_11'),
			content : content,
			fit : true,
			//closable : true,
			//href : 'manage_log_page.php',
			closed: true,
			closable : true
			});
		}
	});
 
	//GM权限管理 
	$('#gm_privilege a').click(function(){
		if($('#tabs').tabs('exists',L('admin_js_19')))
		{
			$('#tabs').tabs('select',L('admin_js_19'));
		}
		else
		{
			//$('tabs').
			var content = '<iframe scrolling="auto" frameborder="0"  src="gm_privilege.php" style="width:100%;height:99%;"></iframe>';
			$('#tabs').tabs('add',{
			title:L('admin_js_19'),
			content : content,
			fit : true,
			//closable : true,
			closed: true,
			closable : true
			});
		}
	});
	
	 
	
});