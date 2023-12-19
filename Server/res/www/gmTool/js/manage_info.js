$(function(){
	$(window).resize(function(){  
		$("#serverinfobox").datagrid({  
			width: $(window).width(),
			height: $(window).height()
		});                
    }); 

	var operateType = undefined;
	
	function add_dialog_jy()
	{
		$('#account').textbox({
			required:true,
			validType:'english',
			missingMessage:L('manager_info_js_0'),
			invalidMessage:L('manager_info_js_34')
		});
		
		$('#password').textbox({
			required:true,
			missingMessage:L('manager_info_js_1'),
			invalidMessage:L('manager_info_js_1')
		});
		
		$('#realname').textbox({
			required:true,
			missingMessage:L('manager_info_js_41'),
			invalidMessage:L('manager_info_js_41')
		});
		
		//权限
		$('#privilege').combotree({
			//required:true,
			width:200,
			height:22,
			panelHeight:300,
			multiple:true,
			separator:'|',
			readOnly:true,
			data:g_privs,
			missingMessage:L('manager_info_js_2')
		});
		
		$.extend($.fn.validatebox.defaults.rules, {
			equals: {
				validator: function(value,param){
					return value == $(param[0]).val();
				},
				message: L('manager_info_js_32')
			},
			english: {// 验证英语
                validator: function (value) {
                    return /^[A-Za-z0-9]+$/i.test(value);
                }
            }
		});
		
		$('#password21').validatebox({
			required:true,
			missingMessage:L('manager_info_js_35'),
			invalidMessage:L('manager_info_js_35')
		});
		$('#password22').validatebox({
			required:true,
			validType:"equals['#password21']",
			missingMessage:L('manager_info_js_36'),
			invalidMessage:L('manager_info_js_32')
		});
	}
	
	$('#serverinfobox').datagrid({
			data:[],
			//width : 1250,
			//height:700,
			//fitColumns:true,
			singleSelect:true,
			fit:true,
			columns : [[
				{
					title : "check",
					field : "check",
					checkbox : true
				},
				{
					title : L('manager_info_js_6'),
					field : "account",
					width:70
				},
			    {
					title : L('manager_info_js_37'),
					field : "realname",
					width:100
				},
				{
					title : L('manager_info_js_38'),
					field : "last_time",
					width:150
				},
				{
					title : L('manager_info_js_39'),
					field : "last_ip",
					width:100,
					formatter(value)
					{
						if(value == '::1')
						{
							return 'localhost';
						}
						return value;
					}
				},
				{
					title : L('manager_info_js_40'),
					field : "login_times",
					width:70
				},
				{
					title : L('manager_info_js_7'),
					field : "privilege",
					width:200,
					formatter(value)
					{
						if(value == '') return;
						var ret = '';
						var pris = value.split('|');
						for(var i = 0; i < pris.length; ++i)
						{
							var val_text = pris[i];
							var val_len = val_text.length;
							if(val_len == 1)
							{
								val_text = g_privs[val_len - 1].text;
							}
							else if(val_len == 3)
							{
								var index1 = parseInt(val_text.substr(0, 1)) - 1; //取第1位
								var index2 = parseInt(val_text.substr(1, 2)); //取第2-3位
								val_text = g_privs[index1].children[index2].text;
							}
							else if(val_len == 4)
							{
								var index1 = parseInt(val_text.substr(0, 1)) - 1; //取第1位
								var index2 = parseInt(val_text.substr(1, 2)); //取第2-3位
								var index3 = parseInt(val_text.substr(3, 1)); //取第4位
								val_text = g_privs[index1].children[index2].children[index3].text;
							}
							if(i != 0)
							{
								ret += '|';
							}
							ret += val_text;
						}
						return ret;
					}
				}
			]],
			toolbar:'#tb'		
	});  
	
	function init_data_grid()
	{
		$.ajax({
			url : 'searchdatafromdb.php',
			type : 'post',
			data : {
				type : 20
			},
			
			beforeSend : function () {
				$.messager.progress({
					text : L('common_geting_data')
				});
			},
				
			success : function (data, response, status) {
				$.messager.progress('close');
				//alert(data);
				//console.log(data);
				if(data == 1)
				{
					$.messager.alert(L('common_2'),L('common_1'),'error');
				}
				else
				{	
					var dataarr = eval('(' + data + ')');
					$('#serverinfobox').datagrid({
								data : dataarr
					}); 
					$.messager.show({
					title:L('common_info'),
					msg:L('common_load_succ')
					});
				}			
			}
		});
	}
    
	$('#manager_add').dialog({
		width : 400,
		height : 400,
		title : L('manager_info_js_8'),
		modal : true,
		closed : true,
		iconCls : 'icon-user-add',
		buttons : [{
			text : L('manager_info_js_9'),
			iconCls : 'icon-add-new',
			handler : function () {
				 if ($('#manager_add').form('validate')) {
					var add_data = {
						account : $('#account').val(),
						password : $('#password').val(),
						realname : $('#realname').val(),
						privilege : $('#privilege').combotree('getValues').join('|')
					};
					if(add_data.privilege.length != '' && add_data.privilege.substr(add_data.privilege.length-1, 1) == '|')
					{
						add_data.privilege = add_data.privilege.substr(0, add_data.privilege.length-1);
					}
					if (operateType == 1){
						$.ajax({
							url : 'insertdatatodb.php',
							type : 'post',
							data : {
								type : 20,
								account : add_data.account,
								password : add_data.password,
								realname : add_data.realname,
								privilege : add_data.privilege
							},

							success : function (data, response, status) {
								//alert(data)
								if (data == 0) {
									$('#serverinfobox').datagrid('appendRow', add_data);
									$.messager.show({
										title : L('common_info'),
										msg : L('common_add_succ')
									});
									$('#manager_add').dialog('close').form('reset');
									
								} else if(data == 1)
								{
									$.messager.alert(L('manager_info_js_25'), L('manager_info_js_26'), 'warning');
								}
								else if(data == 2)
								{
									$.messager.alert(L('manager_info_js_25'), L('manager_info_js_27'), 'warning');
								}
								else if(data == 3)
								{
									$.messager.alert(L('manager_info_js_25'), L('manager_info_js_28'), 'warning');
								}
								else if (data == 4) {
									$.messager.alert(L('common_2'), L('manager_info_js_42'), 'error');
								}
								else
								{
									alert(data);
								}
							}
						});
					} else if (operateType == 2){
						$.ajax({
							url : 'updatedatatodb.php',
							type : 'post',
							data : {
								type : 20,
								childtype : 0,
								account : add_data.account,
								privilege : add_data.privilege
							},

							success : function (data, response, status) {
								if (data == 0) {
									
									var rowsarr = $('#serverinfobox').datagrid('getSelections');

									var rowindex = $('#serverinfobox').datagrid('getRowIndex',rowsarr[0]);
									
									$('#serverinfobox').datagrid('updateRow',{
										index : rowindex,
										row : {
											account : add_data.account,
											privilege : add_data.privilege
										}

									});
									
									$.messager.show({
										title : L('common_info'),
										msg : L('common_mode_succ')
									});
									$('#manager_add').dialog('close').form('reset');
									//$('#serverinfobox').datagrid('reload');
								} else if (data == 4) {
									$.messager.alert(L('common_2'), L('manager_info_js_42'), 'error');
								} else {
									$.messager.alert(L('common_2'), L('common_1'), 'error');
								}
								
							}
						});
					}					
				} 
			}
		},
		{
			text : L('manager_info_js_20'),
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
		
	$('#manager_password').dialog({
		width : 400,
		title : L('manager_info_js_10'),
		modal : true,
		closed : true,
		iconCls : 'icon-user-add',
		buttons : [{
			text : L('manager_info_js_11'),
			iconCls : 'icon-add-new',
			handler : function () {
				if ($('#manager_password').form('validate')) {
					$.ajax({
						url : 'updatedatatodb.php',
						type : 'post',
						data : {
							type : 20,
							childtype : 2,
							password_src : $('#password_src').val(),
							password_new : $('#password21').val()
						},
						success : function (data, response, status) {
							if (data == 0) {
								$.messager.show({
									title : L('common_info'),
									msg : L('common_mode_succ')
								});
								$('#manager_password').dialog('close').form('reset');
							} else if(data == 1){
								$.messager.alert(L('manager_info_js_15'), L('manager_info_js_33'), 'warning');
							}
							else {
								$.messager.alert(L('manager_info_js_15'), data, 'warning');
							}
						}
					});
				}
			}
		},{
			text : L('manager_info_js_20'),
			iconCls : 'icon-redo',
			handler : function () {
				$.messager.confirm(L('common_confirm'),L('common_confirm_quit'),function(r){
					if(r){
						$('#manager_password').dialog('close').form('reset');
					}
				});

			}
		}]
	});
	
	function delSingleDataFromDB(account,rows){
		$.ajax({
			url : 'deldatafromdb.php',
			type : 'post',
			data : {
				account : account,
				type : 20
			},
			success : function(data,response,status){
				//alert(data);
				if(data == 0)
				{
					// 从表中删除数据
					for(var i = 0; i < rows.length; i ++)
					{
						var row = $('#serverinfobox').datagrid('getRowIndex',rows[i]);
						$('#serverinfobox').datagrid('deleteRow',row);
					}
					$.messager.show({
						title : L('common_info'),
						msg : L('common_del_succ')
					});
				}
				else
				{
					// 提示失败
					$.messager.alert(L('common_2'), L('common_1'), 'error');
				}
			}
		});
	}
	
	function reset_password(account){
		$.ajax({
			url : 'updatedatatodb.php',
			type : 'post',
			data : {
				type : 20,
				childtype : 1,
				account : account
			},
			success : function(data,response,status){
				//alert(data);
				if(data == 0)
				{
					$.messager.show({
						title : L('common_info'),
						msg : L('common_mode_succ')
					});
				}
				else
				{
					// 提示失败
					$.messager.alert(L('common_2'), L('common_1'), 'error');
				}
			}
		});
	}
	
	$('#addsingle').click(function(){
			$('#account').val("");
			$('#account').textbox('enable');
			
			$('#password').val("");
			$('#password').textbox('enable');
			
			$('#realname').val("");
			$('#realname').textbox('enable');
			
			$('#privilege').combotree('clear');
			
			operateType = 1;
			$('#manager_add').dialog('open').form('reset');
			$('#manager_add').dialog('center');
			$('#manager_add').focus();
	 });
	
	$('#updatesingle').click(function(){
		//alert("updatesingle");
		var index = $('#serverinfobox').datagrid('getSelections');
		if(index.length != 0 )
		{
			if(index.length > 1)
			{
				$.messager.alert(L('common_info'),L('common_select_one'),'info');
			}
			else
			{
				$('#account').textbox('setValue', index[0].account);
				$('#account').textbox('disable');
				
				$('#password').val("");
				$('#password').textbox('disable');
				
				$('#realname').textbox('setValue', index[0].realname);
				$('#realname').textbox('disable');
				
				var privalege_ayyar = index[0].privilege.split('|');
				var change_node = false;
				for(var i=0;i<g_privs.length;++i)
				{
					if(!(g_privs[i].id>0 && g_privs[i].children && g_privs[i].children.length>0))
					{
						continue;
					}
					//数据库数据有没有g_privs[i].children[j].id
					var index1 = get_data_from_array(privalege_ayyar,g_privs[i].id);
					if(index1<0)
					{
						continue;
					}
					
					for(var j=0;j<g_privs[i].children.length;++j)
					{
						if(!(g_privs[i].children[j].id>0 && g_privs[i].children[j].children && g_privs[i].children[j].children.length>0))
						{
							continue;
						}
						//数据库数据有没有g_privs[i].children[j].id
						var index2 = get_data_from_array(privalege_ayyar,g_privs[i].children[j].id);
						if(index2<0)
						{
							continue;
						}
						//遍历查看有没有新加的
						for(var k=0;k<g_privs[i].children[j].children.length;++k)
						{
							var index3 = get_data_from_array(privalege_ayyar,g_privs[i].children[j].children[k].id);
							if(index3<0)
							{
								//去除上一根节点
								privalege_ayyar.splice(index2,1);
								change_node = true;
								break;
							}
						}
					}
					
					for(var n=0;n<g_privs[i].children.length;++n)
					{
						var index4 = get_data_from_array(privalege_ayyar,g_privs[i].children[n].id);
						if(index4<0)
						{
							//去除上一根节点
							privalege_ayyar.splice(index1,1);
							change_node = true;
							break;
						}
					}
				}
				
				$('#privilege').combotree('setValues', privalege_ayyar);
				
				operateType = 2;
				$('#manager_add').dialog('open');
				$('#manager_add').dialog('center');
				$('#manager_add').focus();
				
				//如果节点变了就更新数据库
				if(change_node)
				{
					$.ajax({
					url : 'updatedatatodb.php',
						type : 'post',
						data : {
							type : 20,
							childtype : 0,
							account : index[0].account,
							privilege : privalege_ayyar.join('|')
						}
					});
				}
			}
		}
		else
		{
			$.messager.alert(L('common_info'),L('common_select_first'),'info');
		}
	});
	
	$('#delsingle').click(function(){
		var index = $('#serverinfobox').datagrid('getSelections');
		if(index.length != 0 )
		{
			if(index.length > 1)
			{
				$.messager.alert(L('common_info'),L('common_select_one'),'info');
			}
			else
			{
				$.messager.confirm(L('common_confirm'),L('common_confirm_del'),function(r){
					if(r){
						delSingleDataFromDB(index[0].account,index);
					}
				});
			}
		}
		else
		{
			$.messager.alert(L('common_info'),L('common_select_first'),'info');
		}
	});
	
	$('#reset_password').click(function(){
		var index = $('#serverinfobox').datagrid('getSelections');
		if(index.length != 0 )
		{
			if(index.length > 1)
			{
				$.messager.alert(L('common_info'),L('common_select_one'),'info');
			}
			else
			{
				$.messager.confirm(L('common_confirm'),L('manager_info_js_31'),function(r){
					if(r){
						reset_password(index[0].account);
					}
				});			
			}
		}
		else
		{
			$.messager.alert(L('common_info'),L('common_select_first'),'info');
		}
	});	
	
	$('#update').click(function(){
		init_data_grid();   
	});	
	
	$('#mod_password').click(function(){
		$('#password_src').val("");
		$('#password21').val("");
		$('#password22').val("");
		
		$('#manager_password').dialog('open').form('reset');
		$('#manager_password').dialog('center');
		$('#manager_password').focus();
	});	
	
	function get_data_from_array(array,data)
	{
		for(var i=0;i<array.length;++i)
		{
			if(array[i]==data)
			{
				return i;
			}
		}
		return -1;
	}
	
	add_dialog_jy();
	init_data_grid();
});