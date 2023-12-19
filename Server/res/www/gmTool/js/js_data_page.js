$(function(){
	
	// 数据库的 增删改查 操作
	var operateType = undefined;
	var filter_name = undefined;
	var filter_value = undefined;
	
	$(window).resize(function(){  
		$("#data_list").datagrid({  
			width: $(window).width(),
			height: $(window).height()
		});                
    });
	
	var m_data_names = [
		{
			id: 'channel',
			text: L('js_data_page_js_3')
		},{
			id: 'item',
			text: L('js_data_page_js_4')
		},{
			id: 'hero',
			text: L('js_data_page_js_5')
		}
	];
	
	//校验
	function init_check()
	{
		$('#js_data_page_data_name').combobox({
			width:70,
			panelHeight:100,
			valueField:'id',
			textField:'text',
			readOnly:true,
			editable:false,
			data:m_data_names,
			onSelect:function(record){
				fill_data_list(record.id);
			}
		});
		
		$('#ip').validatebox({
			required:true,
			missingMessage:L('js_data_page_js_0'),
			invalidMessage:L('js_data_page_js_0')
		});
	}
	
	function init_data_grid()
	{	
		$('#data_list').datagrid({
			//width : 1250,
			//height:700,
			//fitColumns:true,
			singleSelect:false,
			fit:true,
			data:[],
			//sortName:'id',
			//sortOrder:'desc',
			columns : [[
				{
					title : 'id',
					field : "id",
					width:150
				},{
					title : L('common_name'),
					field : "text",
					width:150
				}
			]],
			toolbar:'#tb',
			rownumbers:true,
			onLoadError:function(){
				alert('error');
			}
			
		}); 		
	}
	
	function init_dialog()
	{
		$('#js_data_import_dialog').dialog({
			title:L(''),
			width:400,
			closed:true,
			modal:true,
			onOpen:function(){
				$('#js_data_import_result').val('');
			}
		});
	}
		
	function fill_data_list(name)
	{
		filter_name = undefined;
		if(name == 'channel'){
			$('#data_list').datagrid('loadData', {total:g_channel.length, rows:g_channel});
		}
		else if(name == 'item'){
			$('#data_list').datagrid('loadData', {total:g_items.length, rows:g_items});
		}
		else if(name == 'hero'){
			$('#data_list').datagrid('loadData', {total:g_heros.length, rows:g_heros});
		}
		
	}
		
	function refresh_data()
	{
		var data_name = $('#js_data_page_data_name').combobox('getValue');
		fill_data_list(data_name);
	}
	
	function init_btn()
	{	
		$('#addsingle').click(function(){
			
			var title = L('js_data_page_php_1') + $('#js_data_page_data_name').combobox('getText');
			
			$('#js_data_import_dialog').panel({title: title});
			
			$('#js_data_import_dialog').dialog('open').form('reset');
			$('#js_data_import_dialog').dialog('center');
			$('#js_data_import_dialog').focus();
		});
		
		$('#update').click(function(){
			refresh_data();
		});
		
		$('#js_data_import_btn').uploadify({
			//'width':200,
			'height':20,
            'swf': 'easyui/uploadify.swf', 
            'buttonText': L('js_data_page_js_6'),      
            'uploader': 'import_js_data.php',                     
            'queueID': 'fileQueue',                    
            'queueSizeLimit': 1,                        
            'auto': false,                                
            'multi': false,                                 
            'removeCompleted': true,                     
            'fileSizeLimit': '2MB',                      
            'fileTypeDesc': 'Excel Files',                
            'fileTypeExts': '*.xlsx;', 
			'successTimeout': 10,
			'formData'      : {'id' : 'id', 'name' : 'name', 'start_row' : 4, 'data_name':'item'},
			'onOpen': function (event, queueId, fileObj)
			{
				$('#js_data_import_result').val('');
			},
			'onSelect': function (file)
			{
				var data_name = $('#js_data_page_data_name').combobox('getText');
				if(file.name.search(data_name) == -1)
				{	
					var note = file.name + ' => ' + data_name + '?';
					$.messager.confirm(L('common_confirm'), note, function(r){
						if (r){
							$('#js_data_import_result').val('');
							$('#upload').linkbutton('enable');
						}
						else
						{
							$('#js_data_import_btn').uploadify('cancel', '*', false);
							return false;
						}
					});
				}
				else
				{
					$('#js_data_import_result').val('');
					$('#upload').linkbutton('enable');
				}
			},
			'onUploadStart': function (fileObj)
			{
				var data_name = $('#js_data_page_data_name').combobox('getValue');
				if(data_name == 'channel'){
					var formData = {'id' : '渠道ID', 'name' : '渠道名称', 'start_row' : 2, 'data_name':'channel'};
					$('#js_data_import_btn').uploadify("settings", 'formData', formData);
				}
				else if(data_name == 'item'){
					var formData = {'id' : 'id', 'name' : 'name', 'start_row' : 4, 'data_name':'items'};
					$('#js_data_import_btn').uploadify("settings", 'formData', formData);
				}
				else if(data_name == 'hero'){
					var formData = {'id' : 'id', 'name' : 'name', 'start_row' : 4, 'data_name':'heros'};
					$('#js_data_import_btn').uploadify("settings", 'formData', formData);
				}
				//$('#js_data_import_btn').uploadify("settings", "someOtherKey", 2);
				$('#upload').linkbutton('disable');
			},
            'onUploadError': function (file, errorCode, errorMsg, errorString) {
				if(errorCode != -280)
				{
					//-280 = cancel
					alert('onUploadError' + ' errorCode=' + errorCode + ' errorMsg=' + errorMsg + ' errorString=' + errorString );
				}
				$('#upload').linkbutton('disable');
            },
			'onUploadSuccess': function (file, data, response) {
				if(response == true)
				{
					var js_data = JSON.parse(data);
					if(js_data['err'])
					{
						$('#js_data_import_result').val(js_data['err']);
					}
					else
					{
						var data_name = $('#js_data_page_data_name').combobox('getValue');
						if(data_name == 'channel'){
							g_channel = js_data;
						}
						else if(data_name == 'item'){
							g_items = js_data;
						}
						else if(data_name == 'hero'){
							g_heros = js_data;
						}
						fill_data_list(data_name);
						$('#js_data_import_result').val('load ' + js_data.length);
					}
				}
				else
				{
					$('#js_data_import_result').val(L('mailmanagerpage_js_68'));
				}
				$('#upload').linkbutton('disable');
			}
        });
		
		$('#upload').click(function(){
			$('#js_data_import_btn').uploadify('upload', '*');
		});
	}
		
	function search_data(value,name)
	{
		if(name == '' || value == '')
		{
			refresh_data();
			return;
		}
		
		var data = $('#data_list').datagrid('getData');		
		if(data.total == 0)
		{
			return;
		}
		
		 //过滤数据
		var rows=[];
		var x=0;
		var str = '';
		for (var i = 0; i < data.rows.length; i++) {  
			if(name == 'search_id'){
				str = String(data.rows[i].id);
			}
			else
			{
				str = data.rows[i].text;
			}
			if(str.search(value) == -1)
			{
				continue;
			}
			
			rows[x++]=data.rows[i];
		 }
		 
		$('#data_list').datagrid('loadData', {total:data.total, rows:rows});
	}
	
	//	初始化搜索框
	function initsearchbox()
	{
		$('#js_data_page_menu_searchbox').searchbox({
			width:200,
			height:25,
			searcher:function(value,name){
				search_data(value,name);
			},
			menu:'#js_data_page_menu_item',
			prompt:'Please Input Value'
		});
	}	
	
	
	init_check();
	init_dialog();
	init_data_grid();
	init_btn();
	initsearchbox();
	$('#js_data_page_data_name').combobox('select', 'channel');
	$('#upload').linkbutton('disable');
});