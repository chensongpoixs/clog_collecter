var default_anguage = "zhCN";

var dict = {};

$(function() {
	registerWords();
	var lang = getCookie("lang");
	if(lang == null)
	{
		lang = default_anguage;
	}
	
	setLanguage(lang);
});


function L(lang)
{
	return dict[lang] || lang;
}

function setLanguage(lang) {
	delCookie(lang);
	setCookie("lang", lang);
	setCookie("path", "lang/");
	translate();
}

function translate() {
	loadDict();
	
	$("[lang]").each(function() {
		switch (this.tagName.toLowerCase()) {
			case "input":
				$(this).val( __tr($(this).attr("lang")) );
				break;
			default:
				$(this).text( __tr($(this).attr("lang")) );
		}
	});
}

function __tr(src) {
	return (dict[src] || src);
}

function loadDict() {
	var path = getCookie("path");
	var lang = (getCookie("lang") || default_anguage);

	$.ajax({
		async: false,
		type: "GET",
		url: path + lang + ".json",
		success: function(msg) {
			dict = msg;
		}
	});
}

function registerWords() {
	/*$("[lang]").each(function() {
		$(this).html(lang_dict[$(this).html()] || $(this).html());
	});*/
	
	$("[lang]").each(function() {
		switch (this.tagName.toLowerCase()) {
			case "input":
				$(this).attr("lang", $(this).val());
				break;
			default:
				$(this).attr("lang", $(this).text());
		}
	});
}

function setCookie(name,value) 
{ 
    var Days = 30; 
    var exp = new Date(); 
    exp.setTime(exp.getTime() + Days*24*60*60*1000); 
    document.cookie = name + "="+ escape (value) + ";expires=" + exp.toGMTString(); 
} 

//读取cookies 
function getCookie(name) 
{ 
    var arr,reg=new RegExp("(^| )"+name+"=([^;]*)(;|$)");
 
    if(arr=document.cookie.match(reg))
        return unescape(arr[2]); 
    else 
        return null; 
} 

//删除cookies 
function delCookie(name) 
{ 
    var exp = new Date(); 
    exp.setTime(exp.getTime() - 1); 
    var cval=getCookie(name); 
    if(cval!=null) 
	{
		document.cookie= name + "="+cval+";expires="+exp.toGMTString(); 
	}
}



$('#lang_select').combobox({
	panelHeight:50,
	editable:false,
	valueField:'value',
	textField:'text',
	data:[
		{
			value:'zhCN',
			text:L('简体中文'),
			"selected":true  
		},{
			value:'zhTW',
			text:L('繁体中文')
		}
	],
	onSelect:function(record){
		setLanguage(record.value);
	}
});






