<?php
	require_once('./header.php');
	require_once('./notice_gm.php');

	$ntype = $_POST['type'];
	$db = get_global_db();
	
	if($db == NULL)
	{
		echo "db error !";
		exit();
	}
	
	//echo $ntype
	switch($ntype)
	{
		case 0:
		{
			if(!has_privilege(4013))
			{
				echo 1;
				break;
			}
			
			$serverids = $_POST['serverids'];

			//echo $serverids;
			 $result = $db->query("DELETE  FROM t_app_render_info where `id` in ($serverids)",MYSQLI_STORE_RESULT);
			if($result  == true)
			{
				log_manager($db, "remove_server", get_log_str($_POST));
				echo 0;
			}
			else
			{
				echo 1;
			}
		}
		break;
		case 1:
		{	// billborad
			if(!has_privilege(4003))
			{
				echo 1;
				break;
			}
			$ids = $_POST['ids'];
			$result = $db->query("DELETE FROM `t_billboard`  WHERE `id` IN ($ids)",MYSQLI_STORE_RESULT);
			if($result  == true)
			{
				log_manager($db, "remove_billboard", get_log_str($_POST));
				echo 0;
			}
			else
			{
				echo 1;
			}
			//$result->close();
		}
		break;
		case 2:
		{	// 滚动公告
			if(!has_privilege(4003))
			{
				echo 1;
				break;
			}
			$ids = $_POST['ids'];
			$result = $db->query("DELETE FROM `t_system_event`  WHERE `id` IN ($ids)",MYSQLI_STORE_RESULT);
			if(!$result)
			{
				echo 2;
				break;
			}
			log_manager($db, "remove_system_event", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "system_event";
			$arr_w2gm['op'] = 'del';
			$arr_w2gm['id'] = strval($ids);
			
			$temp = pack_msg(json_encode($arr_w2gm));
			
			if(strcmp($temp['status'],"ok") != 0)
			{
				echo 3;
				break;
			}
			echo 0;
		}
		break;
		case 5:
		{	// activation
			if(!has_privilege(4023))
			{
				echo 1;
				break;
			}
			$childtype = $_POST['childtype'];
			$activationid = $_POST['activation_id'];
			//echo "delete from `activationcode` where `id`='$activationid'";
			$result = $db->query("delete from `t_activationcode` where `id` in ($activationid)");
			
			if(!result)
			{
				echo 2;
				break;
			}
			
			$result = $db->query("delete from `t_activationinfo` where `id` in ($activationid)");
			if($result == false){
				echo 1;
				break;
			}
			
			log_manager($db, "remove_code", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "activation";
			$arr_w2gm['op'] = 'del';
			$arr_w2gm['id'] = strval($activationid);
			
			$temp = pack_msg(json_encode($arr_w2gm));
			if(strcmp($temp['status'],"ok") == 0)
			{
				echo 0;
			}
			else
			{
				echo json_encode($temp);
			}
		}
		break;
		case 7:
		{	// mail manager
			if(!has_privilege(4033))
			{
				echo 1;
				break;
			}
			$childtype = $_POST['childtype'];
			$mail_ids     = $_POST['mail_ids'];
			
			$result = $db->query("select `status` from `t_mail` where `id` in ($mail_ids)");
			if($result == false){
				echo 2;
				break;
			}
			
			$flag_stop = false;
			while($row = $result->fetch_array(MYSQLI_NUM))
			{
				if($row[0] == '1')
				{
					//已发送的邮件不能删除
					$flag_stop = true;
					break;
				}
			}
			if($flag_stop)
			{
				//已发送的邮件不能删除
				echo 3;
				break;
			}
			
			$result = $db->query("delete from `t_mail` where `id` in ($mail_ids)");
			if(!$result)
			{
				echo 2;
				break;
			}
			
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			log_manager($db, "remove_mail", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "mail";
			$arr_w2gm['op'] = 'del';
			$arr_w2gm['id'] = strval($mail_ids);
			
			$temp = pack_msg(json_encode($arr_w2gm));
					
			if(strcmp($temp['status'],"ok") != 0)
			{
				echo 4;
				break;
			}
			echo 0;
		}
		break;
        case 10:
      	{	// activity manager
			if(!has_privilege(4043))
			{
				echo 1;
				break;
			}
			
      		$childtype = $_POST['childtype'];
      		$activity_ids = $_POST['activity_ids'];

      		$result = $db->query("delete from `t_activity` where `id` = $activity_ids");
      		if(!$result){
      			echo 1;
				break;
      		}
      		
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			log_manager($db, "remove_activity", get_log_str($_POST));
		
      		$arr_w2gm = array();
      		$arr_w2gm['cmd']="activity";
            $arr_w2gm['op'] = 'del';
            $arr_w2gm['id'] = strval($activity_ids);

      		$temp = pack_msg(json_encode($arr_w2gm));

      		if(strcmp($temp['status'],"ok") == 0)
      		{
      			echo 0;
      			//echo 0;
      		}
      		else
      		{
      			echo json_encode($temp);
      		}
      	}
		break;
		case 20:
		{	//账号信息
			if(!has_privilege(5003))
			{
				echo 1;
				break;
			}
			
			$account     = $_POST['account'];			
			if($account == 'admin')
			{
				echo 1; //不能删除admin
				break;
			}
			if($_SESSION['admin'] == $account)
			{
				echo 1; //不能删除自己
				break;
			}
			
			$result = $db->query("delete from `t_admin` where `account` = '$account'");
			if(!$result){
      			echo 1;
				break;
      		}
      		
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			log_manager($db, "remove_account", get_log_str($_POST));
			echo 0;
		}
		break;
		case 22:
		{	//角色封禁信息
			if(!has_privilege(3003))
			{
				echo 1;
				break;
			}
			
			$player_ids     = $_POST['player_ids'];
			$result = $db->query("delete from `t_player_ban` where `player_id` IN ($player_ids)");
			if($result == false){
				echo 2;
				break;
			}
			
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			
			log_manager($db, "remove_ban_player", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="player_ban";
			$arr_w2gm['op']='del';
			$arr_w2gm['player_id'] = intval($player_ids);

			$temp = pack_msg(json_encode($arr_w2gm));

			if(strcmp($temp['status'],"ok") == 0)
			{
				echo 0;
			}
			else
			{
				echo 4;
			}
		}
		break;
		case 23:
		{	//IP封禁信息
			if(!has_privilege(3022))
			{
				echo 1;
				break;
			}
			$ip_array     = $_POST['ips'];
			$ips = '';
			for($i = 0; $i < count($ip_array); ++$i)
			{
				if($i != 0)
				{
					$ips .= ',';
				}
				$ips = $ips . "'" . mysql_escape_string($ip_array[$i]) . "'";
			}
			$sql = "delete from `t_ip_ban` where `ip` IN ($ips)";
			$result = $db->query($sql);
			//DEBUG($sql);
			if($result == false){
				echo 2;
				break;
			}
			log_manager(NULL, "remove_ban_ip", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="ip_ban";
			$arr_w2gm['op']='del';
			$arr_w2gm['ip'] = $ips;

			$temp = pack_msg(json_encode($arr_w2gm));

			if(strcmp($temp['status'],"ok") == 0)
			{
				echo 0;
			}
			else
			{
				echo 4;
			}
		}
		break;
		case 24:
		{	//账号封禁信息
			if(!has_privilege(3013))
			{
				echo 1;
				break;
			}
			
			$open_ids     = $_POST['open_ids'];
			$result = $db->query("delete from `t_account_ban` where `open_id` IN ($open_ids)");
			if($result == false){
				echo 2;
				break;
			}
			
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			
			log_manager($db, "remove_ban_account", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="account_ban";
			$arr_w2gm['op']='del';
			$arr_w2gm['open_id'] = intval($open_ids);

			$temp = pack_msg(json_encode($arr_w2gm));

			if(strcmp($temp['status'],"ok") == 0)
			{
				echo 0;
			}
			else
			{
				echo 4;
			}
		}
		break;
	}
	$db->close();
?>