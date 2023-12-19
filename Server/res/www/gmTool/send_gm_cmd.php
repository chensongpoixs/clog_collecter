<?php
	require_once('./header.php');
	
	if(!has_privilege(407))
	{
		DEBUG('has_privilege(407)');
		echo 'no privilege';
		exit;
	}
			
	require_once('./notice_gm.php');
	set_time_limit(300);    
	 
	$cmd0 = '';
	
	if($_POST['to'] == "render_server")
	{
		$cmd0 = 'cmd_to_render';
	}
	
	if($cmd0 == '')
	{
		echo "unknown to " . $_POST['to'];
		exit;
	}
	//DEBUG("");
	$arr_w2gm = array();
	$arr_w2gm['cmd'] = strval($cmd0); 
	$arr_w2gm['para'] = strval($_POST['para']); 
	$temp = pack_msg(json_encode($arr_w2gm));
	echo json_encode($temp);
	
	log_manager(NULL, "gm_cmd", get_log_str($arr_w2gm));
?>