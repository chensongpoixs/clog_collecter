$(function(){
	$(window).resize(function(){  
		$("#privilege_list").datagrid({  
			width: $(window).width(),
			height: $(window).height()
		});                
    });

	function init_data_grid()
	{	
		$('#privilege_list').datagrid({
			singleSelect:true,
			fit:true,
			data:[],
			columns : [[
				{
					title : "check",
					field : "check",
					checkbox : true
				},
				{
					title : L('common_account_id'),
					field : "open_id",
					width:70
				},
				{
					title : L('gm_privilege_js_0'),
					field : "privilege",
					width:100
				}
			]],
			toolbar:'#tb',
			pagination:true,
			pageNumber:1,
			rownumbers:false,
			pageSize:10,
			pageList: [10, 20, 50],
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
		$('#manager_add').dialog({
			width : 400,
			title : L('gm_privilege_js_3'),
			modal : true,
			closed : true,
			buttons : [{
				text : L('common_commit'),
				iconCls : 'icon-ok',
				handler : function () {
					 if ($('#manager_add').form('validate')) {
						$.ajax({
						url : 'searchdatafromdb.php',
						type : 'post',
						data : {
							type : 25,
							childtype : 1,
							condition_type:0,
							condition_value:0,
							set_open_id : $('#account_id').val(),
							set_privilege : $('#privilege').val()
						},
						beforeSend : function () {
						},
						success : function (data, response, status) {
							if(data == 1)
							{
								alert("query_err!");
							}
							else
							{
								$.messager.show({
									title : L('common_commit'),
									msg : L('common_mode_succ')
								});
								fill_privilege_list(0,0,0,0,0);
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
						$('#manager_add').dialog('close').form('reset');
					}
				});
			 }
			}]
		});		
	}
	
			
	function fill_privilege_list(childtype,condition_type,condition_value,set_open_id,set_privilege)
	{
		$('#privilege_list').datagrid({
			url:'searchdatafromdb.php',
			queryParams:{
				type:25,
				childtype:childtype,
				condition_type:condition_type,
				condition_value:condition_value,
				set_open_id:set_open_id,
				set_privilege:set_privilege
			}});
	}
		
	
	function init_btn()
	{	
		$('#updatesingle').click(function(){
			$('#account_id').textbox('clear');
			$('#privilege').textbox('clear');
			var index = $('#privilege_list').datagrid('getSelections');
			if(index.length != 0 )
			{
				$('#account_id').numberbox('setValue', index[0].open_id);
				$('#privilege').numberbox('setValue', index[0].privilege);
			}
			$('#manager_add').dialog('open');
			$('#manager_add').dialog('center');
			$('#manager_add').focus();
		});	
		
		$('#update').click(function(){
			fill_privilege_list(0,0,0,0,0);
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
				fill_privilege_list(0,condition_type,value,0,0);
			},
			menu:'#gm_menu_item',
			prompt:'Please Input Value'
		});
		
	}	
	init_dialog();
	init_data_grid();
	init_btn();
	initsearchbox();
	fill_privilege_list(0,0,0,0,0);
});