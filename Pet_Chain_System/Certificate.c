#include "Certificate.h"
#include "General.h"

#include <stdio.h>
#include <stdlib.h>

int initCertificate(Certificate* pCer, int certificateId)
{
	pCer->animalCertificateId = certificateId;
	pCer->countryOfOrigin = getStrExactName("Enter country of origin");
	if (!pCer->countryOfOrigin)
		return 0;
	pCer->animalDescription = getStrExactName("Enter a short description of the animal breed (255 max string lenght)");
	if (!pCer->animalDescription)
		return 0;
	return 1;
}

void printCertificate(const Certificate* pCer)
{
	printf("Certificate ID of the animal: %d\n", pCer->animalCertificateId);
	printf("Country of origin: %s\n", pCer->countryOfOrigin);
	printf("A short description: %s\n", pCer->animalDescription);
}

void freeCertificate(Certificate* pCer)
{
	free(pCer->countryOfOrigin);
	free(pCer->animalDescription);
}