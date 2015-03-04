// DSISection.h: interface for the AITSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__AIT_SECTION_H__)
#define __AIT_SECTION_H__

using namespace std;
#include <list>

#include "section.h"
class Application;
class Descriptor;

class AITSection : public Section  
{
public:
	AITSection();
	AITSection(unsigned char *raw_buffer);
	AITSection(unsigned char *raw_buffer, unsigned int raw_length);
	virtual ~AITSection();
	virtual void PrintSection();

	/* Interfaces to get information (e.g. getter) */
	int GetTestApplicationFlag() { return test_application_flag;}
	unsigned int GetApplicationType() { return application_type;}
	unsigned int GetVersionNumber(){ return version_number; } 
	int GetCurrentNextIndicator(){return current_next_indicator;}
	unsigned int GetSectionNumber() { return section_number;}
	unsigned int GetLastSectionNumber() { return last_section_number;}
	unsigned int GetCommonDescriptorLength() { return common_descriptors_length;}
	list<Descriptor*> GetCommonDescriptors() { return m_common_descriptors;}
	unsigned int GetApplicationLoopLength() { return application_loop_length;}
	list<Application*> GetApplications() { return m_applications;}

protected:
	int test_application_flag;
	unsigned int application_type;
	unsigned int version_number;
	int current_next_indicator;
	unsigned int section_number;
	unsigned int last_section_number;
	unsigned int common_descriptors_length;
	list<Descriptor*> m_common_descriptors;
	unsigned int application_loop_length;
	list<Application*> m_applications;

private:
	virtual void WriteSection();
	virtual void SetSection();
	virtual void CalcSectionLength();
	virtual void decode();
};

#endif 
