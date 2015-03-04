// simple_application_boundary_descriptor.h: interface for the SimpleApplicationBoundaryDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __SIMPLE_APP_BOUNDARY_DESCRIPTOR_H__
#define __SIMPLE_APP_BOUNDARY_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include "descriptor.h"

class BitReadWriter;

class SimpleApplicationBoundaryDescriptor : public Descriptor
{
public:
	SimpleApplicationBoundaryDescriptor();
	SimpleApplicationBoundaryDescriptor(BitReadWriter *rw);
	virtual ~SimpleApplicationBoundaryDescriptor();

	virtual void WriteDescriptor(BitReadWriter* rw);
	virtual void PrintDescriptor();

	/* Interface to encode (setter) */
	void SetBoundaryExtension(unsigned char ext_count, 
								unsigned char* ext_length,
								unsigned char** ext_byte)
	{
		boundary_extension_count = ext_count;
		memset(boundary_extension_length, 0x00, sizeof(boundary_extension_length));
		memcpy((unsigned char*)boundary_extension_length, 
				(unsigned char*)ext_length, sizeof(boundary_extension_length));
		memcpy((unsigned char**)boundary_extension_byte, 
				(unsigned char**)ext_byte, sizeof(boundary_extension_byte));

	}

	/* Interface to decode (getter) */


protected:
	virtual void calcLength();

	unsigned char boundary_extension_count;
	unsigned char boundary_extension_length[256];
	unsigned char boundary_extension_byte[256][256];

};

#endif 
