/*************************************************************************************************************
	File 		: hdkappcontainer.cpp
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

#include "hdkappcontainer.h"
#include "scxlog.h"

#include <cstring>

using namespace std;

/*------------------------------------------------------------------------
 * class HdkApplicationContainer
 *-----------------------------------------------------------------------*/
HdkApplicationContainer::HdkApplicationContainer()
	: m_service_type(HDK_APPMGR_SERVTYPE_NONE), m_active_app(NULL)
{
}

HdkApplicationContainer::HdkApplicationContainer(eHdkAppContServiceType service_type)
	: m_service_type(service_type), m_active_app(NULL)
{
}

HdkApplicationContainer::~HdkApplicationContainer()
{
	removeAll();
}

bool HdkApplicationContainer::add(HdkApplication *app)
{
	if ( !app )
	{
		sl_err("[HdkApplicationContainer] application is null.\n");
		return false;
	}

	m_apps.push_back(app);

	sl_info("[HdkApplicationContainer] application is added(orgid=%d, appid=%d)\n",
		app->org_id, app->app_id);

	return true;
}

void HdkApplicationContainer::remove(unsigned long org_id, unsigned short app_id)
{
	vector<HdkApplication *>::iterator it = m_apps.begin();
	while ( it != m_apps.end() )
	{
		if ( (*it)->org_id == org_id && (*it)->app_id == app_id  )
		{
			delete *it;
			it = m_apps.erase(it);
		}
	}
}

void HdkApplicationContainer::remove(eHdkAppProtocol proto)
{
	vector<HdkApplication *>::iterator it = m_apps.begin();
	while ( it != m_apps.end() )
	{
		if ( (*it)->protocol == proto )
		{
			delete *it;
			it = m_apps.erase(it);
		}
	}
}

void HdkApplicationContainer::removeAll()
{
	vector<HdkApplication *>::iterator it;
	for ( it=m_apps.begin(); it!=m_apps.end(); ++it )
			delete *it;
	
	m_apps.clear();

	sl_info("[HdkApplicationContailer] All applications are destroyed.\n");
}

HdkApplication *HdkApplicationContainer::find(const char *url)
{
	if ( !url )
	{
		sl_err("[HdkApplicationContainer] url is null.\n");
		return NULL;
	}

	vector<HdkApplication *>::iterator it;
	for ( it=m_apps.begin(); it!=m_apps.end(); ++it )
	{
		for ( unsigned int i=0; i<(*it)->url_count; ++i )
		{
			if ( strncmp((*it)->urls[i], url, strlen(url)) == 0 ) 
				return *it;
		}
	}

	sl_err("[HdkApplicationContainer] cannot find the application(url=%s)\n", url);

	return NULL;
}

HdkApplication *HdkApplicationContainer::find(unsigned long org_id, unsigned short app_id)
{
	vector<HdkApplication *>::iterator it;
	for ( it=m_apps.begin(); it!=m_apps.end(); ++it )
	{
		if ( (*it)->org_id == org_id && (*it)->app_id == app_id  )
			return *it;
	}

	sl_err("[HdkApplicationContainer] cannot find the application(orgid=%d, appid=%d)\n",
		org_id, app_id);

	return NULL;
}

bool HdkApplicationContainer::hasAutoStartApp()
{
	vector<HdkApplication *>::iterator it;
	for ( it=m_apps.begin(); it!=m_apps.end(); ++it )
	{
		if ( (*it)->control_code == HDKAPP_CC_AUTOSTART )
			return true;
	}
	
	return false;
}

HdkApplication *HdkApplicationContainer::getActiveApplication()
{
	return m_active_app;
}

bool HdkApplicationContainer::setActiveApplication(const char *url)
{
	HdkApplication *app = find(url);
	if ( !app ) return false;
	m_active_app = app;

	return true;
}

HdkApplication *HdkApplicationContainer::next(HdkApplication *app)
{
	if ( m_apps.empty() )
	{
		sl_info("[HdkApplicationContailer] Container is empty.\n");
		return NULL;
	}

	// return first application if argument is NULL.
	if ( !app )
	{
		return *m_apps.begin();
	}

	vector<HdkApplication *>::iterator it;
	for ( it = m_apps.begin(); it != m_apps.end(); ++it )
	{
		if ( *it == app )
			return *(++it);
	}
	
	return NULL;
}

eHdkAppContServiceType HdkApplicationContainer::getServiceType() const
{
	return m_service_type;
}

void HdkApplicationContainer::setServcieType(eHdkAppContServiceType service_type)
{
	m_service_type = service_type;
}
