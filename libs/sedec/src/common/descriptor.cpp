// Descriptor.cpp: implementation of the Descriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptor.h"
#include "bit_readwriter.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Descriptor::Descriptor()
{
	descriptor_tag = UNKNOWN_DESCRIPTOR;
	descriptor_length = 0;
}

Descriptor::Descriptor(BitReadWriter *rw)
{
	descriptor_tag = (*(rw->GetCurrentBuffer()-1) & 0xff);
	descriptor_length = rw->Read_On_Buffer(8);
}

Descriptor::~Descriptor()
{

}

int Descriptor::GetDescriptorTag()
{
	return descriptor_tag;
}

int Descriptor::GetDescriptorLength()
{
	calcLength();
	return descriptor_length + 2;
}

UnknownDescriptor::UnknownDescriptor()
{

}

UnknownDescriptor::UnknownDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
	rw->Skip_On_Buffer(descriptor_length*8);
}

UnknownDescriptor::~UnknownDescriptor()
{

}

void UnknownDescriptor::PrintDescriptor()
{
	SECTION_DEBUG("\n");
	SECTION_DEBUG("\tdescriptor_tag : 0x%02x (unknown descriptor) \n", descriptor_tag);
	SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);	
	SECTION_DEBUG("\n");
}
