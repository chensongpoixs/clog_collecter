<?php

	if(!isset($_POST['manager']) || $_POST['manager'] == NULL || !isset($_POST['password']))
	{
		echo 1; //'invalid para';
		exit();
	}
	
	session_start();
	if (isset($_SESSION['admin'])) {
		$_SESSION['admin'] = '';
		$_SESSION['pri'] = array();
	}
	
	require_once('./db_base.php');
	
	$db = get_global_db();
	if($db == NULL)
	{
		echo 2; //"db error";
		exit();
	}

	$manager = $db->real_escape_string($_POST['manager']);
	
	// 查询账号数据
	$result = $db->query("SELECT `password`,`privilege`,`login_times`,`realname` FROM `t_admin` WHERE `account`='$manager'");
	//$db->close();
	if ($result == false)
	{
		$db->close();
		echo 2; //select failed
		exit();
	}
	
	$row = $result->fetch_assoc();
	$result->close();
	if (!$row)
	{
		$db->close();
		echo 3; //invalid account
		exit();
	}
	
	$password = '';
	
	if($_POST['password'] != NULL)
	{
		$password = md5($_POST['password']);
	}
	
	if ($row['password'] != $password)
	{
		$db->close();
		echo 4; //invalid password
		exit();
	}
	
	$_SESSION['admin'] = $manager;
	$_SESSION['pri'] = explode('|', $row['privilege']);
	$_SESSION['admin_name'] = $row['realname'];
	
	$db->query("UPDATE `t_admin` SET `last_time`=now(),`last_ip`='".get_ip()."',`login_times`=" . $row['login_times'] . "+1 WHERE `account`='$manager' ");
	$db->query("insert into `t_manage_log` (`account`,`type`,`note`) values ('$manager','login', 'login')");
	
	$db->close();
	echo 0;	
?>

<?php
function get_ip()
{
	if (getenv("HTTP_CLIENT_IP"))
	{
		$ip = getenv("HTTP_CLIENT_IP");
	}
	else if(getenv("HTTP_X_FORWARDED_FOR"))
	{
		$ip = getenv("HTTP_X_FORWARDED_FOR");
	}
	else if(getenv("REMOTE_ADDR"))
	{
		$ip = getenv("REMOTE_ADDR");
	}
	else 
	{
		$ip = "unknow";
	}
	return $ip;
}
?>