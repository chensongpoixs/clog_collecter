<?php
	require_once('./header.php');
	require_once('./db_function.php');

	$ntype = $_POST['type'];
	$db = get_global_db();
	$log_db = get_global_log_db();

	if($db == NULL)
	{
		echo "db error !!!";
		exit;
	} 
	if ($log_db == NULL)
	{
		
		echo "log db error !!!";
		exit;
	}

	$rows = array();
	switch($ntype)
	{
		case 0:
		{// server info
			$childtype = $_POST['childtype'];
			$value	   = $_POST['value'];
			$flag = 0;
			if(isset($_POST['flag']) && $_POST['flag'] != NULL)
			{
				$flag = $_POST['flag'];
			}
			 
			switch($childtype)
			{
				case 0:
				{
					$result = $db->query("SELECT id, render_server_id as show_id, render_name as name, app_url as att_url FROM `t_app_render_info`",MYSQLI_STORE_RESULT);
				}
				break;
				case 1:
				{	
					$result = $db->query("SELECT `id`, `name`, `show_id`, `cur_id` FROM `t_server_info` where `is_gm`=0 AND `id` like '%$value%'",MYSQLI_STORE_RESULT);
				}
				break;
				case 2:
				{
					$result = $db->query("SELECT `id`, `name`, `show_id`, `cur_id` FROM `t_server_info` where `is_gm`=0 AND `show_id` like '%$value%'",MYSQLI_STORE_RESULT);
				}
				break;
				case 3:
				{
					$result = $db->query("SELECT `id`, `name`,`show_id`, `cur_id` FROM `t_server_info` where `is_gm`=0 AND `name` like '%$value%'",MYSQLI_STORE_RESULT);
				}
				break;
				case 4:
				{
					$result = $db->query("SELECT `id`, `name`, `show_id`, `cur_id` FROM `t_server_info` where `is_gm`=0 AND `cur_id` = `id` or `cur_id` = '0'",MYSQLI_STORE_RESULT);
				}
				break;
				case 5:
				{
					$new_rows = array();
					echo json_encode($new_rows);
					return ;
					//$result = $db->query("SELECT `id`, `name` AS `text` FROM `t_server_info` WHERE `is_gm`=0",MYSQLI_STORE_RESULT);
				}
				break;
				case 6:
				{
					$result = $log_db->query("SELECT id, client_type as show_id, log_level as name, address as att_url FROM `t_user_log_collector_info`",MYSQLI_STORE_RESULT);
				}
				break;
				case 7:
				{
					$time_start = $_POST['start_time'];
					//DEBUG("===");
					$time_end = $_POST['end_time'];;
					$client_type = $_POST['client_type'];
					DEBUG($client_type);
					$address	   = $_POST['address'];
					DEBUG($address);
					
					$sql = "SELECT `id`, `client_type`,  `address`, `timestamp`, `log_file_name`  FROM `t_log_collector_info` ";
					$sql .= " WHERE `timestamp`>".$time_start." AND `timestamp`<=".$time_end;
					$sql .= " AND `client_type` = ".$client_type;
					
					if ($address != '')
					{
						$sql .= " AND `address` = '".$address ."'";
					}
					DEBUG($sql);
					$result = $log_db->query($sql,MYSQLI_STORE_RESULT);
				}
				break;
				default:
				$result = false;
				break;
			}
			if($result == false)
			{	
				echo 1;
				break;
			}
			
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$row['id'] = intval($row['id']);
				if ($childtype == 7)
				{
					$row['client_type'] = get_log_client_type(intval($row['client_type']));
					$row['log_url'] =   $log_collector_url_prefix. $row['log_file_name'] ;
					$row['datetime'] = date("Y-m-d H:i:s", intval($row['timestamp']) + 8 * (60*60));
				}
 				$rows[] = $row;
			}
				 
			$result->close();
			
			if($flag == 1)
			{
				$new_rows = array(); //实际服务器
				$src_rows = array(); // 已经合并的服务器
				foreach ($rows as $row) {
					if( $row['cur_id'] == $row['id'] || $row['cur_id'] == 0 )
					{
						//实际服务器
						$new_rows[] = $row;
					}
					else
					{
						$src_rows[] = $row;
					}
				}
				foreach ($src_rows as $src_row) {
					foreach ($new_rows as &$new_row) {
						if( $new_row['id'] == $src_row['cur_id'])
						{
							//实际服务器
							$new_row['name'] = $new_row['name'] . "|" . $src_row['name'];
							$new_row['show_id'] = $new_row['show_id'] . "|" . $src_row['show_id'];
						}
					}
				} 
				echo json_encode($new_rows);
			}
			else
			{
				 
				echo json_encode($rows);
			}
		}
		break;
		case 1:
		{// billborad 
			if(!has_privilege(4000))
			{
				echo 1;
				break;
			}
			$result = $db->query("SELECT * FROM t_billboard",MYSQLI_STORE_RESULT);
			
			if($result == false)
			{
				echo 1;
				break;
			}
			
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$rows[] = $row;
			}
				
			echo json_encode($rows);
		}
		break;
		case 2:
		{	// player info
			$childtype = $_POST['childtype'];
			$value	   = $_POST['value'];
			switch($childtype)
			{
				case 1:
				{
					$result = $db->query("SELECT `player_name`,`machine_id`,`server_id` FROM `t_player_info` WHERE `player_id`=$value",MYSQLI_STORE_RESULT);
				}
				break;
				case 2:
				{	
					$result = $db->query("SELECT `player_id`, `machine_id`,`server_id` FROM `t_player_info` where `player_name`='$value'",MYSQLI_STORE_RESULT);
				}
				break;
				case 3:
				{
					$result = $db->query("SELECT `player_id`, `player_name`,`server_id` FROM `t_player_info` where `machine_id` = '$value'",MYSQLI_STORE_RESULT);
				}
				break;
				default:
				$result = false;
				break;
			}
			if($result == false)
			{	
				echo 1;
				break;
			}
			
			if($result->num_rows == 0)
			{
				echo 2; //没有结果
				break;
			}
			if($result->num_rows > 1)
			{
				//多余一个结果
				$result->close();
				echo 3;
				break;
			}
			
			$row = $result->fetch_assoc();
			$result->close();
			echo json_encode($row);
		}
		break;
		case 201:
		{	// player info
			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1);
			
			$childtype = $_POST['childtype'];
			$value	   = $_POST['value'];
			
			//$sql = "SELECT `player_id`,`open_id`,`server_id`,`channel_id`, FROM_UNIXTIME(`create_time` + " . BASE_TIME .") AS `create_time`, `create_ip`";
			//$sql .= " ,`money`, `player_level`, `vip_level`, `player_name`, FROM_UNIXTIME(`last_logon_time` + ". BASE_TIME .") AS `last_logon_time`";
			//$sql .= " ,`last_logon_ip`,`machine_type`,`machine_id`";
			//$sql .= " FROM `t_player_info`";
			//$sql .= " WHERE `$childtype` LIKE '%$value%'";
			//
			//$result = $db->query("$sql limit $pageIndex,$rows", MYSQLI_STORE_RESULT);
			$time_start = $_POST['start_time'];
					//DEBUG("===");
			$time_end = $_POST['end_time'];;
			$client_type = $_POST['client_type'];
			//DEBUG($client_type);
			$address	   = $_POST['address'];
			//DEBUG($address);
			
			$sql = "SELECT `id`, `client_type`,  `address`, `timestamp`, `log_file_name`  FROM `t_log_collector_info` ";
			$condition = " WHERE `timestamp`>".$time_start." AND `timestamp`<=".$time_end;
			$condition .= " AND `client_type` = ".$client_type;
			
			if ($address != '')
			{
				$condition .= " AND `address` = '".$address ."'";
			}
			$new_sql = $sql .$condition;
			//DEBUG($new_sql);
			$result = $log_db->query("$new_sql limit $pageIndex,$rows",MYSQLI_STORE_RESULT);
			$total = 0;
			$json = '';
			if($result)
			{
				$count = 0;
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					if($count != 0)
					{
						$json .= ',';
					}
					$row['id'] = intval($row['id']); 
					$row['client_type'] =  intval($row['client_type']);
					$row['log_url'] =   $log_collector_url_prefix. $row['log_file_name'] ;
					$row['datetime'] = date("Y-m-d H:i:s", intval($row['timestamp']) + 8 * (60*60));
				 
 				///$rows[] = $row;
					
					$json .= json_encode($row);
					++$count;
				}
				$result->close();
				$total = get_row_count($log_db, 't_log_collector_info', $condition);
			}
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;		
		case 3:
		{// system_event 系统公告 
			if(!has_privilege(4060))
			{
				echo 1;
				break;
			}
			$sql = 'SELECT `id`, `server_id`, `channel`, FROM_UNIXTIME(`start_time` + ' . BASE_TIME . ') AS `start_time`, FROM_UNIXTIME(`end_time`+' . BASE_TIME . ') AS `end_time`, `delay`, `show`, `priority`, `note`';
			$sql .= ' FROM t_system_event';
			$result = $db->query($sql,MYSQLI_STORE_RESULT);
			
			if($result == false)
			{
				//DEBUG($db->error);
				echo 2;
				break;
			}
			
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$rows[] = $row;
			}
				
			echo json_encode($rows);
		}
		break;
		case 5:
		{	// activationinfo
			if(!has_privilege(4020))
			{
				echo 1;
				break;
			}
/* 			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1); */
			//echo $page;
			$childtype = $_POST['childtype'];
			$values     = $_POST['value'];
			$now_timestamp = time();
			$condition = '';
			switch($childtype){
				case 0:
				{	
				}
				break;
				case 1:
				{
					$condition = "where `id` like '%$values%'";
				}
				break;
				case 2:
				{
					$condition = "where `type` like '%$values%'";
				}
				break;
				case 3:
				{
					$condition = "where `channel` like '%$values%'";
				}
				break;
				case 4:
				{
					$condition = "where $now_timestamp>UNIX_TIMESTAMP(`end_valid`)";
				}
				break;
				case 5:
				{
					$condition = "where $now_timestamp>UNIX_TIMESTAMP(`begin_valid`) AND $now_timestamp<UNIX_TIMESTAMP(`end_valid`)";
				}
				break;
				case 6:
				{
					$condition = "where $now_timestamp<UNIX_TIMESTAMP(`begin_valid`)";
				}
				break;
			}
			
			$result = $db->query("select `id`, `type`, `name`,`channel`,`opid`,`status`,`begin_valid`,`end_valid`,`update_by`,`mail_title`,`mail_sender`,`mail_content`,`mail_affix`,`mail_affix` as `mail_affix1` from `t_activationinfo` $condition");
			
			//limit $pageIndex,$rows
			if($result == false){
				echo 1;
				break;
			}
				
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$rows[] = $row;
				//break;
			}
			
			$row_number = $result->num_rows;
			$result->close();
			
			for($i = 0; $i < $row_number; $i ++)
			{
				$ids = $rows[$i]["id"];
				$actived_total = '';
				if($rows[$i]["type"] == 0 || $rows[$i]["type"] == 1)
				{
					$actived_num = get_row_count($db, 't_activationcode', "where `id`='$ids' and `status`=1");
					$total_num = get_row_count($db, 't_activationcode', "where `id`='$ids'");
					$actived_total = $actived_num . '/' . $total_num;
				}
				else
				{
					$actived_total = get_row_count($db, 't_activationcount', "where `id`='$ids'");
				}							
			
				$rows[$i]["actived_total"] = $actived_total;
			}
			
			echo json_encode($rows);			
		}
		break;
		case 501:
		{	// 礼包领取详细
			if(!has_privilege(4025))
			{
				echo 1;
				break;
			}
 			$page = $_POST['page'];
			$row_count = $_POST['rows'];
			$pageIndex = $row_count*($page - 1);
			//echo $page;
			$childtype = $_POST['childtype'];
			$values     = $_POST['value'];
			$condition = 'WHERE `player_id` <> 0';
			switch($childtype){
				case 0:
				{
					
				}
				break;
				case 1:
				{
					$condition .= " AND `player_id` = '$values'";
				}
				break;
				case 2:
				{
					$condition .= " AND `channel` = '$values'";
				}
				break;
				case 3:
				{
					$condition .= " AND `server_id` = '$values'";
				}
				break;
			}
			
			
			$sql = "SELECT `player_id`, `id`, `channel`, `server_id` FROM `t_activationcode` " . $condition;
			
			// $sql = "SELECT `t_activationcode`.`player_id`, `t_player_info`.`player_name`, `t_activationinfo`.`id`, `t_activationinfo`.`name`"
					// . " FROM `t_activationcode`,`t_activationinfo`,`t_player_info`"
					// . " WHERE `t_activationcode`.`id`=`t_activationinfo`.`id` AND `t_activationcode`.`player_id`=`t_player_info`.`player_id`"
					// . $condition
					// . " LIMIT $pageIndex,$row_count";
					
			$result = $db->query($sql . " LIMIT $pageIndex,$row_count");
			
			if($result == false){
				echo 1;
				break;
			}
			
			//找到当前页的内容
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$rows[] = $row;
			}
			
			$row_number = $result->num_rows;
			$result->close();
			
			//取出用户名 礼包名
			for($i = 0; $i < $row_number; $i ++)
			{
				//取出用户名
				$result = $db->query("SELECT `player_name` FROM `t_player_info` WHERE `player_id`=".$rows[$i]['player_id']);
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$rows[$i]['player_name'] = $row[0];
					}
					$result->close();
				}
				
				//取出 礼包名
				$result = $db->query("SELECT `name` FROM `t_activationinfo` WHERE `id`=".$rows[$i]['id']);
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$rows[$i]['name'] = $row[0];
					}
					$result->close();
				}
			}
			
			$json='';
			for($i = 0; $i < $row_number; $i ++)
			{
				if($i != 0)
				{
					$json .= ',';
				}
				$json .= json_encode($rows[$i]);
			}
			$total = get_row_count($db, 't_activationcode', $condition);
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;
		case 502:
		{
			if(!has_privilege(4026))
			{
				echo 1;
				break;
			}
			$childtype = $_POST['childtype'];
			$values     = $_POST['value'];
			$condition = 'WHERE `id` <> 0';
			switch($childtype){
				case 1:
				{
					$condition .= " AND `player_id` = '$values'";
				}
				break;
				case 2:
				{
					//先查出layer_id
					$tmp_player_id = '';
					$result1 = $db->query("SELECT `player_id` FROM `t_player_info` WHERE `open_id`=".$values);
					if($result1)
					{
						$row1 = $result1->fetch_row();
						if($row)
						{
							$tmp_player_id = $row1[0];
						}
						$result1->close();
					}
					if($tmp_player_id=='')
					{
						echo 1;
						exit;
					}
					
					$condition .= " AND `player_id` = '$tmp_player_id'";
				}
				break;
				case 3:
				{
					$condition .= " AND `code` = '$values'";
				}
				break;
			}
			
			$sql = "SELECT * FROM `t_activationcode` " . $condition;
			
			$result = $db->query($sql);
			
			if($result == false){
				echo 1;
				break;
			}
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				$rows[] = $row;
			}
			echo json_encode($rows);
		}
		break;
		case 7:
		{	// mail
			if(!has_privilege(4030))
			{
				echo 1;
				break;
			}
			$childtype = $_POST['childtype'];
			$value	   = $_POST['value'];
			
			switch($childtype){
				case 0:
				{
					$result = $db->query("select * from `t_mail`");
					if($result == false){
						echo 1;
					}
					else{
						while($row = $result->fetch_array(MYSQLI_ASSOC))
						{
							$rows[] = $row;
						}
						echo json_encode($rows);
						$result->close();
					}
				}
				break;
				case 1:
				{
					$result = $db->query("select * from `t_mail`where `id` like '%$value%'");
					if($result == false){
						echo 1;
					}
					else{
						while($row = $result->fetch_array(MYSQLI_ASSOC))
						{
							$rows[] = $row;
						}
						echo json_encode($rows);
						$result->close();
					}
				}
				break;
				case 2:
				{
					$result = $db->query("select * from `t_mail` where `mail_sender` like '%$value%'");
					if($result == false){
						echo 1;
					}
					else{
						while($row = $result->fetch_array(MYSQLI_ASSOC))
						{
							$rows[] = $row;
						}
						echo json_encode($rows);
						$result->close();
					}
				}
				break;
				case 3:
				{
					$result = $db->query("select * from `t_mail` where `mail_title` like '%$value%'");
					if($result == false){
						echo 1;
					}
					else{
						while($row = $result->fetch_array(MYSQLI_ASSOC))
						{
							$rows[] = $row;
						}
						echo json_encode($rows);
						$result->close();
					}
				}
				break;
			}
		}
		break;
		case 701:
		{	// 邮件领取详细
			if(!has_privilege(4035))
			{
				echo 1;
				break;
			}
 			$page = $_POST['page'];
			$row_count = $_POST['rows'];
			$pageIndex = $row_count*($page - 1);
			//echo $page;
			$childtype = $_POST['childtype'];
			$values     = $_POST['value'];
			$condition = '';
			switch($childtype){
				case 0:
				{
					
				}
				break;
				case 1:
				{
					$condition = "WHERE `player_id` = '$values'";
				}
				break;
				case 2:
				{
					$condition = "WHERE `server_id` = '$values'";
				}
				break;
			}
			
			
			$sql = "SELECT `player_id`, `id`, `server_id`, `taken_time` FROM `t_taken_mail` " . $condition;
					
			$result = $db->query($sql . " LIMIT $pageIndex,$row_count");
			
			if($result == false){
				echo 1;
				break;
			}
			
			$mail_ids = array();
			$player_ids = array();
			
			//找到当前页的内容, 同事获取邮件id
			while($row = $result->fetch_array(MYSQLI_ASSOC))
			{
				if(! in_array($row['id'], $mail_ids))
				{
					$mail_ids[] = $row['id'];
				}
				if(! in_array($row['player_id'], $player_ids))
				{
					$player_ids[] = $row['player_id'];
				}
				$row['player_name'] = '';
				$row['mail_title'] = '';
				$rows[] = $row;
			}
			$result->close();
			
			$row_number = count($rows);
			
			if($row_number > 0)
			{
				//取出邮件名
				$ids_str = implode(',', $mail_ids);
				$result = $db->query("SELECT `id`, `mail_title` FROM `t_mail` WHERE `id` IN ($ids_str)");
				if(!$result)
				{
					echo 1;
					break;
				}
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					for($i = 0; $i < $row_number; $i ++)
					{
						if($rows[$i]['id'] == $row['id'])
						{
							$rows[$i]['mail_title'] = $row['mail_title'];
						}
					}
				}
				$result->close();
				
				//取出角色名
				$ids_str = implode(',', $player_ids);
				$result = $db->query("SELECT `player_id`, `player_name` FROM `t_player_info` WHERE `player_id` IN ($ids_str)");
				if(!$result)
				{
					echo 1;
					break;
				}
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					for($i = 0; $i < $row_number; $i ++)
					{
						if($rows[$i]['player_id'] == $row['player_id'])
						{
							$rows[$i]['player_name'] = $row['player_name'];
						}
					}
				}
				$result->close();
			}
			
			$json='';
			for($i = 0; $i < $row_number; $i ++)
			{
				if($i != 0)
				{
					$json .= ',';
				}
				$json .= json_encode($rows[$i]);
			}
			$total = get_row_count($db, 't_taken_mail', $condition);
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;
        case 10:
    	{	// activity
			if(!has_privilege(4040))
			{
				echo 1;
				break;
			}
    		$childtype = $_POST['childtype'];
    		$value	   = $_POST['value'];
			
    		switch($childtype){
    			case 0:
    			{
    				$result = $db->query("select * from `t_activity` order by id asc");
    			}
    			break;
    			case 1:
    			{
    				$result = $db->query("select * from `t_activity` where `id` like '%$value%' order by id asc");
    			}
    			break;
    			case 2:
    			{
    				$result = $db->query("select * from `t_activity` where `type` like '%$value%' order by id asc");
    			}
    			break;
    			case 3:
    			{
    				$result = $db->query("select * from `t_activity` where `name` like '%$value%' order by id asc");
    			}
    			break;
                case 4:
            	{
            		$result = $db->query("select * from `t_activity` where `server` like '%$value%' order by id asc");
            	}
            	break;
				case 5:
            	{
            		$result = $db->query("select * from `t_activity` where `channel` like '%$value%' order by id asc");
            	}
            	break;
				default:
				$result = false;
				break;
    		}
			if($result == false){
    			echo 1;
			}
    		else{
    			while($row = $result->fetch_array(MYSQLI_ASSOC))
    			{
    				$rows[] = $row;
    			}
    			echo json_encode($rows);
    			$result->close();
    		}
    	}
    	break;
		case 20:
		{	// 账号管理
				$condition = '';
				if($_SESSION['admin'] == 'admin')
				{
					//管理员最高权限
				}
				else if(has_privilege(5001) || has_privilege(5002) || has_privilege(5003) || has_privilege(5004))
				{
					//有管理权限也看不到超级账号
					$condition = "WHERE `account` <> 'admin'";
				}
				else
				{
					//没有管理权限只能看到自己
					$condition = "WHERE `account`='" . $_SESSION['admin'] . "'";
				}
				$result = $db->query("SELECT `account`,`privilege`,`realname`,`last_time`,`last_ip`,`login_times` FROM `t_admin` $condition", MYSQLI_STORE_RESULT);
				if($result == false)
				{	
					echo 1;
					break;
				}
				
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					$rows[] = $row;
				}
				
				$result->close();
				echo json_encode($rows);
			}	
			
		break;
		case 21:
		{	// 管理日志
			if(!has_privilege(501))
			{
				echo '{"total":0, "rows":[]}';
				break;
			}
			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1);
			
			$childtype = $_POST['childtype'];
			$value     = $_POST['value'];
			
			$condition = '';
			switch($childtype){
				case 0:
				{
					$condition = '';
				}
				break;
				case 1:
				{
					$condition = "where `account` like '%$value%'";
				}
				break;
				case 2:
				{
					$condition = "where `type` like '%$value%'";
				}
				break;
			}
			$total = 0;
			$json = '';
			$result = $db->query("select `account`,`time`,`type`,`note` from `t_manage_log` $condition ORDER BY `time` DESC limit $pageIndex,$rows ",MYSQLI_STORE_RESULT);
			if($result)
			{
				$src_rows = array();
				$accounts = array();
				$ids_str = '';
			
				//找到当前页的内容, 获取account
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					if(! in_array($row['account'], $accounts))
					{
						$accounts[] = $row['account'];
						if($ids_str != '')
						{
							$ids_str .= ',';
						}
						$ids_str .= "'" . $row['account'] . "'";
					}
					$src_rows[] = $row;
				}			
				$result->close();
				
				//取出账号名
				if($ids_str != '')
				{
					$sql = "SELECT `account`, `realname` FROM `t_admin` WHERE `account` IN ($ids_str)";
					$result = $db->query($sql);
					if($result)
					{
						while($row = $result->fetch_array(MYSQLI_ASSOC))
						{
							foreach($src_rows as $i=>$src_row)
							{
								if($src_row['account'] == $row['account'])
								{
									$src_rows[$i]['account'] = $row['realname'];
								}
							}
						}
						$result->close();
					}
				}
				
				$count = 0;
				foreach($src_rows as $row)
				{
					if($count != 0)
					{
						$json .= ',';
					}
					$json .= json_encode($row);
					++$count;
				}
				
				$result = $db->query("select count(*) from `t_manage_log` $condition");
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$total = $row[0];
					}
					$result->close();
				}
			}
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
			//DEBUG('{"total" : '.$total.', "rows" : ['.$json.']}');
		}
		break;
		case 22:
		{	// 角色封禁
			if(!has_privilege(3000))
			{
				echo '{"total":0, "rows":[]}';
				break;
			}
			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1);
			
			$childtype = $_POST['childtype'];
			$value     = $_POST['value'];
			
			$condition = '';
			switch($childtype){
				case 0:
				{
					$condition = '';
				}
				break;
				case 1:
				{
					$condition = "where `player_id` like '%$value%'";
				}
				break;
				case 2:
				{
					$condition = "where `server_id` like '%$value%'";
				}
				break;
			}
			$total = 0;
			$json = '';
			$result = $db->query("select `player_id`,`server_id`,`chat_time`,`ban_time` from `t_player_ban` $condition limit $pageIndex,$rows ",MYSQLI_STORE_RESULT);
			if($result)
			{
				$count = 0;
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					if($count != 0)
					{
						$json .= ',';
					}
					$json .= json_encode($row);
					++$count;
				}
				$result->close();
				
				$result = $db->query("select count(*) from `t_player_ban` $condition");
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$total = $row[0];
					}
					$result->close();
				}
			}
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;
		case 23:
		{	// IP封禁
			if(!has_privilege(3020))
			{
				echo '{"total":0, "rows":[]}';
				break;
			}
			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1);
			
			$childtype = $_POST['childtype'];
			$value     = $_POST['value'];
			
			$condition = '';
			switch($childtype){
				case 0:
				{
					$condition = '';
				}
				break;
				case 1:
				{
					$condition = "where `ip` like '%$value%'";
				}
				break;
			}
			$total = 0;
			$json = '';
			$result = $db->query("select `ip` from `t_ip_ban` $condition limit $pageIndex,$rows ",MYSQLI_STORE_RESULT);
			if($result)
			{
				$count = 0;
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					if($count != 0)
					{
						$json .= ',';
					}
					$json .= json_encode($row);
					++$count;
				}
				$result->close();
				
				$result = $db->query("select count(*) from `t_ip_ban` $condition");
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$total = $row[0];
					}
					$result->close();
				}
			}
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;
		case 24:
		{	// 账号封禁
			if(!has_privilege(3010))
			{
				echo '{"total":0, "rows":[]}';
				break;
			}
			$page = $_POST['page'];
			$rows = $_POST['rows'];
			$pageIndex = $rows*($page - 1);
			
			$childtype = $_POST['childtype'];
			$value     = $_POST['value'];
			
			$condition = '';
			switch($childtype){
				case 0:
				{
					$condition = '';
				}
				break;
				case 1:
				{
					$condition = "where `open_id` like '%$value%'";
				}
				break;
			}
			$total = 0;
			$json = '';
			$result = $db->query("select `open_id`,`ban_time` from `t_account_ban` $condition limit $pageIndex,$rows ",MYSQLI_STORE_RESULT);
			if($result)
			{
				$count = 0;
				while($row = $result->fetch_array(MYSQLI_ASSOC))
				{
					if($count != 0)
					{
						$json .= ',';
					}
					$json .= json_encode($row);
					++$count;
				}
				$result->close();
				
				$result = $db->query("select count(*) from `t_account_ban` $condition");
				if($result)
				{
					$row = $result->fetch_row();
					if($row)
					{
						$total = $row[0];
					}
					$result->close();
				}
			}
			echo '{"total" : '.$total.', "rows" : ['.$json.']}';
		}
		break;
		case 25:
		{	//GM权限管理
			if(!has_privilege(304))
			{
				echo 1;
				break;
			}
			$db_login = get_login_db();
			if(!$db_login)
			{
				echo '{"total":0,"rows":[],"ret":1}';
				break;
			}
			
			$page = $_POST['page'];
			$parm_rows = $_POST['rows'];
			$pageIndex = $parm_rows*($page - 1);
			$total_count = 0;
			
		    $condition_type =  $_POST['condition_type'];
			$condition_value =  $_POST['condition_value'];
			$set_open_id = $_POST['condition_value'];
			$set_privilege = $_POST['set_privilege'];
			$childtype = $_POST['childtype'];
			$con_open_id = '1';
			switch($childtype)
			{
				case 0:
				{//获得权限信息
					if($condition_value!='')
					{
						$condition_value = "'".$condition_value."'";
						if($condition_type==1)//open_id
						{
							$con_open_id = 'open_id='.$condition_value;
						}
						else if(($condition_type==2)||($condition_type==3))//角色名,角色ID
						{
							//查到对应的open_id
							$sql_1 = '';
							if($condition_type==2)
							{
								$sql_1 = 'SELECT `open_id` FROM `t_player_info` WHERE `player_name`='.$condition_value;
							}
							else
							{
								$sql_1 = 'SELECT `open_id` FROM `t_player_info` WHERE `player_id`='.$condition_value;
							}
							$result = $db->query($sql_1,MYSQLI_STORE_RESULT);
							if(!$result)
							{
								echo '{"total":0,"rows":[],"ret":1}';
								break;
							}
							
							
							$j = 0;
							$array_player = array();
							while($row1 = $result->fetch_array(MYSQLI_ASSOC))
							{
								$array_player[$j] = $row1['open_id'];
								$j++;
							}
							if(count($array_player)>0)
							{
								for($i=0;$i<count($array_player);++$i)
								{
									if($con_open_id=="1")
									{
										$con_open_id = " open_id in (";
									}
									$con_open_id .= $array_player[$i];
									if($i<count($array_player)-1)
									{
										$con_open_id .= ",";
									}
								}
								$con_open_id .= ")";
							}
							else
							{
								echo '{"total":0,"rows":[]}';
								break;
							}
						}
					}
					//login查找相关信息
					$sql_2 = 'SELECT `open_id`,`privilege` FROM `t_account_check` WHERE '.$con_open_id.' limit '.$pageIndex.','.$parm_rows;
					$sql_3 = 'SELECT COUNT(*) AS `total_count` FROM `t_account_check` WHERE '.$con_open_id;
					$result2 = $db_login->query($sql_2,MYSQLI_STORE_RESULT);
					$result3 = $db_login->query($sql_3,MYSQLI_STORE_RESULT);
					if((!$result2)||(!$result3))
					{
						echo '{"total":0,"rows":[],"ret":1}';
						break;
					}
					$row3=$result3->fetch_array(MYSQLI_ASSOC);
					if(!$row3)
					{
						$total_count = 0;
					}
					else
					{
						$total_count = $row3['total_count'];
					}
					
					while($row2=$result2->fetch_array(MYSQLI_ASSOC))
					{
						$rows[] = $row2;
					}
				    echo '{"total" : '.$total_count.', "rows" : '.json_encode($rows).'}';
					$db_login->close();
				}
				break;
				case 1:
				{//设置权限
					$set_open_id = $_POST['set_open_id'];
					$set_privilege = $_POST['set_privilege'];
					if(!(($set_open_id>0)&&($set_privilege>=0)))
					{
						echo 1;
						break;
					}
					$sql_1 = 'UPDATE `t_account_check` SET `privilege`='.$set_privilege.' WHERE `open_id`='.$set_open_id;
					$result1 = $db_login->query($sql_1,MYSQLI_STORE_RESULT);
					if(!$result1)
					{
						echo 1;
						break;
					}
					echo 0;
				}
				break;
			}
		}
		break;
		case 26:
		{//评论管理
		
			if(!has_privilege(409))
			{
				echo 1;
				break;
			}
			
			$childtype = $_POST['childtype'];
			switch($childtype)
			{
				case 1:
				{//添加
				    $add_server_id = $_POST['add_server_id'];
					$add_player_id = $_POST['add_player_id'];
					$add_hero_id = $_POST['add_hero_id'];
					$add_name = $_POST['add_name'];
					$add_word = $_POST['add_word'];
					$add_like_count = $_POST['add_like_count'];
					if(!($add_server_id>0 && $add_player_id>0 && $add_hero_id>0 && $add_like_count>=0 && $add_word!='' && $add_name!=''))
					{//数据不完整，无法插入
						echo 1;
				        break;
					}
					$ply_result=$db->query("SELECT * FROM `t_player_info` WHERE `player_id`=$add_player_id;");
					if(!$ply_result)
					{
						echo 1;
						break;
					}
					
					if(!($ply_row=$ply_result->fetch_array(MYSQLI_ASSOC)))
					{//不存在该玩家
						echo 1;
				        break;
					}
					
					$ply_result->close();
					//插入
				
					$add_name=$db->real_escape_string($add_name);
					$add_word=$db->real_escape_string($add_word);
					$add_name="'".$add_name."'";
					$add_word="'".$add_word."'";
					
					$result=$db->query("INSERT INTO `t_comment_info` (`server_id`,`player_id`,`hero_id`,`name`,`word`,`like_count`) VALUES($add_server_id,$add_player_id,$add_hero_id,$add_name,  $add_word,$add_like_count);");
					
					if(!$result)
					{
						echo 1;
				        break;
					}
					
					$result->close();
					echo 0;
				}
				break;
				case 2:
				{//修改赞数
					$up_id = $_POST['up_id'];
					$up_like_count = $_POST['up_like_count'];
					if($up_id<0||$up_like_count<0)
					{
						echo 1;
						break;
					}
					//修改
					$result1=$db->query("SELECT * FROM `t_comment_info` WHERE `id`=$up_id;");

					if((!$result1)||(!($row=$result1->fetch_array(MYSQLI_ASSOC))))
					{	
						echo 1;
						break;
					}
					
					$result1->close();
					
					$result2=$db->query("UPDATE `t_comment_info` SET `like_count`=$up_like_count WHERE `id`=$up_id;");
					if(!$result2)
					{
						echo 1;
						break;
					}
					echo 0;
				}
				break;
				case 3:
				{//删除评论
					$del_id=$_POST['del_id'];
					if(!(count($del_id)>0))
					{
						echo 1;
						break;
					}
					$con='';
					for($i=0;$i<count($del_id);$i++)
					{
						$con .= $del_id[$i];
						if($i<count($del_id)-1)
						{
							$con .= ",";
						}
					}
					$result=$db->query("DELETE FROM `t_comment_info` WHERE `id` IN($con);");
					if(!$result)
					{
						echo 1;
						break;
					}
				}
				break;
				case 4:
				{//查询评论
					$page = $_POST['page'];
					$parm_rows = $_POST['rows'];
					$pageIndex = $parm_rows*($page - 1);
					$total_count = 0;
					
					$condition_type =  $_POST['condition_type'];
					$condition_value =  $_POST['condition_value'];
					$server_id=$_POST['server_id'];
					
					$base_time=946598400;
					
					$con='1';
					if($condition_type>0&&$condition_value!='')
					{//open_id name player_id
						if(($condition_type==3)&&($condition_value>0))
						{
							$con = " `player_id`=$condition_value";
						}
						else if($condition_type==2)
						{
							$result_name=$db->query("SELECT `player_id` FROM `t_player_info` WHERE `player_name`='$condition_value';");
							while($row_name=$result_name->fetch_array(MYSQLI_ASSOC))
							{
								if($con=='1')
								{
									$con = " `player_id` IN(".$row_name['player_id'];
								}
								else
								{
									$con .= ",".$row_name['player_id'];
								}
							}
							if($con!='1')
							{
								$con .= ")";
							}
							else
							{
								echo '{"total":0,"rows":[]}';
								break;
							}
							$result_name->close();
						}
						else if(($condition_type==1)&&($condition_value>0))
						{
							$result_name=$db->query("SELECT `player_id` FROM `t_player_info` WHERE `open_id`=$condition_value;");
							while($row_name=$result_name->fetch_array(MYSQLI_ASSOC))
							{
								if($con=='1')
								{
									$con = " `player_id` IN(".$row_name['player_id'];
								}
								else
								{
									$con .= ",".$row_name['player_id'];
								}
							}
							if($con!='1')
							{
								$con .= ")";
							}
							else
							{
								echo '{"total":0,"rows":[]}';
								break;
							}
							$result_name->close();
						}
						else if($condition_type==4)
						{
							//评论内容
							$con = " `word` like '%$condition_value%' ";
						}
						else if(($condition_type==5)&&($condition_value>0))
						{
							//英雄
							$con = " `hero_id`=$condition_value ";
						}
						else if(($condition_type==6)&&($condition_value>0))
						{
							//点赞数
							$con = " `like_count`>=$condition_value ";
						}
						else if(($condition_type==7)&&($condition_value>0))
						{
							//评论id
							$con = " `id`=$condition_value ";
						}
					}
					
					if($server_id>0)
					{
						$con .= " AND `server_id`=$server_id ";
					}
					
					//查询
					$result=$db->query("SELECT `id`,`server_id`,`player_id`,`hero_id`,`name`,`word`,`like_count`,FROM_UNIXTIME(`time`+$base_time) AS `time` FROM `t_comment_info` WHERE $con limit $pageIndex,$parm_rows;");
					while($row=$result->fetch_array(MYSQLI_ASSOC))
					{
						$rows[] = $row;
					}
					$result->close();
					
					$result1=$db->query("SELECT COUNT(*) AS `count` FROM `t_comment_info` WHERE $con;");
					if($row=$result1->fetch_array(MYSQLI_ASSOC))
					{
						$total_count = $row['count'];
					}
					echo '{"total" : '.$total_count.', "rows" : '.json_encode($rows).'}';
					
				}
				break;
			}
		}
		break;
	}
	
	$db->close();
?>