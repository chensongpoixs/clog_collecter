<?php
require_once('./header.php');

if(!isset($_GET["version"]) || $_GET["version"] == NULL )
{
	$reply["status"] = "arg error, no version";
	echo json_encode($reply);
	exit;	
}

$db = get_global_db();
$str = $db->real_escape_string($_GET["version"]);
if($str == "all")
{
	$result = $db->query("SELECT distinct version FROM t_server_info ", MYSQLI_STORE_RESULT);
	if(!$result){
		$reply["status"] = "query server_info error, version:all";
		echo json_encode($reply);
		exit;
	}
	while ($row = $result->fetch_assoc())
	{
		if($row["version"] == '')
		{
			continue;
		}
		$versions[] = $row["version"];
	}
	$result->close();
}
else
{
	$versions = explode(',',$str); 
}

foreach ($versions as $key => $value) { 
	$result = $db->query("SELECT * FROM t_server_info WHERE version = '$value'", MYSQLI_STORE_RESULT);

	if(!$result){
		$reply["status"] = "query server_info error, version:".$value;
		echo json_encode($reply);
		exit;
	}

	$server_info = [];
	$has_server = false;
	$index = 0;
	$content = "{\n";
	$content = $content . "\t\"server_list\" : [\n";
	while ($row = $result->fetch_assoc())
	{
		if($index != 0)
		{
			$content = $content . "\t\t,\n";
		}			
		$content = $content . "\t\t{\n";
		
		$content = $content . "\t\t\t\"id\" : "         . $row["id"] . ",\n";
		$content = $content . "\t\t\t\"show_id\" : "    . $row["show_id"] . ",\n";
		$content = $content . "\t\t\t\"name\" : \""     . $row["name"] . "\",\n";
		$content = $content . "\t\t\t\"ip\" : \""       . $row["ip"] . "\",\n";
		$content = $content . "\t\t\t\"status\" : "     . $row["status"] . ",\n";
		$content = $content . "\t\t\t\"platform\" : \"" . $row["platform"] . "\",\n";
		$content = $content . "\t\t\t\"is_new\" : "     . $row["is_new"] . ",\n";
		$content = $content . "\t\t\t\"is_suggest\" : " . $row["is_suggest"] . ",\n";
		$content = $content . "\t\t\t\"att_url\" : \""  . $row["att_url"] . "\"\n";
		$content = $content . "\t\t\t\"open_time\" : \""  . $row["open_time"] . "\"\n";
		
		$content = $content . "\t\t}\n";
		
		
		
		$server_info["server_list"][$index]["id"] = (int)$row["id"];
		$server_info["server_list"][$index]["show_id"] = (int)$row["show_id"];
		$server_info["server_list"][$index]["name"] = urlencode($row["name"]);
		$server_info["server_list"][$index]["ip"] = $row["ip"];
		$server_info["server_list"][$index]["status"] = (int)$row["status"];
		$server_info["server_list"][$index]["platform"] = $row["platform"];
		$server_info["server_list"][$index]["is_new"] = (int)$row["is_new"];
		$server_info["server_list"][$index]["is_suggest"] = (int)$row["is_suggest"];
		$server_info["server_list"][$index]["att_url"] = $row["att_url"];
		$index++;
		$has_server = true;
	}
	$content = $content . "\t]\n}\n";
	
	$result->close();

	if(!$has_server)
	{
		$reply["status"] = "server list empty, check the version:".$value;
		echo json_encode($reply);
		exit;	
	}

	if (!is_dir('server_list'))
	{
		mkdir('server_list', 0777); 
	}
	if(file_put_contents('server_list/'.$value, $content))
	//if(file_put_contents('server_list/'.$value, urldecode(json_encode($server_info))))
	{
		$reply["status"] = "ok";
	}
	else
	{
		$reply["status"] = "write file error, check dir write permission";
		echo json_encode($reply);
		exit;
	}
}

echo json_encode($reply);

function free_result(&$db, &$result)
{
	// 存储过程有执行状态结果, 需要释放掉才能执行后面的sql
	while ($result)
	{
		$result->free();
		$db->next_result();
		$result = $db->store_result();
	}
}
?>