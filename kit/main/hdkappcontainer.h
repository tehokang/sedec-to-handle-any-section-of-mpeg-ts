/*************************************************************************************************************
	File 		: hdkappcontainer.h
	author 		: STC Component tstbcomp@humaxdigital.com
	comment		:
	date    	: 2013/12/02
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

#ifndef __HDK_APP_CONTAINER_H__
#define __HDK_APP_CONTAINER_H__

#include "hdkapp.h"
#include <vector>

typedef enum {
	/** if current channel has no AIT, it should be set to HDK_APPMGR_SERVTYPE_NONE */
	HDK_APPMGR_SERVTYPE_NONE	= 0,
	HDK_APPMGR_SERVTYPE_NEW,
	HDK_APPMGR_SERVTYPE_UPDATE
} eHdkAppContServiceType;

/*------------------------------------------------------------------------
 * class HdkApplicationContainer
 *-----------------------------------------------------------------------*/
class HdkApplicationContainer {
public:
	HdkApplicationContainer();
	HdkApplicationContainer(eHdkAppContServiceType service_type);
	virtual ~HdkApplicationContainer();

	bool add(HdkApplication *app);
	void remove(unsigned long org_id, unsigned short app_id);
	void remove(eHdkAppProtocol proto);
	void removeAll();
	HdkApplication *find(const char *url);
	HdkApplication *find(unsigned long org_id, unsigned short app_id);
	bool hasAutoStartApp();
	HdkApplication *getActiveApplication();
	bool setActiveApplication(const char *url);

	// if app is NULL, it returns first application in list.
	HdkApplication *next(HdkApplication *app);

	eHdkAppContServiceType getServiceType() const;
	void setServcieType(eHdkAppContServiceType service_type);

private:
	eHdkAppContServiceType	m_service_type;
	std::vector<HdkApplication *>		m_apps;
	HdkApplication *m_active_app;
};

#endif	/* __HDK_APP_CONTAINER_H__ */
