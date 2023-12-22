$(function(){
	
	$(window).resize(function(){  
		$("#log_search_box").datagrid({  
			width: 1600,
			height: $(window).height()
		});                
    });
	
	var timestamp = 0;
	var timestamp1 = 0;
	var g_client_type=0; 
	var g_address =""; 
		
	function init()
	{ 
		$('#time').datetimebox({   
					required: true,    
					showSeconds: true,
					width:155,
					readOnly:true,
					editable:false,
					formatter: function(date){ return date.getFullYear()+'-'+(date.getMonth()+1)+'-'+date.getDate()+' '+date.getHours()+":"+date.getMinutes(); }, 
                    parser: function(date){ return new Date(Date.parse(date.replace(/-/g,"/")))}

		});
		$('#time1').datetimebox({  
				required: true,    
				showSeconds: true,
				width:155,
				readOnly:true,
				editable:false,
				formatter: function(date){ return date.getFullYear()+'-'+(date.getMonth()+1)+'-'+date.getDate()+' '+date.getHours()+":"+date.getMinutes(); }, 
                parser: function(date){ return new Date(Date.parse(date.replace(/-/g,"/")))}
		});
		$('#time').datetimebox('setValue',get_month_time());
		$('#time1').datetimebox('setValue',get_now_time_min());
		
		$('#client_type').combotree('loadData',
			[
				{
					id: 0,  
					text:  L('on_log_search_js_11')
				},
				{
					id: 1,  
					text: L('on_log_search_js_12')
				},
				{
					id: 2,  
					text: L('on_log_search_js_13')
				} ,
				{
					id: 3,  
					text: L('on_log_search_js_14')
				} 
				
				
			]
		);
		$('#client_type').combotree('setValue',{ id: 0, text: L('on_log_search_js_11') } );
	}
	init();

	$('#log_search_box').datagrid({
			toolbar:'#tb',
			width: 2000,
			height: $(window).height(),
			rownumbers:true,
			url : 'searchdatafromdb.php',
			queryParams:{
			type:0,
			childtype:0,
			value:0,
			start_time:0,
			end_time:0,
			client_type:0,
			address:""
		    },
			pagination:true,
			pageNumber:1,
			pageList: [5,10, 20, 50, 100, 150, 200],
			pagePosition:'top',
			columns : [[
				{
					title : L('log_search_0'),
					field : "id",
					width:80
				}, 
				{
					title : L('log_search_2'),
					field : "client_type",
					width:80,
					formatter: function(value,row,index){
						return get_client_type(value);
					} 
				},
				{
					title : L('log_search_1'),
					field : "datetime",
					width:150
				},
				{
					title : L('log_search_3'),
					field : "log_url",
					width:600
				}
			]],	
			onBeforeLoad:function(param)
			{
				get_info();
				
				param.type=201;
				param.childtype=7;
				param.value = 0;
				param.start_time=timestamp;
				param.end_time=timestamp1;
				param.client_type=g_client_type;
				param.address=g_address; 
				if(timestamp>timestamp1)
				{
					alert( 'common_time_info' );
					return false;
				}
				//alert('before -->');
				 
			},
			onLoadSuccess : function (data) 
			{
				//alert('load data---->');
				var v = eval(data);
				if(v["ret"]==1)
				{
					alert( 'common_1' );
				}
			},
			onLoadError:function(){
				alert( L('common_data_err') );
		    }
	});  
	
	
	
	function get_info()
	{
		//alert('==============');
		 //var server_empty = true;
		// var channel_empty = true;
		 //sql_server = "";
		 //sql_channel = "";
		 
		//sql_server = get_ser_select();
		//sql_channel = get_cch_select();
		
		var stringTime = $('#time').datetimebox('getValue');
		timestamp = Date.parse(new Date(stringTime));
		timestamp = timestamp / 1000;
		
		var stringTime1 = $('#time1').datetimebox('getValue');
		timestamp1 = Date.parse(new Date(stringTime1));
		timestamp1 = timestamp1 / 1000;
		
		g_client_type = $('#client_type').combotree('getValue');
		if(!(g_client_type>=0))
		{
			g_client_type = 0;
		}
		//alert(g_client_type);
		g_address =  $('#address').val();;
	//	alert("address = " +g_address);
		
		//machine_type = $('#machine_type').val();
		
		//r_order_no=$('#order_id').val();
		//open_id=$('#open_id').val();
		//min_money=$('#money_range1').val();
		//max_money=$('#money_range2').val(); 
	}
	
	function get_client_type(value)
	{
		for(var i=0;i<g_channel.length;i++)
		{
			if(g_channel[i].id==value)
			{
				return g_channel[i].text;
			}
		}
		return L('on_order_detail_js_24');
	}
	
});