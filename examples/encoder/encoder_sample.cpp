#include <stdio.h>

#include "application_descriptor.h"
#include "application_name_descriptor.h"
#include "simple_application_location_descriptor.h"
#include "transport_protocol_descriptor.h"
#include "application.h"

#include "ait_section.h"
#include "ait_section_transcoder.h"

using namespace sedec;

int buffer_length(FILE *f)
{
	int pos;
	int end;
	pos = ftell (f);
	fseek (f, 0, SEEK_END);
	end = ftell (f);
	fseek (f, pos, SEEK_SET);
			return end;
}

int main(int argc, char *argv[]){

	printf("***************************\n");
	printf("* Section Transcoding Sample *\n");
	printf("***************************\n\n");

	FILE *fp_ait = NULL;
	if(argc == 2) fp_ait = fopen(argv[1], "rb");
	else 
	{
		printf("Usage : ait_encoder [ait raw filepath] \n");
		return -1;
	}

	if(fp_ait)
	{
		unsigned char raw_buffer[4096] = {0,};
		unsigned int raw_buffer_length = buffer_length(fp_ait);
		fread(raw_buffer, 1, raw_buffer_length, fp_ait);

		/**
		*	Ready for AITSection to be completed
		**/
		printf("Original Section is followings... \n");
		AITSection *ait_section = new AITSection(raw_buffer);
		ait_section->PrintSection();

		/**
		*	Do transcode
		**/
		printf("Transcoded Section is followings... \n");
		AITSectionTranscoder *ait_transcoder = 
					new AITSectionTranscoder(ait_section->GetSection());

		{
			list<Application*> apps = ait_transcoder->GetApplications();
			int app_index = 0;
			for (std::list<Application*>::iterator it=apps.begin();
					it != apps.end(); ++it)
			{
				Application *app = (Application*)*it;
				printf("[%d] before app id : %d \n", app_index, app->GetOrganizationId());
				printf("[%d] before org id : %d \n", app_index, app->GetApplicationId());

				app->SetOrganizationId(11);
				app->SetApplicationId(11);
				printf("[%d] after app id : %d \n", app_index, app->GetOrganizationId());
				printf("[%d] after org id : %d \n", app_index, app->GetApplicationId());
			}
		}

		{
			int major, minor, micro;
			ait_transcoder->GetApplicationVersion(major, minor, micro);
			printf("major.minor.micro = %d.%d.%d\n", major, minor, micro);
			ait_transcoder->SetApplicationVersion(1,1,1);
		}

		{
			const char *base_url, *init_path;
			ait_transcoder->GetApplicationUrl(&base_url, &init_path);
			printf("base : %s \ninit_path : %s \n", base_url, init_path);
			ait_transcoder->SetApplicationUrl("aaa", "bbb");
		}
		ait_transcoder->EncodeSection();
		ait_transcoder->SaveSection("test.ait.section");
		ait_transcoder->PrintSection();

		delete ait_section;
		delete ait_transcoder;
		fclose(fp_ait);
	}



	return 0;
}
