<?php

	require_once('../config.php');
	
	function get_db($tmp_config)
	{
		$tmp_db = @new mysqli($tmp_config["host"], $tmp_config["username"], $tmp_config["passwd"], $tmp_config["dbname"], $tmp_config["port"]);
		if ($tmp_db->connect_errno)
		{
			return NULL;
		}
		$tmp_db->query("set names 'utf8'");
		return $tmp_db;
	}
	
	function get_login_db()
	{
		global $login_db_config;
		return get_db($login_db_config);
	}
	
	function get_global_db()
	{
		global $global_db_config;
		return get_db($global_db_config);
	}
	function get_global_log_db()
	{
		global $global_log_db_config;
		return get_db($global_log_db_config);
	}

?>