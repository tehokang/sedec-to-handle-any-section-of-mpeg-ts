// application_usage_descriptor.h: interface for the ApplicationUsageDescriptor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __APPLICATION_USAGE_DESCRIPTOR_H__
#define __APPLICATION_USAGE_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include "descriptor.h"

class BitReadWriter;

class ApplicationUsageDescriptor : public Descriptor
{
public:
	ApplicationUsageDescriptor();
	ApplicationUsageDescriptor(BitReadWriter *rw);
	virtual ~ApplicationUsageDescriptor();

	virtual void WriteDescriptor(BitReadWriter* rw);
	virtual void PrintDescriptor();

	void SetUsageType(int value) { usage_type = value;}
	unsigned char GetUsageType() { return usage_type;}
	
protected:
	virtual void calcLength();

	unsigned char usage_type;
};

#endif