function reward_objs2db_str(rewards){
	//javascript obj to json string
	var json = "[";
	for(var i = 0; i < rewards.length; i ++){
		if(i != 0)
		{
			json += ',';
		}
		json += '{'
		json += '"type":';
		json += parseInt(rewards[i].type);
		json += ',"value1":';
		json += parseInt(rewards[i].value1);
		json += ',"value2":';
		json += parseInt(rewards[i].value2);
		json += "}";
	}
	json += "]";			
	return json;
}

function id2text(maps, id){
	for(var i = 0; i < maps.length; ++i)
	{
		if(maps[i].id == id)
		{
			return maps[i].text;
		}
	}
	return id;
}

function reward_id2text(id){
	return id2text(g_reward_type, id);
}

function money_id2text(id){
	return id2text(g_currency_type, id);
}

function item_id2text(id){
	return id2text(g_items, id);
}

function hero_id2text(id){
	return id2text(g_heros, id);
}

function text2id(text){
	for(var i = 0; i < maps.length; ++i)
	{
		if(maps[i].text == text)
		{
			return maps[i].id;
		}
	}
	return text;
}

function reward_text2id(text){
	return text2id(g_reward_type, text);
}

function money_text2id(text){
	return text2id(g_currency_type, text);
}

function item_text2id(text){
	return text2id(g_items, text);
}

function hero_text2id(text){
	return text2id(g_heros, text);
}

function get_reward_name(reward_type, reward_id){
	
	if(reward_type == 1)
	{
		return money_id2text(reward_id);
	}
	else if(reward_type == 3)
	{
		return item_id2text(reward_id);
	}
	else if(reward_type == 4)
	{
		return hero_id2text(reward_id);
	}
	else
	{
		return reward_id2text(reward_type);
	}
}

function get_reward_value2_name(reward_type, reward_id){
	
	if(reward_type == 1)
	{
		return money_id2text(reward_id);
	}
	else if(reward_type == 3)
	{
		return item_id2text(reward_id);
	}
	else if(reward_type == 4)
	{
		return hero_id2text(reward_id);
	}
	else
	{
		return '';
	}
}

function reward_db_str2objs(str){
	//json string to javascript obj
	//var rewards = JSON.parse(str);
	var rewards = eval('(' + str + ')');
	for(var i = 0; i < rewards.length; i ++)
	{
		rewards[i].name = get_reward_name(rewards[i].type, rewards[i].value2);
	}
	return rewards;
}

//自动根据奖励类型修改value2 
function auto_value2_combobox(reward_type, combo_name)
{
	if(reward_type == 1)
	{
		$(combo_name).combobox('readonly', false);
		$(combo_name).combobox('loadData', g_currency_type);
		$(combo_name).combobox('setValue', g_currency_type[0].id);
	}
	else if(reward_type == 3)
	{
		$(combo_name).combobox('readonly', false);
		$(combo_name).combobox('loadData', g_items);
		$(combo_name).combobox('setValue', g_items[0].id);
	}
	else if(reward_type == 4)
	{
		$(combo_name).combobox('readonly', false);
		$(combo_name).combobox('loadData', g_heros);
		$(combo_name).combobox('setValue', g_heros[0].id);
	}
	else
	{
		$(combo_name).combobox('loadData', [{'id':0, 'text': L('common_not_used')}]);
		$(combo_name).combobox('setValue', 0);
		$(combo_name).combobox('readonly', true);
	}
}