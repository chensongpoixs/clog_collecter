
$('#server').combotree({
    url:'searchdatafromdb.php',
	required:true,
	multiple: true,
    valueField:'id',
    textField:'text',
	queryParams:{
	type:100
	},
	onCheck:function(node, checked)
	{
		onCheckChannel($('#server'), node, checked);
	}
});

$('#channel').combotree({
	required:true,
	multiple:true,
	readOnly:true,
	data:g_channel,
	value : 0,
	onCheck:function(node, checked)
	{
		onCheckChannel($('#channel'), node, checked);
	}
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



function get_cch_select()
{
	var channel_data = $('#channel').combotree('getValues');
	var sql_channel="";
	if(channel_data!="")
	{
		if(channel_data!=0)
		{
			sql_channel = " in(" + channel_data + ") ";
		}
	}
	return sql_channel;
}

function get_ser_select()
{
	var server_data = $('#server').combotree('getValues');
	var sql_server="";
	if(server_data!="")
	{
		if(server_data!=0)
		{
			sql_server = " in(" + server_data + ") ";
		}
	}
	return sql_server;
}

function get_now_time()
{
	 var date = new Date();

	var seperator1 = "-";

	var seperator2 = ":";

	var month = date.getMonth() + 1;

	var strDate = date.getDate();

	if (month >= 1 && month <= 9) {

		month = "0" + month;

	}

	if (strDate >= 0 && strDate <= 9) {

		strDate = "0" + strDate;

	}

	var currentdate = date.getFullYear() + seperator1 + month + seperator1 + strDate;

	return currentdate;
}
function get_month_time()
{
	 var date = new Date();

	var seperator1 = "-";

	var seperator2 = ":";

	var month = date.getMonth() + 1;

	var strDate = 1;

	if (month >= 1 && month <= 9) {

		month = "0" + month;

	}
	var currentdate = date.getFullYear() + seperator1 + month + seperator1 + strDate;

	return currentdate;
}

function get_now_time_ex()
{
	 var date = new Date();

	var seperator1 = "-";

	var seperator2 = ":";

	var month = date.getMonth() + 1;

	var strDate = date.getDate();

	if (month >= 1 && month <= 9) {

		month = "0" + month;

	}

	if (strDate >= 0 && strDate <= 9) {

		strDate = "0" + strDate;

	}

	var currentdate = date.getFullYear() + seperator1 + month + seperator1 + strDate

			+ " " + date.getHours() + seperator2 + date.getMinutes()

			+ seperator2 + date.getSeconds();

	return currentdate;
}

function get_now_time_min()
{
	 var date = new Date();

	var seperator1 = "-";

	var seperator2 = ":";

	var month = date.getMonth() + 1;

	var strDate = date.getDate();

	if (month >= 1 && month <= 9) {

		month = "0" + month;

	}

	if (strDate >= 0 && strDate <= 9) {

		strDate = "0" + strDate;

	}

	var currentdate = date.getFullYear() + seperator1 + month + seperator1 + strDate + " " + date.getHours()+ seperator2 + date.getMinutes();

	return currentdate;
}
