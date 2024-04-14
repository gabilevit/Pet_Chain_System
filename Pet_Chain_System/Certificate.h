#ifndef __CERTIFICATE__
#define __CERTIFICATE__

typedef struct
{
	int animalId;
	char* AnimalDescription;
	char* countryOfOrigin;
}Certificate;

void initCertificate(Certificate* pCer, Certificate* cerArr, int cerCount);
int getCertificateAnimalId(Certificate* cerArr, int cerCount);
Certificate* findCertificateByAnimalId(Certificate* cerArr, int count, int sn);
int isSerialNumberUnique(Certificate* cerArr, int cerCount, int num);
void printCertificate(const Certificate* pCer);
void freeCertificate(Certificate* pCer);

#endif // !__CERTIFICATE__