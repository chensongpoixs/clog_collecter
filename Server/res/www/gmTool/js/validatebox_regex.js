//扩展easyui表单的验证


$.extend($.fn.validatebox.defaults.rules, {    
    equals: {    
        validator: function(value,param){    
            return /^([a-z0-9A-Z\u4e00-\u9fa5\uac00-\ud7af]|_){1,128}$/.test(value);    
        },    
        message: 'Field do not match.'   
    }, 
    name: {    
        validator: function(value,param){    
            return /^([a-z0-9A-Z\u4e00-\u9fa5\uac00-\ud7af]|_){1,128}$/.test(value);
        },    
        message: 'Field do not match.'   
    },  	
	jhm: {    
        validator: function(value,param){    
            return /^([a-z0-9A-Z\u4e00-\u9fa5\uac00-\ud7af]|_|\.){1,128}$/.test(value);    
        },    
        message: 'Field do not match.'   
    },  
	nochiness: {    
			validator: function(value,param){    
				return /^([a-z0-9A-Z]|_|\.|-|:|@|#){1,128}$/.test(value);    
			},    
			message: 'Field do not match.'   
	}, 	
	billboradtitle:{
		validator:function(value,param){
			return /^([a-z0-9A-Z\u4e00-\u9fa5\uac00-\ud7af]|_|\.|\[|\]|-|:)*$/.test(value);
		},
		message:'Field do not match.'
	},
	billboradcontext:{
		validator:function(value,param){
			return /^[^`'"]*$/.test(value);
		},
		message:'Field do not match.'
	},
	ipport: {    
		validator: function(value,param){  
			var reg =/^(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9])\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[0-9]):(\d{1,5})$/;
			return reg.test(value);

		},    
		message: 'Field do not match.'   
    },	
	accountid:{
		validator: function(value,param){  
			var reg =/^([a-z]|[A-Z]|[0-9]|\.|@|_|:){1,128}$/;
			return reg.test(value);

		},    
		message: 'Field do not match.'   
	},
	onlynumber:{
		validator: function(value,param){  
			var reg =/^([0-9]){1,20}$/;
			return reg.test(value);

		},    
		message: '请输入1-20位数字'   
	},
	multinumber:{
		validator: function(value,param){  
			var reg =/^([0-9]|,){1,}$/;
			return reg.test(value);

		},    
		message: 'Field do not match.'   
	},
	singleaccount:{
		validator: function(value,param){  
			var reg =/^([a-z]|[A-Z]|[0-9]|@|\.|_|:){1,128}$/;
			return reg.test(value);

		},    
		message: 'Field do not match.'   
	},
	multiaccount:{
		validator: function(value,param){  
			var reg =/^([a-z]|[A-Z]|[0-9]|@|\.|_|,|:){1,}$/;
			return reg.test(value);
		},    
		message: 'Field do not match.'   
	},
	use_code_ten:
	{
        validator: function(value,param){    
            return /^([a-z0-9A-Z]){1,1}$/.test(value);    
        },    
        message: 'Field do not match.'   		
	},
	order_id:{
		validator: function(value,param){  
			var reg =/^([a-z]|[A-Z]|[0-9]|_|-|){1,}$/;
			return reg.test(value);
		},    
		message: 'Field do not match.'   
	}
});  


