<?php
header('Content-type: application/json; charset=utf-8');

include_once('../config.php');

error_reporting(0);
//set_time_limit(0);

// 包头结构 2字节(MSG_ID_SIZE) 4字节(CONTENT_SIZE) n字节(json字符串内容)
define('CONTENT_SIZE', '4'); 	// CONTENT_SIZE后边总长度
define('MSG_ID_SIZE', '2');		// 固定值

// 包头总大小6字节
define('PACK_HEAD_SIZE', '6');

// msg_id 定值
define('MSG_ID', '4109');

function CommunicateWithGM($request_str)
{
	$reply = array();
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket === false)
	{
		$reply["status"] = "socket_create error code :".(socket_last_error());
		return $reply;
	}
	DEBUG($GLOBALS['gm_port']);
	// 连接gm服务器
	if (!socket_connect($socket, $GLOBALS['gm_ip'], $GLOBALS['gm_port']))
	{
		$reply["status"] = "socket_connect error code:".(socket_last_error());
		socket_close($socket);
		return $reply;
	}
	
	socket_set_option($socket,SOL_SOCKET,SO_SNDTIMEO,array("sec"=>10, "usec"=>0 ));
	socket_set_option($socket,SOL_SOCKET,SO_RCVTIMEO,array("sec"=>10, "usec"=>0 ));
	
	// 发送消息
	//DEBUG('request_str len=' . strlen($request_str));
	if (!socket_write($socket, $request_str, strlen($request_str)))
	{
		$reply["status"] = "socket_write error code :".(socket_last_error());
		socket_close($socket);
		return $reply;
	}

	// 接收响应
	$server_reply = "";
	$buf = "";
	
	//header
	//DEBUG('recv header begin');
	while(socket_recv($socket, $buf, PACK_HEAD_SIZE, MSG_WAITALL))
	{
		$server_reply .= $buf;
		if(strlen($server_reply) >= PACK_HEAD_SIZE)
		{
			break;
		}
	}
	//DEBUG('recv header end size = ' . strlen($server_reply));	
	if(strlen($server_reply) < PACK_HEAD_SIZE)
	{
		$reply["status"] = "gmserver operate timeout";
		socket_close($socket);
		return $reply;
	}
	
	//content
	$arr = unpack("smsg_id/lcontent_len", $server_reply);
	//DEBUG('recv content begin, content len = ' . $arr["content_len"]);
	while(socket_recv($socket, $buf, $arr["content_len"] + PACK_HEAD_SIZE - strlen($server_reply), MSG_WAITALL))
	{
		$server_reply .= $buf;
		if(strlen($server_reply) >= $arr["content_len"] + PACK_HEAD_SIZE)
		{
			$server_reply = substr($server_reply, PACK_HEAD_SIZE, $arr["content_len"]);
			socket_close($socket);
			return json_decode($server_reply,true);
		}
	}
	
	$reply["status"] = "timeout";	
	socket_close($socket);
	return $reply;
}


 function pack_msg($string)
{
	$len = strlen($string);
	$msg = pack("sl", MSG_ID, $len).$string;

	return CommunicateWithGM($msg);
	 


}
?>