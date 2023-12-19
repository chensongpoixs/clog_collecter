$(function () {
	
	//登录界面
	$('#login').dialog({
		title : L("index_js_0"),
		width : 300,
		height : 180,
		modal : true,
		iconCls : 'icon-login',
		buttons : '#btn'
	});
	
	//管理员帐号验证
	$('#manager').validatebox({
		required : true,
		missingMessage : L('index_js_1'),
		invalidMessage : L('index_js_2')
	});
	
	//管理员密码验证
	$('#password').validatebox({
		required : false,
		validType : 'length[0,30]',
		//missingMessage : L('index_js_3'),
		invalidMessage : L('index_js_4')
	});
	
	//加载时判断验证
	if (!$('#manager').validatebox('isValid')) {
		$('#manager').focus();
	} else if (!$('#password').validatebox('isValid')) {
		$('#password').focus();
	}
	
	
	//单击登录
	$('#btn a').click(function () {
		if (!$('#manager').validatebox('isValid')) {
			$('#manager').focus();
		} else if (!$('#password').validatebox('isValid')) {
			$('#password').focus();
		} else {
			$.ajax({
				url : 'login.php',
				type : 'post',
				data : {
					login:"login",
					manager : $('#manager').val(),
					password : $('#password').val()
				},
				beforeSend : function () {
					$.messager.progress({
						text : L('index_js_5') + "..."
					});
				},
				success : function (data, response, status) {
					
					$.messager.progress('close');
					//alert(data);
					if (data == 0) {
						$.messager.show({
							title:L('index_js_6'),
							msg:L('index_js_7')
						});
						location.href = 'admin.php';
					} 
					else if(data == 1)
					{
						$.messager.alert(L('index_js_8'), L('common_0'), 'error');
					}
					else if(data == 2)
					{
						$.messager.alert(L('index_js_8'), L('common_1'), 'error');
					}
					else if(data == 3)
					{
						$.messager.alert(L('index_js_8'),L('index_js_9'),'warning');
					}
					else if(data == 4)
					{
						$.messager.alert(L('index_js_8'),L('index_js_10'),'warning');
					}
					else
					{
					//	alert(data);
					}
				}
			});
		}
	});
	
});








