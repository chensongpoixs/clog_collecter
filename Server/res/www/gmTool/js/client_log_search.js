$(function(){
	
	var operateType = undefined;
	
	var m_status = 	[
		{
			id: 0, // 维护
			text: L('serverslist_js_10')
		},
		{
			id: 1, // 空闲
			text: L('serverslist_js_6')
		},
		{
			id: 2, // 良好
			text: L('serverslist_js_7')
		},{
			id: 3, // 繁忙
			text: L('serverslist_js_8')
		},
		{
			id: 4, // 爆满
			text: L('serverslist_js_9')
		}
	];
	
	var m_platform = [
		{
			id: 'ios',
			text: '苹果'
		},{
			id: 'ad',
			text: '安卓'
		}
	];
	
	var m_yes_no = [
		{
			id: 0,
			text: L('serverslist_js_51')
		},{
			id: 1,
			text: L('serverslist_js_52')
		}
	];
		
	function get_text(values, id)
	{
		for(var i = 0; i < values.length; i++)
		{
			if(values[i].id == id)
			{
				return values[i].text;
			}
		}
		return id;
	}
	
	function trans_ids2texts(src_array, ids)
	{
		var ids_array = ids.split("|");
		var str = '';
		for(var i = 0; i < ids_array.length; i++)
		{
			if(i != 0)
			{
				str += '|';
			}
			str += get_text(src_array, ids_array[i]);
		}
		return str;
	}
	
	
	$(window).resize(function(){  
		$("#loginfobox").datagrid({  
			width: $(window).width(),
			height: $(window).height()
		});                
    }); 

	function add_dialog_jy()
	{
		$('#id').numberbox({
			required:true,
			min:0,
			max:65535,
			missingMessage:L('serverslist_js_0')
		});
			
		$('#cur_id').numberbox({
			required:true,
			min:0,
			max:65535,
			missingMessage:L('serverslist_js_0'),
			invalidMessage:L('serverslist_js_0')
		});
		
		$('#show_id').numberbox({
			required:true,
			min:0,
			max:65535,
			missingMessage:L('serverslist_js_0'),
			invalidMessage:L('serverslist_js_0')
		});
		
		$('#name').validatebox({
			required:true,
			validType:'name',
			missingMessage:L('serverslist_js_1'),
			invalidMessage:L('serverslist_js_2')
		});
		
		$('#ipport').validatebox({
			required:true,
			missingMessage:L('serverslist_js_3')
		});
		
		//权重
		$('#rate').numberbox({
			required:true,
			min:0,
			max:10,
			missingMessage:L('serverslist_js_60')
		});
		
		// 状态	
		$('#status').combotree({
			required:true,
			width:200,
			height:22,
			panelHeight:100,
			multiple:false  ,
			separator:'|',
			readOnly:true,
			data:m_status,
			missingMessage:L('serverslist_js_5')
		});	
			
		// 运行平台	
		$('#platform').combotree({
			required:false,
			width:200,
			height:22,
			panelHeight:100,
			multiple:true  ,
			separator:'|',
			readOnly:true,
			data:m_platform,
			missingMessage:L('serverslist_js_5')
			});

		// 是否是新服
		$('#new').combotree({
			required:true,
			width:200,
			height:22,
			panelHeight:50,
			multiple:false  ,
			separator:'|',
			readOnly:true,
			data:m_yes_no,
			missingMessage:L('serverslist_js_5')
			});
		
		// 推荐	
		$('#suggest').combotree({
			required:true,
			width:200,
			height:22,
			panelHeight:100,
			multiple:false  ,
			readOnly:true,
			data:m_yes_no,
			missingMessage:L('serverslist_js_5')
			});
		
		// GM	
		$('#is_gm').combotree({
			required:true,
			width:200,
			height:22,
			panelHeight:100,
			multiple:false  ,
			readOnly:true,
			data:m_yes_no,
			missingMessage:L('serverslist_js_5')
			});
	
		$('#version').validatebox({
			required:false,
			validType:'nochiness',
			missingMessage:L('serverslist_js_12'),
			invalidMessage:L('serverslist_js_13')
		});
		
		function onCheckChannel(combotree_obj, node, checked)
		{
			if(checked == true)
			{
				var tree = combotree_obj.combotree('tree');
				if(node.id == g_channel[0].id)
				{
					var nodes = tree.tree('getChecked');
					if(nodes != null)
					{
						for(var i = 0; i < nodes.length; i++)
						{
							if(nodes[i].id != g_channel[0].id)
							{
								tree.tree("uncheck", nodes[i].target);
							}
						}
					}
				}
				else 
				{
					var node = tree.tree('find', g_channel[0].id);
					if(node.checked)
					{
						tree.tree("uncheck", node.target);
					}
				}
			}
		}
		
		// 渠道添加
		$('#channel').combotree({
			required:true,
			width:200,
			height:22,
			panelHeight:100,
			multiple:true  ,
			separator:'|',
			readOnly:true,
			data:g_channel,
			missingMessage:L('serverslist_js_5'),
			onCheck:function(node, checked)
			{
				onCheckChannel($('#channel'), node, checked);
			}
		});	
		
		$('#open_time').datetimebox({
			width:150,
			value: '1/1/2017 00:00:00',
			showSeconds: true,
			invalidMessage:L('common_invalid_time')
		});
	}
	
	$('#loginfobox').datagrid({
			data:[],
			//width : 1250,
			//height:700,
			//fitColumns:true,
			fit:true,
			columns : [[
				{
					title : "check",
					field : "check",
					checkbox : true
				},
				{
					title : L('clientlogsearch_js_0'),
					field : "id",
					width:60
				},{
					title : L('clientlogsearch_js_3'),
					field : "datetime",
					width:130
				},
				{
					title : L('clientlogsearch_js_1'),
					field : "client_type",
					width:80
				},
				{
					title : L('clientlogsearch_js_2'),
					field : "address",
					width:100
				}
				,{
					title : L('clientlogsearch_js_4'),
					field : "log_file_url",
					width:600
				}					
			]],
			toolbar:'#tb'		
	});  
	
	function search_server_list(childtype, value)
    {
		$.ajax({
			url : 'searchdatafromdb.php',
			type : 'post',
			data : {
				type : 0,
				childtype:childtype,
				value:value
			},
			success : function (data, response, status) {
				// $.messager.progress('close');
				//alert(data);
				//console.log(data);
				if(data == 1)
				{
					$.messager.alert(L('common_2'),L('common_1'),'error');
				}
				else
				{
					$.messager.show({
					title:L('clientlogsearch_js_5'),
					msg:L('clientlogsearch_js_6')
					});
					var dataarr = eval('(' + data + ')');
					$('#loginfobox').datagrid({
								data : dataarr
					}); 
				}			
			}
		});
	}	
	 
	 $('#manager_add').dialog({
		width : 400,
		title : L('serverslist_js_26'),
		modal : true,
		closed : true,
		iconCls : 'icon-user-add',
		buttons : [{
			text : L('serverslist_js_27'),
			iconCls : 'icon-add-new',
			handler : function () {
				//alert($('#id').val());
				 if ($('#manager_add').form('validate')) {
					 
					if (operateType == 1)
					{
						$.ajax({
							url : 'insertdatatodb.php',
							type : 'post',
							data : {
								type : 6,
								id : $('#id').val(), 
								show_id : $('#show_id').val(),
								name : $('#name').val(), 
								att_url : $('#att_url').val() 
							},
							success : function (data, response, status) {
								//alert(data)
								if (data == 0) {
									$('#manager_add').dialog('close');
									search_server_list(6, 0);
									
									 
								}
								else if(data == 1)
								{
									$.messager.alert(L('serverslist_js_30'), L('common_no_privilege'), 'warning');
								}
								else if(data == 2)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_32'), 'warning');
								}
								else if(data == 3)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_33'), 'warning');
								}
								else if(data == 4)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_31'), 'warning');
								}
							}
						}); 
					}
					else if(operateType == 2)
					{
						$.ajax({
							url : 'updatedatatodb.php',
							type : 'post',
							data : {
								type    : 6,
								id : $('#id').val(), 
								show_id : $('#show_id').val(),
								name : $('#name').val(), 
								att_url : $('#att_url').val() 
							},

							success : function (data, response, status) {
								
								if (data == 0) {
									
									var rowsarr = $('#loginfobox').datagrid('getSelections');

									var rowindex = $('#loginfobox').datagrid('getRowIndex',rowsarr[0]);
									
									$('#loginfobox').datagrid('updateRow',{
										index : rowindex,
										row : {
											id : $('#id').val(), 
											show_id : $('#show_id').val(),
											name : $('#name').val(),
											 
											att_url : $('#att_url').val() 
										}

									});
									
									$.messager.show({
										title : L('serverslist_js_28'),
										msg : L('serverslist_js_39')
									});
									$('#manager_add').dialog('close');
									$('#loginfobox').datagrid('reload');
									
									
									 
									
								}
								else if(data == 1)
								{
									$.messager.alert(L('serverslist_js_30'), L('common_no_privilege'), 'warning');
								}
								else if(data == 2)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_32'), 'warning');
								}
								else if(data == 3)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_33'), 'warning');
								}
								else if(data == 4)
								{
									$.messager.alert(L('serverslist_js_30'), L('serverslist_js_31'), 'warning');
								}
							}
						});
					
					 
					}
				} 
			}
		},
		{
			text : L('serverslist_js_37'),
			iconCls : 'icon-redo',
			handler : function () {
				$.messager.confirm(L('serverslist_js_34'),L('serverslist_js_35'),function(r){
					if(r){
						$('#manager_add').dialog('close').form('reset');
					}
				});
			}
		}]
	});
		
	function delSingleDataFromDB(obj,rows){
		//alert(obj);
		$.ajax({
			url : 'deldatafromdb.php',
			type : 'post',
			data : {
				serverids : obj,
				type : 0
			},
			success : function(data,response,status){
				//alert(data);
				if(data == 0)
				{
					// 从表中删除数据

					for(var i = 0; i < rows.length; i ++)
					{
						var row = $('#loginfobox').datagrid('getRowIndex',rows[i]);
						$('#loginfobox').datagrid('deleteRow',row);
					}
					$.messager.show({
						title : L('serverslist_js_28'),
						msg : L('serverslist_js_42')
					});
				}
				else
				{
					// 提示失败
					$.messager.alert(L('serverslist_js_28'),L('serverslist_js_43'),'info');
				}
			}
		});
	}
	
	 $('#addsingle').click(function()
	 {
		operateType = 1;
		
		//$('#id').numberbox('enable');
		$('#show_id').numberbox('enable');
		
		$('#manager_add').dialog('open').form('reset');
	//	$('#channel').combotree('setValues',[0]);
		
		$('#manager_add').dialog('center');
		$('#manager_add').focus();
	 });
	
	$('#updatesingle').click(function(){
		//alert("updatesingle");
		var index = $('#loginfobox').datagrid('getSelections');
		if(index.length != 0 )
		{
			if(index.length > 1)
			{
				$.messager.alert(L('serverslist_js_28'),L('serverslist_js_44'),'info');
			}
			else
			{
				$('#id').numberbox('setValue',index[0].id);
				$('#id').numberbox('disable');
				
				//$('#cur_id').numberbox('setValue',index[0].cur_id);
				$('#show_id').numberbox('setValue',index[0].show_id);
				//$('#show_id').numberbox('disable');
				
				$('#name').val(index[0].name);
				 
				$('#att_url').val(index[0].att_url);
				 
				operateType = 2;
				$('#manager_add').dialog('open');
				$('#manager_add').dialog('center');
				$('#manager_add').focus();
			}
		}
		else
		{
			$.messager.alert(L('serverslist_js_28'),L('serverslist_js_45'),'info');
		}
	});
	
	 $('#delsingle').click(function(){
		var index = $('#loginfobox').datagrid('getSelections');
		if(index.length != 0 )
		{
			var jsondata = "";
			for(var i = 0; i < index.length; i ++)
			{
				jsondata += index[i].id;
				jsondata += ',';
			}
			
			jsondata = jsondata.substr(0,jsondata.length - 1);
			
			$.messager.confirm(L('serverslist_js_34'),L('serverslist_js_46'),function(r){
					if(r){
						delSingleDataFromDB(jsondata,index);
					}
			});
		}
		else
		{
			$.messager.alert(L('serverslist_js_28'),L('serverslist_js_45'),'info');
		}
	});
	
	$('#update').click(function(){
		search_server_list(6, 0);  
	});	

	$('#create_static').click(function(){
		$.messager.confirm(L('serverslist_js_34'),L('serverslist_js_49'),function(r){
			if(r){
				$.ajax({
					url : 'create_server_list.php',
					type : 'get',
					data : {
						version : 'all'
					},
					
					beforeSend : function () {
						$.messager.progress({
							text : L('serverslist_js_47')
						});
					},
						
					success : function (data, response, status) {
						$.messager.progress('close');
						var dataarr = eval('(' + data + ')');
						var ret = L('serverslist_js_50')
						if (dataarr.status != "ok")
						{
							ret = dataarr.status;
						}
						$.messager.show({
							title:L('serverslist_js_28'),
							msg:ret
						}); 	
					}
				});
			}
		});
	});
	
	add_dialog_jy();
	search_server_list(7, 0);
});