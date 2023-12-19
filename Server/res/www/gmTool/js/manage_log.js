$(function(){
	$(window).resize(function(){  
		$("#log_table").datagrid({
			width: $(window).width() - 100,
			height: $(window).height() - 100
		});                
    });
	
	$('#log_table').datagrid({
		url:'searchdatafromdb.php',
		queryParams:{
			type:21,
			childtype:0,
			value:0
		},
		columns:[[
		{
			title:L('manager_log_js_0'),
			field:'account',
			width:80
		},{
			title:L('manager_log_js_2'),
			field:'time',
			width:130
		},{
			title:L('manager_log_js_1'),
			field:'type',
			width:130
		},{
			title:L('manager_log_js_3'),
			field:'note',
			width:500
		}
		]],
		toolbar:'#tb',
		pagination:true,
		pageNumber:1,
		rownumbers:true,
		pageSize:10,
		pageList: [10, 20, 50, 100, 150, 200],
		pagePosition:'top',
		onLoadError:function(XMLHttpRequest, textStatus, errorThrown){
			alert(JSON.stringify(XMLHttpRequest));
			alert(textStatus);
			alert(errorThrown);
		}
	}); 
	
	$('#sss').searchbox({ 
		width:200, 
		searcher:function(value,name){
			if(name == "account")
			{
				$('#log_table').datagrid({
				url:'searchdatafromdb.php',
				queryParams:{
					type:21,
					childtype:1,
					value:value
				}});
			}
			else if(name == "type")
			{
				$('#log_table').datagrid({
					url:'searchdatafromdb.php',
					queryParams:{
						type:21,
						childtype:2,
						value:value
					}
				});	
			}	
		}, 
		menu:'#mmm', 
		prompt:'Please Input Value' 
	}); 

	// $('#log_table').datagrid({
				// url:'searchdatafromdb.php',
				// queryParams:{
					// type:21,
					// childtype:0
				// }});
});