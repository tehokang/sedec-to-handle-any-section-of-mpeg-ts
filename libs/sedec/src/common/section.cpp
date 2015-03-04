// Section.cpp: implementation of the Section class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "section.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Section::Section()
{
	m_buffer = NULL;
	m_buffer_length = 0;
}

Section::Section(unsigned char* raw_buffer, unsigned int raw_length)
{
	m_buffer_length = raw_length;
	m_buffer = new unsigned char[m_buffer_length];

	memcpy(m_buffer, raw_buffer, m_buffer_length);
	SetBuffer(m_buffer);

	table_id = Read_On_Buffer(8);
	section_syntax_indicator = Read_On_Buffer(1);
	Skip_On_Buffer(3);
	section_length = Read_On_Buffer(12);
}

Section::~Section()
{	
	if(m_buffer != NULL)
	{
		delete []m_buffer;
	}		
}

void Section::ReadyBuffer()
{
	if(m_buffer != NULL)
	{
		delete m_buffer;
	}
	m_buffer_length = section_length + 3;
	m_buffer = new unsigned char[m_buffer_length];		

	memset(m_buffer, 0xFF, m_buffer_length);	
	SetBuffer(m_buffer);
}

void Section::WriteSectionHeader()
{
	Write_On_Buffer( table_id, 8 );
	Write_On_Buffer( section_syntax_indicator, 1);
	Write_On_Buffer( 1, 1);
	Write_On_Buffer( 3, 2);
	Write_On_Buffer( section_length, 12);
	
}

void Section::EncodeSection()
{
	CalcSectionLength();
	SetSection();
	ReadyBuffer();
	WriteSectionHeader();
	WriteSection();
}

void Section::MakeCRC()
{
	m_crc = new unsigned char[section_length-1];
	memcpy( m_crc, m_buffer, section_length-1 );
	checksum_CRC32 = calculate_crc32( m_crc, section_length-1 );
	delete m_crc;

	Write_On_Buffer(checksum_CRC32, 32);
}


void Section::SaveSection()
{
	FILE *fp = NULL;
	fp = fopen(m_section_name, "wb");
	if(fp) 
	{
		fwrite(m_buffer, 1, m_buffer_length, fp);
		fclose(fp);
	}
}

void Section::SaveSection(char *filename)
{
	FILE *fp = NULL;
	fp = fopen(filename, "wb");
	if(fp) 
	{
		fwrite(m_buffer, 1, m_buffer_length, fp);
		fclose(fp);
	}
}

void Section::PrintRawSection()
{
	int j=1;
	printf("#### %12s's Byte Align #### \n", m_section_name);
	printf("%03d : ", j);
	for(int i=0; i<m_buffer_length; i++)
	{
		printf("%02X ", m_buffer[i]);
		if(i%10 == 9) printf("\n%03d : ", ++j);
	}
	printf("\n################################### \n\n");
}

unsigned char* Section::GetSection()
{
	return m_buffer;
}

int Section::GetSectionLen()
{
	return m_buffer_length;
}
