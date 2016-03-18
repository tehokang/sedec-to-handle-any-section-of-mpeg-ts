// DSISection.h: interface for the AITSectionTranscoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__AIT_SECTION_TRANSCODER_H__)
#define __AIT_SECTION_TRANSCODER_H__

#include <list>

#include "application.h"
#include "descriptor.h"
#include "ait_section.h"
#include "section_common.h"
using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class Descriptor;

class AITSectionTranscoder : public AITSection 
{
public:
	AITSectionTranscoder();
	AITSectionTranscoder(unsigned char *raw_buffer);
	AITSectionTranscoder(unsigned char *raw_buffer, unsigned int raw_length);
	virtual ~AITSectionTranscoder();

	/* Scenario Interfaces to encode (setter) */
	void SetApplicationUrl(const char *base_url, const char *init_path);
	void SetApplicationVersion(const int major, const int minor, const int micro);
	void SetApplicationId(const int value);
	void SetOrganizationId(const int value);
	void SetRemoteConnection(const int value);
	void SetProtocolId(const int value);
	void SetOriginalNetworkId(const int value);
	void SetTransportStreamId(const int value);
	void SetServiceId(const int value);
	void SetComponentTag(const int value);

	/* Scenario Interfaces to encode (getter) */
	void GetApplicationVersion(int &major, int &minor, int &micro);
	void GetApplicationUrl(const char **base_url, const char **init_path);

	/* Interfaces to encode (setter) */
	void SetTestApplicationFlag(const int value) { test_application_flag = value;}
	void SetApplicationType(const int value) { application_type = value;}
	void SetVersionNumber(const int value) { version_number = value;}
	void SetCurrentNextIndicator(const int value) { current_next_indicator = value;}
	void SetSectionNumber(const int value) { section_number = value;}
	void SetLastSectionNumber(const int value) { last_section_number = value;}
	void SetTransportProtocolLabel(const char *label);
	void SetCommonDescriptors(const list<Descriptor*> value);
	void SetApplications(const list<Application*> value);

private:
	Descriptor* findDescriptor(list<Descriptor*>descriptors, Descriptor::DESCRIPTOR_TAG tag);
};

/** @} */

} // end of sedec namespace

#endif 
