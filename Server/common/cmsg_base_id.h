/***********************************************************************************************
created: 		2019-05-13

author:			chensong

purpose:		msg_base_id
************************************************************************************************/


#ifndef _C_MSG_BASE_ID_H_
#define _C_MSG_BASE_ID_H_

namespace chen {
	enum EMsgBaseID
	{
		Msg_Client_Max = 3000,
		R2A_BeartHeart,
		A2R_BeartHeart,
		A2R_EncryptKeyUpdate,
		R2A_Login,
		A2R_Login,
		A2R_AuthorizationUpdate,

		D2A_BeartHeart  = 3100,
		A2D_BeartHeart,
		A2D_EncryptKeyUpdate,
		D2A_Login,
		A2D_Login,
		A2D_AuthorizationUpdate,
		
		Msg_Max,
	};

}// namespace chen

#endif // !#define _C_MSG_BASE_ID_H_