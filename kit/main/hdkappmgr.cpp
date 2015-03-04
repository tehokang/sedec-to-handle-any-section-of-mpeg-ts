/*************************************************************************************************************
	File 		: hdkappmgr.h
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

#include "hdkappmgr.h"
#include "hdkappcontainer.h"
#include "hdksystem.h"
#include "scxlog.h"

#include <iostream>

using namespace std;

#define HDK_APPMGR_MAX_CONTAINERS		(2)

/*------------------------------------------------------------------------
 * class HdkApplicationManager
 *-----------------------------------------------------------------------*/
HdkApplicationManager *HdkApplicationManager::s_the_appmgr = NULL;

HdkApplicationManager::HdkApplicationManager()
	: m_state(HDKAPPMGR_STATE_IDLE),
	m_prev_app_container(NULL),
	m_target_app(NULL)
{
}

HdkApplicationManager::~HdkApplicationManager()
{
	popAll();
	m_state = HDKAPPMGR_STATE_IDLE;
	m_prev_app_container = NULL;
	m_target_app = NULL;
}

bool HdkApplicationManager::push(HdkApplicationContainer *container)
{
	if ( !container )
	{
		sl_err("[HdkApplicationManager] invalid container argument.\n");
		return false;
	}

	m_lock.lock();
	m_prev_app_container = m_app_container_queue.front();
	m_app_container_queue.push(container);
	m_lock.unlock();

	sl_info("[HdkApplicationManager] push the application container to queue(total=%d).\n",
		m_app_container_queue.size());

	return true;
}

void HdkApplicationManager::pop()
{
	if ( m_app_container_queue.empty() ) return;

	m_lock.lock();

	HdkApplicationContainer *cont = m_app_container_queue.front();
	if ( cont ) delete cont;

	m_app_container_queue.pop();

	m_lock.unlock();

	sl_info("[HdkApplicationManager] pop the application container from queue(total=%d).\n",
		m_app_container_queue.size());
}

void HdkApplicationManager::popAll()
{
	m_lock.lock();
	while ( !m_app_container_queue.empty() )
	{
		HdkApplicationContainer *cont = m_app_container_queue.front();
		if ( cont ) delete cont;
		m_app_container_queue.pop();
	}
	m_lock.unlock();

	sl_info("[HdkApplicationManager] pop all application containers from queue.\n");
}

bool HdkApplicationManager::runApplication(HdkApplication *app)
{
	return true;
}

bool HdkApplicationManager::stopCurrentApplication()
{
	return true;
}

HdkApplicationContainer *HdkApplicationManager::getCurrentContainer()
{
	return m_app_container_queue.front();
}

void *HdkApplicationManager::run()
{
	for ( ;; )
	{
		runLifeCycle();

		SCXThread::sleep(10);
	}

	return NULL;
}

void HdkApplicationManager::runLifeCycle()
{
	switch ( m_state )
	{
	case HDKAPPMGR_STATE_IDLE:
		return stateIdle();
	case HDKAPPMGR_STATE_NEW:
		return stateNew();
	case HDKAPPMGR_STATE_PREV_CHECK:
		return statePrevCheck();
	case HDKAPPMGR_STATE_PREV_CHECK_AUTH:
		return statePrevCheckAuth();
	case HDKAPPMGR_STATE_DISCARD:
		return stateDiscard();
	case HDKAPPMGR_STATE_KILL:
		return stateKill();
	case HDKAPPMGR_STATE_LOAD:
		return stateLoad();
	default:
		break;
	}
}

void HdkApplicationManager::stateIdle()
{
	if ( m_app_container_queue.empty() < HDK_APPMGR_MAX_CONTAINERS ) return;

	m_target_app = NULL;
	m_state = HDKAPPMGR_STATE_NEW;
	sl_info("[HdkApplicationManager] state changed [IDLE] -> [NEW]\n");
}

