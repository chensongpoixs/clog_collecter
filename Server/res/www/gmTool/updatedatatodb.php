<?php
	require_once('./header.php');
	require_once('./notice_gm.php');
	
	$ntype = $_POST['type'];

	$db = get_global_db();
	$log_db = get_global_log_db();
	
	if($db == NULL)
	{
		echo "connect db error";
		exit();
	}	
	if($log_db == NULL)
	{
		echo "connect log db error !!!";
		exit();
	}
	switch($ntype)
	{
		case 0:
		{	// server info
			if(!has_privilege(4012))
			{
				echo 1;
				break;
			}
			$id = $_POST['id'];
			//$cur_id = $_POST['cur_id'];
			$show_id = intval($_POST['show_id']);
			$name =  $_POST['name'] ;
			 
			$att_url =  $_POST['att_url'] ;
			//$open_time = $_POST['open_time'];
			
			 
			
			//echo $new1.$status.$envi.$platform1;
			$sql = "UPDATE `t_app_render_info` SET   `render_name`='$name' ";
			$sql .= ", `render_server_id`='$show_id', `app_url`='$att_url' "; 
			$sql .= " WHERE (`id`='$id')";
			$result = $db->query($sql);
			{
				require_once('./notice_gm.php');
				set_time_limit(300);   // 最大执行时间这里设置300秒 
				$cmd0 = 'cmd_update_render'; 
				$arr_w2gm = array();
				$arr_w2gm['cmd'] = strval($cmd0);
				//$arr_w2gm['server_id'] = intval($_POST['server_id']);
				$arr_w2gm['render_id'] = intval($id);; 
				//DEBUG(json_encode($arr_w2gm));
				$temp = pack_msg(json_encode($arr_w2gm));
				//echo json_encode($temp);
				
			}
			if($result == true)
			{
				log_manager($db, "update_server", get_log_str($_POST));
				echo 0;
			}
			else
			{
				echo 4;
			}
		}
		break;
		case 1:
		{	//公告
			if(!has_privilege(4002))
			{
				echo 1;
				break;
			}
			$id = $_POST['id'];
			
			$channel = $_POST['channel'];
			$start_time = $_POST['start_time'];
			$end_time = $_POST['end_time'];
			$pic = mysql_escape_string($_POST['pic']);
			$url = mysql_escape_string($_POST['url']);
			$note = mysql_escape_string($_POST['note']);
			$board_type = $_POST['board_type'];
			
			$result = $db->query("UPDATE `t_billboard` SET `channel`='$channel', `start_time`='$start_time', `end_time`='$end_time', `pic`='$pic', `url`='$url', `note`='$note', `board_type`=$board_type WHERE `id`='$id'");
			if($result == true)
			{
				log_manager($db, "update_billboard", get_log_str($_POST));
				echo 0;
			}
			else
			{
				//DEBUG($db->error);
				echo 1;
			}
		}
		break;
		case 2:
     	{ // system_event 系统公告
			if(!has_privilege(4062))
			{
				echo 1;
				break;
			}
     		$id = $_POST['id'];
			$server_id = $db->real_escape_string($_POST['server_id']);
			$channel = $db->real_escape_string($_POST['channel']);
			$start_time = strtotime($_POST['start_time']) - BASE_TIME;
			$end_time = strtotime($_POST['end_time']) - BASE_TIME;
			$delay = intval($_POST['delay']);
			$show = intval($_POST['show']);
			$priority = intval($_POST['priority']);
			$note = $db->real_escape_string($_POST['note']);
			
     		$result = $db->query("update `t_system_event` set `server_id`='$server_id',`channel`='$channel',`start_time`='$start_time',`end_time`='$end_time'"
				. ",`delay`='$delay',`show`='$show', `priority`=$priority,`note`='$note'"
				. " where `id`='$id'");

			if(!$result)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "update_system_event", get_log_str($_POST));
						
     		$arr_w2gm = array();
     		$arr_w2gm['cmd'] = "system_event";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($id);

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
		{	// activationinfo
			if(!has_privilege(4022))
			{
				echo 1;
				break;
			}
			$activationid = $_POST['activation_id'];
			$status = $_POST['status'];
			$result = $db->query("update `t_activationinfo` set `status`=$status where `id`=$activationid");
			if($result == false){
				 echo 1;
				 break;
			}
			
			log_manager($db, "update_code", get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "activation";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($activationid);
			$arr_w2gm['status'] = intval($status);
			
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
		case 6:
		{
			if(!has_privilege(4012))
			{
				echo 1;
				break;
			}
			$id = $_POST['id'];
			//$cur_id = $_POST['cur_id'];
			$show_id = intval($_POST['show_id']);
			$name =  $_POST['name'] ;
			 
			$att_url =  $_POST['att_url'] ;
			//$open_time = $_POST['open_time'];
			
			 
			
			//echo $new1.$status.$envi.$platform1;
			$sql = "UPDATE `t_user_log_collector_info` SET `client_type`='$name' ";
			$sql .= ", `log_level`='$show_id', `address`='$att_url' "; 
			$sql .= " WHERE (`id`='$id')";
			$result = $log_db->query($sql);
			{
				//require_once('./notice_gm.php');
				//set_time_limit(300);   // 最大执行时间这里设置300秒 
				//$cmd0 = 'cmd_update_render'; 
				//$arr_w2gm = array();
				//$arr_w2gm['cmd'] = strval($cmd0);
				////$arr_w2gm['server_id'] = intval($_POST['server_id']);
				//$arr_w2gm['render_id'] = intval($id);; 
				////DEBUG(json_encode($arr_w2gm));
				//$temp = pack_msg(json_encode($arr_w2gm));
				//echo json_encode($temp);
				
			}
			if($result == true)
			{
				log_manager($db, "update_server", get_log_str($_POST));
				echo 0;
			}
			else
			{
				echo 4;
			}
		}
		break;
		case 7:
		{	// mail
			if(!has_privilege(4032))
			{
				echo 1;
				break;
			}
			$mail_id = $_POST['mail_id'];
			
			$result = $db->query("select `status` from `t_mail` where `id`='$mail_id'");
			if($result == false){
				echo 2;
				break;
			}
			$row = $result->fetch_array(MYSQLI_NUM);
			if($row && $row[0] == '1')
			{
				//已发送的邮件不能删除
				echo 3;
				break;
			}
			
			$mailtitle = mysql_escape_string($_POST['mailtitle']);
			$mailsender = mysql_escape_string($_POST['mailsender']);
			$mailcontent = mysql_escape_string($_POST['mailcontent']);
			$mailsendtime = $_POST['mailsendtime'];
			$mailstatus = $_POST['mailstatus'];
			//$mailplayerids = $_POST['playerids'];
			//$mailserverids = $_POST['serverids'];
			$affixs = mysql_escape_string($_POST['affixs']);
			$sql = "update `t_mail` set `mail_title`='$mailtitle',`mail_sender`='$mailsender',`mail_content`='$mailcontent',`send_time`='$mailsendtime',`affix`='$affixs',`status`='$mailstatus' where `id`='$mail_id'";
			
			$result = $db->query($sql);
			
			if(!$result)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "update_mail", get_log_str($_POST));
		
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "mail";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($mail_id);
			
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
     	{ // activity
			if(!has_privilege(4042))
			{
				echo 1;
				break;
			}
     		$childtype = $_POST['childtype'];
            $activity_id = $_POST['activity_id'];
			//$activity_type = $_POST['activity_type'];
			$activity_name = mysql_escape_string($_POST['activity_name']);
            $activity_enable = $_POST['activity_enable'];
			$activity_serverids = $_POST['activity_serverids'];
      		$activity_channel = $_POST['activity_channel'];
      		$activity_show_time = $_POST['activity_show_time'];
			$activity_start_time = $_POST['activity_start_time'];
      		$activity_end_time = $_POST['activity_end_time'];      			
      		$activity_disappear_time = $_POST['activity_disappear_time'];
			$activity_image = mysql_escape_string($_POST['activity_image']);
			$activity_desc = mysql_escape_string($_POST['activity_desc']);
			//DEBUG($_POST['activity_data']);
      		$activity_data = mysql_escape_string($_POST['activity_data']);
			//DEBUG($activity_data);
     		$result = $db->query("update `t_activity` set `name`='$activity_name',`enable`='$activity_enable',`server`='$activity_serverids',`channel`='$activity_channel'"
				. ",`show_time`='$activity_show_time',`start_time`='$activity_start_time',`end_time`='$activity_end_time',`disappear_time`='$activity_disappear_time'"
				. ",`image`='$activity_image',`desc`='$activity_desc',`data`='$activity_data' where `id`='$activity_id'");

			if(!$result)
			{
				echo 1;
				break;
			}
			
			log_manager($db, "update_activity", get_log_str($_POST));
			
     		$arr_w2gm = array();
     		$arr_w2gm['cmd'] = "activity";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($activity_id);

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
		case 20:
		{	//账号信息
			$childtype = $_POST['childtype'];
			if($childtype == 0)
			{
				//mod other privilege
				if(!has_privilege(5002))
				{
					echo 'no privilege';
					break;
				}
				$account = $_POST['account'];
				if(!has_privilege(5002))
				{
					echo 'no privilege';
					break;
				}
				if($account == 'admin')
				{
					echo 'no privilege1';
					break;
				}
				
				$privilege = $_POST['privilege'];
				//不能把自己没有的权限赋值给其他人
				if($privilege != '')
				{
					$flag = false;
					$pris = explode('|', $privilege);
					for($i = 0; $i < count($pris); ++$i)
					{
						if(!has_privilege($pris[$i]))
						{
							$flag = true;
							break;
						}
					}
					if($flag)
					{
						echo 4;
						break;
					}
				}
			
				$result = $db->query("update `t_admin` set `privilege` = '$privilege' where `account` = '$account'");
				if(!$result)
				{
					echo 'update error';
					break;
				}
				log_manager($db, "update_account_privilege", get_log_str($_POST));
			}
			else if($childtype == 1)
			{
				//reset other password
				if(!has_privilege(5004))
				{
					echo 'no privilege';
					break;
				}
				$account = $_POST['account'];
				if($account == 'admin')
				{
					echo 'no privilege1';
					break;
				}
				$result = $db->query("update `t_admin` set `password` = '' where `account` = '$account'");
				if(!$result)
				{
					echo 'update error';
					break;
				}
				log_manager($db, "reset_account_password", "account=$account");
			}
			else if($childtype == 2)
			{
				//mod self password
				$account = $_SESSION['admin'];
				$password_src = '';
				if(isset($_POST['password_src']) && $_POST['password_src'] != NULL && $_POST['password_src'] != '')
				{
					$password_src = md5($_POST['password_src']);
				}
				$result = $db->query("SELECT `account` FROM `t_admin` where `account` = '$account' AND `password` = '$password_src'");
				if($result == false)
				{
					echo 'select error';
					break;
				}
				if($result->num_rows == 0)
				{
					$result->close();
					echo 1;
					break;
				}
				$result->close();
				$password_new = md5($_POST['password_new']);
				$result = $db->query("update `t_admin` set `password` = '$password_new' where `account` = '$account'");
				if(!$result)
				{
					echo 'update error';
					break;
				}
				log_manager($db, "mod_account_password", "account=$account");
			}
			else
			{
				echo "unknown type";
			}
			echo 0;
		}
		break;
		case 22:
		{	//角色封禁信息
			if(!has_privilege(3002))
			{
				echo 1;
				break;
			}
			
			$player_id = $_POST['player_id'];
			$server_id = $_POST['server_id'];
			$chat_time = $_POST['chat_time'];
			$ban_time = $_POST['ban_time'];
			
			$result = $db->query("update `t_player_ban` set `chat_time` = '$chat_time', `ban_time` = '$ban_time' where `player_id`='$player_id'");
			if($result == false)
			{
				echo 2;
				break;
			}
			if($db->affected_rows == 0)
			{
				echo 0;
				break;
			}
			
			log_manager($db, "update_ban_player", get_log_str($_POST));
			
			// echo 0;
			// break;
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="player_ban";
			$arr_w2gm['op']='update';
			$arr_w2gm['player_id'] = intval($player_id);
			$arr_w2gm['server_id'] = intval($server_id);
			$arr_w2gm['chat_time'] = strtotime($chat_time);
			$arr_w2gm['ban_time']  = strtotime($ban_time);

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
			if(!has_privilege(3012))
			{
				echo 1;
				break;
			}
			
			$open_id = $_POST['open_id'];
			$ban_time = $_POST['ban_time'];
			
			$result = $db->query("update `t_account_ban` set `ban_time` = '$ban_time' where `open_id`='$open_id'");
			if($result == false)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "update_ban_account", get_log_str($_POST));
			
			// echo 0;
			// break;
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="account_ban";
			$arr_w2gm['op']='update';
			$arr_w2gm['open_id'] = intval($open_id);
			$arr_w2gm['ban_time']  = strtotime($ban_time);

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