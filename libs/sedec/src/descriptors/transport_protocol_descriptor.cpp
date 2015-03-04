// transport_protocol_descriptor.cpp: implementation of the TransportProtocolDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "transport_protocol_descriptor.h"
#include "bit_readwriter.h"

#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TransportProtocolDescriptor::TransportProtocolDescriptor()
{
	descriptor_tag = TRANSPORT_PROTOCOL_DESCRIPTOR;
	descriptor_length = 0;
	
	protocol_id = 0;
	transport_protocol_label = 0;
	memset(&oc_transport, 0x00, sizeof(OCtransport));
	memset(&channel_transport, 0x00, sizeof(Channeltransport));
}

TransportProtocolDescriptor::TransportProtocolDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
	protocol_id = rw->Read_On_Buffer(16);
	transport_protocol_label = rw->Read_On_Buffer(8);

	if( 0 < descriptor_length-3 )
	{
		switch(protocol_id)
		{
			case PROTOCOL_CAROUSEL:
				{
					memset(&oc_transport, 0x00, sizeof(OCtransport));
					oc_transport.remote_connection = rw->Read_On_Buffer(1);
					rw->Skip_On_Buffer(7);
					if(0x01 == oc_transport.remote_connection)
					{
						oc_transport.original_network_id = rw->Read_On_Buffer(16);
						oc_transport.transport_stream_id = rw->Read_On_Buffer(16);
						oc_transport.service_id = rw->Read_On_Buffer(16);
					}
					oc_transport.component_tag = rw->Read_On_Buffer(8);
				}
				break;
			case PROTOCOL_HTTP:
				{
					memset(&channel_transport, 0x00, sizeof(Channeltransport));
					channel_transport.URL_base_length = rw->Read_On_Buffer(8);
					for(int i=0;i<channel_transport.URL_base_length;i++)
						channel_transport.URL_base_byte[i] = rw->Read_On_Buffer(8);
					channel_transport.URL_extension_count = rw->Read_On_Buffer(8);
					for(int i=0;i<channel_transport.URL_extension_count;i++)
					{
						channel_transport.URL_extension_length = rw->Read_On_Buffer(8);
						for(int j=0;j<channel_transport.URL_extension_length;j++)
							channel_transport.URL_extension_byte[j] = rw->Read_On_Buffer(8);
					}

				}
				break;
			default:
				break;
		}
	}
}

TransportProtocolDescriptor::~TransportProtocolDescriptor()
{

}

void TransportProtocolDescriptor::PrintDescriptor()
{
	SECTION_DEBUG("\n");
	SECTION_DEBUG("\tdescriptor_tag : 0x%02x (transport_protocol_descriptor)\n", descriptor_tag);
	SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);	
	SECTION_DEBUG("\tprotocol_id : %x \n", protocol_id);
	SECTION_DEBUG("\ttransport_protocol_label : %x \n", transport_protocol_label);

	switch(protocol_id)
	{
		case 0x0001:
			{
				SECTION_DEBUG("\tremote_connection : %x \n", oc_transport.remote_connection);
				if(0x01 == oc_transport.remote_connection)
				{
					SECTION_DEBUG("\toriginal_network_id : %x \n", oc_transport.original_network_id);
					SECTION_DEBUG("\ttransport_stream_id : %x \n", oc_transport.transport_stream_id);
					SECTION_DEBUG("\tservice_id : %x \n", oc_transport.service_id);
				}
				SECTION_DEBUG("\tcomponent_tag : %x \n", oc_transport.component_tag);
			}
			break;
		case 0x0003:
			{
				SECTION_DEBUG("\tURL_base_length : 0x%x (%d) \n", 
								channel_transport.URL_base_length, channel_transport.URL_base_length);
				SECTION_DEBUG("\tURL_base_byte : %s \n", channel_transport.URL_base_byte);
				SECTION_DEBUG("\tURL_extension_count : 0x%x \n", channel_transport.URL_extension_count);
				for(int i=0;i<channel_transport.URL_extension_count;i++)
				{
					SECTION_DEBUG("\tURL_extension_length : %d \n", channel_transport.URL_extension_length);
					SECTION_DEBUG("\tURL_extension_byte : %s \n", channel_transport.URL_extension_byte);
				}
			}
			break;
		default:
			break;
	}
	SECTION_DEBUG("\n");
}

void TransportProtocolDescriptor::calcLength()
{
	int selector_byte_length = 0;
	switch(protocol_id)
	{
		case 0x0001:
			if(0x01 == oc_transport.remote_connection) 
				selector_byte_length = 8; 
			else 
				selector_byte_length = 2;
			break;
		case 0x0003:
			{
				selector_byte_length = 1 + channel_transport.URL_base_length +
										1 + channel_transport.URL_extension_count;
				for(int i=0;i<channel_transport.URL_extension_count;i++)
				{
					selector_byte_length += 1 + channel_transport.URL_extension_length;
				}
			}
			break;
		default:
			break;
	}
	descriptor_length = 3 + selector_byte_length;
}

void TransportProtocolDescriptor::WriteDescriptor(BitReadWriter *rw)
{
	rw->Write_On_Buffer(descriptor_tag, 8);
	rw->Write_On_Buffer(descriptor_length, 8);
	rw->Write_On_Buffer(protocol_id, 16);
	rw->Write_On_Buffer(transport_protocol_label, 8);

	switch(protocol_id)
	{
		case 0x0001:
			rw->Write_On_Buffer(oc_transport.remote_connection, 1);
			rw->Write_On_Buffer(0x7f, 7);
			if(0x01 == oc_transport.remote_connection)
			{
				rw->Write_On_Buffer(oc_transport.original_network_id, 16);
				rw->Write_On_Buffer(oc_transport.transport_stream_id, 16);
				rw->Write_On_Buffer(oc_transport.service_id, 16);
			}
			rw->Write_On_Buffer(oc_transport.component_tag, 8);
			break;
		case 0x0003:
			rw->Write_On_Buffer(channel_transport.URL_base_length, 8);
			for(int i=0;i<channel_transport.URL_base_length;i++) 
				rw->Write_On_Buffer(channel_transport.URL_base_byte[i], 8);
			
			rw->Write_On_Buffer(channel_transport.URL_extension_count, 8);
			for(int i=0;i<channel_transport.URL_extension_count;i++)
			{
				rw->Write_On_Buffer(channel_transport.URL_extension_length, 8);
				for(int j=0;j<channel_transport.URL_extension_length;j++)
					rw->Write_On_Buffer(channel_transport.URL_extension_byte[j], 8);
			}	
			break;
		default:
		 	break;
	}

}

