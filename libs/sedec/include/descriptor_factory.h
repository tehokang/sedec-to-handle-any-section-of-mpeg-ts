// descriptor_factory.h: interface for the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __DESCRIPTOR_FACTORY_H__
#define __DESCRIPTOR_FACTORY_H__

class Descriptor;
class BitReadWriter;

class DescriptorFactory
{
public:
	static Descriptor* CreateDescriptor(BitReadWriter *rw);

private:	
	DescriptorFactory(){};
	virtual ~DescriptorFactory(){};
};

#endif 
