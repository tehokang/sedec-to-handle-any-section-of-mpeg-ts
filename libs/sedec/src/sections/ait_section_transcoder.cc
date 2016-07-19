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

namespace sedec
{

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

void AITSectionTranscoder::SetApplicationUrl(const char *base_url, const char *init_path)
{
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

void AITSectionTranscoder::SetApplicationVisibility(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetVisibility(value);
    }
}

void AITSectionTranscoder::SetApplicationVersion(const int major, const int minor, const int micro)
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

void AITSectionTranscoder::SetTransportProtocolLabel(const char *label)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetTransportProtocolLabel(label);

        desc = findDescriptor(app->GetDescriptors(),
                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportProtocolLabel((unsigned char)atoi(label));
    }
}

void AITSectionTranscoder::SetApplicationId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetApplicationId(value);
    }
}

void AITSectionTranscoder::SetOrganizationId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetOrganizationId(value);
    }
}

void AITSectionTranscoder::SetProtocolId(int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetProtocolId(value);
    }
}

void AITSectionTranscoder::SetRemoteConnection(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetRemoteConnection(value);
    }
}

void AITSectionTranscoder::SetOriginalNetworkId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetOriginalNetworkId(value);
    }
}

void AITSectionTranscoder::SetTransportStreamId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportStreamId(value);
    }
}

void AITSectionTranscoder::SetServiceId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetServiceId(value);
    }
}

void AITSectionTranscoder::SetComponentTag(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetComponentTag(value);
    }
}

void AITSectionTranscoder::SetCommonDescriptors(list<Descriptor*> value)
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

void AITSectionTranscoder::SetApplications(list<Application*> value)
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

} // end of sedec namespace

