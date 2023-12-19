$(function(){
	
	var m_servers = new Array();
	var m_to = '';
	
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

	function add_dialog_jy()
	{
		$('#gm_cmd_cmd').combobox({
			required:true,
			editable:false,
			valueField: 'id',
            textField: 'text',
            data:g_cmds,
			onSelect: function(rec){
				var desc = '';
				var deme = '';
				var to = '';
				for(var i = 0; i < g_cmds.length; i++)
				{
					if(g_cmds[i].id == rec.id)
					{
						desc = g_cmds[i].desc;
						demo = g_cmds[i].demo;
						to = g_cmds[i].to;
						break;
					}
				}
				$('#gm_cmd_desc').val(desc);
				$('#gm_cmd_demo').val(demo);
				$('#gm_cmd_para').val(demo);
				m_to = to;
			}
		});
		
		// 服务器ID
		$('#gm_cmd_server_id').combotree({
			width:150,
			height:22,
			required:true,
			panelHeight:100,
			multiple:false  ,
			separator:',',
			readOnly:false,
			data: m_servers
		});		
	}
	 

	$('#gm_cmd_do').click(function()
	{
		$('#gm_cmd_result').val('');
		//var server_id = $('#gm_cmd_server_id').combotree('getValue');
		var cmd = $('#gm_cmd_cmd').combobox('getValue');
		var para = $('#gm_cmd_para').val();
		console.log('cmd = '+cmd);
		console.log(para);
		$.ajax({
			url : 'send_gm_cmd.php',
			type : 'post',
			data : {
				to : m_to,
				//server_id : server_id,
				cmd : cmd,
				para : para
			},
			success : function (data, response, status) {
				//succ
				//var dataarr = JSON.parse(data);
				$('#gm_cmd_result').val(data["status"]);
			},error : function (XMLHttpRequest, textStatus, errorThrown) {
				alert(textStatus)
			}		
		});
	}
	);
	
	init_servers();
	add_dialog_jy();
});