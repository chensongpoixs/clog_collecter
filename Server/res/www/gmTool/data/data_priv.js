var g_privs=[
{id:1},{id:2},{id:3},
	{
	id: 4,
	text: '操作管理',
	children: [
			{		
				id:400
			},
			{
			  
				id: 401,
				text: '云渲染信息',
				children: [
						{
							id: 4010,
							text: '查看云渲染app信息'
						},{
							id: 4011,
							text: '添加云渲染app信息'
						},{
							id: 4012,
							text: '修改云渲染app信息'
						},{
							id: 4013,
							text: '删除云渲染app信息'
						}
				]
			} ,{},{},{},{},{}
			,{
				id: 407,
				text: 'gm命令'
			} 
		]
	},
	{
		id: 5,
		text: '后台管理',
		children: [
					{
						id: 500,
						text: '权限管理',
						children: [
									{
										id: 5000,
										text: '添加后台账号'
									},{
										id: 5001,
										text: '修改权限'
									},{
										id: 5002,
										text: '删除后台账号'
									},{
										id: 5003,
										text: '重置密码'
									}
						]
					},{
						id: 501,
						text: '操作日志'
					}
		]
	}
];
