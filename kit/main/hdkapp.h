/*************************************************************************************************************
	File 		: hdkapp.h
	author 		: STC Component tstbcomp@humaxdigital.com
	comment		:
	date    	: 2013/11/25
	attention 	:

	(c) 2011-2014 Humax Co., Ltd.
	This program is produced by Humax Co., Ltd. (¡°Humax¡±) and
	the proprietary Software of Humax and its licensors. Humax provides you, as an Authorized Licensee,
	non-assignable, non-transferable and non-exclusive license to use this Software.
	You acknowledge that this Software contains valuable trade secrets of Humax and by using this Software
	you agree to the responsibility to take all reasonable efforts to protect the any information
	you receive from Humax. You are not permitted to duplicate, modify, distribute, sell or lease and
	reverse engineer or extract the source code of this Software unless you have Humax's written permission
	to do so.
	If you have no authorized license, discontinue using this Software immediately.

	THE SOFTWARE IS PROVIDED ¡°AS IS¡± AND HUMAX MAKES NO PROMISES, REPRESENTATIONS OR WARRANTIES,
	EITHER EXPRESS, IMPLIED OR STATUTORY, OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.
	IN NO EVENT SHALL HUMAX BE LIABLE FOR LOST PROFITS, REVENUES, OR DATA, FINANCIAL LOSSES OR
	INDIRECT, SPECIAL, CONSEQUENTIAL, EXEMPLARTY OR PUNITIVE DAMAGES WHATSOEVER RELATING TO YOUR USE OR
	INABILITY TO USE THE SOFTWARE.

	This License is effective until terminated. You may terminate this License at any time
	by destroying all copies of the Software including all documentation. This License will terminate
	immediately without notice from Humax to you if you fail to comply with any provision of this License.
	Upon termination, you must destroy all copies of the Software and all documentation.

	The laws of the Republic of Korea will apply to any disputes arising out of or relating to
	this Copyright Notice. All claims arising out of or relating to this Copyright Notice will be litigated
	in the Seoul Central District Court, in the Republic of Korea.
*************************************************************************************************************/

#ifndef __HDK_APPLICATION_H__
#define __HDK_APPLICATION_H__

typedef enum {
	HDKAPP_CC_INVALID		= 0,
	HDKAPP_CC_AUTOSTART		= 1,
	HDKAPP_CC_PRESENT		= 2,
	HDKAPP_CC_KILL			= 4,
	HDKAPP_CC_DISABLED		= 7
} eHdkAppControlCode;

typedef enum {
	HDKAPP_UT_RESERVED		= 0,
	HDKAPP_UT_TELETEST		= 1
} eHdkAppUsageType;

typedef enum {
	HDKAPP_PROTO_HTTP		= 0,
	HDKAPP_PROTO_OC
} eHdkAppProtocol;

/*------------------------------------------------------------------------
 * class HdkApplication
 *-----------------------------------------------------------------------*/
class HdkApplication {
public:
	bool	trused;
	/** if broadcast_related is false, it means that this application is broadcast independent application */
	bool	broadcast_related;
	bool	service_bound;
	unsigned int url_count;
	const char **urls;
	unsigned long org_id;
	unsigned short app_id;
	unsigned int priority;
	eHdkAppControlCode	control_code;
	eHdkAppUsageType	usage_type;
	eHdkAppProtocol		protocol;
};

#endif
