// ait_section_transcoder.cpp: implementation of the AITSectionTranscoder class.
//
//////////////////////////////////////////////////////////////////////

#include "section_common.h"
#include "ait_section_transcoder.h"
#include "descriptor.h"
#include "application.h"
#include "descriptor_factory.h"
#include "simple_application_location_descriptor.h"
#include "transport_protocol_descriptor.h"
#include "application_descriptor.h"

#include <string.h>
#include <cstddef>
#include <stdlib.h>


AITSectionTranscoder::AITSectionTranscoder()
{
	m_section_name = strdup("AITSectionTranscoder");
}

AITSectionTranscoder::AITSectionTranscoder(unsigned char *raw_buffer)
: AITSection(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{

}


AITSectionTranscoder::AITSectionTranscoder(unsigned char *raw_buffer, unsigned int raw_length) 
: AITSection(raw_buffer, raw_length)
{
	
}

AITSectionTranscoder::~AITSectionTranscoder()
{
	if(m_section_name) {
		free(m_section_name);
		m_section_name = NULL;
	}
}

Descriptor* AITSectionTranscoder::findDescriptor(list<Descriptor*>descriptors, 
												Descriptor::DESCRIPTOR_TAG tag)
{
	for (std::list<Descriptor*>::iterator it=descriptors.begin();
		it != descriptors.end(); ++it)
	{
		Descriptor *desc = (Descriptor*)*it;
		if( tag == desc->GetDescriptorTag())
			return desc;
	}
	return NULL;
}

void AITSectionTranscoder::SetApplicationUrl(char *base_url, char *init_path)
{
	printf("base_url +++: %s\n", base_url);
	printf("init_path +++: %s\n", init_path);

	for (std::list<Application*>::iterator it=m_applications.begin();
			it != m_applications.end(); ++it)
	{
		Application *app = (Application*)*it;
		Descriptor *desc = findDescriptor(app->GetDescriptors(), 
									Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
		((SimpleApplicationLocationDescriptor*)desc)->SetInitialPath(init_path);

		desc = findDescriptor(app->GetDescriptors(), 
								Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
		((TransportProtocolDescriptor*)desc)->SetBaseUrl(base_url);
	}
}

void AITSectionTranscoder::SetApplicationVersion(int major, int minor, int micro)
{
	for (std::list<Application*>::iterator it=m_applications.begin();
			it != m_applications.end(); ++it)
	{
		Application *app = (Application*)*it;
		Descriptor *desc = findDescriptor(app->GetDescriptors(), 
											Descriptor::APPLICATION_DESCRIPTOR);
		((ApplicationDescriptor*)desc)->SetApplicationVersion(major, minor, micro);
	}
}

void AITSectionTranscoder::GetApplicationVersion(int &major, int &minor, int &micro)
{
	for (std::list<Application*>::iterator it=m_applications.begin();
			it != m_applications.end(); ++it)
	{
		Application *app = (Application*)*it;
		Descriptor *desc = findDescriptor(app->GetDescriptors(), 
											Descriptor::APPLICATION_DESCRIPTOR);
		((ApplicationDescriptor*)desc)->GetApplicationVersion(&major, &minor, &micro);
	}
}

void AITSectionTranscoder::GetApplicationUrl(const char **base_url, const char **init_path)
{
	for (std::list<Application*>::iterator it=m_applications.begin();
			it != m_applications.end(); ++it)
	{
		Application *app = (Application*)*it;
		Descriptor *desc = findDescriptor(app->GetDescriptors(), 
											Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
		*init_path = ((SimpleApplicationLocationDescriptor*)desc)->GetInitialPath();

		desc = findDescriptor(app->GetDescriptors(), 
								Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
		*base_url = ((TransportProtocolDescriptor*)desc)->GetBaseUrl();
	}

}