<?php

header('Content-Type:text/html; charset=utf-8');

// gm进程端口
$gm_port = 9803;
// gm进程ip
$gm_ip = '127.0.0.1';
// gm msg id
$gm_msg_id = 4109;

// global库
$global_db_config = [
    "host" => "localhost",
    "username" => "root",
	"passwd" => "",
	"dbname"  => "global_table",
	"port" => "3306",
];

 


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