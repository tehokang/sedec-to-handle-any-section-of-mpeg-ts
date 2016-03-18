// descriptor_factory.h: interface for the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __DESCRIPTOR_FACTORY_H__
#define __DESCRIPTOR_FACTORY_H__

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

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

/** @} */

} // end of sedec namespace
#endif 