void HdkApplicationManager::stateNew()
{
	if ( !m_prev_app_container
		|| m_prev_app_container->getServiceType() == HDK_APPMGR_SERVTYPE_NONE
		|| !m_prev_app_container->hasAutoStartApp() )
	{
		m_state = HDKAPPMGR_STATE_DISCARD;
		sl_info("[HdkApplicationManager] state changed [NEW] -> [DISCARD]\n");
	}
	else
	{
		HdkApplicationContainer *cont = getCurrentContainer();
		if ( !cont ) return goIdle();

		if ( cont->getServiceType() == HDK_APPMGR_SERVTYPE_NEW )
		{
			m_state = HDKAPPMGR_STATE_PREV_CHECK;
			sl_info("[HdkApplicationManager] state changed [NEW] -> [PREV_CHECK]\n");
		}
		else
		{
			m_state = HDKAPPMGR_STATE_PREV_CHECK_AUTH;
			sl_info("[HdkApplicationManager] state changed [NEW] -> [PREV_CHECK_AUTH]\n");
		}
	}
}

void HdkApplicationManager::statePrevCheck()
{
	HdkApplication *app = m_prev_app_container->getActiveApplication();
	if ( !app ) return goIdle();

	if ( app->service_bound )
	{
		m_state = HDKAPPMGR_STATE_KILL;
		sl_info("[HdkApplicationManager] state changed [PREV_CHECK] -> [KILL]\n");
		return;
	}

	if ( !app->broadcast_related )
	{
		// TODO::Was the service selection triggered by the application?
	}

	// TODO::Is it signaled in the new service??? 
	
	if ( app->control_code == HDKAPP_CC_KILL )
	{
		m_state = HDKAPPMGR_STATE_KILL;
		sl_info("[HdkApplicationManager] state changed [PREV_CHECK] -> [KILL]\n");
		return;
	}

	sl_info("[HdkApplicationManager] state changed [PREV_CHECK] -> [FINISH]\n");
	return goIdle();
}

void HdkApplicationManager::statePrevCheckAuth()
{
	HdkApplication *app = m_prev_app_container->getActiveApplication();
	if ( !app ) return goIdle();

	// TODO:: Is it still signalled as a separate entry or through an external appliation
	// authorization descriptor?

	if ( app->control_code == HDKAPP_CC_KILL )
	{
		m_state = HDKAPPMGR_STATE_KILL;
		sl_info("[HdkApplicationManager] state changed [PREV_CHECK_AUTH] -> [KILL]\n");
		return;
	}

	sl_info("[HdkApplicationManager] state changed [PREV_CHECK_AUTH] -> [FINISH]\n");
	return goIdle();
}

void HdkApplicationManager::stateDiscard()
{
	if ( !HdkSystem::getNetworkStatus() )
	{
		HdkApplicationContainer *cont = getCurrentContainer();
		if ( !cont ) return goIdle();
		cont->remove(HDKAPP_PROTO_HTTP);
	}

	m_state = HDKAPPMGR_STATE_LOAD;
	sl_info("[HdkApplicationManager] state changed [DISCARD] -> [LOAD]\n");
}

void HdkApplicationManager::stateKill()
{
	stopCurrentApplication();

	m_state = HDKAPPMGR_STATE_DISCARD;
	sl_info("[HdkApplicationManager] state changed [KILL] -> [DISCARD]\n");
}

void HdkApplicationManager::stateLoad()
{
	HdkApplicationContainer *cont = getCurrentContainer();
	if ( !cont ) return goIdle();

	while ( (m_target_app = cont->next(m_target_app)) )
	{
		if ( m_target_app->control_code == HDKAPP_CC_AUTOSTART ) break;
	}
}

void HdkApplicationManager::stateFinish()
{
	sl_info("[HdkApplicationManager] state changed [FINISH] -> [IDLE]\n");
	return goIdle();
}

void HdkApplicationManager::goIdle()
{
	pop();
	m_state = HDKAPPMGR_STATE_IDLE;
	sl_info("[HdkApplicationManager] go to [IDLE]\n");
}
