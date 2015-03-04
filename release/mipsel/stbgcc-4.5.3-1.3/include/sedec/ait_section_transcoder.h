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

class AITSectionTranscoder : public AITSection 
{
public:
	AITSectionTranscoder();
	AITSectionTranscoder(unsigned char *raw_buffer);
	AITSectionTranscoder(unsigned char *raw_buffer, unsigned int raw_length);
	virtual ~AITSectionTranscoder();

	/* Scenario Interfaces to encode (setter) */
	void SetApplicationUrl(char *base_url, char *init_path);	
	void SetApplicationVersion(int major, int minor, int micro);

	/* Scenario Interfaces to encode (getter) */
	void GetApplicationVersion(int &major, int &minor, int &micro);
	void GetApplicationUrl(const char **base_url, const char **init_path);

	/* Interfaces to encode (setter) */
	void SetTestApplicationFlag(int value) { test_application_flag = value;}
	void SetApplicationType(int value) { application_type = value;}
	void SetVersionNumber(int value) { version_number = value;}
	void SetCurrentNextIndicator(int value) { current_next_indicator = value;}
	void SetSectionNumber(int value) { section_number = value;}
	void SetLastSectionNumber(int value) { last_section_number = value;} 
	void SetCommonDescriptors(list<Descriptor*> value) 
	{ 
		common_descriptors_length = 0;
		for (list<Descriptor*>::iterator it=value.begin();
			it != value.end(); ++it)
		{
			Descriptor *desc = (Descriptor*)*it;
			common_descriptors_length+=desc->GetDescriptorLength();
		}
		m_common_descriptors = value;
	}
	void SetApplications(list<Application*> value) 
	{ 
		application_loop_length = 0;
		for (list<Application*>::iterator it=value.begin();
				it != value.end(); ++it)
		{
			Application *app = (Application*)*it;
			application_loop_length += app->GetApplicationLength();
		}		
		m_applications = value;
	}



private:
	Descriptor* findDescriptor(list<Descriptor*>descriptors, Descriptor::DESCRIPTOR_TAG tag);
};

#endif 
