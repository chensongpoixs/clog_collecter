$(function(){
	$(window).resize(function(){  
		$("#comment_list").datagrid({  
			width: $(window).width(),
			height: $(window).height()
		});                
    });
	var del_id_array=new Array();
	var m_servers = new Array();
	function init_data_grid()
	{	
		$('#comment_list').datagrid({
			singleSelect:false,
			fit:true,
			data:[],
			columns : [[
				{
					title : "check",
					field : "check",
					checkbox : true
				},
				{
					title : L('comment_php_4'),
					field : "id",
					width:70
				},
				{
					title : L('account_ban_js_11'),
					field : "server_id",
					width:70
				},
				{
					title : L('player_ban_js_4'),
					field : "player_id",
					width:70
				},
				{
					title : L('player_ban_js_13'),
					field : "name",
					width:70
				},
				{
					title : L('comment_php_1'),
					field : "hero_id",
					width:70
				},
				{
					title : L('comment_php_0'),
					field : "word",
					width:400
				},
				{
					title : L('comment_php_3'),
					field : "like_count",
					width:70
				},
				{
					title : L('manager_log_js_2'),
					field : "time",
					width:120
				}
			]],
			toolbar:'#tb',
			pagination:true,
			pageNumber:1,
			rownumbers:false,
			pageSize:20,
			pageList: [20, 50, 100],
			pagePosition:'top',
			onLoadSuccess : function (data) 
			{
				var v = eval(data);
				if(v["ret"]==1)
				{
					alert('sql error');
				}
			},
			onLoadError:function(){
				alert('error');
			}			
		});
	}
	
	function init_dialog()
	{
		// 服务器ID
		$('#server_id').combobox({
			width:150,
			height:22,
			required:true,
			panelHeight:100,
			multiple:false  ,
			separator:',',
			readOnly:false,
			valueField:'id',
			textField:'text',
			data:m_servers
		});	
		
		$('#comment_add').dialog({
			width : 400,
			title : L('manager_info_php_0'),
			modal : true,
			closed : true,
			buttons : [{
				text : L('common_commit'),
				iconCls : 'icon-ok',
				handler : function () {
					 if ($('#comment_add').form('validate')) {
						$.ajax({
						url : 'searchdatafromdb.php',
						type : 'post',
						data : {
							type : 26,
							childtype : 1,
							add_server_id : $('#add_server_id').val(),
							add_player_id : $('#add_player_id').val(),
							add_hero_id : $('#add_hero_id').val(),
							add_name : $('#add_name').val(),
							add_word : $('#add_word').val(),
							add_like_count : $('#add_like_count').val()
						},
						beforeSend : function () {
							
						},
						success : function (data, response, status) {
							if(data == 1)
							{
								alert("Add Failed!!!");
							}
							else
							{
								fresh(0,0);
								$.messager.show({
									title : L('common_commit'),
									msg : L('common_add_succ')
								});
							}
						}
					});
						
					} 
				}
			},
			{
			text : L('common_cancel'),
			iconCls : 'icon-redo',
			handler : function () {
				$.messager.confirm(L('common_confirm'),L('common_confirm_quit'),function(r){
					if(r){
						$('#comment_add').dialog('close').form('reset');
					}
				});
			 }
			}]
		});		
		
		$('#comment_update').dialog({
			width : 400,
			title : L('gm_privilege_js_3'),
			modal : true,
			closed : true,
			buttons : [{
				text : L('common_commit'),
				iconCls : 'icon-ok',
				handler : function () {
					 if ($('#comment_update').form('validate')) {
						$.ajax({
						url : 'searchdatafromdb.php',
						type : 'post',
						data : {
							type : 26,
							childtype : 2,
							up_id : $('#com_id').val(),
							up_like_count : $('#com_like').val()
						},
						beforeSend : function () {
						},
						success : function (data, response, status) {
							if(data == 1)
							{
								alert("Updata Failed!!!");
							}
							else
							{
								fresh(0,0);
								$.messager.show({
									title : L('common_commit'),
									msg : L('common_mode_succ')
								});
							}
						}
					});
						
					} 
				}
			},
			{
			text : L('common_cancel'),
			iconCls : 'icon-redo',
			handler : function () {
				$.messager.confirm(L('common_confirm'),L('common_confirm_quit'),function(r){
					if(r){
						$('#comment_update').dialog('close').form('reset');
					}
				});
			 }
			}]
		});

		$('#comment_delete').dialog({
			width : 400,
			title : L('manager_info_php_2'),
			modal : true,
			closed : true,
			buttons : [{
				text : L('common_commit'),
				iconCls : 'icon-ok',
				handler : function () {
					 if ($('#comment_delete').form('validate')) {
						get_del_id();
						//将勾选的选项删除
						$.ajax({
								url : 'searchdatafromdb.php',
								type : 'post',
								data : {
									type : 26,
									childtype : 3,
									del_id : del_id_array
								},
								beforeSend : function () {
									if(del_id_array.length<=0)
									{
										return false;
									}
								},
								success : function (data, response, status) {
									if(data == 1)
									{
										alert("Updata Failed!!!");
									}
									else
									{
										fresh(0,0);
										$.messager.show({
											title : L('common_commit'),
											msg : L('common_del_succ')
										});
									}
								}
							});
					} 
				}
			},
			{
			text : L('common_cancel'),
			iconCls : 'icon-redo',
			handler : function () {
				$.messager.confirm(L('common_confirm'),L('common_confirm_quit'),function(r){
					if(r){
						$('#comment_delete').dialog('close').form('reset');
					}
				});
			 }
			}]
		});	
	}
	
			
	function fill_privilege_list(childtype,condition_type,condition_value,server_id)
	{
		$('#comment_list').datagrid({
			url:'searchdatafromdb.php',
			queryParams:{
				type:26,
				childtype:childtype,
				condition_type:condition_type,
				condition_value:condition_value,
				server_id:server_id
			}});
	}
		
	
	function init_btn()
	{	
	
	
		//添加
		$('#addsingle').click(function(){
			$('#add_server_id').textbox('clear');
			$('#add_player_id').textbox('clear');
			$('#add_hero_id').textbox('clear');
			$('#add_name').textbox('clear');
			$('#add_word').textbox('clear');
			$('#add_like_count').textbox('clear');
			$('#comment_add').dialog('open');
			$('#comment_add').dialog('center');
			$('#comment_add').focus();
			
		});
		
		//修改
		$('#updatesingle').click(function(){
			$('#com_id').textbox('clear');
			$('#com_like').textbox('clear');
			var index = $('#comment_list').datagrid('getSelections');
			if(index.length != 0 )
			{
				$('#com_id').numberbox('setValue', index[0].open_id);
				$('#com_like').numberbox('setValue', index[0].privilege);
			}
			$('#comment_update').dialog('open');
			$('#comment_update').dialog('center');
			$('#comment_update').focus();
		});	
		
		//删除
		$('#delsingle').click(function(){
			
			$('#comment_delete').dialog('open');
			$('#comment_delete').dialog('center');
			$('#comment_delete').focus();
		});
		
		//刷新
		$('#update').click(function(){
			fresh(0,0);
		});	
		
	}
	
	//	初始化搜索框
	function initsearchbox()
	{
		$('#gm_menu_searchbox').searchbox({
			width:200,
			height:25,
			searcher:function(value,name){
				var condition_type = 0;
				if(name=='gm_menu_open_id')
				{
					condition_type = 1;
				}
				else if(name=='gm_menu_name')
				{
					condition_type = 2;
				}
				else if(name=='gm_menu_player_id')
				{
					condition_type = 3;
				}
				else if(name=='comment_menu_word')
				{
					condition_type = 4;
				}
				else if(name=='comment_menu_hero')
				{
					condition_type = 5;
				}
				else if(name=='comment_menu_like')
				{
					condition_type = 6;
				}
				else if(name=='comment_menu_id')
				{
					condition_type = 7;
				}
				fresh(condition_type,value);
			},
			menu:'#gm_menu_item',
			prompt:'Please Input Value'
		});
		
	}	
	
	function get_del_id()
	{
		del_id_array=[];
		var index = $('#comment_list').datagrid('getSelections');
		for(var i=0;i<index.length;i++)
		{
			del_id_array[i]=index[i].id;
		}
	}
	
	function fresh(condition_type,value)
	{
		var server_id=$('#server_id').combobox('getValue');
		fill_privilege_list(4,condition_type,value,server_id);
	}
		//初始化服务器
	function init_servers()
	{
		$.ajax({
			url : 'searchdatafromdb.php',
			type : 'post',
			data : {
				type : 0,
				childtype:5,
				value:0
			},
			async: false,
			success : function (data, response, status) {
				if(data == 1)
				{
					$.messager.alert(L('common_2'),L('common_no_privilege'),'error');
				}
				else if(data == 2)
				{
					$.messager.alert(L('common_2'),L('common_1'),'error');
				}
				else
				{
					//alert(data);
					var tmp = eval('(' + data + ')');
					m_servers = m_servers.concat(tmp);
				}
			}
		});
	}
	init_servers();
	init_dialog();
	init_data_grid();
	init_btn();
	initsearchbox();
	fresh(0,0);
});