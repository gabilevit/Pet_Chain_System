#ifndef __CERTIFICATE__
#define __CERTIFICATE__

#include "General.h"
#include "FileHelper.h"

#define MIN_CERTIFICATE_ID 1000
#define MAX_CERTIFICATE_ID 9999

typedef struct
{
	int animalCertificateId;
	char* countryOfOrigin;
	char* animalDescription;
}Certificate;

int initCertificate(Certificate* pCer, int certificateAnimalId);

// FILE FUNCTIONS
int	saveCertificateToTextFile(const Certificate* pCer, FILE* fp);
int	loadCertificateFromTextFile(Certificate* pCer, FILE* fp);
int	saveCertificateToBinaryFile(const Certificate* pCer, FILE* fp);
int	loadCertificateFromBinaryFile(Certificate* pCer, FILE* fp);

// PRINT FUNCTION
void printCertificate(const Certificate* pCer);

// FREE FUNCTION
void freeCertificate(Certificate* pCer);

#endif // !__CERTIFICATE__