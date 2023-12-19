<?php
	require_once('../config.php');
	
	function get_column_names($db, $table_name, $fileds, $excepts)
	{
		//DEBUG("query SHOW COLUMNS FROM $table_name");
		$rescolumns = $db->query("SHOW COLUMNS FROM $table_name");
		if($rescolumns == false)
		{
			//DEBUG("query failed");
			return 1;
		}
		$result = array(array(), array());
		
		while($row = $rescolumns->fetch_array(MYSQLI_ASSOC))
		{
			//DEBUG(json_encode($row));
			if($fileds != NULL)
			{
				if(is_array($fileds))
				{
					if(in_array($row['Field'], $fileds) == false)
					{
						continue;	
					}
				}
				else if($row['Field'] != $fileds)
				{
					continue;
				}
			}
			if($excepts != NULL)
			{
				if(is_array($excepts))
				{
					if(in_array($row['Field'], $excepts) == true)
					{
						continue;	
					}
				}
				else if($row['Field'] == $excepts)
				{
					continue;
				}
			}
			$result[0][] = $row['Field'];
			$result[1][] = $row['Type'];
		}
		return $result;
	}
	
	function is_record_exist($db, $table_name, $column_name, $id)
	{
		$sql = "select $column_name from $table_name where $column_name='$id'";
		//DEBUG("sql = $sql");
		$codeidexist = $db->query($sql);
		$ret = 0;
		if($codeidexist && ($codeidexist->num_rows > 0))
		{
			//DEBUG("id=$id, num_rows=".$codeidexist->num_rows);
			$ret = 1;
		}
		$codeidexist->close();
		return $ret;
	}
	
	function insert_to_db($db, $table_name, $col_name_array, $col_value_str, $test)
	{
		$col_name_str = '`' . implode("`,`",$col_name_array) . '`';
		$sql = "insert into $table_name ($col_name_str) values ($col_value_str)";
		if($test)
		{
			DEBUG($sql);
			return make_result(0, '');
		}
		 
		$result = $db->query($sql);

		if($result == false)
		{
			return make_result(1, $sql);
		}
		return make_result(0, '');
	}
	
	function db_query($db, $sql, $test)
	{
		if($test)
		{
			DEBUG($sql);
			return true;
		}
		return $db->query($sql);
	}
	
	//索引是整数 从 0 开始
	function integer_array_to_sql_value($db, $array_integer_key)
	{
		$sql_values = '';
		$flag_first = true;
		foreach($array_integer_key as $data)
		{
			if($flag_first == false)
			{
				$sql_values = $sql_values . ',';
			}
			$sql_values = $sql_values . "'" . $db->real_escape_string($data) . "'";
			$flag_first = false;
		}
		return $sql_values;
	 }
	 
	 function make_result($ret_code, $ret_msg)
	 {
		$result = array();
		$result['code'] = $ret_code;
		$result['msg'] = $ret_msg;
		return $result;
	 }
	 
	 function get_result_code($result)
	 {
		if(is_array($result) && isset($result['code']))
		{
			return $result['code']; 
		}
		return 0;
	 }
	 
	 function get_result_msg($result)
	 {
		if(is_array($result) && isset($result['msg']))
		{
			return $result['msg']; 
		}
		return '';
	 }
	 
	 //$condition include where. like 'where id = 1'
	 function get_row_count($db, $table_name, $condition)
	 {
		$result = $db->query("SELECT count(*) from `$table_name` $condition");
		if($result)
		{
			$row = $result->fetch_row();
			$result->close();
			if($row)
			{
				return $row[0];
			}
		}
		return 0;
	 }
	 
	 //索引是字符串
	 //$array_string_key array(excel_column_name1=>excel_value1, ...)
	 //$keys array(db_column_name1, ...)
	 function string_array_to_sql_value($db, $array_string_key, $keys)
	 {
		$ret_code = 0;
		$ret_msg = '';
		$flag_first = true;
		foreach($keys as $key)
		{
			if(isset($array_string_key[$key]) == false)
			{
				$ret_code = 1;
				$ret_msg = "$key not exist";
				return make_result($ret_code, $ret_msg);
			}
			if($flag_first == false)
			{
				$ret_msg = $ret_msg . ',';
			}
			if($array_string_key[$key] == 'NOW()')
			{
				$ret_msg = $ret_msg . "NOW()";
			}
			else
			{
				$ret_msg = $ret_msg . "'" . $db->real_escape_string($array_string_key[$key]) . "'";
			}
			$flag_first = false;
		}
		return make_result($ret_code, $ret_msg);
	 }
	 
	 //check key
	 function check_column($excel_keys, $db_keys, $skips)
	 {
		foreach($db_keys as $key)
		{
			if(is_skip($key, $skips))
			{
				continue;
			}
			if(in_array($key, $excel_keys) == false)
			{
				return make_result(1, "column '$key' not exist in excel");
			}
		}
		return make_result(0, '');
	 }
 
	 function check_datetime($data)
	 {
		 $patten = '/(\d{4})-(\d{2})-(\d{2})\s(\d{2}):(\d{2}):(\d{2})/';
		 $matches = array();
		if(preg_match($patten, $data, $matches))
		{
			if($matches[1] >= 2015 //年
			  && $matches[2] >= 1 && $matches[2] <= 12 //月
			  && $matches[3] >= 1 && $matches[3] <= 31 //日
			  && $matches[4] >= 0 && $matches[4] <= 23 //时
			  && $matches[5] >= 0 && $matches[5] <= 59 //分
			  && $matches[6] >= 0 && $matches[6] <= 59) //秒
			{
				return '';
			}
		}
		return 'YYYY-MM-DD hh:mm:ss';
	 }
 
	//col_name_array = [][] 第一维列名 第二维数据类型名
	 function check_excel_column_format($ExcelData, $col_name_array, $start_index, $skips)
	 {
		$highestRow = count($ExcelData);
		$highestColumn = count($ExcelData[0]);
		$column_names = $col_name_array[0];
		$column_types = $col_name_array[1];
		// DEBUG('highestRow='. json_encode($highestRow));
		// DEBUG('highestColumn='. json_encode($highestColumn));
		// DEBUG('col_name_array='. json_encode($col_name_array));
		for ($row = $start_index; $row < $highestRow; $row++)
		{
			for ($col = 0; $col < $highestColumn; $col++)
			{ 
				$column_name = $ExcelData[0][$col];
				if(is_skip($column_name, $skips))
				{
					continue;
				}
				$key = array_search($column_name, $column_names);
				if($key != false)
				{
					$column_value = $ExcelData[$row][$col];
					if($column_types[$key] == 'datetime')
					{
						//date time format check
						$ret = check_datetime($column_value);
						if($ret != '')
						{
							// DEBUG("row = " . ($row + 1) . ', ExcelData=' . json_encode($ExcelData[$row]));
							return("[line:" . ($row + 1) . ", column:$column_name format error: $column_value => format should be " . $ret);
						}
					}
				}
			}
		}
		return '';
	 }
	 
	 function is_skip($key, $skips)
	 {
		if($skips != NULL)
		{
			if(is_array($skips))
			{
				if(in_array($key, $skips) == true)
				{
					return true;	
				}
			}
			else if($key == $skips)
			{
				return true;
			}
		}
		return false;
	 }
?>
