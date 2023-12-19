<?php
	session_start();
	
	require_once('./db_base.php');
	
	class ERetult
	{
	  const ER_SUCCESS  					= 0;
	  const ER_DB_ERROR  					= 1;
	  const ER_ARGS_ERROR   				= 2;
	  const ER_ACCOUNT_INVAILD				= 3; 
	  const ER_CREATE_REGISTER_INFO_ERROR 	= 4;
	  const ER_GET_SERVER_LIST_ERROR 		= 5;
	  const ER_PASSWORD_INVAILD				= 6;
	  const ER_UPDATE_KEY_ERROR				= 7;
	  const ER_SERVER_LIST_EMPTY			= 8;
	  const ER_ACCOUNT_EXIST				= 9;
	  const ER_PASSWORD_TOO_SHORT			= 10;
	  const ER_GET_BILLBORD_ERROR			= 11;
	  const ER_VERSION_ERROR				= 12;
	  const ER_GET_GM_ERROR					= 13;
	  const ER_GET_ROLE_SEVER_ERROR			= 14;
	  const ER_VERSION_NOT_EXIST			= 15;
	  const ER_QUERY_SERVER_INFO_ERROR		= 16;
	  const ER_WRITE_FILE_ERROR				= 17;
	}
	
	function has_login()
	{	
		if (!isset($_SESSION['admin']) || $_SESSION['admin'] == NULL || $_SESSION['admin'] == '')
		{
			return false;
		}
		return true;
	}
	
	function has_privilege($pri)
	{	
		if (!isset($_SESSION['admin']) || $_SESSION['admin'] == NULL || $_SESSION['admin'] == '')
		{
			return false;
		}
		if($_SESSION['admin'] == 'admin')
		{
			return true;
		}
		return in_array($pri, $_SESSION['pri']);
	}
	
	function has_priv_prefix($pri)
	{	
		if (!isset($_SESSION['admin']) || $_SESSION['admin'] == NULL || $_SESSION['admin'] == '')
		{
			return false;
		} 
		if($_SESSION['admin'] == 'admin')
		{ 
			return true;
		} 
		$pri_str = strval($pri);
		$pri_len = strlen($pri_str);
		$privs = $_SESSION['pri'];
		$count = count($privs);
		for($i = 0; $i < $count; ++$i)
		{
			if($pri == $privs[$i])
			{
				return true;
			}
			$str = strval($privs[$i]);
			$len = strlen($str);
			if($pri_len >= $len)
			{
				continue;
			}
			if(strncmp($pri_str, $str, $pri_len) == 0)
			{
				return true;
			}
		} 
		return false;
	}
	
	function DEBUG($str)
	{
		error_log(date("[Y-m-d H:i:s]")." [".$_SERVER['REQUEST_URI']."] : ".$str."\n", 3, "./debug.log");
	}
	
	function log_manager($db, $type, $str)
	{
		$account = $_SESSION['admin'];
		if($db != NULL)
		{
			$note = $db->real_escape_string($str);
			$result = $db->query("insert into `t_manage_log` (`account`,`type`,`note`) values ('$account','$type', '$note')");
			if(!$result)
			{
				DEBUG($db->error);
			}
		}
		else
		{
			$tmp_db = get_global_db();
			if($tmp_db == NULL)
			{
				DEBUG('get_global_db failed');
				return;
			}
			$note = $tmp_db->real_escape_string($str);
			$result = $tmp_db->query("insert into `t_manage_log` (`account`,`type`,`note`) values ('$account','$type', '$note')");
			if(!$result)
			{
				DEBUG($tmp_db->error);
			}
			$tmp_db->close();
		}
	}
	
	function get_log_str($params)
	{
		$arg='';
		$i = 0;
		foreach($params as $key=>$value){
			if($key == 'type' || $key == 'childtype')
			{
				continue;
			}
			if ($i != 0)
			{
				$arg .= ',';
			}
			if(is_array($value))
			{
				$arg.= $key . '=' . implode('|',$value);
			}
			else
			{
				$arg.= $key . '=' . $value;
			}
			++$i;
		}
		return $arg;
	}
	
	
	function get_log_client_type($client_type)
	{
		//0 未知客户端 1: 3D  2: Rte
		switch($client_type)
		{
			case 0:
			{
				return "未知客户端";
			}
			break;
			case 1:
			{
				return "3D";
			}
			break;
			case 2:
			{
				return "Rte";
			}
			break;
		}
		return "未知客户端";
	}
?>