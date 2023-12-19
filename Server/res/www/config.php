<?php

header('Content-Type:text/html; charset=utf-8');
header('Access-Control-Allow-Origin:*');
// gm进程端口
$gm_port = 9800;
// gm进程ip
$gm_ip = '127.0.0.1';
// gm msg id
$gm_msg_id = 4109;

// global库
$global_db_config = [
    "host" => "localhost",
    "username" => "root",
	"passwd" => "",
	"dbname"  => "cloud_render_global_table",
	"port" => "3308",
];


// global库
$global_log_db_config = [
    "host" => "localhost",
    "username" => "root",
	"passwd" => "",
	"dbname"  => "global_log",
	"port" => "3308",
];

 // cloud_render_


$log_collector_url_prefix = "http://192.168.1.133:10001/log_collector/";

$name = "gm工具名称";

class EPrivilege
{
  const EP_Manager  			= 1; // 管理员
  const EP_ModifyUser  			= 2; // 修改数据
  const EP_User   				= 3; // 查看数据
  const EP_Guest   				= 4;
}

define('BASE_TIME', '946598400');

//socket connect error 13 Permission denied  'setsebool -P httpd_can_network_connect=1'
?>