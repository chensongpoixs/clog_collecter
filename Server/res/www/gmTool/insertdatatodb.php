<?php
	require_once('./header.php');
	require_once('./notice_gm.php');
	date_default_timezone_set('PRC');
	set_time_limit(300);   // 最大执行时间这里设置300秒
	//ini_set('memory_limit','512M');
	$ntype = $_POST['type'];

	$db = get_global_db();
	$log_db = get_global_log_db();
	
	if($db == NULL)
	{
		echo "db error !";
		exit();
	}
	if ($log_db == NULL)
	{
		echo "log db connect error !!!";
		exit();
	}

	switch($ntype)
	{
		case 0:
		{ // 插入服务器信息
			DEBUG('');
			if(!has_privilege(4011))
			{
				echo 1;
				break;
			}
			DEBUG('----');
			$id = $_POST['id'];
			DEBUG('----id = '.$id);
			//$cur_id = $_POST['cur_id'];
			$show_id = intval($_POST['show_id']);
			DEBUG('----show_id = '.$show_id);
			$name = $_POST['name'];//mysql_escape_string($_POST['name']);
			DEBUG('----name = '.$name);
			//$ipport = mysql_escape_string($_POST['ipport']);
			//$rate = $_POST['rate'];
			//$status1 = $_POST['status'];
			////$env1 = $_POST['env'];
			//$platform = mysql_escape_string($_POST['platform']);
			//$new1 = $_POST['newserver'];
			//$suggest1 = $_POST['suggest_server'];
			//$is_gm = intval($_POST['is_gm']);
			//$channel = mysql_escape_string($_POST['channel']);
			//$version = mysql_escape_string($_POST['version']);
			$att_url = $_POST['att_url'];//mysql_escape_string($_POST['att_url']);
			//$open_time = $_POST['open_time'];
			DEBUG('----att_url = '.$att_url);
			//检查数据是否已存在 同一个show_id只允许一个
			$result = $db->query("select `render_name` from `t_app_render_info` where `id`=$id ");
			if(!$result)
			{
				DEBUG('----  3');
				echo 3;
				break;
			}
			if($result->num_rows > 0)
			{
				//DEBUG('----  > 0');
				$result->close();
				echo 2;
				break;
			}
			$result->close();
			//检查数据是否已存在 同一个id且is_gm==0只允许一个
			/*if(0 == $is_gm)
			{
				$result = $db->query("select `id` from `t_app_render_info` where `id`='$id' AND `is_gm`=0");
				if(!$result)
				{
					echo 3;
					break;
				}
				if($result->num_rows > 0)
				{
					$result->close();
					echo 2;
					break;
				}
				$result->close();
			}*/
			$sql = "INSERT INTO `t_app_render_info` (`id`, `render_server_id`,  `render_name`,  `app_url`";
			$sql .= ") VALUES (";
			$sql .= "'$id',  '$show_id', '$name',   '$att_url' ";
			$sql .= ")";
			$result = $db->query($sql);
			if(!$result)
			{
				echo 4;
				break;
			}
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
			log_manager($db, "add_server", get_log_str($_POST));
			echo 0;
		}
		break;
		case 1:
		{ // 插入公告信息
			if(!has_privilege(4001))
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
			$result = $db->query("INSERT INTO `t_billboard` (`id`, `channel`, `start_time`, `end_time`, `pic`, `url`, `note`,`board_type`) VALUES ($id, '$channel','$start_time','$end_time', '$pic', '$url', '$note','$board_type')");
			if(!$result)
			{
				echo 1;
				break;
			}
			
			log_manager($db, "add_billboard", get_log_str($_POST));
			echo 0;
		}
		break;
		case 2:
		{	//system_event 系统公告
			if(!has_privilege(4061))
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
			
			$sql = 'INSERT INTO `t_system_event` (`id`, `server_id`, `channel`, `start_time`, `end_time`, `delay`, `show`, `priority`, `note`) VALUES (';
			$sql .="$id, '$server_id', '$channel','$start_time','$end_time', $delay, $show, $priority, '$note'";
			$sql .=')';
			$result = $db->query($sql);
			if(!$result)
			{
				//DEBUG($db->error);
				//DEBUG($sql);
				echo 2;
				break;
			}
			
			log_manager($db, "add_system_event", get_log_str($_POST));
			
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
		{	// 激活码
			if(!has_privilege(4021))
			{
				echo 1;
				break;
			}
			$code_id = $_POST['activation_id'];
			$code_type = $_POST['activation_type'];
			
			$code_note = mysql_escape_string($_POST['activation_note']);
			$code_channel = $_POST['activation_channel'];
			
			$code_opid = $_POST['activation_opid'];
			$code_status = $_POST['activation_status'];
			
			$code_beginValid = $_POST['activation_begin_valid'];
			$code_endValid = $_POST['activation_end_valid'];
			
			$code_name = $_POST['activation_name'];
			
			//$code_giftCode = $_POST['activation_giftCode'];
			
			$code_updateBy = mysql_escape_string($_SESSION['admin_name']);
			$code_mailTitle = mysql_escape_string($_POST['activation_mailTitle']);
			
			$code_mailSender = mysql_escape_string($_POST['activation_mailSender']);
			$code_mailContext = mysql_escape_string($_POST['activation_mailContext']);
			$code_mailAffix = mysql_escape_string($_POST['activation_mailAffix']);
			
			$codeCount = $_POST['activation_number'];
			$codeLength = $_POST['activation_length'];
			
			$codeidexist = $db->query("select `id` from `t_activationinfo` where `id`='$code_id'");
			
			if($codeidexist && ($codeidexist->num_rows == 1))
			{
				$codeidexist->close();
				echo 1;
				break;
			}			
			$codeidexist->close();
			
			$sql = "INSERT INTO `t_activationinfo` ("
				. "`id`, `type`, `name`,`channel`,`opid`,`status`,`begin_valid`,`end_valid`"
				. ",`update_time`,`update_by`,`mail_title`,`mail_sender`,`mail_content`,`mail_affix`"
				. ")VALUES("
				. "'$code_id','$code_type','$code_note','$code_channel','$code_opid','$code_status','$code_beginValid','$code_endValid'"
				. ",NOW(),'$code_updateBy','$code_mailTitle','$code_mailSender','$code_mailContext','$code_mailAffix'"
				. ')';
			
			$result = $db->query($sql);
			if($result == false)
			{
				echo 2;
				break;
			}
				
			log_manager($db, "add_code", get_log_str($_POST));
			$hashArray = array();
			$index = 0;
			$countindex = 0;
			$lowindex = 0;
			$highindex = 33;
			$RandomSed = "123456789ABCDEFGHIJKLMNPQRSTUVWXYZ";
			
			if($code_type==2 && $code_name!='')
			{
				$hashArray[$code_name] = "1";
			}
			else
			{
				while($index < $codeCount)
				{
					$code = '';
					$code .= $code_id;
					$code .= $code_opid;
					
					for($i = 0; $i < $codeLength ; $i++)
					{
						$index1 = rand($lowindex,$highindex);
						$code .= $RandomSed[$index1];
					}
					
					if(array_key_exists($code,$hashArray) == false )
					{
						$hashArray[$code] = "1";
						$index ++;	
					}
					else
					{	
						if($countindex != $highindex)
						{
							$one = substr($RandomSed,strlen($RandomSed)-1,1);
							$RandomSed = substr($RandomSed,0,strlen($RandomSed)-1);
							
							$RandomSed = $one.$RandomSed;
							$countindex ++;
						}
						else
						{
							$randomalph = $RandomSed[rand($lowindex,$highindex)];
							$highindex ++;
							$countindex = 0;
							str_pad($RandomSed,$highindex + 1,$randomalph);
							
						}
						continue;
					}
				}
			}
			

			$count = 0;
			$temp = '';
			$successcount = 0;
			$failcount = 0;
			$bsuccess = true;
			foreach($hashArray as $key=>$value)
			{
				if( $count != 100)
				{
					if($count == 0)
					{
						$temp .= "('$code_id','$code_type','$code_opid','$key','$code_channel','0','0','0000-00-00 00:00:00','')";
					}
					else
					{
						$temp .= ",('$code_id','$code_type','$code_opid','$key','$code_channel','0','0','0000-00-00 00:00:00','')";	
					}
					$count ++;
				}
				else
				{
					$temp .= ",('$code_id','$code_type','$code_opid','$key','$code_channel','0','0','0000-00-00 00:00:00','')";
					$suc = $db->query("INSERT INTO `t_activationcode` VALUES $temp");
					if($suc == false)
					{
						$bsuccess = false;
						$failcount ++;
					}
					else
					{
						$successcount ++;
					}
					$temp = '';
					$count = 0;

				}	
			}

			if($count != 0)
			{
				$suc = $db->query("INSERT INTO `t_activationcode` VALUES $temp");
				if($suc == false)
				{
					$bsuccess = false;
					$failcount ++;
				}
				else
				{
					$successcount ++;
				}
			}
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "activation";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($code_id);
			$arr_w2gm['status'] = intval($code_status);
			
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
			//DEBUG('');
			if(!has_privilege(4011))
			{
				echo 1;
				break;
			}
			//DEBUG('----');
			$id = $_POST['id'];
			//DEBUG('----id = '.$id);
			//$cur_id = $_POST['cur_id'];
			$show_id = intval($_POST['show_id']);
			//DEBUG('----show_id = '.$show_id);
			$name = $_POST['name'];//mysql_escape_string($_POST['name']);
			//DEBUG('----name = '.$name);
			//$ipport = mysql_escape_string($_POST['ipport']);
			//$rate = $_POST['rate'];
			//$status1 = $_POST['status'];
			////$env1 = $_POST['env'];
			//$platform = mysql_escape_string($_POST['platform']);
			//$new1 = $_POST['newserver'];
			//$suggest1 = $_POST['suggest_server'];
			//$is_gm = intval($_POST['is_gm']);
			//$channel = mysql_escape_string($_POST['channel']);
			//$version = mysql_escape_string($_POST['version']);
			$att_url = $_POST['att_url'];//mysql_escape_string($_POST['att_url']);
			//$open_time = $_POST['open_time'];
			//DEBUG('----att_url = '.$att_url);
			//检查数据是否已存在 同一个show_id只允许一个
			$result = $log_db->query("SELECT `log_level` FROM `t_user_log_collector_info` WHERE `id`=$id ");
			if(!$result)
			{
				DEBUG('----  3');
				echo 3;
				break;
			}
			if($result->num_rows > 0)
			{
				//DEBUG('----  > 0');
				$result->close();
				echo 2;
				break;
			}
			$result->close();
			//检查数据是否已存在 同一个id且is_gm==0只允许一个
			/*if(0 == $is_gm)
			{
				$result = $db->query("select `id` from `t_app_render_info` where `id`='$id' AND `is_gm`=0");
				if(!$result)
				{
					echo 3;
					break;
				}
				if($result->num_rows > 0)
				{
					$result->close();
					echo 2;
					break;
				}
				$result->close();
			}*/
			$sql = "INSERT INTO `t_user_log_collector_info` (`id`, `client_type`,  `log_level`,  `address`";
			$sql .= ") VALUES (";
			$sql .= "'$id',  '$show_id', '$name',   '$att_url' ";
			$sql .= ")";
			$result = $log_db->query($sql);
			if(!$result)
			{
				echo 4;
				break;
			}
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
			log_manager($db, "add_server", get_log_str($_POST));
			echo 0;
		}
		break;
		case 7:
		{	//mail
			if(!has_privilege(4031))
			{
				echo 1;
				break;
			}
			//$childtype = $_POST['childtype'];
			$mailtitle = mysql_escape_string($_POST['mailtitle']);
			$mailsender = mysql_escape_string($_POST['mailsender']);
			$mailcontent = mysql_escape_string($_POST['mailcontent']);
			$affixs = mysql_escape_string($_POST['affixs']);
			$mailsendtime = $_POST['mailsendtime'];
			$mailplayerids = $_POST['playerids'];
			$mailserverids = $_POST['serverids'];
			
			$result = $db->query("select max(`id`) from `t_mail`");
			if(!$result)
			{
				echo 2;
				break;
			}
			$row = $result->fetch_array(MYSQLI_NUM);
			if(!$row)
			{
				echo 2;
				break;
			}
			$id = $row[0];
			if($id == NULL)
			{
				$id = 1;
			}
			else
			{
				++$id;
			}
			$sql = "INSERT INTO `t_mail` (`id`, `server_id`,`player_id`,`mail_title`,`mail_sender`,`mail_content`,`affix`,`send_time`)"
				."VALUES "
				."($id, '$mailserverids','$mailplayerids','$mailtitle','$mailsender','$mailcontent','$affixs','$mailsendtime')";
			
			$result = $db->query($sql);
			
			if(!$result)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "add_mail", 'mail_id=' . $id . ', ' . get_log_str($_POST));
			
			$arr_w2gm = array();
			$arr_w2gm['cmd'] = "mail";
			$arr_w2gm['op'] = 'update';
			$arr_w2gm['id'] = intval($id);
			
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
      	{	//activity
			if(!has_privilege(4041))
			{
				echo 1;
				break;
			}
      		//$childtype = $_POST['childtype'];
            $activity_id = $_POST['activity_id'];
			$activity_type = $_POST['activity_type'];
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
      		$activity_data = mysql_escape_string($_POST['activity_data']);

      		$result = $db->query("insert into `t_activity` (`id`,`type`,`name`,`enable`,`server`,`channel`,`show_time`,`start_time`,`end_time`,`disappear_time`,`image`,`desc`,`data`)"
                              . " values ('$activity_id','$activity_type','$activity_name','$activity_enable','$activity_serverids','$activity_channel'"
							  . " ,'$activity_show_time','$activity_start_time','$activity_end_time','$activity_disappear_time','$activity_image','$activity_desc','$activity_data')");

      		if(!$result)
			{
				echo 1;
				break;
			}
			
			log_manager($db, "add_activity", get_log_str($_POST));
			
      		$arr_w2gm = array();
      		$arr_w2gm['cmd']="activity";
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
		{	// 插入账号信息
			if(!has_privilege(5001))
			{
				echo 1;
				break;
			}
			
			$account = $_POST['account'];
			$password = md5($_POST['password']);
			$privilege = $_POST['privilege'];
			$realname = $_POST['realname'];
			
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
			
			$result = $db->query("select `account` from `t_admin` where `account`='$account'");
			if($result == false)
			{
				echo 3;
				break;
			}
			
			$num_rows = $result->num_rows;
			$result->close();
			
			if($num_rows != 0)
			{
				echo 2;
				break;
			}
			$result = $db->query("INSERT INTO `t_admin` (`account`, `password`,`realname` ,`privilege`) VALUES ('$account', '$password','$realname', '$privilege')");
			if($result == false)
			{
				echo 1;
				break;
			}
			
			log_manager($db, "add_account", "account=$account, privilege=$privilege,realname=$realname");
			echo 0;
		}
		break;
		case 22:
		{	// 角色封禁信息
			if(!has_privilege(3001))
			{
				echo 1;
				break;
			}
			$player_id = $_POST['player_id'];
			$server_id = $_POST['server_id'];
			$chat_time = $_POST['chat_time'];
			$ban_time = $_POST['ban_time'];
			
			$idexist = $db->query("SELECT `player_id` from `t_player_ban` WHERE `player_id`='$player_id'");
			if($idexist == false)
			{
				echo 2;
				break;
			}
			
			if($idexist->num_rows >= 1)
			{
				$idexist->close();
				echo 3;
				break;
			}
			$idexist->close();
			
			$result = $db->query("INSERT INTO `t_player_ban` (`player_id`, `server_id`, `chat_time`, `ban_time`) VALUES ('$player_id', '$server_id', '$chat_time', '$ban_time')");
			if($result == false)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "add_ban_player", get_log_str($_POST));
			
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
		case 23:
		{	// IP封禁
			if(!has_privilege(3021))
			{
				echo 1;
				break;
			}
			$ip = mysql_escape_string($_POST['ip']);
			
			$result = $db->query("select `ip` from `t_ip_ban` where `ip`='$ip'");
			if($result == false)
			{
				echo 2;
				break;
			}
			
			if($result->num_rows >= 1)
			{
				$result->close();
				echo 3;
				break;
			}
			$result->close();
			
			$result = $db->query("INSERT INTO `t_ip_ban` (`ip`) VALUES ('$ip')");
			if($result == false)
			{
				echo 2;
				break;
			}

			log_manager(NULL, "add_ban_ip", "ip=$ip");
			
			$arr_w2gm = array();
			$arr_w2gm['cmd']="ip_ban";
			$arr_w2gm['op']='update';
			
			$arr_w2gm['ip'] = $ip;

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
		{	// 账号封禁信息
			if(!has_privilege(3011))
			{
				echo 1;
				break;
			}
			$open_id = $_POST['open_id'];
			$ban_time = $_POST['ban_time'];
			
			$idexist = $db->query("SELECT `open_id` from `t_account_ban` WHERE `open_id`='$open_id'");
			if($idexist == false)
			{
				echo 2;
				break;
			}
			
			if($idexist->num_rows >= 1)
			{
				$idexist->close();
				echo 3;
				break;
			}
			$idexist->close();
			
			$result = $db->query("INSERT INTO `t_account_ban` (`open_id`, `ban_time`) VALUES ('$open_id', '$ban_time')");
			if($result == false)
			{
				echo 2;
				break;
			}
			
			log_manager($db, "add_ban_account", get_log_str($_POST));
			
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