// descriptor_factory.cpp: implementation of the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptor_factory.h"
#include "bit_readwriter.h"
#include "descriptor.h"
#include "application_descriptor.h"
#include "application_name_descriptor.h"
#include "application_usage_descriptor.h"
#include "application_recording_descriptor.h"
#include "simple_application_location_descriptor.h"
#include "simple_application_boundary_descriptor.h"
#include "transport_protocol_descriptor.h"
#include "parental_rating_descriptor.h"
#include "connection_requirement_descriptor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

Descriptor* DescriptorFactory::CreateDescriptor(BitReadWriter *rw)
{
    int descriptor_tag = rw->Read_On_Buffer(8);

    switch(descriptor_tag)
    {
        case Descriptor::APPLICATION_DESCRIPTOR:
            return new ApplicationDescriptor(rw);
        case Descriptor::APPLICATION_NAME_DESCRIPTOR:
            return new ApplicationNameDescriptor(rw);
        case Descriptor::APPLICATION_USAGE_DESCRIPTOR:
            return new ApplicationUsageDescriptor(rw);
        //case Descriptor::APPLICATION_RECORDING_DESCRIPTOR:
        //	return new ApplicationRecordingDescriptor(rw);
        case Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR:
            return new SimpleApplicationLocationDescriptor(rw);
        case Descriptor::SIMPLE_APPLICATION_BOUNDARY_DESCRIPTOR:
            return new SimpleApplicationBoundaryDescriptor(rw);
        case Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR:
            return new TransportProtocolDescriptor(rw);
        //case Descriptor::PARENTAL_RATING_DESCRIPTOR:
        //	return new ParentalRatingDescriptor(rw);
        case Descriptor::CONNECTION_REQUIREMENT_DESCRIPTOR:
            return new ConnectionRequirementDescriptor(rw);
        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of sedec namespace
