#ifndef __CERTIFICATE__
#define __CERTIFICATE__

#define MIN_CERTIFICATE_ID 1000
#define MAX_CERTIFICATE_ID 9999

typedef struct
{
	int animalCertificateId;
	char* countryOfOrigin;
	char* animalDescription;
}Certificate;

int initCertificate(Certificate* pCer, int certificateAnimalId);
void printCertificate(const Certificate* pCer);
void freeCertificate(Certificate* pCer);

#endif // !__CERTIFICATE__